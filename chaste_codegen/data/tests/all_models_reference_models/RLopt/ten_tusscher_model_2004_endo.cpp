//! @file
//!
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//!
//! Model: tentusscher_model_2004_endo
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: normal)
//! on (date omitted as unimportant)
//!
//! <autogenerated>

#include "ten_tusscher_model_2004_endo.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"



    double Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }
    Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::Cellten_tusscher_model_2004_endoFromCellMLRushLarsen(boost::shared_ptr<AbstractIvpOdeSolver> /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractRushLarsenCardiacCell(
                17,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellten_tusscher_model_2004_endoFromCellMLRushLarsen>::Instance();
        Init();
        
    }

    Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::~Cellten_tusscher_model_2004_endoFromCellMLRushLarsen()
    {
    }
    
    double Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -86.2
        double var_chaste_interface__calcium_dynamics__Ca_i = rY[1];
        // Units: millimolar; Initial value: 0.0002
        double var_chaste_interface__rapid_time_dependent_potassium_current_Xr1_gate__Xr1 = rY[2];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__rapid_time_dependent_potassium_current_Xr2_gate__Xr2 = rY[3];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_time_dependent_potassium_current_Xs_gate__Xs = rY[4];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[5];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[6];
        // Units: dimensionless; Initial value: 0.75
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[7];
        // Units: dimensionless; Initial value: 0.75
        double var_chaste_interface__L_type_Ca_current_d_gate__d = rY[8];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__L_type_Ca_current_f_gate__f = rY[9];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__L_type_Ca_current_fCa_gate__fCa = rY[10];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__transient_outward_current_s_gate__s = rY[11];
        // Units: dimensionless; Initial value: 0.3212
        double var_chaste_interface__transient_outward_current_r_gate__r = rY[12];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__sodium_dynamics__Na_i = rY[15];
        // Units: millimolar; Initial value: 11.6
        double var_chaste_interface__potassium_dynamics__K_i = rY[16];
        // Units: millimolar; Initial value: 138.3
        
        const double var_calcium_pump_current__i_p_Ca = 0.82499999999999996 * var_chaste_interface__calcium_dynamics__Ca_i / (0.00050000000000000001 + var_chaste_interface__calcium_dynamics__Ca_i); // picoA_per_picoF
        const double var_L_type_Ca_current__i_CaL = 2.5282752177944188 * (-0.68200000000000005 + var_chaste_interface__calcium_dynamics__Ca_i * exp(0.074867781645490947 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_current_d_gate__d * var_chaste_interface__L_type_Ca_current_fCa_gate__fCa * var_chaste_interface__L_type_Ca_current_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.074867781645490947 * var_chaste_interface__membrane__V)); // picoA_per_picoF
        const double var_calcium_background_current__i_b_Ca = 0.00059199999999999997 * var_chaste_interface__membrane__V - 0.0079072731552699126 * log(2.0 / var_chaste_interface__calcium_dynamics__Ca_i); // picoA_per_picoF
        const double var_reversal_potentials__E_K = 26.713760659695652 * log(5.4000000000000004 / var_chaste_interface__potassium_dynamics__K_i); // millivolt
        const double var_inward_rectifier_potassium_current__i_K1 = 0.54050000000000009 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) / ((1.0 + exp(-12.0 + 0.059999999999999998 * var_chaste_interface__membrane__V - 0.059999999999999998 * var_reversal_potentials__E_K)) * (0.10000000000000001 / (1.0 + exp(-12.0 + 0.059999999999999998 * var_chaste_interface__membrane__V - 0.059999999999999998 * var_reversal_potentials__E_K)) + (3.0 * exp(0.02 + 0.00020000000000000001 * var_chaste_interface__membrane__V - 0.00020000000000000001 * var_reversal_potentials__E_K) + exp(-1.0 + 0.10000000000000001 * var_chaste_interface__membrane__V - 0.10000000000000001 * var_reversal_potentials__E_K)) / (1.0 + exp(0.5 * var_reversal_potentials__E_K - 0.5 * var_chaste_interface__membrane__V)))); // picoA_per_picoF
        const double var_potassium_pump_current__i_p_K = 0.0146 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) / (1.0 + exp(4.1806020066889626 - 0.16722408026755853 * var_chaste_interface__membrane__V)); // picoA_per_picoF
        const double var_rapid_time_dependent_potassium_current__i_Kr = 0.096000000000000002 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__rapid_time_dependent_potassium_current_Xr1_gate__Xr1 * var_chaste_interface__rapid_time_dependent_potassium_current_Xr2_gate__Xr2; // picoA_per_picoF
        const double var_reversal_potentials__E_Na = 26.713760659695652 * log(140.0 / var_chaste_interface__sodium_dynamics__Na_i); // millivolt
        const double var_fast_sodium_current__i_Na = 14.837999999999999 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // picoA_per_picoF
        const double var_slow_time_dependent_potassium_current__i_Ks = 0.245 * pow(var_chaste_interface__slow_time_dependent_potassium_current_Xs_gate__Xs, 2) * (-26.713760659695652 * log(9.5999999999999996 / (0.029999999999999999 * var_chaste_interface__sodium_dynamics__Na_i + var_chaste_interface__potassium_dynamics__K_i)) + var_chaste_interface__membrane__V); // picoA_per_picoF
        const double var_sodium_background_current__i_b_Na = 0.00029 * var_chaste_interface__membrane__V - 0.00029 * var_reversal_potentials__E_Na; // picoA_per_picoF
        const double var_sodium_calcium_exchanger_current__i_NaCa = 8.6662202299424464e-5 * (2.0 * pow(var_chaste_interface__sodium_dynamics__Na_i, 3) * exp(0.013101861787960915 * var_chaste_interface__membrane__V) - 6860000.0 * var_chaste_interface__calcium_dynamics__Ca_i * exp(-0.024332029034784559 * var_chaste_interface__membrane__V)) / (1.0 + 0.10000000000000001 * exp(-0.024332029034784559 * var_chaste_interface__membrane__V)); // picoA_per_picoF
        const double var_sodium_potassium_pump_current__i_NaK = 1.1491875 * var_chaste_interface__sodium_dynamics__Na_i / ((40.0 + var_chaste_interface__sodium_dynamics__Na_i) * (1.0 + 0.035299999999999998 * exp(-0.037433890822745473 * var_chaste_interface__membrane__V) + 0.1245 * exp(-0.0037433890822745472 * var_chaste_interface__membrane__V))); // picoA_per_picoF
        const double var_transient_outward_current__i_to = 0.072999999999999995 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__transient_outward_current_r_gate__r * var_chaste_interface__transient_outward_current_s_gate__s; // picoA_per_picoF
        const double var_chaste_interface__i_ionic = (var_L_type_Ca_current__i_CaL + var_calcium_background_current__i_b_Ca + var_calcium_pump_current__i_p_Ca + var_fast_sodium_current__i_Na + var_inward_rectifier_potassium_current__i_K1 + var_potassium_pump_current__i_p_K + var_rapid_time_dependent_potassium_current__i_Kr + var_slow_time_dependent_potassium_current__i_Ks + var_sodium_background_current__i_b_Na + var_sodium_calcium_exchanger_current__i_NaCa + var_sodium_potassium_pump_current__i_NaK + var_transient_outward_current__i_to) * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }

    void Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::EvaluateEquations(double var_chaste_interface__environment__time, std::vector<double> &rDY, std::vector<double> &rAlphaOrTau, std::vector<double> &rBetaOrInf)
    {
        std::vector<double>& rY = rGetStateVariables();
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -86.2
        double var_chaste_interface__calcium_dynamics__Ca_i = rY[1];
        // Units: millimolar; Initial value: 0.0002
        double var_chaste_interface__rapid_time_dependent_potassium_current_Xr1_gate__Xr1 = rY[2];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__rapid_time_dependent_potassium_current_Xr2_gate__Xr2 = rY[3];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_time_dependent_potassium_current_Xs_gate__Xs = rY[4];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[5];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[6];
        // Units: dimensionless; Initial value: 0.75
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[7];
        // Units: dimensionless; Initial value: 0.75
        double var_chaste_interface__L_type_Ca_current_d_gate__d = rY[8];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__L_type_Ca_current_f_gate__f = rY[9];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__L_type_Ca_current_fCa_gate__fCa = rY[10];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__transient_outward_current_s_gate__s = rY[11];
        // Units: dimensionless; Initial value: 0.3212
        double var_chaste_interface__transient_outward_current_r_gate__r = rY[12];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__calcium_dynamics__Ca_SR = rY[13];
        // Units: millimolar; Initial value: 0.2
        double var_chaste_interface__calcium_dynamics__g = rY[14];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__sodium_dynamics__Na_i = rY[15];
        // Units: millimolar; Initial value: 11.6
        double var_chaste_interface__potassium_dynamics__K_i = rY[16];
        // Units: millimolar; Initial value: 138.3

        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double var_calcium_dynamics__g_inf = ((var_chaste_interface__calcium_dynamics__Ca_i < 0.00035) ? (1.0 / (1.0 + 5.439910241481016e+20 * pow(var_chaste_interface__calcium_dynamics__Ca_i, 6))) : (1.0 / (1.0 + 1.9720198874049176e+55 * pow(var_chaste_interface__calcium_dynamics__Ca_i, 16)))); // dimensionless
        const double var_L_type_Ca_current_d_gate__d_inf = 1.0 / (1.0 + exp(-0.66666666666666663 - 0.13333333333333333 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_L_type_Ca_current_f_gate__f_inf = 1.0 / (1.0 + exp(2.8571428571428572 + 0.14285714285714285 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_L_type_Ca_current_f_gate__tau_f = 80.0 + 165.0 / (1.0 + exp(2.5 - 0.10000000000000001 * var_chaste_interface__membrane__V)) + 1125.0 * exp(-3.0375000000000001 * pow((1 + 0.037037037037037035 * var_chaste_interface__membrane__V), 2)); // millisecond
        const double var_fast_sodium_current_h_gate__h_inf = 1.0 / pow((1.0 + exp(9.6298788694481825 + 0.13458950201884254 * var_chaste_interface__membrane__V)), 2); // dimensionless
        const double var_fast_sodium_current_j_gate__j_inf = 1.0 / pow((1.0 + exp(9.6298788694481825 + 0.13458950201884254 * var_chaste_interface__membrane__V)), 2); // dimensionless
        const double var_fast_sodium_current_m_gate__m_inf = 1.0 / pow((1.0 + exp(-6.2967884828349945 - 0.11074197120708749 * var_chaste_interface__membrane__V)), 2); // dimensionless
        const double var_rapid_time_dependent_potassium_current_Xr1_gate__xr1_inf = 1.0 / (1.0 + exp(-3.7142857142857144 - 0.14285714285714285 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_rapid_time_dependent_potassium_current_Xr2_gate__xr2_inf = 1.0 / (1.0 + exp(3.6666666666666665 + 0.041666666666666664 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_slow_time_dependent_potassium_current_Xs_gate__xs_inf = 1.0 / (1.0 + exp(-0.35714285714285715 - 0.071428571428571425 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_transient_outward_current_r_gate__r_inf = 1.0 / (1.0 + exp(3.3333333333333335 - 0.16666666666666666 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_transient_outward_current_r_gate__tau_r = 0.80000000000000004 + 9.5 * exp(-0.88888888888888884 * pow((1 + 0.025000000000000001 * var_chaste_interface__membrane__V), 2)); // millisecond

        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            const double var_L_type_Ca_current_fCa_gate__fCa_inf = 0.15753424657534248 + 0.068493150684931517 / (1.0 + exp(-5.0 + 10000.0 * var_chaste_interface__calcium_dynamics__Ca_i)) + 0.13698630136986303 / (1.0 + exp(-0.9375 + 1250.0 * var_chaste_interface__calcium_dynamics__Ca_i)) + 0.68493150684931503 / (1.0 + 8.034023767017109e+27 * pow(var_chaste_interface__calcium_dynamics__Ca_i, 8)); // dimensionless
            const double var_calcium_dynamics__i_leak = 8.0000000000000007e-5 * var_chaste_interface__calcium_dynamics__Ca_SR - 8.0000000000000007e-5 * var_chaste_interface__calcium_dynamics__Ca_i; // millimolar_per_millisecond
            const double var_calcium_dynamics__i_rel = (0.0082319999999999997 + 0.016463999999999999 * pow(var_chaste_interface__calcium_dynamics__Ca_SR, 2) / (0.0625 + pow(var_chaste_interface__calcium_dynamics__Ca_SR, 2))) * var_chaste_interface__L_type_Ca_current_d_gate__d * var_chaste_interface__calcium_dynamics__g; // millimolar_per_millisecond
            const double var_calcium_dynamics__i_up = 0.00042499999999999998 / (1.0 + 6.2499999999999997e-8 / pow(var_chaste_interface__calcium_dynamics__Ca_i, 2)); // millimolar_per_millisecond
            const double var_calcium_pump_current__i_p_Ca = 0.82499999999999996 * var_chaste_interface__calcium_dynamics__Ca_i / (0.00050000000000000001 + var_chaste_interface__calcium_dynamics__Ca_i); // picoA_per_picoF
            const double d_dt_chaste_interface_var_L_type_Ca_current_fCa_gate__fCa = (((var_chaste_interface__membrane__V > -60.0) && (var_chaste_interface__L_type_Ca_current_fCa_gate__fCa < var_L_type_Ca_current_fCa_gate__fCa_inf)) ? (0.0) : (0.5 * var_L_type_Ca_current_fCa_gate__fCa_inf - 0.5 * var_chaste_interface__L_type_Ca_current_fCa_gate__fCa)); // 1 / millisecond
            const double d_dt_chaste_interface_var_calcium_dynamics__g = (((var_chaste_interface__membrane__V > -60.0) && (var_chaste_interface__calcium_dynamics__g < var_calcium_dynamics__g_inf)) ? (0.0) : (0.5 * var_calcium_dynamics__g_inf - 0.5 * var_chaste_interface__calcium_dynamics__g)); // 1 / millisecond
            const double var_L_type_Ca_current__i_CaL = 2.5282752177944188 * (-0.68200000000000005 + var_chaste_interface__calcium_dynamics__Ca_i * exp(0.074867781645490947 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_current_d_gate__d * var_chaste_interface__L_type_Ca_current_fCa_gate__fCa * var_chaste_interface__L_type_Ca_current_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.074867781645490947 * var_chaste_interface__membrane__V)); // picoA_per_picoF
            const double var_L_type_Ca_current_d_gate__tau_d = 1.0 / (1.0 + exp(2.5 - 0.050000000000000003 * var_chaste_interface__membrane__V)) + 1.3999999999999999 * (0.25 + 1.3999999999999999 / (1.0 + exp(-2.6923076923076925 - 0.076923076923076927 * var_chaste_interface__membrane__V))) / (1.0 + exp(1.0 + 0.20000000000000001 * var_chaste_interface__membrane__V)); // millisecond
            const double var_fast_sodium_current_h_gate__tau_h = ((var_chaste_interface__membrane__V < -40.0) ? (1.0 / (310000.0 * exp(0.34849999999999998 * var_chaste_interface__membrane__V) + 2.7000000000000002 * exp(0.079000000000000001 * var_chaste_interface__membrane__V) + 0.057000000000000002 * exp(-11.764705882352942 - 0.14705882352941177 * var_chaste_interface__membrane__V))) : (0.16883116883116883 + 0.16883116883116883 * exp(-0.96036036036036043 - 0.0900900900900901 * var_chaste_interface__membrane__V))); // millisecond
            const double var_fast_sodium_current_j_gate__tau_j = ((var_chaste_interface__membrane__V < -40.0) ? (1.0 / (0.024240000000000001 * exp(-0.01052 * var_chaste_interface__membrane__V) / (1.0 + exp(-5.5312920000000005 - 0.13780000000000001 * var_chaste_interface__membrane__V)) + 1.0 * (37.780000000000001 + var_chaste_interface__membrane__V) * (-25428.0 * exp(0.24440000000000001 * var_chaste_interface__membrane__V) - 6.9480000000000002e-6 * exp(-0.043909999999999998 * var_chaste_interface__membrane__V)) / (1.0 + exp(24.640530000000002 + 0.311 * var_chaste_interface__membrane__V)))) : (1.6666666666666667 * (1.0 + exp(-3.2000000000000002 - 0.10000000000000001 * var_chaste_interface__membrane__V)) / exp(0.057000000000000002 * var_chaste_interface__membrane__V))); // millisecond
            const double var_fast_sodium_current_m_gate__tau_m = 1.0 * (0.10000000000000001 / (1.0 + exp(7.0 + 0.20000000000000001 * var_chaste_interface__membrane__V)) + 0.10000000000000001 / (1.0 + exp(-0.25 + 0.0050000000000000001 * var_chaste_interface__membrane__V))) / (1.0 + exp(-12.0 - 0.20000000000000001 * var_chaste_interface__membrane__V)); // millisecond
            const double d_dt_chaste_interface_var_calcium_dynamics__Ca_SR = 14.994515539305301 * (-var_calcium_dynamics__i_leak - var_calcium_dynamics__i_rel + var_calcium_dynamics__i_up) / (1.0 + 3.0 / pow((0.29999999999999999 + var_chaste_interface__calcium_dynamics__Ca_SR), 2)); // millimolar / millisecond
            const double var_membrane__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time) / HeartConfig::Instance()->GetCapacitance(); // picoA_per_picoF
            const double var_rapid_time_dependent_potassium_current_Xr1_gate__tau_xr1 = 2700.0 / ((1.0 + exp(2.6086956521739131 + 0.086956521739130432 * var_chaste_interface__membrane__V)) * (1.0 + exp(-4.5 - 0.10000000000000001 * var_chaste_interface__membrane__V))); // millisecond
            const double var_rapid_time_dependent_potassium_current_Xr2_gate__tau_xr2 = 3.3600000000000003 / ((1.0 + exp(-3.0 + 0.050000000000000003 * var_chaste_interface__membrane__V)) * (1.0 + exp(-3.0 - 0.050000000000000003 * var_chaste_interface__membrane__V))); // millisecond
            const double var_calcium_background_current__i_b_Ca = 0.00059199999999999997 * var_chaste_interface__membrane__V - 0.0079072731552699126 * log(2.0 / var_chaste_interface__calcium_dynamics__Ca_i); // picoA_per_picoF
            const double var_reversal_potentials__E_K = 26.713760659695652 * log(5.4000000000000004 / var_chaste_interface__potassium_dynamics__K_i); // millivolt
            const double var_inward_rectifier_potassium_current__i_K1 = 0.54050000000000009 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) / ((1.0 + exp(-12.0 + 0.059999999999999998 * var_chaste_interface__membrane__V - 0.059999999999999998 * var_reversal_potentials__E_K)) * (0.10000000000000001 / (1.0 + exp(-12.0 + 0.059999999999999998 * var_chaste_interface__membrane__V - 0.059999999999999998 * var_reversal_potentials__E_K)) + (3.0 * exp(0.02 + 0.00020000000000000001 * var_chaste_interface__membrane__V - 0.00020000000000000001 * var_reversal_potentials__E_K) + exp(-1.0 + 0.10000000000000001 * var_chaste_interface__membrane__V - 0.10000000000000001 * var_reversal_potentials__E_K)) / (1.0 + exp(0.5 * var_reversal_potentials__E_K - 0.5 * var_chaste_interface__membrane__V)))); // picoA_per_picoF
            const double var_potassium_pump_current__i_p_K = 0.0146 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) / (1.0 + exp(4.1806020066889626 - 0.16722408026755853 * var_chaste_interface__membrane__V)); // picoA_per_picoF
            const double var_rapid_time_dependent_potassium_current__i_Kr = 0.096000000000000002 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__rapid_time_dependent_potassium_current_Xr1_gate__Xr1 * var_chaste_interface__rapid_time_dependent_potassium_current_Xr2_gate__Xr2; // picoA_per_picoF
            const double var_slow_time_dependent_potassium_current_Xs_gate__tau_xs = 1100.0 / ((1.0 + exp(-3.0 + 0.050000000000000003 * var_chaste_interface__membrane__V)) * sqrt(1.0 + exp(-1.6666666666666667 - 0.16666666666666666 * var_chaste_interface__membrane__V))); // millisecond
            const double var_reversal_potentials__E_Na = 26.713760659695652 * log(140.0 / var_chaste_interface__sodium_dynamics__Na_i); // millivolt
            const double var_fast_sodium_current__i_Na = 14.837999999999999 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // picoA_per_picoF
            const double var_slow_time_dependent_potassium_current__i_Ks = 0.245 * pow(var_chaste_interface__slow_time_dependent_potassium_current_Xs_gate__Xs, 2) * (-26.713760659695652 * log(9.5999999999999996 / (0.029999999999999999 * var_chaste_interface__sodium_dynamics__Na_i + var_chaste_interface__potassium_dynamics__K_i)) + var_chaste_interface__membrane__V); // picoA_per_picoF
            const double var_sodium_background_current__i_b_Na = 0.00029 * var_chaste_interface__membrane__V - 0.00029 * var_reversal_potentials__E_Na; // picoA_per_picoF
            const double var_sodium_calcium_exchanger_current__i_NaCa = 8.6662202299424464e-5 * (2.0 * pow(var_chaste_interface__sodium_dynamics__Na_i, 3) * exp(0.013101861787960915 * var_chaste_interface__membrane__V) - 6860000.0 * var_chaste_interface__calcium_dynamics__Ca_i * exp(-0.024332029034784559 * var_chaste_interface__membrane__V)) / (1.0 + 0.10000000000000001 * exp(-0.024332029034784559 * var_chaste_interface__membrane__V)); // picoA_per_picoF
            const double d_dt_chaste_interface_var_calcium_dynamics__Ca_i = 1.0 * (-var_calcium_dynamics__i_up + 0.00011688549744401942 * var_sodium_calcium_exchanger_current__i_NaCa - 5.8442748722009712e-5 * var_L_type_Ca_current__i_CaL - 5.8442748722009712e-5 * var_calcium_background_current__i_b_Ca - 5.8442748722009712e-5 * var_calcium_pump_current__i_p_Ca + var_calcium_dynamics__i_leak + var_calcium_dynamics__i_rel) / (1.0 + 0.00014999999999999999 / pow((0.001 + var_chaste_interface__calcium_dynamics__Ca_i), 2)); // millimolar / millisecond
            const double var_sodium_potassium_pump_current__i_NaK = 1.1491875 * var_chaste_interface__sodium_dynamics__Na_i / ((40.0 + var_chaste_interface__sodium_dynamics__Na_i) * (1.0 + 0.035299999999999998 * exp(-0.037433890822745473 * var_chaste_interface__membrane__V) + 0.1245 * exp(-0.0037433890822745472 * var_chaste_interface__membrane__V))); // picoA_per_picoF
            const double d_dt_chaste_interface_var_sodium_dynamics__Na_i = -0.00035065649233205829 * var_sodium_calcium_exchanger_current__i_NaCa - 0.00035065649233205829 * var_sodium_potassium_pump_current__i_NaK - 0.00011688549744401942 * var_fast_sodium_current__i_Na - 0.00011688549744401942 * var_sodium_background_current__i_b_Na; // millimolar / millisecond
            const double var_transient_outward_current__i_to = 0.072999999999999995 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__transient_outward_current_r_gate__r * var_chaste_interface__transient_outward_current_s_gate__s; // picoA_per_picoF
            d_dt_chaste_interface_var_membrane__V = -var_L_type_Ca_current__i_CaL - var_calcium_background_current__i_b_Ca - var_calcium_pump_current__i_p_Ca - var_fast_sodium_current__i_Na - var_inward_rectifier_potassium_current__i_K1 - var_membrane__i_Stim - var_potassium_pump_current__i_p_K - var_rapid_time_dependent_potassium_current__i_Kr - var_slow_time_dependent_potassium_current__i_Ks - var_sodium_background_current__i_b_Na - var_sodium_calcium_exchanger_current__i_NaCa - var_sodium_potassium_pump_current__i_NaK - var_transient_outward_current__i_to; // millivolt / millisecond
            const double d_dt_chaste_interface_var_potassium_dynamics__K_i = 0.00023377099488803885 * var_sodium_potassium_pump_current__i_NaK - 0.00011688549744401942 * var_inward_rectifier_potassium_current__i_K1 - 0.00011688549744401942 * var_membrane__i_Stim - 0.00011688549744401942 * var_potassium_pump_current__i_p_K - 0.00011688549744401942 * var_rapid_time_dependent_potassium_current__i_Kr - 0.00011688549744401942 * var_slow_time_dependent_potassium_current__i_Ks - 0.00011688549744401942 * var_transient_outward_current__i_to; // millimolar / millisecond
            const double var_transient_outward_current_s_gate__s_inf = 1.0 / (1.0 + exp(5.5999999999999996 + 0.20000000000000001 * var_chaste_interface__membrane__V)); // dimensionless
            const double var_transient_outward_current_s_gate__tau_s = 8.0 + 1000.0 * exp(-4.4889999999999999 * pow((1 + 0.014925373134328358 * var_chaste_interface__membrane__V), 2)); // millisecond
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V;
        rDY[1] = d_dt_chaste_interface_var_calcium_dynamics__Ca_i;
        rAlphaOrTau[2] = var_rapid_time_dependent_potassium_current_Xr1_gate__tau_xr1;
        rBetaOrInf[2] = var_rapid_time_dependent_potassium_current_Xr1_gate__xr1_inf;
        rAlphaOrTau[3] = var_rapid_time_dependent_potassium_current_Xr2_gate__tau_xr2;
        rBetaOrInf[3] = var_rapid_time_dependent_potassium_current_Xr2_gate__xr2_inf;
        rAlphaOrTau[4] = var_slow_time_dependent_potassium_current_Xs_gate__tau_xs;
        rBetaOrInf[4] = var_slow_time_dependent_potassium_current_Xs_gate__xs_inf;
        rAlphaOrTau[5] = var_fast_sodium_current_m_gate__tau_m;
        rBetaOrInf[5] = var_fast_sodium_current_m_gate__m_inf;
        rAlphaOrTau[6] = var_fast_sodium_current_h_gate__tau_h;
        rBetaOrInf[6] = var_fast_sodium_current_h_gate__h_inf;
        rAlphaOrTau[7] = var_fast_sodium_current_j_gate__tau_j;
        rBetaOrInf[7] = var_fast_sodium_current_j_gate__j_inf;
        rAlphaOrTau[8] = var_L_type_Ca_current_d_gate__tau_d;
        rBetaOrInf[8] = var_L_type_Ca_current_d_gate__d_inf;
        rAlphaOrTau[9] = var_L_type_Ca_current_f_gate__tau_f;
        rBetaOrInf[9] = var_L_type_Ca_current_f_gate__f_inf;
        rDY[10] = d_dt_chaste_interface_var_L_type_Ca_current_fCa_gate__fCa;
        rAlphaOrTau[11] = var_transient_outward_current_s_gate__tau_s;
        rBetaOrInf[11] = var_transient_outward_current_s_gate__s_inf;
        rAlphaOrTau[12] = var_transient_outward_current_r_gate__tau_r;
        rBetaOrInf[12] = var_transient_outward_current_r_gate__r_inf;
        rDY[13] = d_dt_chaste_interface_var_calcium_dynamics__Ca_SR;
        rDY[14] = d_dt_chaste_interface_var_calcium_dynamics__g;
        rDY[15] = d_dt_chaste_interface_var_sodium_dynamics__Na_i;
        rDY[16] = d_dt_chaste_interface_var_potassium_dynamics__K_i;
    }
    void Cellten_tusscher_model_2004_endoFromCellMLRushLarsen::ComputeOneStepExceptVoltage(const std::vector<double> &rDY, const std::vector<double> &rAlphaOrTau, const std::vector<double> &rBetaOrInf)
    {
        std::vector<double>& rY = rGetStateVariables();
        
        rY[1] += mDt * rDY[1];
        rY[2] = rBetaOrInf[2] + (rY[2] - rBetaOrInf[2])*exp(-mDt/rAlphaOrTau[2]);
        rY[3] = rBetaOrInf[3] + (rY[3] - rBetaOrInf[3])*exp(-mDt/rAlphaOrTau[3]);
        rY[4] = rBetaOrInf[4] + (rY[4] - rBetaOrInf[4])*exp(-mDt/rAlphaOrTau[4]);
        rY[5] = rBetaOrInf[5] + (rY[5] - rBetaOrInf[5])*exp(-mDt/rAlphaOrTau[5]);
        rY[6] = rBetaOrInf[6] + (rY[6] - rBetaOrInf[6])*exp(-mDt/rAlphaOrTau[6]);
        rY[7] = rBetaOrInf[7] + (rY[7] - rBetaOrInf[7])*exp(-mDt/rAlphaOrTau[7]);
        rY[8] = rBetaOrInf[8] + (rY[8] - rBetaOrInf[8])*exp(-mDt/rAlphaOrTau[8]);
        rY[9] = rBetaOrInf[9] + (rY[9] - rBetaOrInf[9])*exp(-mDt/rAlphaOrTau[9]);
        rY[10] += mDt * rDY[10];
        rY[11] = rBetaOrInf[11] + (rY[11] - rBetaOrInf[11])*exp(-mDt/rAlphaOrTau[11]);
        rY[12] = rBetaOrInf[12] + (rY[12] - rBetaOrInf[12])*exp(-mDt/rAlphaOrTau[12]);
        rY[13] += mDt * rDY[13];
        rY[14] += mDt * rDY[14];
        rY[15] += mDt * rDY[15];
        rY[16] += mDt * rDY[16];
    }

template<>
void OdeSystemInformation<Cellten_tusscher_model_2004_endoFromCellMLRushLarsen>::Initialise(void)
{
    this->mSystemName = "tentusscher_model_2004_endo";
    this->mFreeVariableName = "environment__time";
    this->mFreeVariableUnits = "millisecond";

    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-86.2);

    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.0002);

    // rY[2]:
    this->mVariableNames.push_back("rapid_time_dependent_potassium_current_Xr1_gate__Xr1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // rY[3]:
    this->mVariableNames.push_back("rapid_time_dependent_potassium_current_Xr2_gate__Xr2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[4]:
    this->mVariableNames.push_back("slow_time_dependent_potassium_current_Xs_gate__Xs");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // rY[5]:
    this->mVariableNames.push_back("fast_sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // rY[6]:
    this->mVariableNames.push_back("fast_sodium_current_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.75);

    // rY[7]:
    this->mVariableNames.push_back("fast_sodium_current_j_gate__j");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.75);

    // rY[8]:
    this->mVariableNames.push_back("L_type_Ca_current_d_gate__d");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // rY[9]:
    this->mVariableNames.push_back("L_type_Ca_current_f_gate__f");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[10]:
    this->mVariableNames.push_back("L_type_Ca_current_fCa_gate__fCa");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[11]:
    this->mVariableNames.push_back("transient_outward_current_s_gate__s");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.3212);

    // rY[12]:
    this->mVariableNames.push_back("transient_outward_current_r_gate__r");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // rY[13]:
    this->mVariableNames.push_back("calcium_dynamics__Ca_SR");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.2);

    // rY[14]:
    this->mVariableNames.push_back("calcium_dynamics__g");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[15]:
    this->mVariableNames.push_back("sodium_dynamics__Na_i");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(11.6);

    // rY[16]:
    this->mVariableNames.push_back("potassium_dynamics__K_i");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(138.3);

    
    this->mAttributes["SuggestedForwardEulerTimestep"] = 0.001;
    this->mInitialised = true;
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellten_tusscher_model_2004_endoFromCellMLRushLarsen)
