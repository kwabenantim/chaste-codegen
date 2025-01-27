#ifdef CHASTE_CVODE
//! @file
//!
//! This source file was generated from CellML by chaste_codegen version (version omitted as unimportant)
//!
//! Model: hodgkin_huxley_squid_axon_model_1952_modified
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: NumericCvode)
//! on (date omitted as unimportant)
//!
//! <autogenerated>

#include "hodgkin_huxley_squid_axon_model_1952_modified.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

#if CHASTE_SUNDIALS_VERSION >= 60000
#include "CvodeContextManager.hpp"
#endif



    boost::shared_ptr<RegularStimulus> Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__membrane__stim_amplitude = -20; // microA_per_cm2
        const double var_chaste_interface__membrane__stim_duration = 0.5; // millisecond
        const double var_chaste_interface__membrane__stim_period = 1000; // millisecond
        const double var_chaste_interface__membrane__stim_start = 10; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__membrane__stim_amplitude),
                var_chaste_interface__membrane__stim_duration,
                var_chaste_interface__membrane__stim_period,
                var_chaste_interface__membrane__stim_start
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }

    Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode(boost::shared_ptr<AbstractIvpOdeSolver> pOdeSolver /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCvodeCell(
                pOdeSolver,
                4,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        //
        this->mpSystemInfo = OdeSystemInformation<Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode>::Instance();
        Init();

        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
        NV_Ith_S(this->mParameters, 0) = 1; // (var_membrane__Cm) [microF_per_cm2]
        NV_Ith_S(this->mParameters, 1) = 120; // (var_sodium_channel__g_Na) [milliS_per_cm2]
        NV_Ith_S(this->mParameters, 2) = 0.29999999999999999; // (var_leakage_current__g_L) [milliS_per_cm2]
        NV_Ith_S(this->mParameters, 3) = 36; // (var_potassium_channel__g_K) [milliS_per_cm2]
    }

    Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::~Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode()
    {
    }

    
    double Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        N_Vector rY;
        bool made_new_cvode_vector = false;
        if (!pStateVariables)
        {
            rY = rGetStateVariables();
        }
        else
        {
            made_new_cvode_vector = true;
            rY = MakeNVector(*pStateVariables);
        }
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : NV_Ith_S(rY, 0));
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = NV_Ith_S(rY, 1);
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = NV_Ith_S(rY, 2);
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = NV_Ith_S(rY, 3);
        // Units: dimensionless; Initial value: 0.325
        
        const double var_membrane__E_R = -75; // millivolt
        const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
        const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 2); // microA_per_cm2
        const double var_potassium_channel__E_K = -12 + var_membrane__E_R; // millivolt
        const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 3); // microA_per_cm2
        const double var_sodium_channel__E_Na = 115 + var_membrane__E_R; // millivolt
        const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 1) * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2
        const double var_chaste_interface__i_ionic = var_leakage_current__i_L + var_potassium_channel__i_K + var_sodium_channel__i_Na; // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        if (made_new_cvode_vector)
        {
            DeleteVector(rY);
        }
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }

    void Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::EvaluateYDerivatives(double var_chaste_interface__environment__time, const N_Vector rY, N_Vector rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : NV_Ith_S(rY, 0));
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = NV_Ith_S(rY, 1);
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = NV_Ith_S(rY, 2);
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = NV_Ith_S(rY, 3);
        // Units: dimensionless; Initial value: 0.325

        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double var_potassium_channel_n_gate__alpha_n = (((var_chaste_interface__membrane__V >= -65.000000999999997) && (var_chaste_interface__membrane__V <= -64.999999000000003)) ? (1.0000000000287556e-8 / (-1 + exp(1.0000000000287557e-7)) + 499999.99998562218 * (65.000000999999997 + var_chaste_interface__membrane__V) * (-1.0000000000287556e-8 / (-1 + exp(1.0000000000287557e-7)) - 1.0000000000287556e-8 / (-1 + exp(-1.0000000000287557e-7)))) : (-0.01 * (65 + var_chaste_interface__membrane__V) / (-1 + exp(-6.5 - 0.10000000000000001 * var_chaste_interface__membrane__V)))); // per_millisecond
        const double var_potassium_channel_n_gate__beta_n = 0.125 * exp(0.9375 + 0.012500000000000001 * var_chaste_interface__membrane__V); // per_millisecond
        const double d_dt_chaste_interface_var_potassium_channel_n_gate__n = (1 - var_chaste_interface__potassium_channel_n_gate__n) * var_potassium_channel_n_gate__alpha_n - var_potassium_channel_n_gate__beta_n * var_chaste_interface__potassium_channel_n_gate__n; // 1 / millisecond
        const double var_sodium_channel_h_gate__alpha_h = 0.070000000000000007 * exp(-3.75 - 0.050000000000000003 * var_chaste_interface__membrane__V); // per_millisecond
        const double var_sodium_channel_h_gate__beta_h = 1 / (1 + exp(-4.5 - 0.10000000000000001 * var_chaste_interface__membrane__V)); // per_millisecond
        const double d_dt_chaste_interface_var_sodium_channel_h_gate__h = (1 - var_chaste_interface__sodium_channel_h_gate__h) * var_sodium_channel_h_gate__alpha_h - var_sodium_channel_h_gate__beta_h * var_chaste_interface__sodium_channel_h_gate__h; // 1 / millisecond
        const double var_sodium_channel_m_gate__alpha_m = (((var_chaste_interface__membrane__V >= -50.000000999999997) && (var_chaste_interface__membrane__V <= -49.999999000000003)) ? (1.0000000000287557e-7 / (-1 + exp(1.0000000000287557e-7)) + 499999.99998562218 * (50.000000999999997 + var_chaste_interface__membrane__V) * (-1.0000000000287557e-7 / (-1 + exp(1.0000000000287557e-7)) - 1.0000000000287557e-7 / (-1 + exp(-1.0000000000287557e-7)))) : (-0.10000000000000001 * (50 + var_chaste_interface__membrane__V) / (-1 + exp(-5 - 0.10000000000000001 * var_chaste_interface__membrane__V)))); // per_millisecond
        const double var_sodium_channel_m_gate__beta_m = 4 * exp(-4.166666666666667 - 0.055555555555555552 * var_chaste_interface__membrane__V); // per_millisecond
        const double d_dt_chaste_interface_var_sodium_channel_m_gate__m = (1 - var_chaste_interface__sodium_channel_m_gate__m) * var_sodium_channel_m_gate__alpha_m - var_sodium_channel_m_gate__beta_m * var_chaste_interface__sodium_channel_m_gate__m; // 1 / millisecond

        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            const double var_membrane__E_R = -75; // millivolt
            const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
            const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 2); // microA_per_cm2
            const double var_membrane__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // microA_per_cm2
            const double var_potassium_channel__E_K = -12 + var_membrane__E_R; // millivolt
            const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 3); // microA_per_cm2
            const double var_sodium_channel__E_Na = 115 + var_membrane__E_R; // millivolt
            const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 1) * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2
            d_dt_chaste_interface_var_membrane__V = (-var_leakage_current__i_L - var_membrane__i_Stim - var_potassium_channel__i_K - var_sodium_channel__i_Na) / NV_Ith_S(mParameters, 0); // millivolt / millisecond
        }
        
        NV_Ith_S(rDY,0) = d_dt_chaste_interface_var_membrane__V;
        NV_Ith_S(rDY,1) = d_dt_chaste_interface_var_sodium_channel_m_gate__m;
        NV_Ith_S(rDY,2) = d_dt_chaste_interface_var_sodium_channel_h_gate__h;
        NV_Ith_S(rDY,3) = d_dt_chaste_interface_var_potassium_channel_n_gate__n;
    }

    N_Vector Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode::ComputeDerivedQuantities(double var_chaste_interface__environment__time, const N_Vector & rY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : NV_Ith_S(rY, 0));
        // Units: millivolt; Initial value: -75.0
        double var_chaste_interface__sodium_channel_m_gate__m = NV_Ith_S(rY, 1);
        // Units: dimensionless; Initial value: 0.05
        double var_chaste_interface__sodium_channel_h_gate__h = NV_Ith_S(rY, 2);
        // Units: dimensionless; Initial value: 0.6
        double var_chaste_interface__potassium_channel_n_gate__n = NV_Ith_S(rY, 3);
        // Units: dimensionless; Initial value: 0.325
        
        // Mathematics
        const double var_membrane__E_R = -75; // millivolt
        const double var_leakage_current__E_L = 10.613 + var_membrane__E_R; // millivolt
        const double var_leakage_current__i_L = (-var_leakage_current__E_L + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 2); // microA_per_cm2
        const double var_membrane__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // microA_per_cm2
        const double var_potassium_channel__E_K = -12 + var_membrane__E_R; // millivolt
        const double var_potassium_channel__i_K = pow(var_chaste_interface__potassium_channel_n_gate__n, 4) * (-var_potassium_channel__E_K + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 3); // microA_per_cm2
        const double var_sodium_channel__E_Na = 115 + var_membrane__E_R; // millivolt
        const double var_sodium_channel__i_Na = pow(var_chaste_interface__sodium_channel_m_gate__m, 3) * (-var_sodium_channel__E_Na + var_chaste_interface__membrane__V) * NV_Ith_S(mParameters, 1) * var_chaste_interface__sodium_channel_h_gate__h; // microA_per_cm2

