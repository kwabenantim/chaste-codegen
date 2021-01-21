import pytest

from chaste_codegen._chaste_printer import ChastePrinter
from chaste_codegen._lookup_tables import _EXPENSIVE_FUNCTIONS, DEFAULT_LOOKUP_PARAMETERS, LookupTables


def test_defaults(s_model):
    """ Test to check defaults are not changed unintentionally"""
    assert str(_EXPENSIVE_FUNCTIONS) == ("(exp, log, log, sin, cos, tan, sec, csc, cot, sinh, cosh, tanh, sech, csch, "
                                         "coth, asin, acos, atan, asinh, acosh, atanh, asec, acsc, acot, asech, acsch,"
                                         " acoth, exp_, acos_, cos_, sin_)")
    assert DEFAULT_LOOKUP_PARAMETERS == (['membrane_voltage', -250.0001, 549.9999, 0.001], )


def test_no_method_printed_for(s_model):
    lut = LookupTables(s_model)
    lut.calc_lookup_tables(s_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)
    output = ""
    for eq in s_model.equations:
        output += printer.doprint(eq)
    assert '_lt_0_row[0]' not in output
    # We can't use an external text files here since the data contains sets
    # printing these would make the test dependant on their order
    assert lut.print_lookup_parameters(printer) == \
        [{'metadata_tag': 'membrane_voltage', 'mTableMins': -250.0001, 'mTableMaxs': 549.9999, 'mTableSteps': 0.001,
          'table_used_in_methods': set(), 'var': 'cell$V',
          'lookup_epxrs':
            ['(47.13 + cell$V) * 0.32 / ((-exp(-(47.13 + cell$V) * 0.1) + 1.0) * 1.0)',
             '0.08 * exp(-cell$V / 11.0)',
             '1.0 / (1.0 + exp((-50.0 - cell$V) / 7.5))',
             ('1.0 / ((10.0 + cell$V) * 0.00061 / (-1.0 + exp((10.0 + cell$V) * 0.145)) + (7.0 + cell$V) * 0.00138 / '
              '(-exp(-(7.0 + cell$V) * 0.123) + 1.0))'),
             '1.0 / (1.0 + exp((33.0 + cell$V) / 22.4))',
             '1.0 / (1.0 + exp((-cell$V + 1.5) / 16.7))',
             ('1.0 / ((30.0 + cell$V) * 0.000131 / (-1.0 + exp((30.0 + cell$V) * 0.0687)) + (30.0 + cell$V) * 7.19e-05'
              ' / (-exp(-(30.0 + cell$V) * 0.148) + 1.0))'),
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '9.0 / (1.0 + exp((3.0 + cell$V) / 15.0)) + 0.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '3000.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 30.0',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '2800.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 220.0',
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '3.5 * exp(-pow((cell$V / 30.0), 2.0)) + 1.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '20.0 / (1.0 + exp((33.5 + cell$V) / 10.0)) + 20.0',
             '1.0 / (1.0 + exp((-14.5 - cell$V) / 6.0))',
             '-exp((-14.5 - cell$V) / 6.0) + 1.0',
             '1.0 / (1.0 + exp((35.06 + cell$V) / 3.6)) + 0.6 / (1.0 + exp((-cell$V + 50.0) / 20.0))',
             '1.0 / (0.0197 * exp(-pow(((14.5 + cell$V) * 0.0337), 2.0)) + 0.02)']}]


def test_method_printed_for(s_model):
    lut = LookupTables(s_model)
    lut.calc_lookup_tables(s_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)

    output = ""
    for eq in s_model.equations:
        with lut.method_being_printed('template_method'):
            output += printer.doprint(eq.rhs)
    assert '_lt_0_row[0]' in output
    assert lut.print_lookup_parameters(printer) == \
        [{'metadata_tag': 'membrane_voltage', 'mTableMins': -250.0001, 'mTableMaxs': 549.9999, 'mTableSteps': 0.001,
          'table_used_in_methods': {'template_method'}, 'var': 'cell$V',
          'lookup_epxrs':
            ['(47.13 + cell$V) * 0.32 / ((-exp(-(47.13 + cell$V) * 0.1) + 1.0) * 1.0)',
             '0.08 * exp(-cell$V / 11.0)',
             '1.0 / (1.0 + exp((-50.0 - cell$V) / 7.5))',
             ('1.0 / ((10.0 + cell$V) * 0.00061 / (-1.0 + exp((10.0 + cell$V) * 0.145)) + (7.0 + cell$V) * 0.00138 / '
              '(-exp(-(7.0 + cell$V) * 0.123) + 1.0))'),
             '1.0 / (1.0 + exp((33.0 + cell$V) / 22.4))',
             '1.0 / (1.0 + exp((-cell$V + 1.5) / 16.7))',
             ('1.0 / ((30.0 + cell$V) * 0.000131 / (-1.0 + exp((30.0 + cell$V) * 0.0687)) + (30.0 + cell$V) * 7.19e-05'
              ' / (-exp(-(30.0 + cell$V) * 0.148) + 1.0))'),
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '9.0 / (1.0 + exp((3.0 + cell$V) / 15.0)) + 0.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '3000.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 30.0',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '2800.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 220.0',
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '3.5 * exp(-pow((cell$V / 30.0), 2.0)) + 1.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '20.0 / (1.0 + exp((33.5 + cell$V) / 10.0)) + 20.0',
             '1.0 / (1.0 + exp((-14.5 - cell$V) / 6.0))',
             '-exp((-14.5 - cell$V) / 6.0) + 1.0',
             '1.0 / (1.0 + exp((35.06 + cell$V) / 3.6)) + 0.6 / (1.0 + exp((-cell$V + 50.0) / 20.0))',
             '1.0 / (0.0197 * exp(-pow(((14.5 + cell$V) * 0.0337), 2.0)) + 0.02)']}]


