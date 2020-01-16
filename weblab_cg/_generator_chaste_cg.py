import logging
import time
import sympy as sp
import weblab_cg as cg
from copy import deepcopy
from cellmlmanip.model import NumberDummy, DataDirectionFlow
from pint import DimensionalityError


class ChasteModel(object):
    """ Holds information about a cellml model for which chaste code is to be generated.

    It also holds relevant formatted equations and derivatives.
    Please Note: this calass cannot generate chaste code directly, instead use a subclass fo the model type
    """
    # TODO: implement modifiable-parameter bit of expose-annotated-variables (similar to derived quantities)
    # TODO: implement and check options see https://chaste.cs.ox.ac.uk/trac/wiki/ChasteGuides/CodeGenerationFromCellML
    # TODO: variable conversion via cellmlmanip
    # TODO: script to call generator from command line
    # TODO: Model types Opt, Analytic_j, Numerical_j, BE

    _MEMBRANE_VOLTAGE_INDEX = 0
    _CYTOSOLIC_CALCIUM_CONCENTRATION_INDEX = 1
    _OXMETA = 'https://chaste.comlab.ox.ac.uk/cellml/ns/oxford-metadata#'
    _PYCMLMETA = 'https://chaste.comlab.ox.ac.uk/cellml/ns/pycml#'

    _HEARTCONFIG_GETCAPACITANCE = 'HeartConfig::Instance()->GetCapacitance'
    _UNIT_DEFINITIONS = {'uA_per_cm2': [{'prefix': 'micro', 'units': 'ampere'},
                                        {'exponent': '-2', 'prefix': 'centi', 'units': 'metre'}],
                         'uA_per_uF': [{'prefix': 'micro', 'units': 'ampere'},
                                       {'exponent': '-1', 'prefix': 'micro', 'units': 'farad'}],
                         'uA': [{'prefix': 'micro', 'units': 'ampere'}],
                         'uF': [{'prefix': 'micro', 'units': 'farad'}],
                         'uF_per_mm2': [{'prefix': 'micro', 'units': 'farad'}, {
                             'units': 'metre', 'prefix': 'milli', 'exponent': '-2'}],
                         'millisecond': [{'prefix': 'milli', 'units': 'second'}],
                         'millimolar': [{'units': 'mole', 'prefix': 'milli'}, {'units': 'litre', 'exponent': '-1'}],
                         'millivolt': [{'prefix': 'milli', 'units': 'volt'}]}

    _STIM_UNITS = {'membrane_stimulus_current':
                   [{'units': 'uA_per_cm2', 'use_capacitance': False, 'use_heartconfig_capacitance': False},
                    {'units': 'uA', 'use_capacitance': True, 'use_heartconfig_capacitance': True},
                    {'units': 'uA_per_uF', 'use_capacitance': False, 'use_heartconfig_capacitance': True}],
                   'membrane_stimulus_current_period': [{'units': 'millisecond'}],
                   'membrane_stimulus_current_duration': [{'units': 'millisecond'}],
                   'membrane_stimulus_current_amplitude': [{'units': 'uA_per_cm2'},
                                                           {'units': 'uA_per_uF'},
                                                           {'units': 'uA'}],
                   'membrane_stimulus_current_offset': [{'units': 'millisecond'}],
                   'membrane_stimulus_current_end': [{'units': 'millisecond'}],
                   'membrane_capacitance': [{'units': 'uF'}, {'units': 'uF_per_mm2'}]}

    _STIM_RHS_MULTIPLIER = {'membrane_stimulus_current_amplitude':
                            {'uA_per_uF': sp.Function(_HEARTCONFIG_GETCAPACITANCE)(),
                             'uA': sp.Function(_HEARTCONFIG_GETCAPACITANCE)()}}

    _STIM_CONVERSION_RULES_ERR_CHECK = \
        {'membrane_stimulus_current_amplitude':
            {'uA':
                {'condition': lambda self: self._membrane_capacitance is not None,
                 'message': 'Membrane capacitance is required to be able to apply conversion to stimulus current!'}}
         }
    _STIM_CONVERSION_RULES = \
        {'membrane_stimulus_current_amplitude':
            {'uA':
                lambda self,
                current_units,
                factor, eq:
                (self._stim_units['membrane_stimulus_current_amplitude'][0]['units'],
                 factor / self._membrane_capacitance_factor,
                 sp.Eq(eq.lhs, eq.rhs / self._membrane_capacitance.lhs),
                 [{'lhs': self._printer.doprint(self._membrane_capacitance.lhs),
                   'rhs': self._printer.doprint(self._membrane_capacitance.rhs),
                   'units': str(self._model.units.summarise_units(self._membrane_capacitance.lhs))}]
                 )}}

    def __init__(self, model, class_name, file_name, **kwargs):
        """ Initialise a ChasteModel instance
        Arguments

        ``model``
            A :class:`cellmlmanip.Model` object.
        ``output_path``
            The path to store the generated model code at.
            (Just the path, excluding the file name as file name will be determined by the model_name)
        ``class_name``
            The name of the class to be generated.
        ``file_name``
            The name you want to give your generated files WITHOUT the .hpp and .cpp extension
            (e.g. aslanidi_model_2009 leads to aslanidi_model_2009.cpp and aslanidi_model_2009.hpp)
        """
        # Store default options
        self.class_name = class_name
        self.file_name = file_name
        self.generated_hpp = ''
        self.generated_cpp = ''

        self._is_self_excitatory = False
        self._dynamically_loadable = kwargs.get('dynamically_loadable', False)
        self._expose_annotated_variables = kwargs.get('expose_annotated_variables', False)

        self._logger = logging.getLogger(__name__)
        self._logger.setLevel(logging.INFO)

        # Store parameters for future reference
        self._model = model

        self._stim_units = self._add_units()

        self._in_interface = []

        self._time_variable = self._get_time_variable()
        self._membrane_voltage_var = self._get_membrane_voltage_var()
        self._cytosolic_calcium_concentration_var = self._get_cytosolic_calcium_concentration_var()

        self._state_vars = self._get_state_variables()
        self._in_interface.extend(self._state_vars)

        self._modifiable_parameters = self._get_modifiable_parameters()
        self._in_interface.append(self._time_variable)

        self._membrane_stimulus_current = self._get_membrane_stimulus_current()
        self._original_membrane_stimulus_current = self._membrane_stimulus_current
        self._membrane_capacitance, self._membrane_capacitance_factor = self._get_membrane_capacitance()
        self._default_stimulus = self._get_stimulus()

        self._ionic_derivs = self._get_ionic_derivs()
        self._equations_for_ionic_vars, self._current_unit_and_capacitance, self._membrane_stimulus_current_factor = \
            self._get_equations_for_ionic_vars()
        self._extended_equations_for_ionic_vars = self._get_extended_equations_for_ionic_vars()

        self._y_derivatives = self._get_y_derivatives()
        self._y_derivatives_voltage = self._get_y_derivatives_voltage()
        self._y_derivatives_excl_voltage = self._get_y_derivatives_excl_voltage()
        self._derivative_equations = self._get_derivative_equations()
        self._derivative_eqs_voltage = self._get_derivative_eqs_voltage()
        self._derivative_eqs_exlc_voltage = self._get_derivative_eqs_exlc_voltage()
        self._derived_quant = self._get_derived_quant()
        self._derived_quant_eqs = self._get_derived_quant_eqs()

        self._add_printers()
        self._formatted_modifiable_parameters = self._format_modifiable_parameters()
        self._formatted_state_vars, self._use_verify_state_variables = self._format_state_variables()
        self._formatted_default_stimulus = self._format_default_stimulus()
        self._formatted_extended_equations_for_ionic_vars = self._format_extended_equations_for_ionic_vars()
        self._formatted_y_derivatives = self._format_y_derivatives()
        self._formatted_derivative_eqs = self._format_derivative_equations()
        self._free_variable = self._format_free_variable()
        self._ode_system_information = self._format_system_info()
        self._named_attributes = self._format_named_attributes()

        self._formatted_derived_quant = self._format_derived_quant()
        self._formatted_quant_eqs = self._format_derived_quant_eqs()

    def _state_var_key_order(self, var):
        """Returns a key to order state variables in the same way as pycml does"""
        if isinstance(var, sp.Derivative):
            var = var.args[0]
        if var == self._membrane_voltage_var:
            return self._MEMBRANE_VOLTAGE_INDEX
        elif var == self._cytosolic_calcium_concentration_var and \
                self._model.units.summarise_units(self._cytosolic_calcium_concentration_var).dimensionality == \
                self._model.units.ureg.millimolar.dimensionality:
            return self._CYTOSOLIC_CALCIUM_CONCENTRATION_INDEX
        else:
            return self._MEMBRANE_VOLTAGE_INDEX + self._CYTOSOLIC_CALCIUM_CONCENTRATION_INDEX + 1

    def _get_var_display_name(self, var):
        """Return a display name for the given variable.

        Looks for OXMETA ontology annotation tage first, then cmeta:id if present, or the name attribute if not.
        If there is an interface component, strip the name of it out of the display name.
        """
        display_name = var.name
        if self._model.has_ontology_annotation(var, self._OXMETA):
            display_name = self._model.get_ontology_terms_by_symbol(var, self._OXMETA)[-1]
        elif var.cmeta_id:
            display_name = var.cmeta_id
