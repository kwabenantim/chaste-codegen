//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: luo_rudy_1994
//! 
//! Processed by weblab_cg: https://github.com/ModellingWebLab/weblab-cg
//!     (translator: weblab_cg, model type: normal, options: )
//! on 2020-01-29 22:57:44
//! 
//! <autogenerated>

#include "luo_rudy_1994.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

    boost::shared_ptr<RegularStimulus> Cellluo_rudy_1994FromCellML::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__membrane__stimCurrent = 50.0; // uA_per_cm2
        const double var_chaste_interface__membrane__stimDuration = 0.5; // millisecond
        const double var_chaste_interface__membrane__stimPeriod = 1000.0; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__membrane__stimCurrent),
                var_chaste_interface__membrane__stimDuration,
                var_chaste_interface__membrane__stimPeriod,
                0.0
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }
    
    double Cellluo_rudy_1994FromCellML::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }
    
    Cellluo_rudy_1994FromCellML::Cellluo_rudy_1994FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                12,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellluo_rudy_1994FromCellML>::Instance();
        Init();
        
        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
    }
    
    Cellluo_rudy_1994FromCellML::~Cellluo_rudy_1994FromCellML()
    {
    }

    double Cellluo_rudy_1994FromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -84.624
        double var_chaste_interface__ionic_concentrations__Cai_converted = rY[1];
        // Units: millimolar; Initial value: 0.00012
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[2];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[3];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[4];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__L_type_Ca_channel_d_gate__d = rY[5];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__L_type_Ca_channel_f_gate__f = rY[6];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__time_dependent_potassium_current_X_gate__X = rY[7];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__ionic_concentrations__Nai = rY[8];
        // Units: mM; Initial value: 10.0
        double var_chaste_interface__ionic_concentrations__Ki = rY[9];
        // Units: mM; Initial value: 145.0
        
        const double var_ionic_concentrations__Cai = 1.0 * var_chaste_interface__ionic_concentrations__Cai_converted; // mM
        const double var_L_type_Ca_channel_f_Ca_gate__f_Ca = 1.0 / (1.0 + 2777777.777777778 * pow(var_ionic_concentrations__Cai, 2.0)); // dimensionless
        const double var_fast_sodium_current__E_Na = 26.614641953637257 * log(140.0 / var_chaste_interface__ionic_concentrations__Nai); // mV
        const double var_L_type_Ca_channel__i_Ca_L = 7.0228579563684895e-06 * (-4.050000000000001 + 0.75 * var_chaste_interface__ionic_concentrations__Ki * exp(0.03757330276101408 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757330276101408 * var_chaste_interface__membrane__V)) + 0.07859778852723283 * (-0.6120000000000001 + 1.0 * var_ionic_concentrations__Cai * exp(0.07514660552202816 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.07514660552202816 * var_chaste_interface__membrane__V)) + 2.4561808914760263e-05 * (-105.0 + 0.75 * var_chaste_interface__ionic_concentrations__Nai * exp(0.03757330276101408 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757330276101408 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_Na_Ca_exchanger__i_NaCa = 1.8422531054846208e-06 * (1.8 * pow(var_chaste_interface__ionic_concentrations__Nai, 3.0) * exp(0.013150655966354929 * var_chaste_interface__membrane__V) - 2744000.0 * var_ionic_concentrations__Cai * exp(-0.024422646794659154 * var_chaste_interface__membrane__V)) / (1.0 + 0.1 * exp(-0.024422646794659154 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_calcium_background_current__i_Ca_b = 3.016e-05 * var_chaste_interface__membrane__V - 0.00040134880066084984 * log(1.8 / var_ionic_concentrations__Cai); // uA_per_mm2
        const double var_fast_sodium_current__i_Na = 0.16 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_fast_sodium_current__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // uA_per_mm2
        const double var_non_specific_calcium_activated_current__Vns = -26.614641953637257 * log(145.4 / (var_chaste_interface__ionic_concentrations__Ki + var_chaste_interface__ionic_concentrations__Nai)) + var_chaste_interface__membrane__V; // mV
        const double var_non_specific_calcium_activated_current__i_ns_Ca = 6.3678763853082165e-06 * (-105.0 + 0.75 * var_chaste_interface__ionic_concentrations__Nai * exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns)) * var_non_specific_calcium_activated_current__Vns / ((1.0 + 1.7279999999999996e-09 * pow(1 / var_ionic_concentrations__Cai, 3.0)) * (-1.0 + exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns))) + 6.3678763853082165e-06 * (-4.050000000000001 + 0.75 * var_chaste_interface__ionic_concentrations__Ki * exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns)) * var_non_specific_calcium_activated_current__Vns / ((1.0 + 1.7279999999999996e-09 * pow(1 / var_ionic_concentrations__Cai, 3.0)) * (-1.0 + exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns))); // uA_per_mm2
        const double var_sarcolemmal_calcium_pump__i_p_Ca = 0.0115 * var_ionic_concentrations__Cai / (0.0005 + var_ionic_concentrations__Cai); // uA_per_mm2
        const double var_sodium_background_current__i_Na_b = 1.41e-05 * var_chaste_interface__membrane__V - 1.41e-05 * var_fast_sodium_current__E_Na; // uA_per_mm2
        const double var_sodium_potassium_pump__i_NaK = 0.01173913043478261 / ((1.0 + 31.622776601683793 * pow(1 / var_chaste_interface__ionic_concentrations__Nai, 1.5)) * (1.0 + 0.1245 * exp(-0.003757330276101409 * var_chaste_interface__membrane__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.03757330276101408 * var_chaste_interface__membrane__V))); // uA_per_mm2
        const double var_time_dependent_potassium_current__i_K = 0.00282 * pow(var_chaste_interface__time_dependent_potassium_current_X_gate__X, 2.0) * (-26.614641953637257 * log(7.966200000000001 / (0.01833 * var_chaste_interface__ionic_concentrations__Nai + var_chaste_interface__ionic_concentrations__Ki)) + var_chaste_interface__membrane__V) / (1.0 + exp(-1.7526479750778816 + 0.03115264797507788 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_time_independent_potassium_current__E_K1 = 26.614641953637257 * log(5.4 / var_chaste_interface__ionic_concentrations__Ki); // mV
        const double var_plateau_potassium_current__i_Kp = 0.000183 * (-var_time_independent_potassium_current__E_K1 + var_chaste_interface__membrane__V) / (1.0 + exp(1.2521739130434784 - 0.16722408026755853 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_time_independent_potassium_current__i_K1 = 0.00765 * (-var_time_independent_potassium_current__E_K1 + var_chaste_interface__membrane__V) / ((1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__membrane__V - 0.2385 * var_time_independent_potassium_current__E_K1)) * (1.02 / (1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__membrane__V - 0.2385 * var_time_independent_potassium_current__E_K1)) + (0.49124 * exp(0.43983232 + 0.08032 * var_chaste_interface__membrane__V - 0.08032 * var_time_independent_potassium_current__E_K1) + exp(-36.6986425 + 0.06175 * var_chaste_interface__membrane__V - 0.06175 * var_time_independent_potassium_current__E_K1)) / (1.0 + exp(-2.4444679 + 0.5143 * var_time_independent_potassium_current__E_K1 - 0.5143 * var_chaste_interface__membrane__V)))); // uA_per_mm2
        const double var_chaste_interface__i_ionic = 100.0 * var_L_type_Ca_channel__i_Ca_L + 100.0 * var_Na_Ca_exchanger__i_NaCa + 100.0 * var_calcium_background_current__i_Ca_b + 100.0 * var_fast_sodium_current__i_Na + 100.0 * var_non_specific_calcium_activated_current__i_ns_Ca + 100.0 * var_plateau_potassium_current__i_Kp + 100.0 * var_sarcolemmal_calcium_pump__i_p_Ca + 100.0 * var_sodium_background_current__i_Na_b + 100.0 * var_sodium_potassium_pump__i_NaK + 100.0 * var_time_dependent_potassium_current__i_K + 100.0 * var_time_independent_potassium_current__i_K1; // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Cellluo_rudy_1994FromCellML::EvaluateYDerivatives(double var_chaste_interface__environment__time, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -84.624
        double var_chaste_interface__ionic_concentrations__Cai_converted = rY[1];
        // Units: millimolar; Initial value: 0.00012
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[2];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[3];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[4];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__L_type_Ca_channel_d_gate__d = rY[5];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__L_type_Ca_channel_f_gate__f = rY[6];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__time_dependent_potassium_current_X_gate__X = rY[7];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__ionic_concentrations__Nai = rY[8];
        // Units: mM; Initial value: 10.0
        double var_chaste_interface__ionic_concentrations__Ki = rY[9];
        // Units: mM; Initial value: 145.0
        double var_chaste_interface__ionic_concentrations__Ca_JSR = rY[10];
        // Units: mM; Initial value: 1.8
        double var_chaste_interface__ionic_concentrations__Ca_NSR = rY[11];
        // Units: mM; Initial value: 1.8
        
        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double var_calcium_fluxes_in_the_SR__i_leak = 0.0003333333333333333 * var_chaste_interface__ionic_concentrations__Ca_NSR; // mM_per_ms
        const double var_calcium_fluxes_in_the_SR__i_tr = 0.005555555555555556 * var_chaste_interface__ionic_concentrations__Ca_NSR - 0.005555555555555556 * var_chaste_interface__ionic_concentrations__Ca_JSR; // mM_per_ms
        const double var_ionic_concentrations__Cai = 1.0 * var_chaste_interface__ionic_concentrations__Cai_converted; // mM
        const double var_L_type_Ca_channel_f_Ca_gate__f_Ca = 1.0 / (1.0 + 2777777.777777778 * pow(var_ionic_concentrations__Cai, 2.0)); // dimensionless
        const double var_calcium_fluxes_in_the_SR__i_rel = 0; // mM_per_ms
        const double var_calcium_fluxes_in_the_SR__i_up = 0.005 * var_ionic_concentrations__Cai / (0.00092 + var_ionic_concentrations__Cai); // mM_per_ms
        const double d_dt_chaste_interface_var_ionic_concentrations__Ca_NSR = -var_calcium_fluxes_in_the_SR__i_leak - var_calcium_fluxes_in_the_SR__i_tr + var_calcium_fluxes_in_the_SR__i_up; // mM / ms
        const double d_dt_chaste_interface_var_ionic_concentrations__Ca_JSR = -var_calcium_fluxes_in_the_SR__i_rel + 11.5 * var_calcium_fluxes_in_the_SR__i_tr; // mM / ms
        const double var_fast_sodium_current__E_Na = 26.614641953637257 * log(140.0 / var_chaste_interface__ionic_concentrations__Nai); // mV
        const double var_L_type_Ca_channel__i_CaCa = 0.07859778852723283 * (-0.6120000000000001 + 1.0 * var_ionic_concentrations__Cai * exp(0.07514660552202816 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.07514660552202816 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_L_type_Ca_channel__i_CaK = 7.0228579563684895e-06 * (-4.050000000000001 + 0.75 * var_chaste_interface__ionic_concentrations__Ki * exp(0.03757330276101408 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757330276101408 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_L_type_Ca_channel__i_CaNa = 2.4561808914760263e-05 * (-105.0 + 0.75 * var_chaste_interface__ionic_concentrations__Nai * exp(0.03757330276101408 * var_chaste_interface__membrane__V)) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757330276101408 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_L_type_Ca_channel_d_gate__d_infinity = 1.0 / (1.0 + exp(-1.6025641025641024 - 0.16025641025641024 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_L_type_Ca_channel_d_gate__tau_d = 28.57142857142857 * (1.0 - exp(-1.6025641025641024 - 0.16025641025641024 * var_chaste_interface__membrane__V)) * var_L_type_Ca_channel_d_gate__d_infinity / (10.0 + var_chaste_interface__membrane__V); // ms
        const double d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d = (1.0 - var_chaste_interface__L_type_Ca_channel_d_gate__d) * var_L_type_Ca_channel_d_gate__d_infinity / var_L_type_Ca_channel_d_gate__tau_d - (1.0 - var_L_type_Ca_channel_d_gate__d_infinity) * var_chaste_interface__L_type_Ca_channel_d_gate__d / var_L_type_Ca_channel_d_gate__tau_d; // 1 / ms
        const double var_L_type_Ca_channel_f_gate__f_infinity = 1.0 / (1.0 + exp(4.076744186046512 + 0.11627906976744186 * var_chaste_interface__membrane__V)) + 0.6 / (1.0 + exp(2.5 - 0.05 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_L_type_Ca_channel_f_gate__tau_f = 1.0 / (0.02 + 0.0197 * exp(-0.11356900000000002 * pow((1 + 0.09999999999999999 * var_chaste_interface__membrane__V), 2.0))); // ms
        const double d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f = (1.0 - var_chaste_interface__L_type_Ca_channel_f_gate__f) * var_L_type_Ca_channel_f_gate__f_infinity / var_L_type_Ca_channel_f_gate__tau_f - (1.0 - var_L_type_Ca_channel_f_gate__f_infinity) * var_chaste_interface__L_type_Ca_channel_f_gate__f / var_L_type_Ca_channel_f_gate__tau_f; // 1 / ms
        const double var_Na_Ca_exchanger__i_NaCa = 1.8422531054846208e-06 * (1.8 * pow(var_chaste_interface__ionic_concentrations__Nai, 3.0) * exp(0.013150655966354929 * var_chaste_interface__membrane__V) - 2744000.0 * var_ionic_concentrations__Cai * exp(-0.024422646794659154 * var_chaste_interface__membrane__V)) / (1.0 + 0.1 * exp(-0.024422646794659154 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_calcium_background_current__i_Ca_b = 3.016e-05 * var_chaste_interface__membrane__V - 0.00040134880066084984 * log(1.8 / var_ionic_concentrations__Cai); // uA_per_mm2
        const double var_fast_sodium_current__i_Na = 0.16 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_fast_sodium_current__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // uA_per_mm2
        const double d_dt_chaste_interface_var_fast_sodium_current_h_gate__h = (1.0 - var_chaste_interface__fast_sodium_current_h_gate__h) * ((var_chaste_interface__membrane__V < -40.0) ? (0.135 * exp(-11.764705882352942 - 0.14705882352941177 * var_chaste_interface__membrane__V)) : (0.0)) - ((var_chaste_interface__membrane__V < -40.0) ? (310000.0 * exp(0.35 * var_chaste_interface__membrane__V) + 3.56 * exp(0.079 * var_chaste_interface__membrane__V)) : (7.692307692307692 / (1.0 + exp(-0.9603603603603604 - 0.0900900900900901 * var_chaste_interface__membrane__V)))) * var_chaste_interface__fast_sodium_current_h_gate__h; // 1 / ms
        const double d_dt_chaste_interface_var_fast_sodium_current_j_gate__j = (1.0 - var_chaste_interface__fast_sodium_current_j_gate__j) * ((var_chaste_interface__membrane__V < -40.0) ? ((37.78 + var_chaste_interface__membrane__V) * (-127140.0 * exp(0.2444 * var_chaste_interface__membrane__V) - 3.474e-05 * exp(-0.04391 * var_chaste_interface__membrane__V)) / (1.0 + exp(24.640530000000002 + 0.311 * var_chaste_interface__membrane__V))) : (0.0)) - ((var_chaste_interface__membrane__V < -40.0) ? (0.1212 * exp(-0.01052 * var_chaste_interface__membrane__V) / (1.0 + exp(-5.5312920000000005 - 0.1378 * var_chaste_interface__membrane__V))) : (0.3 * exp(-2.535e-07 * var_chaste_interface__membrane__V) / (1.0 + exp(-3.2 - 0.1 * var_chaste_interface__membrane__V)))) * var_chaste_interface__fast_sodium_current_j_gate__j; // 1 / ms
        const double d_dt_chaste_interface_var_fast_sodium_current_m_gate__m = -0.08 * var_chaste_interface__fast_sodium_current_m_gate__m * exp(-0.09090909090909091 * var_chaste_interface__membrane__V) + 0.32 * (1.0 - var_chaste_interface__fast_sodium_current_m_gate__m) * (47.13 + var_chaste_interface__membrane__V) / (1.0 - exp(-4.713 - 0.1 * var_chaste_interface__membrane__V)); // 1 / ms
        const double var_non_specific_calcium_activated_current__Vns = -26.614641953637257 * log(145.4 / (var_chaste_interface__ionic_concentrations__Ki + var_chaste_interface__ionic_concentrations__Nai)) + var_chaste_interface__membrane__V; // mV
        const double var_non_specific_calcium_activated_current__i_ns_K = 6.3678763853082165e-06 * (-4.050000000000001 + 0.75 * var_chaste_interface__ionic_concentrations__Ki * exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns)) * var_non_specific_calcium_activated_current__Vns / ((1.0 + 1.7279999999999996e-09 * pow(1 / var_ionic_concentrations__Cai, 3.0)) * (-1.0 + exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns))); // uA_per_mm2
        const double var_non_specific_calcium_activated_current__i_ns_Na = 6.3678763853082165e-06 * (-105.0 + 0.75 * var_chaste_interface__ionic_concentrations__Nai * exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns)) * var_non_specific_calcium_activated_current__Vns / ((1.0 + 1.7279999999999996e-09 * pow(1 / var_ionic_concentrations__Cai, 3.0)) * (-1.0 + exp(0.03757330276101408 * var_non_specific_calcium_activated_current__Vns))); // uA_per_mm2
        const double var_sarcolemmal_calcium_pump__i_p_Ca = 0.0115 * var_ionic_concentrations__Cai / (0.0005 + var_ionic_concentrations__Cai); // uA_per_mm2
        const double d_dt_chaste_interface_var_ionic_concentrations__Cai_converted = 0.007058823529411763 * var_calcium_fluxes_in_the_SR__i_rel + 0.0015184968096382027 * var_Na_Ca_exchanger__i_NaCa + 0.08117647058823528 * var_calcium_fluxes_in_the_SR__i_leak - 0.0015184968096382027 * var_L_type_Ca_channel__i_CaCa - 0.0015184968096382027 * var_calcium_background_current__i_Ca_b - 0.0015184968096382027 * var_sarcolemmal_calcium_pump__i_p_Ca - 0.08117647058823528 * var_calcium_fluxes_in_the_SR__i_up; // millimolar / ms
        const double var_sodium_background_current__i_Na_b = 1.41e-05 * var_chaste_interface__membrane__V - 1.41e-05 * var_fast_sodium_current__E_Na; // uA_per_mm2
        const double var_sodium_potassium_pump__i_NaK = 0.01173913043478261 / ((1.0 + 31.622776601683793 * pow(1 / var_chaste_interface__ionic_concentrations__Nai, 1.5)) * (1.0 + 0.1245 * exp(-0.003757330276101409 * var_chaste_interface__membrane__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.03757330276101408 * var_chaste_interface__membrane__V))); // uA_per_mm2
        const double d_dt_chaste_interface_var_ionic_concentrations__Nai = -0.009110980857829215 * var_Na_Ca_exchanger__i_NaCa - 0.009110980857829215 * var_sodium_potassium_pump__i_NaK - 0.0030369936192764053 * var_L_type_Ca_channel__i_CaNa - 0.0030369936192764053 * var_fast_sodium_current__i_Na - 0.0030369936192764053 * var_non_specific_calcium_activated_current__i_ns_Na - 0.0030369936192764053 * var_sodium_background_current__i_Na_b; // mM / ms
        const double d_dt_chaste_interface_var_time_dependent_potassium_current_X_gate__X = 7.19e-05 * (1.0 - var_chaste_interface__time_dependent_potassium_current_X_gate__X) * (30.0 + var_chaste_interface__membrane__V) / (1.0 - exp(-4.4399999999999995 - 0.148 * var_chaste_interface__membrane__V)) - 0.000131 * (30.0 + var_chaste_interface__membrane__V) * var_chaste_interface__time_dependent_potassium_current_X_gate__X / (-1.0 + exp(2.061 + 0.0687 * var_chaste_interface__membrane__V)); // 1 / ms
        const double var_time_dependent_potassium_current__i_K = 0.00282 * pow(var_chaste_interface__time_dependent_potassium_current_X_gate__X, 2.0) * (-26.614641953637257 * log(7.966200000000001 / (0.01833 * var_chaste_interface__ionic_concentrations__Nai + var_chaste_interface__ionic_concentrations__Ki)) + var_chaste_interface__membrane__V) / (1.0 + exp(-1.7526479750778816 + 0.03115264797507788 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_time_independent_potassium_current__E_K1 = 26.614641953637257 * log(5.4 / var_chaste_interface__ionic_concentrations__Ki); // mV
        const double var_plateau_potassium_current__i_Kp = 0.000183 * (-var_time_independent_potassium_current__E_K1 + var_chaste_interface__membrane__V) / (1.0 + exp(1.2521739130434784 - 0.16722408026755853 * var_chaste_interface__membrane__V)); // uA_per_mm2
        const double var_time_independent_potassium_current__i_K1 = 0.00765 * (-var_time_independent_potassium_current__E_K1 + var_chaste_interface__membrane__V) / ((1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__membrane__V - 0.2385 * var_time_independent_potassium_current__E_K1)) * (1.02 / (1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__membrane__V - 0.2385 * var_time_independent_potassium_current__E_K1)) + (0.49124 * exp(0.43983232 + 0.08032 * var_chaste_interface__membrane__V - 0.08032 * var_time_independent_potassium_current__E_K1) + exp(-36.6986425 + 0.06175 * var_chaste_interface__membrane__V - 0.06175 * var_time_independent_potassium_current__E_K1)) / (1.0 + exp(-2.4444679 + 0.5143 * var_time_independent_potassium_current__E_K1 - 0.5143 * var_chaste_interface__membrane__V)))); // uA_per_mm2
        const double d_dt_chaste_interface_var_ionic_concentrations__Ki = 0.006073987238552811 * var_sodium_potassium_pump__i_NaK - 0.0030369936192764053 * var_L_type_Ca_channel__i_CaK - 0.0030369936192764053 * var_non_specific_calcium_activated_current__i_ns_K - 0.0030369936192764053 * var_plateau_potassium_current__i_Kp - 0.0030369936192764053 * var_time_dependent_potassium_current__i_K - 0.0030369936192764053 * var_time_independent_potassium_current__i_K1; // mM / ms
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_membrane__V = -1.0 * GetIntracellularAreaStimulus(var_chaste_interface__environment__time) - 100.0 * var_L_type_Ca_channel__i_CaCa - 100.0 * var_L_type_Ca_channel__i_CaK - 100.0 * var_L_type_Ca_channel__i_CaNa - 100.0 * var_Na_Ca_exchanger__i_NaCa - 100.0 * var_calcium_background_current__i_Ca_b - 100.0 * var_fast_sodium_current__i_Na - 100.0 * var_non_specific_calcium_activated_current__i_ns_K - 100.0 * var_non_specific_calcium_activated_current__i_ns_Na - 100.0 * var_plateau_potassium_current__i_Kp - 100.0 * var_sarcolemmal_calcium_pump__i_p_Ca - 100.0 * var_sodium_background_current__i_Na_b - 100.0 * var_sodium_potassium_pump__i_NaK - 100.0 * var_time_dependent_potassium_current__i_K - 100.0 * var_time_independent_potassium_current__i_K1; // mV / ms
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V;
        rDY[1] = d_dt_chaste_interface_var_ionic_concentrations__Cai_converted;
        rDY[2] = d_dt_chaste_interface_var_fast_sodium_current_m_gate__m;
        rDY[3] = d_dt_chaste_interface_var_fast_sodium_current_h_gate__h;
        rDY[4] = d_dt_chaste_interface_var_fast_sodium_current_j_gate__j;
        rDY[5] = d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d;
        rDY[6] = d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f;
        rDY[7] = d_dt_chaste_interface_var_time_dependent_potassium_current_X_gate__X;
        rDY[8] = d_dt_chaste_interface_var_ionic_concentrations__Nai;
        rDY[9] = d_dt_chaste_interface_var_ionic_concentrations__Ki;
        rDY[10] = d_dt_chaste_interface_var_ionic_concentrations__Ca_JSR;
        rDY[11] = d_dt_chaste_interface_var_ionic_concentrations__Ca_NSR;
    }

template<>
void OdeSystemInformation<Cellluo_rudy_1994FromCellML>::Initialise(void)
{
    this->mSystemName = "luo_rudy_1994";
    this->mFreeVariableName = "time";
    this->mFreeVariableUnits = "ms";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("mV");
    this->mInitialConditions.push_back(-84.624);
    
    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.00012);
    
    // rY[2]:
    this->mVariableNames.push_back("fast_sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);
    
    // rY[3]:
    this->mVariableNames.push_back("fast_sodium_current_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);
    
    // rY[4]:
    this->mVariableNames.push_back("fast_sodium_current_j_gate__j");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);
    
    // rY[5]:
    this->mVariableNames.push_back("L_type_Ca_channel_d_gate__d");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);
    
    // rY[6]:
    this->mVariableNames.push_back("L_type_Ca_channel_f_gate__f");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);
    
    // rY[7]:
    this->mVariableNames.push_back("time_dependent_potassium_current_X_gate__X");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);
    
    // rY[8]:
    this->mVariableNames.push_back("cytosolic_sodium_concentration");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(10.0);
    
    // rY[9]:
    this->mVariableNames.push_back("cytosolic_potassium_concentration");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(145.0);
    
    // rY[10]:
    this->mVariableNames.push_back("JSR_calcium_concentration");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(1.8);
    
    // rY[11]:
    this->mVariableNames.push_back("NSR_calcium_concentration");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(1.8);
    
    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellluo_rudy_1994FromCellML)