def test_nested_method_printed_for(s_model):
    lut = LookupTables(s_model)
    lut.calc_lookup_tables(s_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)

    output = ""
    for eq in s_model.equations:
        with lut.method_being_printed('outer_method'):
            with lut.method_being_printed('innter_method'):
                output += printer.doprint(eq.rhs)
    assert '_lt_0_row[0]' in output
    assert lut.print_lookup_parameters(printer) == \
        [{'metadata_tag': 'membrane_voltage', 'mTableMins': -250.0001, 'mTableMaxs': 549.9999, 'mTableSteps': 0.001,
          'table_used_in_methods': {'outer_method'}, 'var': 'cell$V',
          'lookup_epxrs':
            ['(47.13 + cell$V) * 0.32 / ((-exp(-(47.13 + cell$V) * 0.1) + 1.0) * 1.0)',
             '0.08 * exp(-cell$V / 11.0)',
             '1.0 / (1.0 + exp((-50.0 - cell$V) / 7.5))',
             ('1.0 / ((10.0 + cell$V) * 0.00061 / (-1.0 + exp((10.0 + cell$V) * 0.145)) + (7.0 + cell$V) * 0.00138 / '
              '(-exp(-(7.0 + cell$V) * 0.123) + 1.0))'),
             '1.0 / (1.0 + exp((33.0 + cell$V) / 22.4))',
             '1.0 / (1.0 + exp((-cell$V + 1.5) / 16.7))',
             ('1.0 / ((30.0 + cell$V) * 0.000131 / (-1.0 + exp((30.0 + cell$V) * 0.0687)) + (30.0 + cell$V) * 7.19e-05'
              ' / (-exp(-(30.0 + cell$V) * 0.148) + 1.0))'),
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '9.0 / (1.0 + exp((3.0 + cell$V) / 15.0)) + 0.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '3000.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 30.0',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '2800.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 220.0',
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '3.5 * exp(-pow((cell$V / 30.0), 2.0)) + 1.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '20.0 / (1.0 + exp((33.5 + cell$V) / 10.0)) + 20.0',
             '1.0 / (1.0 + exp((-14.5 - cell$V) / 6.0))',
             '-exp((-14.5 - cell$V) / 6.0) + 1.0',
             '1.0 / (1.0 + exp((35.06 + cell$V) / 3.6)) + 0.6 / (1.0 + exp((-cell$V + 50.0) / 20.0))',
             '1.0 / (0.0197 * exp(-pow(((14.5 + cell$V) * 0.0337), 2.0)) + 0.02)']}]


def test_multiple_methods_printed_for(s_model):
    lut = LookupTables(s_model)
    lut.calc_lookup_tables(s_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)

    for eq in s_model.equations:
        with lut.method_being_printed('method1'):
            printer.doprint(eq.rhs)

    for eq in s_model.equations:
        with lut.method_being_printed('method2'):
            printer.doprint(eq.rhs)
    print(lut.print_lookup_parameters(printer))
    assert lut.print_lookup_parameters(printer) == \
        [{'metadata_tag': 'membrane_voltage', 'mTableMins': -250.0001, 'mTableMaxs': 549.9999, 'mTableSteps': 0.001,
          'table_used_in_methods': {'method2', 'method1'}, 'var': 'cell$V',
          'lookup_epxrs':
            ['(47.13 + cell$V) * 0.32 / ((-exp(-(47.13 + cell$V) * 0.1) + 1.0) * 1.0)',
             '0.08 * exp(-cell$V / 11.0)',
             '1.0 / (1.0 + exp((-50.0 - cell$V) / 7.5))',
             ('1.0 / ((10.0 + cell$V) * 0.00061 / (-1.0 + exp((10.0 + cell$V) * 0.145)) + (7.0 + cell$V) * 0.00138 / '
              '(-exp(-(7.0 + cell$V) * 0.123) + 1.0))'),
             '1.0 / (1.0 + exp((33.0 + cell$V) / 22.4))',
             '1.0 / (1.0 + exp((-cell$V + 1.5) / 16.7))',
             ('1.0 / ((30.0 + cell$V) * 0.000131 / (-1.0 + exp((30.0 + cell$V) * 0.0687)) + (30.0 + cell$V) * 7.19e-05'
              ' / (-exp(-(30.0 + cell$V) * 0.148) + 1.0))'),
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '9.0 / (1.0 + exp((3.0 + cell$V) / 15.0)) + 0.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '3000.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 30.0',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '2800.0 / (1.0 + exp((60.0 + cell$V) / 10.0)) + 220.0',
             '1.0 / (1.0 + exp((-3.0 - cell$V) / 15.0))',
             '3.5 * exp(-pow((cell$V / 30.0), 2.0)) + 1.5',
             '1.0 / (1.0 + exp((33.5 + cell$V) / 10.0))',
             '20.0 / (1.0 + exp((33.5 + cell$V) / 10.0)) + 20.0',
             '1.0 / (1.0 + exp((-14.5 - cell$V) / 6.0))',
             '-exp((-14.5 - cell$V) / 6.0) + 1.0',
             '1.0 / (1.0 + exp((35.06 + cell$V) / 3.6)) + 0.6 / (1.0 + exp((-cell$V + 50.0) / 20.0))',
             '1.0 / (0.0197 * exp(-pow(((14.5 + cell$V) * 0.0337), 2.0)) + 0.02)']}]


