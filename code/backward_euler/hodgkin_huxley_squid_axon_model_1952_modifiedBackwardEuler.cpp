//! @file
//!
//! This source file was generated from CellML by chaste_codegen version 0.8.0
//!
//! Model: hodgkin_huxley_squid_axon_model_1952_modified
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: BackwardEuler)
//! on 2021-06-10 11:26:45
//!
//! <autogenerated>

#include "CardiacNewtonSolver.hpp"
#include "hodgkin_huxley_squid_axon_model_1952_modifiedBackwardEuler.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"




    boost::shared_ptr<RegularStimulus> Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__membrane__stim_amplitude = -20.0; // microA_per_cm2
        const double var_chaste_interface__membrane__stim_duration = 0.5; // millisecond
        const double var_chaste_interface__membrane__stim_period = 1000.0; // millisecond
        const double var_chaste_interface__membrane__stim_start = 10.0; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__membrane__stim_amplitude),
                var_chaste_interface__membrane__stim_duration,
                var_chaste_interface__membrane__stim_period,
                var_chaste_interface__membrane__stim_start
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }

    Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler(boost::shared_ptr<AbstractIvpOdeSolver> /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractBackwardEulerCardiacCell<0>(
                4,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        //
        this->mpSystemInfo = OdeSystemInformation<Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler>::Instance();
        Init();

        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
        this->mParameters[0] = 1.0; // (var_membrane__Cm) [microF_per_cm2]
        this->mParameters[1] = 120.0; // (var_sodium_channel__g_Na) [milliS_per_cm2]
        this->mParameters[2] = 0.29999999999999999; // (var_leakage_current__g_L) [milliS_per_cm2]
        this->mParameters[3] = 36.0; // (var_potassium_channel__g_K) [milliS_per_cm2]
    }

    Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::~Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler()
    {
    }

    
    double Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = rY[3];
        // Units: dimensionless; Initial value: 0.325
        
        const double var_membrane__E_R = -75.0; // millivolt
        const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
        const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * mParameters[2]; // microA_per_cm2
        const double var_potassium_channel__E_K = -12.0 + var_membrane__E_R; // millivolt
        const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * mParameters[3]; // microA_per_cm2
        const double var_sodium_channel__E_Na = 115.0 + var_membrane__E_R; // millivolt
        const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * mParameters[1] * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2
        const double var_chaste_interface__i_ionic = var_leakage_current__i_L + var_potassium_channel__i_K + var_sodium_channel__i_Na; // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }



    void Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::UpdateTransmembranePotential(double var_chaste_interface__environment__time)
    {
        // Time units: millisecond
        std::vector<double>& rY = rGetStateVariables();
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = rY[3];
        // Units: dimensionless; Initial value: 0.325
        
        const double var_membrane__E_R = -75.0; // millivolt
        const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
        const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * mParameters[2]; // microA_per_cm2
        const double var_membrane__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // microA_per_cm2
        const double var_potassium_channel__E_K = -12.0 + var_membrane__E_R; // millivolt
        const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * mParameters[3]; // microA_per_cm2
        const double var_sodium_channel__E_Na = 115.0 + var_membrane__E_R; // millivolt
        const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * mParameters[1] * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2
        const double d_dt_chaste_interface_var_membrane__V = (-var_leakage_current__i_L - var_membrane__i_Stim - var_potassium_channel__i_K - var_sodium_channel__i_Na) / mParameters[0]; // millivolt / millisecond
        
        rY[0] += mDt*d_dt_chaste_interface_var_membrane__V;
    }
    
    void Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::ComputeOneStepExceptVoltage(double var_chaste_interface__environment__time)
    {
        // Time units: millisecond
        std::vector<double>& rY = rGetStateVariables();
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = rY[3];
        // Units: dimensionless; Initial value: 0.325
        
        const double var_potassium_channel_n_gate__B = -0.10000000000000001;
        const double var_potassium_channel_n_gate__A = -0.01 / var_potassium_channel_n_gate__B;
        const double var_potassium_channel_n_gate__beta_n = 0.125 * exp(0.9375 + 0.012500000000000001 * var_chaste_interface__membrane__V);
        const double var_potassium_channel_n_gate__v0 = -65.0;
        const double var_potassium_channel_n_gate__U = (-var_potassium_channel_n_gate__v0 + var_chaste_interface__membrane__V) * var_potassium_channel_n_gate__B;
        const double var_potassium_channel_n_gate__alpha_n = (((var_potassium_channel_n_gate__U >= -9.9999999999999995e-8) && (var_potassium_channel_n_gate__U <= 9.9999999999999995e-8)) ? ((1.0 - 0.5 * var_potassium_channel_n_gate__U) * var_potassium_channel_n_gate__A) : (var_potassium_channel_n_gate__A * var_potassium_channel_n_gate__U / (-1.0 + exp(var_potassium_channel_n_gate__U))));
        const double var_sodium_channel_h_gate__alpha_h = 0.070000000000000007 * exp(-3.75 - 0.050000000000000003 * var_chaste_interface__membrane__V);
        const double var_sodium_channel_h_gate__beta_h = 1 / (1.0 + exp(-4.5 - 0.10000000000000001 * var_chaste_interface__membrane__V));
        const double var_sodium_channel_m_gate__B = -0.10000000000000001;
        const double var_sodium_channel_m_gate__A = -0.10000000000000001 / var_sodium_channel_m_gate__B;
        const double var_sodium_channel_m_gate__beta_m = 4.0 * exp(-4.166666666666667 - 0.055555555555555552 * var_chaste_interface__membrane__V);
        const double var_sodium_channel_m_gate__v0 = -50.0;
        const double var_sodium_channel_m_gate__U = (-var_sodium_channel_m_gate__v0 + var_chaste_interface__membrane__V) * var_sodium_channel_m_gate__B;
        const double var_sodium_channel_m_gate__alpha_m = (((var_sodium_channel_m_gate__U >= -9.9999999999999995e-8) && (var_sodium_channel_m_gate__U <= 9.9999999999999995e-8)) ? ((1.0 - 0.5 * var_sodium_channel_m_gate__U) * var_sodium_channel_m_gate__A) : (var_sodium_channel_m_gate__A * var_sodium_channel_m_gate__U / (-1.0 + exp(var_sodium_channel_m_gate__U))));
        
        
        rY[3] = (var_chaste_interface__potassium_channel_n_gate__n + ((var_potassium_channel_n_gate__alpha_n) * mDt)) / (1.0 - ((-var_potassium_channel_n_gate__alpha_n - var_potassium_channel_n_gate__beta_n) * mDt));
        rY[2] = (var_chaste_interface__sodium_channel_h_gate__h + ((var_sodium_channel_h_gate__alpha_h) * mDt)) / (1.0 - ((-var_sodium_channel_h_gate__alpha_h - var_sodium_channel_h_gate__beta_h) * mDt));
        rY[1] = (var_chaste_interface__sodium_channel_m_gate__m + ((var_sodium_channel_m_gate__alpha_m) * mDt)) / (1.0 - ((-var_sodium_channel_m_gate__alpha_m - var_sodium_channel_m_gate__beta_m) * mDt));
        
    }

    std::vector<double> Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler::ComputeDerivedQuantities(double var_chaste_interface__environment__time, const std::vector<double> & rY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = rY[3];
        // Units: dimensionless; Initial value: 0.325
        
        // Mathematics
        const double var_membrane__E_R = -75.0; // millivolt
        const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
        const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * mParameters[2]; // microA_per_cm2
        const double var_membrane__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // microA_per_cm2
        const double var_potassium_channel__E_K = -12.0 + var_membrane__E_R; // millivolt
        const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * mParameters[3]; // microA_per_cm2
        const double var_sodium_channel__E_Na = 115.0 + var_membrane__E_R; // millivolt
        const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * mParameters[1] * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2

        std::vector<double> dqs(5);
        dqs[0] = var_sodium_channel__i_Na;
        dqs[1] = var_leakage_current__i_L;
        dqs[2] = var_potassium_channel__i_K;
        dqs[3] = var_membrane__i_Stim;
        dqs[4] = var_chaste_interface__environment__time;
        return dqs;
    }

template<>
void OdeSystemInformation<Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler>::Initialise(void)
{
    this->mSystemName = "hodgkin_huxley_squid_axon_model_1952_modified";
    this->mFreeVariableName = "time";
    this->mFreeVariableUnits = "millisecond";

    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-75.0);

    // rY[1]:
    this->mVariableNames.push_back("sodium_channel_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.05);

    // rY[2]:
    this->mVariableNames.push_back("sodium_channel_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.6);

    // rY[3]:
    this->mVariableNames.push_back("potassium_channel_n_gate__n");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.325);

    // mParameters[0]:
    this->mParameterNames.push_back("membrane_capacitance");
    this->mParameterUnits.push_back("microF_per_cm2");

    // mParameters[1]:
    this->mParameterNames.push_back("membrane_fast_sodium_current_conductance");
    this->mParameterUnits.push_back("milliS_per_cm2");

    // mParameters[2]:
    this->mParameterNames.push_back("membrane_leakage_current_conductance");
    this->mParameterUnits.push_back("milliS_per_cm2");

    // mParameters[3]:
    this->mParameterNames.push_back("membrane_potassium_current_conductance");
    this->mParameterUnits.push_back("milliS_per_cm2");

    // Derived Quantity index [0]:
    this->mDerivedQuantityNames.push_back("membrane_fast_sodium_current");
    this->mDerivedQuantityUnits.push_back("microA_per_cm2");

    // Derived Quantity index [1]:
    this->mDerivedQuantityNames.push_back("membrane_leakage_current");
    this->mDerivedQuantityUnits.push_back("microA_per_cm2");

    // Derived Quantity index [2]:
    this->mDerivedQuantityNames.push_back("membrane_potassium_current");
    this->mDerivedQuantityUnits.push_back("microA_per_cm2");

    // Derived Quantity index [3]:
    this->mDerivedQuantityNames.push_back("membrane_stimulus_current");
    this->mDerivedQuantityUnits.push_back("microA_per_cm2");

    // Derived Quantity index [4]:
    this->mDerivedQuantityNames.push_back("time");
    this->mDerivedQuantityUnits.push_back("millisecond");

    this->mInitialised = true;
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLBackwardEuler)