#if CHASTE_SUNDIALS_VERSION >= 60000
        N_Vector dqs = N_VNew_Serial(5, CvodeContextManager::Instance()->GetSundialsContext());
#else
        N_Vector dqs = N_VNew_Serial(5);
#endif
        NV_Ith_S(dqs, 0) = var_sodium_channel__i_Na;
        NV_Ith_S(dqs, 1) = var_leakage_current__i_L;
        NV_Ith_S(dqs, 2) = var_potassium_channel__i_K;
        NV_Ith_S(dqs, 3) = var_membrane__i_Stim;
        NV_Ith_S(dqs, 4) = var_chaste_interface__environment__time;
        return dqs;
    }

template<>
void OdeSystemInformation<Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode>::Initialise(void)
{
    this->mSystemName = "hodgkin_huxley_squid_axon_model_1952_modified";
    this->mFreeVariableName = "time";
    this->mFreeVariableUnits = "millisecond";

    // NV_Ith_S(rY, 0):
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-75.0);

    // NV_Ith_S(rY, 1):
    this->mVariableNames.push_back("sodium_channel_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.05);

    // NV_Ith_S(rY, 2):
    this->mVariableNames.push_back("sodium_channel_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.6);

    // NV_Ith_S(rY, 3):
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
CHASTE_CLASS_EXPORT(Cellhodgkin_huxley_squid_axon_model_1952_modifiedFromCellMLCvode)

#endif // CHASTE_CVODE