def test_change_lookup_table(be_model):
    lut = LookupTables(be_model, lookup_params=[['membrane_voltage', -25.0001, 54.9999, 0.01],
                                                ['cytosolic_calcium_concentration', 0.0, 50.0, 0.01],
                                                ['unknown_tag', 0.0, 50.0, 0.01]])
    lut.calc_lookup_tables(be_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)

    output = ""
    for eq in be_model.equations:
        with lut.method_being_printed('template_method'):
            output += printer.doprint(eq.rhs)
    assert '_lt_0_row[0]' in output
    assert '_lt_1_row[0]' in output
    assert '_lt_2_row[0]' not in output
    assert lut.print_lookup_parameters(printer) == \
        [{'metadata_tag': 'membrane_voltage', 'mTableMins': -25.0001, 'mTableMaxs': 54.9999, 'mTableSteps': 0.01,
          'table_used_in_methods': {'template_method'}, 'var': 'membrane$V',
          'lookup_epxrs': ['-(47.0 + membrane$V) * 1.0 / (-1.0 + exp(-(47.0 + membrane$V) * 0.1))',
                           '40.0 * exp(-(72.0 + membrane$V) * 0.056)', '0.126 * exp(-(77.0 + membrane$V) * 0.25)',
                           '1.7 / (1.0 + exp(-(22.5 + membrane$V) * 0.082))',
                           '0.055 * exp(-(78.0 + membrane$V) * 0.25) / (1.0 + exp(-(78.0 + membrane$V) * 0.2))',
                           '0.3 / (1.0 + exp(-(32.0 + membrane$V) * 0.1))',
                           '0.095 * exp((-membrane$V + 5.0) / 100.0) / (1.0 + exp((-membrane$V + 5.0) / 13.89))',
                           '0.07 * exp((-44.0 - membrane$V) / 59.0) / (1.0 + exp((44.0 + membrane$V) / 20.0))',
                           '0.012 * exp((-28.0 - membrane$V) / 125.0) / (1.0 + exp((28.0 + membrane$V) / 6.67))',
                           '0.0065 * exp((-30.0 - membrane$V) / 50.0) / (1.0 + exp((-30.0 - membrane$V) / 5.0))',
                           '1 / exp((35.0 + membrane$V) * 0.04)', '-1.0 + exp((77.0 + membrane$V) * 0.04)',
                           '0.0005 * exp((50.0 + membrane$V) / 12.1) / (1.0 + exp((50.0 + membrane$V) / 17.5))',
                           '0.0013 * exp((-20.0 - membrane$V) / 16.67) / (1.0 + exp((-20.0 - membrane$V) / 25.0))',
                           ("((23.0 + membrane$V) * 0.2 / (-exp(-(23.0 + membrane$V) * 0.04) + 1.0) + (-1.0 + exp((85."
                            "0 + membrane$V) * 0.04)) * 4.0 / (exp((53.0 + membrane$V) * 0.08) + exp((53.0 + membrane$V"
                            ") * 0.04))) * 0.0035")]},
         {'metadata_tag': 'cytosolic_calcium_concentration', 'mTableMins': 0.0, 'mTableMaxs': 50.0,
          'mTableSteps': 0.01, 'table_used_in_methods': {'template_method'}, 'var': 'slow_inward_current$Cai',
          'lookup_epxrs': ['-82.3 - 13.0287 * log(0.001 * slow_inward_current$Cai)']}]


def test_no_print_after_table(s_model):
    lut = LookupTables(s_model)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)
    assert lut.print_lookup_parameters(printer) == []

    with pytest.raises(ValueError, match="Cannot print lookup expression after main table has been printed"):
        for eq in s_model.equations:
            printer.doprint(eq)


def test_no_calc_after_print(s_model):
    lut = LookupTables(s_model)
    lut.calc_lookup_tables(s_model.equations)
    printer = ChastePrinter(lookup_table_function=lut.print_lut_expr)

    for eq in s_model.equations:
        printer.doprint(eq)

    with pytest.raises(ValueError, match="Cannot calculate lookup tables after printing has started"):
        lut.calc_lookup_tables(s_model.equations)