#        else:
#            if var in self._in_interface:
#                display_name = var.name.split('$')[-1]
#        return display_name.replace('$', '__').replace('var_', '', 1)
        return display_name.replace('$', '__').replace('var_chaste_interface_', '', 1).replace('var_', '', 1)

    def _add_units(self):
        """ Add needed units to the model to allow converting time, voltage and calcium in specific units
            as well as units for converting membrane_stimulus_current."""
        for unit_name in self._UNIT_DEFINITIONS:
            try:
                self._model.units.add_custom_unit(unit_name, self._UNIT_DEFINITIONS[unit_name])
            except AssertionError:
                pass  # Unit already exists, but that is not a problem
        # Now that we have the units in the model, we can populate the stim_units dictionary with units from this model
        # make sure we do not store units of the model statically as it would interfere with generating the next model
        stim_units = deepcopy(self._STIM_UNITS)
        for key in stim_units:
            for i in range(len(stim_units[key])):
                stim_units[key][i]['units'] = getattr(self._model.units.ureg, stim_units[key][i]['units'])
        return stim_units

    def _get_time_variable(self):
        time_variable = self._model.get_free_variable_symbol()
        desired_units = self._model.units.ureg.millisecond
        assert self._model.units.summarise_units(time_variable).dimensionality == desired_units.dimensionality, \
            'Incorrect definition of time variable (units of time needs to be demensionally equivalent to second)'
        # If the variable is in units that can be converted to millimolar, perform conversion
        return self._model.convert_variable(time_variable, desired_units, DataDirectionFlow.INPUT)

    def _get_membrane_voltage_var(self):
        """ Find the membrane_voltage variable"""
        voltage = self._model.get_symbol_by_ontology_term(self._OXMETA, "membrane_voltage")
        desired_units = self._model.units.ureg.millivolt
        assert self._model.units.summarise_units(voltage).dimensionality == desired_units.dimensionality, \
            'Incorrect definition of membrane_voltage variable '\
            '(units of membrane_voltage needs to be demensionally equivalent to Volt)'
        # Convert if necessary
        return self._model.convert_variable(voltage, desired_units, DataDirectionFlow.INPUT)

    def _get_cytosolic_calcium_concentration_var(self):
        """ Find the cytosolic_calcium_concentration variable if it exists"""
        try:
            cytosolic_calcium_concentration = \
                self._model.get_symbol_by_ontology_term(self._OXMETA, "cytosolic_calcium_concentration")
        except KeyError:
            self._logger.info(self._model.name + ' has no cytosolic_calcium_concentration')
            return None

        # Convert if necessary
        desired_units = self._model.units.ureg.millimolar
        try:
            return self._model.convert_variable(cytosolic_calcium_concentration,
                                                desired_units, DataDirectionFlow.INPUT)
        except DimensionalityError:
            # units can't be converted to millimolar (e.g. could be dimensionless)
            return cytosolic_calcium_concentration

    def _get_modifiable_parameters_annotated(self):
        """ Get the variables annotated in the model as modifiable parametery"""
        return self._model.get_symbols_by_rdf((self._PYCMLMETA, 'modifiable-parameter'), 'yes')

    def _get_modifiable_parameters_exposed(self):
        """ Get the variables in the model that have exposed annotation and are modifiable parameters
            (irrespective of any modifiable_parameters tags)"""
        return [q for q in self._model.variables()
                if self._model.has_ontology_annotation(q, self._OXMETA)
                and not self._model.get_ontology_terms_by_symbol(q, self._OXMETA)[-1]
                .startswith('membrane_stimulus_current')
                and q not in self._model.get_derived_quantities()
                and q not in self._model.get_state_symbols()
                and not q == self._time_variable]

    def _get_modifiable_parameters(self):
        """ Get all modifiable parameters

            Note: the result depends on self._expose_annotated_variables to determine whether or not to include
            variables exposed with oxford metadata that are a modifiable parameter but are not annotated as such"""
        if self._expose_annotated_variables:
            # Combined and sorted in display name order
            return \
                sorted(self._get_modifiable_parameters_annotated() + self._get_modifiable_parameters_exposed(),
                       key=lambda v: self._get_var_display_name(v))
        else:
            return sorted(self._get_modifiable_parameters_annotated(), key=lambda v: self._get_var_display_name(v))

    def _get_state_variables(self):
        """ Sort the state variables, in similar order to pycml to prevent breaking existing code"""
        return sorted(self._model.get_state_symbols(),
                      key=lambda state_var: self._state_var_key_order(state_var))

    def _get_membrane_stimulus_current(self):
        """ Find the membrane_stimulus_current variable if it exists"""
        try:
            return self._model.get_symbol_by_ontology_term(self._OXMETA, 'membrane_stimulus_current')
        except KeyError:
            self._logger.info(self._model.name + ' has no membrane_stimulus_current')
            self._is_self_excitatory = len(list(self._model.get_rdf_annotations(subject=self._model.rdf_identity,
                                                predicate=(self._PYCMLMETA, 'is-self-excitatory'), object_='yes'))) > 0
            return None

    def _get_membrane_capacitance(self):
        """ Find membrane_capacitance if the model has it"""
        equation, capacitance_factor = None, 1.0
        # add membrane_capacitance if the model has it
        try:
            # add membrane_capacitance factor
            membrane_capacitance = self._model.get_symbol_by_ontology_term(self._OXMETA, "membrane_capacitance")
            if membrane_capacitance is not None:
                current_units = self._model.units.summarise_units(membrane_capacitance)
                for desired_units in [unit_dict['units'] for unit_dict in self._stim_units['membrane_capacitance']]:
                    if current_units.dimensionality == desired_units.dimensionality:
                        capacitance_factor = \
                            self._model.units.get_conversion_factor(desired_units, from_unit=current_units)
                        initial_value = self._model.get_initial_value(membrane_capacitance)
                        if initial_value is not None:
                            membrane_capacitance.initial_value = None
                            equation = sp.Eq(membrane_capacitance, initial_value)
                            # Add to the model
                            self._model.add_equation(equation)
                            assert len([eq for eq in self._model.equations if eq.lhs == membrane_capacitance]) == 1, \
                                'Expecting 1 definition equation for membrane_capacitance'
                        break
        except KeyError:
            # no membrane_capacitance
            pass
        return equation, capacitance_factor

    def _get_stimulus(self):
        """ Store the stimulus currents in the model"""
        default_stimulus = dict()
        if self._membrane_stimulus_current is not None:
            # Get remaining stimulus current variables If they have metadata use that as key, ortherwise use the name
            # Exclude _membrane_stimulus_current itself so we can treat it seperately
            for eq in self._model.get_equations_for([self._membrane_stimulus_current], strip_units=False):
                if eq.lhs != self._membrane_stimulus_current:
                    ontology_terms = self._model.get_ontology_terms_by_symbol(eq.lhs, self._OXMETA)
                    key = ontology_terms[0] if len(ontology_terms) > 0 else eq.lhs
                    default_stimulus[key] = eq
        return default_stimulus

    def _get_ionic_derivs(self):
        """ Getting the derivative symbols that define V (self._membrane_voltage_var)"""
        # use the RHS of the ODE defining V
        return [x for x in self._model.get_derivative_symbols() if x.args[0] == self._membrane_voltage_var]

    def _get_equations_for_ionic_vars(self):
        """ Get the equations defining the ionic derivatives"""
        # figure out the currents (by finding variables with the same units as the stimulus)
        # Only equations with the same (lhs) units as the STIMULUS_CURRENT are kept.
        # Also exclude membrane_stimulus_current variable itself, and default_stimulus equations (if model has those)
        # Manually recurse down the equation graph (bfs style) if no currents are found
        equations_for_ionic_vars, desired_units_and_capacitance, stimulus_current_factor = [], None, 1.0
        units_to_try = self._stim_units['membrane_stimulus_current']
        if self._membrane_stimulus_current is not None:
            membrane_stimulus_units = self._model.units.summarise_units(self._membrane_stimulus_current)
            units_to_try = \
                [u for u in units_to_try if u['units'].dimensionality == membrane_stimulus_units.dimensionality]

        for unit_cap in units_to_try:
            if len(equations_for_ionic_vars) > 0:
                break
            equations, old_equations = self._ionic_derivs, None
            while len(equations_for_ionic_vars) == 0 and old_equations != equations:
                old_equations = equations
                equations = self._model.get_equations_for(equations, recurse=False, strip_units=False)
                equations_for_ionic_vars = [eq for eq in equations
                                            if ((self._membrane_stimulus_current is None)
                                                or (eq.lhs != self._membrane_stimulus_current
                                                and eq not in self._default_stimulus.values()))
                                            and self._model.units.summarise_units(eq.lhs).dimensionality
                                            == unit_cap['units'].dimensionality
                                            and eq.lhs not in self._modifiable_parameters
                                            and eq.lhs not in self._ionic_derivs]
                equations = [eq.lhs for eq in equations]
            desired_units_and_capacitance = unit_cap
        if self._membrane_stimulus_current is not None:
            stimulus_current_factor = \
                self._model.units.get_conversion_factor(desired_units_and_capacitance['units'],
                                                        from_unit=membrane_stimulus_units)
        desired_units_and_capacitance['use_capacitance'] = desired_units_and_capacitance['use_capacitance'] \
            and self._membrane_capacitance is not None
        # Reverse topological order is more similar (though not necessarily identical) to pycml
        return equations_for_ionic_vars, desired_units_and_capacitance, stimulus_current_factor

    def _get_extended_equations_for_ionic_vars(self):
        """ Get the equations defining the ionic derivatives and all dependant equations"""

        # create the const double var_chaste_interface__i_ionic = .. equation
        i_ionic_lhs = self._model.add_variable(name='_i_ionic', units=self._model.units.ureg.uA_per_cm2)
        i_ionic_rhs = sp.sympify(0.0, evaluate=False)

        # add i_ionic to interface for printing
        self._in_interface.append(i_ionic_lhs)
        # sum up all lhs * conversion_factor for all ionic equations
        for var in self._equations_for_ionic_vars:
            factor = self._model.units.get_conversion_factor(self._current_unit_and_capacitance['units'],
                                                             from_unit=self._model.units.summarise_units(var.lhs))
            i_ionic_rhs = (factor * var.lhs if factor != 1.0 else var.lhs) + i_ionic_rhs

        # check if we need to convert using capacitance
        if self._current_unit_and_capacitance['use_capacitance']:
            div = self._membrane_capacitance_factor * self._membrane_capacitance.lhs \
                if self._membrane_capacitance_factor != 1.0 else self._membrane_capacitance.lhs
            i_ionic_rhs /= div

        # check if we need to convert using _HEARTCONFIG_GETCAPACITANCE
        if self._current_unit_and_capacitance['use_heartconfig_capacitance']:
            i_ionic_rhs *= sp.Function(self._HEARTCONFIG_GETCAPACITANCE)()

        i_ionic_eq = sp.Eq(i_ionic_lhs, i_ionic_rhs)
        self._model.add_equation(i_ionic_eq)
        self._equations_for_ionic_vars.append(i_ionic_eq)

        # Remove equations where lhs is a modifiable parameter or stimulus vars
        return \
            [eq for eq in
                self._model.get_equations_for([ionic_var_eq.lhs for ionic_var_eq in self._equations_for_ionic_vars],
                                              strip_units=False)
                if eq.lhs not in self._modifiable_parameters
                and eq.lhs not in [st.lhs for st in self._default_stimulus.values()]]

    def _get_y_derivatives(self):
        """ Get derivatives for state variables"""
        return sorted(self._model.get_derivative_symbols(),
                      key=lambda state_var: self._state_var_key_order(state_var))

    def _get_y_derivatives_voltage(self):
        """ Get derivatives for V (self._membrane_voltage_var)"""
        return [deriv for deriv in self._y_derivatives if deriv.args[0] == self._membrane_voltage_var]

    def _get_y_derivatives_excl_voltage(self):
        """ Get derivatives for state variables, excluding V (self._membrane_voltage_var)"""
        return [deriv for state_var in self._state_vars for deriv in self._y_derivatives
                if deriv.args[0] == state_var and deriv.args[0] != self._membrane_voltage_var]

    def _get_derivative_eqs_voltage(self):
        """ Get equations defining the derivatives for V (self._membrane_voltage_var)"""
        # Remove equations where lhs is a modifiable parameter or default stimulus
        return [eq for eq in self._model.get_equations_for(self._y_derivatives_voltage, strip_units=False)
                if eq.lhs not in self._modifiable_parameters
                and eq not in self._default_stimulus.values()]

    def _get_derivative_eqs_exlc_voltage(self):
        """ Get equations defining the derivatives excluding V (self._membrane_voltage_var)"""
        # Remove equations where lhs is a modifiable parameter or default stimulus
        return [eq for eq in self._model.get_equations_for(self._y_derivatives_excl_voltage, strip_units=False)
                if eq.lhs not in self._modifiable_parameters
                and eq not in self._default_stimulus.values()]

    def _get_derivative_equations(self):
        """ Get equations defining the derivatives including V (self._membrane_voltage_var)"""
        def get_deriv_eqs():
            """ Get equations defining the derivatives"""
            # Remove equations where lhs is a modifiable parameter or default stimulus
            return [eq for eq in self._model.get_equations_for(self._y_derivatives, strip_units=False)
                    if eq.lhs not in self._modifiable_parameters
                    and eq not in self._default_stimulus.values()]

        d_eqs = get_deriv_eqs()
        # If there is a _membrane_stimulus_current set, convert it.
        if self._membrane_stimulus_current is not None:
            negate_stimulus = False
            # loop through equations backwards as derivatives are last
            for i in range(len(d_eqs) - 1, - 1, - 1):
                if isinstance(d_eqs[i].lhs, sp.Derivative):
                    # This is dV/dt
                    # Assign temporary values to variables in order to check the stimulus sign.
                    # This will process defining expressions in a breadth first search until the stimulus
                    # current is found.  Each variable that doesn't have its definitions processed will
                    # be given a value as follows:
                    # - stimulus current = 1
                    # - other currents = 0
                    # - other variables = 1
                    # The stimulus current is then negated from the sign expected by Chaste if evaluating
                    # dV/dt gives a positive value.
                    if d_eqs[i].lhs.args[0] == self._membrane_voltage_var:
                        voltage_rhs = d_eqs[i].rhs
                        symbols = list(voltage_rhs.free_symbols)
                        for symbol in symbols:
                            if self._membrane_stimulus_current != symbol:
                                if self._current_unit_and_capacitance['units'].dimensionality == \
                                        self._model.units.summarise_units(symbol).dimensionality:
                                    voltage_rhs = voltage_rhs.subs({symbol: 0.0})  # other currents = 0
                                else:
                                    # For other variables see if we need to follow their definitions first
                                    rhs = None
                                    if symbol in [eq.lhs for eq in d_eqs]:
                                        rhs = [eq.rhs for eq in d_eqs if eq.lhs == symbol][-1]

                                    if rhs is not None and not isinstance(rhs, sp.numbers.Float):
                                        voltage_rhs = voltage_rhs.subs({symbol: rhs})  # Update definition
                                        symbols.extend(rhs.free_symbols)
                                    else:
                                        voltage_rhs = voltage_rhs.subs({symbol: 1.0})  # other variables = 1
                        voltage_rhs = voltage_rhs.subs({self._membrane_stimulus_current: 1.0})  # - stimulus current = 1
                        # Deal with NumberDummy variables (we haven't striped units, this may contain NumberDummys)
                        subs_dict = {s: float(s) for s in voltage_rhs.free_symbols if isinstance(s, NumberDummy)}
                        negate_stimulus = voltage_rhs.subs(subs_dict) > 0.0

            # Set GetIntracellularAreaStimulus calculaion
            GetIntracellularAreaStimulus = sp.Function('GetIntracellularAreaStimulus')
            area = GetIntracellularAreaStimulus(self._time_variable)
            if negate_stimulus:
                area = -area

            # remove metadata tag
            self._membrane_stimulus_current.cmeta_id = None
            # add converter equation
            converter_var = self._model.add_variable(name=self._membrane_stimulus_current.name + '_converter',
                                                     units=self._model.units.ureg.uA_per_cm2,
                                                     cmeta_id='membrane_stimulus_current')
            # add new equation for converter_var
            self._model.add_equation(sp.Eq(converter_var, area))

            # determine capacitance stuff
            stim_current_eq_rhs = converter_var
            if self._current_unit_and_capacitance['use_capacitance']:
                stim_current_eq_rhs *= self._membrane_capacitance.lhs
                fac = self._membrane_capacitance_factor / self._membrane_stimulus_current_factor
                if fac != 1.0:
                    stim_current_eq_rhs *= fac
            else:
                fac = 1 / self._membrane_stimulus_current_factor
                if fac != 1.0:
                    stim_current_eq_rhs *= fac

            # check if the results needs to be divided by heartconfig_capacitance and add if needed
            if self._current_unit_and_capacitance['use_heartconfig_capacitance']:
                stim_current_eq_rhs /= sp.Function(self._HEARTCONFIG_GETCAPACITANCE)()

            # Get stimulus defining equation
            eq = [e for e in self._model.equations if e.lhs == self._membrane_stimulus_current][-1]
            # remove old equation
            self._model.remove_equation(eq)
            # add eq self._membrane_stimulus_current = area to model
            self._model.add_equation(sp.Eq(self._membrane_stimulus_current, stim_current_eq_rhs))

            # update self._membrane_stimulus_current
            self._membrane_stimulus_current = self._get_membrane_stimulus_current()

        return get_deriv_eqs()

    def _get_derived_quant_annotated(self):
        """ Get the variables annotated in the model as derived derived-quantity"""
        return self._model.get_symbols_by_rdf((self._PYCMLMETA, 'derived-quantity'), 'yes')

    def _get_derived_quant_exposed(self):
        """ Get the variables in the model that have exposed annotation and are derived quantities
            (irrespective of any derived-quantity tags)"""
        return [q for q in self._model.get_derived_quantities()
                if self._model.has_ontology_annotation(q, self._OXMETA)
                and not self._model.get_ontology_terms_by_symbol(q, self._OXMETA)[-1]
                .startswith('membrane_stimulus_current')] + \
               [self._membrane_stimulus_current]

    def _get_derived_quant(self):
        """ Get all derived quantities

            Note: the result depends on self._expose_annotated_variables to determine whether or not to include
            variables exposed with oxford metadata that are derived quantities but are not annotated as such"""
        if self._expose_annotated_variables:
            # Combined and sorted in display name order
            return \
                sorted(self._get_derived_quant_annotated() + self._get_derived_quant_exposed(),
                       key=lambda v: self._get_var_display_name(v))
        else:
            return self._get_derived_quant_annotated()  # These are already sorted

    def _get_derived_quant_eqs(self):
        """ Get the defining equations for derived quantities"""
        return self._model.get_equations_for(self._derived_quant, strip_units=False)

    def _add_printers(self):
        """ Initialises Printers for outputting chaste code. """
        def get_symbol_name(s, interface=False):
            """Get the correct variable name based on the symbol and whether it should be in the chaste_interface."""
            s_name = str(s).replace('$', '__')

            # Deal with NumberDummy variables
            if isinstance(s, NumberDummy):
                return s_name

            prefix = 'var_chaste_interface_' if interface else 'var'
            if not s_name.startswith('_'):
                s_name = '_' + s_name
            return prefix + s_name
        # Printer for printing chaste regular variable assignments (var_ prefix)
        # Print variables in interface as var_chaste_interface
        # (state variables, time, lhs of default_stimulus eqs, i_ionic and lhs of y_derivatives)
        # Print modifiable parameters as mParameters[index]
        self._printer = \
            cg.ChastePrinter(lambda symbol:
                             get_symbol_name(symbol, symbol in self._in_interface)
                             if symbol not in self._modifiable_parameters
                             else 'mParameters[' + str(self._modifiable_parameters.index(symbol)) + ']',
                             lambda deriv: 'd_dt_chaste_interface_' +
                                           (get_symbol_name(deriv.expr)
                                            if isinstance(deriv, sp.Derivative) else get_symbol_name(deriv)))

        # Printer for printing variable in comments e.g. for ode system information
        self._name_printer = cg.ChastePrinter(lambda symbol: get_symbol_name(symbol))

    def _format_modifiable_parameters(self):
        """ Format the modifiable parameter for printing to chaste code"""
        return [{'units': self._model.units.summarise_units(param),
                 'comment_name': self._name_printer.doprint(param), 'name': self._get_var_display_name(param),
                 'initial_value': self._model.get_initial_value(param)} for param in self._modifiable_parameters]

    def _format_state_variables(self):
        """ Get equations defining the derivatives including  V (self._membrane_voltage_var)"""
        def get_range_annotation(subject, annotation_tag):
            """ Get range-low and range-high annotation for to verify state variables. """
            if subject.cmeta_id is not None:
                range_annotation = list(self._model.get_rdf_annotations(subject='#' + subject.cmeta_id,
                                                                        predicate=(self._PYCMLMETA, annotation_tag)))
                assert len(range_annotation) < 2, 'Expecting 0 or 1 range annotation'
                if len(range_annotation) == 1:
                    return float(range_annotation[0][2])
            return ''

        # Get all used symbols for eqs for ionic variables to be able to indicate if a state var is used
        ionic_var_symbols = set()
        for eq in self._extended_equations_for_ionic_vars:
            ionic_var_symbols.update(eq.rhs.free_symbols)

        # Get all used symbols for y derivs to be able to indicate if a state var is used
        y_deriv_symbols = set()
        for eq in self._derivative_equations:
            y_deriv_symbols.update(eq.rhs.free_symbols)

        # Get all used symbols for eqs for derived quantities variables to be able to indicate if a state var is used
        derived_quant_symbols = set()
        for eq in self._derived_quant_eqs:
            derived_quant_symbols.update(eq.rhs.free_symbols)

        formatted_state_vars = \
            [{'var': self._printer.doprint(var),
              'annotated_var_name': self._get_var_display_name(var),
              'initial_value': str(self._model.get_initial_value(var)),
              'units': str(self._model.units.summarise_units(var)),
              'in_ionic': var in ionic_var_symbols,
              'in_y_deriv': var in y_deriv_symbols,
              'in_derived_quant': var in derived_quant_symbols,
              'range_low': get_range_annotation(var, 'range-low'),
              'range_high': get_range_annotation(var, 'range-high')}
             for var in self._state_vars]

        use_verify_state_variables = \
            len([eq for eq in formatted_state_vars if eq['range_low'] != '' or eq['range_high'] != '']) > 0
        return formatted_state_vars, use_verify_state_variables

    def _format_default_stimulus(self):
        """ Format eqs for stimulus_current for outputting to chaste code"""
        formatted_default_stimulus = dict()
        for key, eq in self._default_stimulus.items():
            # exclude (equations for) variables that don't have annotation
            if self._model.has_ontology_annotation(eq.lhs, self._OXMETA):
                formatted_default_stimulus[key] = []
                factor = 1.0
                rhs_multiplier = None
                current_units = self._model.units.summarise_units(eq.lhs)
                units = None
                if key in self._stim_units:
                    rhs_multiplier = None
                    for units_to_try in [unit_dict['units'] for unit_dict in self._stim_units[key]]:

                        if units_to_try.dimensionality == current_units.dimensionality:
                            units = units_to_try
                            factor = self._model.units.get_conversion_factor(units, from_unit=current_units)
                            # Check if there is a rhs multiplier for this key and unit combo (e.g. for the amplitude:
                            if key in self._STIM_RHS_MULTIPLIER and str(units) in self._STIM_RHS_MULTIPLIER[key]:
                                rhs_multiplier = self._STIM_RHS_MULTIPLIER[key][str(units)]
                            if key in self._STIM_CONVERSION_RULES and str(units) in self._STIM_CONVERSION_RULES[key]:
                                additional_eqs = []

                                assert self._STIM_CONVERSION_RULES_ERR_CHECK[key][str(units)]['condition'](self), \
                                    self._STIM_CONVERSION_RULES_ERR_CHECK[key][str(units)]['message']
                                # Apply conversion rules if we have any
                                units, factor, eq, additional_eqs = \
                                    self._STIM_CONVERSION_RULES[key][str(units)](
                                        self, current_units, factor, eq)
                                formatted_default_stimulus[key].extend(additional_eqs)
                            break
                rhs = eq.rhs if factor == 1.0 else factor * eq.rhs
                self._in_interface.append(eq.lhs)
                formatted_default_stimulus[key].append({'lhs': self._printer.doprint(eq.lhs),
                                                        'rhs': self._printer.doprint(rhs)
                                                        if rhs_multiplier is None
                                                        else self._printer.doprint(rhs * rhs_multiplier),
                                                        'units': str(units if units is not None else current_units)
                                                        })
        return formatted_default_stimulus

    def _format_extended_equations_for_ionic_vars(self):
        """ Format equations and dependant equations ionic derivatives"""

        def print_rhs(eq):
            """ Print the rhs, set _membrane_stimulus_current to 0.0"""
            if eq.lhs != self._membrane_stimulus_current and eq.lhs != self._original_membrane_stimulus_current:
                return self._printer.doprint(eq.rhs)
            else:
                return 0.0
        # Format the state ionic variables
        return [{'lhs': self._printer.doprint(eq.lhs), 'rhs': print_rhs(eq),
                 'units': self._model.units.summarise_units(eq.lhs)} for eq in self._extended_equations_for_ionic_vars]

    def _format_y_derivatives(self):
        """ Format y_derivatives for writing to chaste output"""
        self._in_interface.extend(self._y_derivatives)
        return [self._printer.doprint(deriv) for deriv in self._y_derivatives]

    def _format_derivative_equations(self):
        """Format derivative equations for chaste output"""
        # exclude ionic currents
        return [{'lhs': self._printer.doprint(eqs.lhs),
                 'rhs': self._printer.doprint(eqs.rhs),
                 'units': self._model.units.summarise_units(eqs.lhs),
                 'in_membrane_voltage': eqs not in self._derivative_eqs_exlc_voltage,
                 'is_voltage': isinstance(eqs.lhs, sp.Derivative) and eqs.lhs.args[0] == self._membrane_voltage_var}
                for eqs in self._derivative_equations]

    def _format_free_variable(self):
        """ Format free variable for chaste output"""
        return {'name': self._get_var_display_name(self._time_variable),
                'units': self._model.units.summarise_units(self._time_variable),
                'system_name': self._model.name,
                'var_name': self._printer.doprint(self._time_variable)}

    def _format_system_info(self):
        """ Format general ode system info for chaste output"""
        return [{'name': self._get_var_display_name(var),
                 'initial_value': str(self._model.get_initial_value(var)),
                 'units': self._model.units.summarise_units(var)}
                for var in self._state_vars]

    def _format_named_attributes(self):
        """ Format named attributes for chaste output"""
        named_attributes = []
        named_attrs = self._model.get_rdf_annotations(subject=self._model.rdf_identity,
                                                      predicate=(self._PYCMLMETA, 'named-attribute'))
        for s, p, attr in named_attrs:
            name = self._model.get_rdf_value(subject=attr, predicate=(self._PYCMLMETA, 'name'))
            value = self._model.get_rdf_value(subject=attr, predicate=(self._PYCMLMETA, 'value'))
            named_attributes.append({'name': name, 'value': value})

        return sorted(named_attributes, key=lambda a: a['name'])

    def _format_derived_quant(self):
        return [{'units': self._model.units.summarise_units(quant),
                 'var': self._printer.doprint(quant), 'name': self._get_var_display_name(quant)}
                for quant in self._derived_quant]

    def _format_derived_quant_eqs(self):
        """ Format equations for derivd quantites based on current settings"""
        return [{'lhs': self._printer.doprint(eq.lhs),
                 'rhs': self._printer.doprint(eq.rhs),
                 'units': str(self._model.units.summarise_units(eq.lhs))}
                for eq in self._derived_quant_eqs]

    def generate_chaste_code(self):
        """ Generate chaste code
        Please Note: not implemented, use a subclass for the relevant model type
        """
        raise NotImplementedError("Should not be called directly, use the specific model types instead!")


