//! @file
//!
//! This source file was generated from CellML by chaste_codegen version (version omitted as unimportant)
//!
//! Model: component_with_units
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: Normal)
//! on (date omitted as unimportant)
//!
//! <autogenerated>

#include "test_V_not_state_mparam.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"





    Celltest_V_not_state_mparamFromCellML::Celltest_V_not_state_mparamFromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                1,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        //
        this->mpSystemInfo = OdeSystemInformation<Celltest_V_not_state_mparamFromCellML>::Instance();
        Init();
        
    }

    Celltest_V_not_state_mparamFromCellML::~Celltest_V_not_state_mparamFromCellML()
    {
    }

    
    double Celltest_V_not_state_mparamFromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        
        const double var_chaste_interface__i_ionic = 0; // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }

    void Celltest_V_not_state_mparamFromCellML::EvaluateYDerivatives(double var_chaste_interface__membrane__time_converted, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        

        // Mathematics
        
        const double var_membrane__V1_orig_deriv = 25; // volt / second
        const double d_dt_chaste_interface_var_membrane__V1 = 0.001 * var_membrane__V1_orig_deriv; // volt / millisecond

        if (mSetVoltageDerivativeToZero)
        {
            
        }
        else
        {
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V1;
    }

    std::vector<double> Celltest_V_not_state_mparamFromCellML::ComputeDerivedQuantities(double var_chaste_interface__membrane__time_converted, const std::vector<double> & rY)
    {
        // Inputs:
        // Time units: millisecond
        
        // Mathematics
        const double var_membrane__V_converted = -75000; // millivolt

        std::vector<double> dqs(2);
        dqs[0] = var_chaste_interface__membrane__time_converted;
        dqs[1] = var_membrane__V_converted;
        return dqs;
    }

template<>
void OdeSystemInformation<Celltest_V_not_state_mparamFromCellML>::Initialise(void)
{
    this->mSystemName = "component_with_units";
    this->mFreeVariableName = "membrane__time";
    this->mFreeVariableUnits = "millisecond";

    // rY[0]:
    this->mVariableNames.push_back("membrane__V1");
    this->mVariableUnits.push_back("volt");
    this->mInitialConditions.push_back(-69.1865);

    // Derived Quantity index [0]:
    this->mDerivedQuantityNames.push_back("membrane__time");
    this->mDerivedQuantityUnits.push_back("millisecond");

    // Derived Quantity index [1]:
    this->mDerivedQuantityNames.push_back("membrane_voltage");
    this->mDerivedQuantityUnits.push_back("millivolt");

    this->mInitialised = true;
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Celltest_V_not_state_mparamFromCellML)

