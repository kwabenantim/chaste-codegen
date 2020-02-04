#ifdef CHASTE_CVODE
#ifndef {% filter upper %}{{class_name}}_HPP_{% endfilter %}
#define {% filter upper %}{{class_name}}_HPP_{% endfilter %}

//! @file
//!
//! This source file was generated from CellML by chaste_codegen version {{converter_version}}
//!
//! Model: {{model_name}}
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: CVODE )
//! on {{generation_date}}
//!
//! <autogenerated>

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>
#include "AbstractCvodeCell.hpp"
{% if dynamically_loadable %}#include "AbstractDynamicallyLoadableEntity.hpp"{%- endif %}
#include "AbstractStimulusFunction.hpp"

class {{class_name}} : public AbstractCvodeCell{%- if dynamically_loadable %}, public AbstractDynamicallyLoadableEntity{%- endif %}
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractCvodeCell >(*this);
        {% if dynamically_loadable %}archive & boost::serialization::base_object<AbstractDynamicallyLoadableEntity>(*this);{%- endif %}
    }
    
    // 
    // Settable parameters and readable variables
    // 
    
public:
    {%- if default_stimulus_equations["equations"]|length > 0 %}
    boost::shared_ptr<RegularStimulus> UseCellMLDefaultStimulus();
    {%- endif %}
    {%- if use_get_intracellular_calcium_concentration %}
    double GetIntracellularCalciumConcentration();
    {%- endif %}
    {{class_name}}(boost::shared_ptr<AbstractIvpOdeSolver> pOdeSolver /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus);
    ~{{class_name}}();
    {%- if use_verify_state_variables %}
    void VerifyStateVariables();
    {%- endif %}
    double GetIIonic(const std::vector<double>* pStateVariables=NULL);
    void EvaluateYDerivatives(double {{free_variable.var_name}}, const N_Vector rY, N_Vector rDY);
    {%- if derived_quantities|length > 0 %}
    std::vector<double> ComputeDerivedQuantities(double {{free_variable.var_name}}, const std::vector<double> & rY);
    {%- endif %}
    {%- if jacobian_equations|length > 0 %}
    void EvaluateAnalyticJacobian(double var_chaste_interface__environment__time, N_Vector rY, N_Vector rDY, CHASTE_CVODE_DENSE_MATRIX rJacobian, N_Vector rTmp1, N_Vector rTmp2, N_Vector rTmp3);
    {%- endif %}
};


// Needs to be included last
#include "SerializationExportWrapper.hpp"
CHASTE_CLASS_EXPORT({{class_name}})

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        inline void save_construct_data(
            Archive & ar, const {{class_name}} * t, const unsigned int fileVersion)
        {
            const boost::shared_ptr<AbstractIvpOdeSolver> p_solver = t->GetSolver();
            const boost::shared_ptr<AbstractStimulusFunction> p_stimulus = t->GetStimulusFunction();
            ar << p_solver;
            ar << p_stimulus;
        }
        
        template<class Archive>
        inline void load_construct_data(
            Archive & ar, {{class_name}} * t, const unsigned int fileVersion)
        {
            boost::shared_ptr<AbstractIvpOdeSolver> p_solver;
            boost::shared_ptr<AbstractStimulusFunction> p_stimulus;
            ar >> p_solver;
            ar >> p_stimulus;
            ::new(t){{class_name}}(p_solver, p_stimulus);
        }
        
    }
    
}

#endif // {% filter upper %}{{class_name}}_HPP_{% endfilter %}
#endif // CHASTE_CVODE