class NormalChasteModel(ChasteModel):
    """ Holds information specific for the Normal model type"""

    def __init__(self, model, class_name, file_name, **kwargs):
        super().__init__(model, class_name, file_name, **kwargs)

    def generate_chaste_code(self):
        """ Generates and stores chaste code for the Normal model"""

        # Generate hpp for model
        template = cg.load_template('chaste', 'normal_model.hpp')
        self.generated_hpp = template.render({
            'model_name': self._model.name,
            'class_name': self.class_name,
            'dynamically_loadable': self._dynamically_loadable,
            'generation_date': time.strftime('%Y-%m-%d %H:%M:%S'),
            'default_stimulus_equations': self._formatted_default_stimulus,
            'use_get_intracellular_calcium_concentration':
                self._cytosolic_calcium_concentration_var in self._state_vars,
            'free_variable': self._free_variable,
            'use_verify_state_variables': self._use_verify_state_variables,
            'derived_quantities': self._formatted_derived_quant})

        # Generate cpp for model
        template = cg.load_template('chaste', 'normal_model.cpp')
        self.generated_cpp = template.render({
            'model_name': self._model.name,
            'file_name': self.file_name,
            'class_name': self.class_name,
            'dynamically_loadable': self._dynamically_loadable,
            'generation_date': time.strftime('%Y-%m-%d %H:%M:%S'),
            'default_stimulus_equations': self._formatted_default_stimulus,
            'use_get_intracellular_calcium_concentration':
                self._cytosolic_calcium_concentration_var in self._state_vars,
            'membrane_voltage_index': self._MEMBRANE_VOLTAGE_INDEX,
            'cytosolic_calcium_concentration_index':
                self._state_vars.index(self._cytosolic_calcium_concentration_var)
                if self._cytosolic_calcium_concentration_var in self._state_vars
                else self._CYTOSOLIC_CALCIUM_CONCENTRATION_INDEX,
            'state_vars': self._formatted_state_vars,
            'ionic_vars': self._formatted_extended_equations_for_ionic_vars,
            'y_derivative_equations': self._formatted_derivative_eqs,
            'y_derivatives': self._formatted_y_derivatives,
            'use_capacitance_i_ionic': self._current_unit_and_capacitance['use_capacitance'],
            'free_variable': self._free_variable,
            'ode_system_information': self._ode_system_information,
            'modifiable_parameters': self._formatted_modifiable_parameters,
            'named_attributes': self._named_attributes,
            'use_verify_state_variables': self._use_verify_state_variables,
            'derived_quantities': self._formatted_derived_quant,
            'derived_quantity_equations': self._formatted_quant_eqs})


class OptChasteModel(ChasteModel):
    pass


class Analytic_jChasteModel(ChasteModel):
    pass


class Numerical_jChasteModel(ChasteModel):
    pass


class BEOptChasteModel(ChasteModel):
    pass