//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: courtemanche_ramirez_nattel_model_1998
//! 
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: normal)
//! on 2020-01-29 22:54:01
//! 
//! <autogenerated>

#include "courtemanche_ramirez_nattel_model_1998.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

    boost::shared_ptr<RegularStimulus> Cellcourtemanche_ramirez_nattel_model_1998FromCellML::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__membrane__stim_amplitude = -20.0 * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2
        const double var_chaste_interface__membrane__stim_duration = 2.0; // millisecond
        const double var_chaste_interface__membrane__stim_period = 1000.0; // millisecond
        const double var_chaste_interface__membrane__stim_start = 50.0; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__membrane__stim_amplitude),
                var_chaste_interface__membrane__stim_duration,
                var_chaste_interface__membrane__stim_period,
                var_chaste_interface__membrane__stim_start
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }
    
    Cellcourtemanche_ramirez_nattel_model_1998FromCellML::Cellcourtemanche_ramirez_nattel_model_1998FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                21,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellcourtemanche_ramirez_nattel_model_1998FromCellML>::Instance();
        Init();
        
        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
    }
    
    Cellcourtemanche_ramirez_nattel_model_1998FromCellML::~Cellcourtemanche_ramirez_nattel_model_1998FromCellML()
    {
    }

    double Cellcourtemanche_ramirez_nattel_model_1998FromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -81.18
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.002908
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.9649
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[3];
        // Units: dimensionless; Initial value: 0.9775
        double var_chaste_interface__transient_outward_K_current_oa_gate__oa = rY[4];
        // Units: dimensionless; Initial value: 0.03043
        double var_chaste_interface__transient_outward_K_current_oi_gate__oi = rY[5];
        // Units: dimensionless; Initial value: 0.9992
        double var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ua_gate__ua = rY[6];
        // Units: dimensionless; Initial value: 0.004966
        double var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ui_gate__ui = rY[7];
        // Units: dimensionless; Initial value: 0.9986
        double var_chaste_interface__rapid_delayed_rectifier_K_current_xr_gate__xr = rY[8];
        // Units: dimensionless; Initial value: 3.296e-05
        double var_chaste_interface__slow_delayed_rectifier_K_current_xs_gate__xs = rY[9];
        // Units: dimensionless; Initial value: 0.01869
        double var_chaste_interface__L_type_Ca_channel_d_gate__d = rY[10];
        // Units: dimensionless; Initial value: 0.0001367
        double var_chaste_interface__L_type_Ca_channel_f_gate__f = rY[11];
        // Units: dimensionless; Initial value: 0.9996
        double var_chaste_interface__L_type_Ca_channel_f_Ca_gate__f_Ca = rY[12];
        // Units: dimensionless; Initial value: 0.7755
        double var_chaste_interface__intracellular_ion_concentrations__Na_i = rY[16];
        // Units: millimolar; Initial value: 11.17
        double var_chaste_interface__intracellular_ion_concentrations__Ca_i = rY[17];
        // Units: millimolar; Initial value: 0.0001013
        double var_chaste_interface__intracellular_ion_concentrations__K_i = rY[18];
        // Units: millimolar; Initial value: 139.0
        
        const double var_L_type_Ca_channel__i_Ca_L = 12.375 * (-65.0 + var_chaste_interface__membrane__V) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_chaste_interface__L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f; // picoA
        const double var_sarcolemmal_calcium_pump_current__i_CaP = 27.500000000000004 * var_chaste_interface__intracellular_ion_concentrations__Ca_i / (0.0005 + var_chaste_interface__intracellular_ion_concentrations__Ca_i); // picoA
        const double var_background_currents__i_B_Ca = 0.1131 * var_chaste_interface__membrane__V - 1.5106106453013732 * log(1.8 / var_chaste_interface__intracellular_ion_concentrations__Ca_i); // picoA
        const double var_Na_Ca_exchanger_current__i_NaCa = 0.014738024843876967 * (1.8 * pow(var_chaste_interface__intracellular_ion_concentrations__Na_i, 3.0) * exp(0.013102317305629283 * var_chaste_interface__membrane__V) - 2744000.0 * var_chaste_interface__intracellular_ion_concentrations__Ca_i * exp(-0.02433287499616867 * var_chaste_interface__membrane__V)) / (1.0 + 0.1 * exp(-0.02433287499616867 * var_chaste_interface__membrane__V)); // picoA
        const double var_fast_sodium_current__E_Na = 26.71283192398538 * log(140.0 / var_chaste_interface__intracellular_ion_concentrations__Na_i); // millivolt
        const double var_background_currents__i_B_Na = 0.06744375 * var_chaste_interface__membrane__V - 0.06744375 * var_fast_sodium_current__E_Na; // picoA
        const double var_fast_sodium_current__i_Na = 780.0 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_fast_sodium_current__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // picoA
        const double var_sodium_potassium_pump__i_NaK = 46.90477095652174 * pow((1.0 + 0.1245 * exp(-0.0037435192301797956 * var_chaste_interface__membrane__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.037435192301797954 * var_chaste_interface__membrane__V)), (-1.0)) / (1.0 + 31.622776601683793 * pow(1 / var_chaste_interface__intracellular_ion_concentrations__Na_i, 1.5)); // picoA
        const double var_time_independent_potassium_current__E_K = 26.71283192398538 * log(5.4 / var_chaste_interface__intracellular_ion_concentrations__K_i); // millivolt
        const double var_rapid_delayed_rectifier_K_current__i_Kr = 2.9411765 * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__rapid_delayed_rectifier_K_current_xr_gate__xr / (1.0 + exp(0.6696428571428572 + 0.044642857142857144 * var_chaste_interface__membrane__V)); // picoA
        const double var_slow_delayed_rectifier_K_current__i_Ks = 12.941175999999999 * pow(var_chaste_interface__slow_delayed_rectifier_K_current_xs_gate__xs, 2.0) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V); // picoA
        const double var_time_independent_potassium_current__i_K1 = 9.0 * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) / (1.0 + exp(5.6000000000000005 + 0.07 * var_chaste_interface__membrane__V)); // picoA
        const double var_transient_outward_K_current__i_to = 16.520000000000003 * pow(var_chaste_interface__transient_outward_K_current_oa_gate__oa, 3.0) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__transient_outward_K_current_oi_gate__oi; // picoA
        const double var_ultrarapid_delayed_rectifier_K_current__i_Kur = 100.0 * pow(var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ua_gate__ua, 3.0) * (0.005 + 0.05 / (1.0 + exp(1.153846153846154 - 0.07692307692307693 * var_chaste_interface__membrane__V))) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ui_gate__ui; // picoA
        const double var_chaste_interface__i_ionic = 10000.0 * (1e-06 * var_L_type_Ca_channel__i_Ca_L + 1e-06 * var_Na_Ca_exchanger_current__i_NaCa + 1e-06 * var_background_currents__i_B_Ca + 1e-06 * var_background_currents__i_B_Na + 1e-06 * var_fast_sodium_current__i_Na + 1e-06 * var_rapid_delayed_rectifier_K_current__i_Kr + 1e-06 * var_sarcolemmal_calcium_pump_current__i_CaP + 1e-06 * var_slow_delayed_rectifier_K_current__i_Ks + 1e-06 * var_sodium_potassium_pump__i_NaK + 1e-06 * var_time_independent_potassium_current__i_K1 + 1e-06 * var_transient_outward_K_current__i_to + 1e-06 * var_ultrarapid_delayed_rectifier_K_current__i_Kur) * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Cellcourtemanche_ramirez_nattel_model_1998FromCellML::EvaluateYDerivatives(double var_chaste_interface__environment__time, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -81.18
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.002908
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[2];
        // Units: dimensionless; Initial value: 0.9649
        double var_chaste_interface__fast_sodium_current_j_gate__j = rY[3];
        // Units: dimensionless; Initial value: 0.9775
        double var_chaste_interface__transient_outward_K_current_oa_gate__oa = rY[4];
        // Units: dimensionless; Initial value: 0.03043
        double var_chaste_interface__transient_outward_K_current_oi_gate__oi = rY[5];
        // Units: dimensionless; Initial value: 0.9992
        double var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ua_gate__ua = rY[6];
        // Units: dimensionless; Initial value: 0.004966
        double var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ui_gate__ui = rY[7];
        // Units: dimensionless; Initial value: 0.9986
        double var_chaste_interface__rapid_delayed_rectifier_K_current_xr_gate__xr = rY[8];
        // Units: dimensionless; Initial value: 3.296e-05
        double var_chaste_interface__slow_delayed_rectifier_K_current_xs_gate__xs = rY[9];
        // Units: dimensionless; Initial value: 0.01869
        double var_chaste_interface__L_type_Ca_channel_d_gate__d = rY[10];
        // Units: dimensionless; Initial value: 0.0001367
        double var_chaste_interface__L_type_Ca_channel_f_gate__f = rY[11];
        // Units: dimensionless; Initial value: 0.9996
        double var_chaste_interface__L_type_Ca_channel_f_Ca_gate__f_Ca = rY[12];
        // Units: dimensionless; Initial value: 0.7755
        double var_chaste_interface__Ca_release_current_from_JSR_u_gate__u = rY[13];
        // Units: dimensionless; Initial value: 2.35e-112
        double var_chaste_interface__Ca_release_current_from_JSR_v_gate__v = rY[14];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__Ca_release_current_from_JSR_w_gate__w = rY[15];
        // Units: dimensionless; Initial value: 0.9992
        double var_chaste_interface__intracellular_ion_concentrations__Na_i = rY[16];
        // Units: millimolar; Initial value: 11.17
        double var_chaste_interface__intracellular_ion_concentrations__Ca_i = rY[17];
        // Units: millimolar; Initial value: 0.0001013
        double var_chaste_interface__intracellular_ion_concentrations__K_i = rY[18];
        // Units: millimolar; Initial value: 139.0
        double var_chaste_interface__intracellular_ion_concentrations__Ca_rel = rY[19];
        // Units: millimolar; Initial value: 1.488
        double var_chaste_interface__intracellular_ion_concentrations__Ca_up = rY[20];
        // Units: millimolar; Initial value: 1.488
        
        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double var_Ca_uptake_current_by_the_NSR__i_up = 0.005 / (1.0 + 0.00092 / var_chaste_interface__intracellular_ion_concentrations__Ca_i); // millimolar_per_millisecond
        const double d_dt_chaste_interface_var_L_type_Ca_channel_f_Ca_gate__f_Ca = 0.5 * pow((1.0 + 2857.1428571428573 * var_chaste_interface__intracellular_ion_concentrations__Ca_i), (-1.0)) - 0.5 * var_chaste_interface__L_type_Ca_channel_f_Ca_gate__f_Ca; // 1 / millisecond
        const double var_Ca_release_current_from_JSR__i_rel = 30.0 * pow(var_chaste_interface__Ca_release_current_from_JSR_u_gate__u, 2.0) * (-var_chaste_interface__intracellular_ion_concentrations__Ca_i + var_chaste_interface__intracellular_ion_concentrations__Ca_rel) * var_chaste_interface__Ca_release_current_from_JSR_v_gate__v * var_chaste_interface__Ca_release_current_from_JSR_w_gate__w; // millimolar_per_millisecond
        const double var_Ca_leak_current_by_the_NSR__i_up_leak = 0.0003333333333333333 * var_chaste_interface__intracellular_ion_concentrations__Ca_up; // millimolar_per_millisecond
        const double d_dt_chaste_interface_var_Ca_release_current_from_JSR_w_gate__w = (1.0 - pow((1.0 + exp(2.3529411764705883 - 0.058823529411764705 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__Ca_release_current_from_JSR_w_gate__w) * ((fabs(-7.9 + var_chaste_interface__membrane__V) < 1e-10) ? (1.0833333333333333) : (0.16666666666666666 * (1.0 + 0.3 * exp(1.58 - 0.2 * var_chaste_interface__membrane__V)) * (-7.9 + var_chaste_interface__membrane__V) / (1.0 - exp(1.58 - 0.2 * var_chaste_interface__membrane__V)))); // 1 / millisecond
        const double var_L_type_Ca_channel__i_Ca_L = 12.375 * (-65.0 + var_chaste_interface__membrane__V) * var_chaste_interface__L_type_Ca_channel_d_gate__d * var_chaste_interface__L_type_Ca_channel_f_Ca_gate__f_Ca * var_chaste_interface__L_type_Ca_channel_f_gate__f; // picoA
        const double d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d = (pow((1.0 + exp(-1.25 - 0.125 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__L_type_Ca_channel_d_gate__d) * ((fabs(10.0 + var_chaste_interface__membrane__V) < 1e-10) ? (0.21838829438742086 + 0.21838829438742086 * exp(-1.6025641025641024 - 0.16025641025641024 * var_chaste_interface__membrane__V)) : (0.035 * (1.0 + exp(-1.6025641025641024 - 0.16025641025641024 * var_chaste_interface__membrane__V)) * (10.0 + var_chaste_interface__membrane__V) / (1.0 - exp(-1.6025641025641024 - 0.16025641025641024 * var_chaste_interface__membrane__V)))); // 1 / millisecond
        const double d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f = 0.1111111111111111 * pow((0.02 + 0.0197 * exp(-0.113569 * pow((1 + 0.1 * var_chaste_interface__membrane__V), 2.0))), 1.0) * (-var_chaste_interface__L_type_Ca_channel_f_gate__f + exp(-4.057971014492754 - 0.14492753623188406 * var_chaste_interface__membrane__V) / (1.0 + exp(-4.057971014492754 - 0.14492753623188406 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double var_fast_sodium_current_h_gate__alpha_h = ((var_chaste_interface__membrane__V < -40.0) ? (0.135 * exp(-11.764705882352942 - 0.14705882352941177 * var_chaste_interface__membrane__V)) : (0.0)); // per_millisecond
        const double var_fast_sodium_current_h_gate__beta_h = ((var_chaste_interface__membrane__V < -40.0) ? (310000.0 * exp(0.35 * var_chaste_interface__membrane__V) + 3.56 * exp(0.079 * var_chaste_interface__membrane__V)) : (7.692307692307692 / (1.0 + exp(-0.9603603603603604 - 0.0900900900900901 * var_chaste_interface__membrane__V)))); // per_millisecond
        const double d_dt_chaste_interface_var_fast_sodium_current_h_gate__h = (-var_chaste_interface__fast_sodium_current_h_gate__h + var_fast_sodium_current_h_gate__alpha_h / (var_fast_sodium_current_h_gate__alpha_h + var_fast_sodium_current_h_gate__beta_h)) * (1.0 * var_fast_sodium_current_h_gate__alpha_h + 1.0 * var_fast_sodium_current_h_gate__beta_h); // 1 / millisecond
        const double var_fast_sodium_current_j_gate__alpha_j = ((var_chaste_interface__membrane__V < -40.0) ? ((37.78 + var_chaste_interface__membrane__V) * (-127140.0 * exp(0.2444 * var_chaste_interface__membrane__V) - 3.474e-05 * exp(-0.04391 * var_chaste_interface__membrane__V)) / (1.0 + exp(24.640530000000002 + 0.311 * var_chaste_interface__membrane__V))) : (0.0)); // per_millisecond
        const double var_fast_sodium_current_j_gate__beta_j = ((var_chaste_interface__membrane__V < -40.0) ? (0.1212 * exp(-0.01052 * var_chaste_interface__membrane__V) / (1.0 + exp(-5.5312920000000005 - 0.1378 * var_chaste_interface__membrane__V))) : (0.3 * exp(-2.535e-07 * var_chaste_interface__membrane__V) / (1.0 + exp(-3.2 - 0.1 * var_chaste_interface__membrane__V)))); // per_millisecond
        const double d_dt_chaste_interface_var_fast_sodium_current_j_gate__j = (-var_chaste_interface__fast_sodium_current_j_gate__j + var_fast_sodium_current_j_gate__alpha_j / (var_fast_sodium_current_j_gate__alpha_j + var_fast_sodium_current_j_gate__beta_j)) * (1.0 * var_fast_sodium_current_j_gate__alpha_j + 1.0 * var_fast_sodium_current_j_gate__beta_j); // 1 / millisecond
        const double var_fast_sodium_current_m_gate__alpha_m = ((var_chaste_interface__membrane__V == (-47.13)) ? (3.2) : (0.32 * (47.13 + var_chaste_interface__membrane__V) / (1.0 - exp(-4.713 - 0.1 * var_chaste_interface__membrane__V)))); // per_millisecond
        const double var_fast_sodium_current_m_gate__beta_m = 0.08 * exp(-0.09090909090909091 * var_chaste_interface__membrane__V); // per_millisecond
        const double d_dt_chaste_interface_var_fast_sodium_current_m_gate__m = (-var_chaste_interface__fast_sodium_current_m_gate__m + var_fast_sodium_current_m_gate__alpha_m / (var_fast_sodium_current_m_gate__alpha_m + var_fast_sodium_current_m_gate__beta_m)) * (1.0 * var_fast_sodium_current_m_gate__alpha_m + 1.0 * var_fast_sodium_current_m_gate__beta_m); // 1 / millisecond
        const double d_dt_chaste_interface_var_rapid_delayed_rectifier_K_current_xr_gate__xr = pow((((fabs(14.1 + var_chaste_interface__membrane__V) < 1e-10) ? (0.0015) : (0.0003 * (14.1 + var_chaste_interface__membrane__V) / (1.0 - exp(-2.8200000000000003 - 0.2 * var_chaste_interface__membrane__V)))) + ((fabs(-3.3328 + var_chaste_interface__membrane__V) < 1e-10) ? (0.00037836118) : (7.3898e-05 * (-3.3328 + var_chaste_interface__membrane__V) / (-1.0 + exp(-0.6504674356422117 + 0.19517145812596365 * var_chaste_interface__membrane__V))))), 1.0) * (pow((1.0 + exp(-2.1692307692307695 - 0.15384615384615385 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__rapid_delayed_rectifier_K_current_xr_gate__xr); // 1 / millisecond
        const double var_sarcolemmal_calcium_pump_current__i_CaP = 27.500000000000004 * var_chaste_interface__intracellular_ion_concentrations__Ca_i / (0.0005 + var_chaste_interface__intracellular_ion_concentrations__Ca_i); // picoA
        const double d_dt_chaste_interface_var_slow_delayed_rectifier_K_current_xs_gate__xs = 2.0 * pow((((fabs(-19.9 + var_chaste_interface__membrane__V) < 1e-10) ? (0.00068) : (4e-05 * (-19.9 + var_chaste_interface__membrane__V) / (1.0 - exp(1.1705882352941175 - 0.058823529411764705 * var_chaste_interface__membrane__V)))) + ((fabs(-19.9 + var_chaste_interface__membrane__V) < 1e-10) ? (0.000315) : (3.5e-05 * (-19.9 + var_chaste_interface__membrane__V) / (-1.0 + exp(-2.211111111111111 + 0.1111111111111111 * var_chaste_interface__membrane__V))))), 1.0) * (pow((1.0 + exp(1.5669291338582676 - 0.07874015748031496 * var_chaste_interface__membrane__V)), (-0.5)) - var_chaste_interface__slow_delayed_rectifier_K_current_xs_gate__xs); // 1 / millisecond
        const double var_background_currents__i_B_Ca = 0.1131 * var_chaste_interface__membrane__V - 1.5106106453013732 * log(1.8 / var_chaste_interface__intracellular_ion_concentrations__Ca_i); // picoA
        const double var_Na_Ca_exchanger_current__i_NaCa = 0.014738024843876967 * (1.8 * pow(var_chaste_interface__intracellular_ion_concentrations__Na_i, 3.0) * exp(0.013102317305629283 * var_chaste_interface__membrane__V) - 2744000.0 * var_chaste_interface__intracellular_ion_concentrations__Ca_i * exp(-0.02433287499616867 * var_chaste_interface__membrane__V)) / (1.0 + 0.1 * exp(-0.02433287499616867 * var_chaste_interface__membrane__V)); // picoA
        const double var_Ca_release_current_from_JSR__Fn = 9.647999999999999e-11 * var_Ca_release_current_from_JSR__i_rel + 1.0364122723649995e-15 * var_Na_Ca_exchanger_current__i_NaCa - 2.5910306809124988e-15 * var_L_type_Ca_channel__i_Ca_L; // dimensionless
        const double d_dt_chaste_interface_var_Ca_release_current_from_JSR_u_gate__u = 0.125 * pow((1.0 + exp(250.0 - 731528895391368.0 * var_Ca_release_current_from_JSR__Fn)), (-1.0)) - 0.125 * var_chaste_interface__Ca_release_current_from_JSR_u_gate__u; // 1 / millisecond
        const double d_dt_chaste_interface_var_Ca_release_current_from_JSR_v_gate__v = (1.0 - pow((1.0 + exp(50.0 - 731528895391368.0 * var_Ca_release_current_from_JSR__Fn)), (-1.0)) - var_chaste_interface__Ca_release_current_from_JSR_v_gate__v) / (1.91 + 2.09 * pow((1.0 + exp(250.0 - 731528895391368.0 * var_Ca_release_current_from_JSR__Fn)), (-1.0))); // 1 / millisecond
        const double var_fast_sodium_current__E_Na = 26.71283192398538 * log(140.0 / var_chaste_interface__intracellular_ion_concentrations__Na_i); // millivolt
        const double var_background_currents__i_B_Na = 0.06744375 * var_chaste_interface__membrane__V - 0.06744375 * var_fast_sodium_current__E_Na; // picoA
        const double var_fast_sodium_current__i_Na = 780.0 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_fast_sodium_current__E_Na + var_chaste_interface__membrane__V) * var_chaste_interface__fast_sodium_current_h_gate__h * var_chaste_interface__fast_sodium_current_j_gate__j; // picoA
        const double d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_i = (0.08117647058823528 * var_Ca_leak_current_by_the_NSR__i_up_leak + 7.582764650021944e-07 * var_Na_Ca_exchanger_current__i_NaCa + 0.007058823529411762 * var_Ca_release_current_from_JSR__i_rel - 0.08117647058823528 * var_Ca_uptake_current_by_the_NSR__i_up - 3.791382325010972e-07 * var_L_type_Ca_channel__i_Ca_L - 3.791382325010972e-07 * var_background_currents__i_B_Ca - 3.791382325010972e-07 * var_sarcolemmal_calcium_pump_current__i_CaP) / (1.0 + 0.00011900000000000002 * pow((0.00238 + var_chaste_interface__intracellular_ion_concentrations__Ca_i), (-2.0)) + 3.5000000000000004e-05 * pow((0.0005 + var_chaste_interface__intracellular_ion_concentrations__Ca_i), (-2.0))); // millimolar / millisecond
        const double var_sodium_potassium_pump__i_NaK = 46.90477095652174 * pow((1.0 + 0.1245 * exp(-0.0037435192301797956 * var_chaste_interface__membrane__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.037435192301797954 * var_chaste_interface__membrane__V)), (-1.0)) / (1.0 + 31.622776601683793 * pow(1 / var_chaste_interface__intracellular_ion_concentrations__Na_i, 1.5)); // picoA
        const double d_dt_chaste_interface_var_intracellular_ion_concentrations__Na_i = -2.2748293950065834e-06 * var_Na_Ca_exchanger_current__i_NaCa - 2.2748293950065834e-06 * var_sodium_potassium_pump__i_NaK - 7.582764650021944e-07 * var_background_currents__i_B_Na - 7.582764650021944e-07 * var_fast_sodium_current__i_Na; // millimolar / millisecond
        const double var_time_independent_potassium_current__E_K = 26.71283192398538 * log(5.4 / var_chaste_interface__intracellular_ion_concentrations__K_i); // millivolt
        const double var_rapid_delayed_rectifier_K_current__i_Kr = 2.9411765 * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__rapid_delayed_rectifier_K_current_xr_gate__xr / (1.0 + exp(0.6696428571428572 + 0.044642857142857144 * var_chaste_interface__membrane__V)); // picoA
        const double var_slow_delayed_rectifier_K_current__i_Ks = 12.941175999999999 * pow(var_chaste_interface__slow_delayed_rectifier_K_current_xs_gate__xs, 2.0) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V); // picoA
        const double var_time_independent_potassium_current__i_K1 = 9.0 * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) / (1.0 + exp(5.6000000000000005 + 0.07 * var_chaste_interface__membrane__V)); // picoA
        const double var_transfer_current_from_NSR_to_JSR__i_tr = 0.005555555555555556 * var_chaste_interface__intracellular_ion_concentrations__Ca_up - 0.005555555555555556 * var_chaste_interface__intracellular_ion_concentrations__Ca_rel; // millimolar_per_millisecond
        const double d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_rel = pow((1.0 + 8.0 * pow((0.8 + var_chaste_interface__intracellular_ion_concentrations__Ca_rel), (-2.0))), (-1.0)) * (-var_Ca_release_current_from_JSR__i_rel + var_transfer_current_from_NSR_to_JSR__i_tr); // millimolar / millisecond
        const double d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_up = -var_Ca_leak_current_by_the_NSR__i_up_leak - 0.08695652173913042 * var_transfer_current_from_NSR_to_JSR__i_tr + var_Ca_uptake_current_by_the_NSR__i_up; // millimolar / millisecond
        const double d_dt_chaste_interface_var_transient_outward_K_current_oa_gate__oa = 3.0 * pow((0.65 * pow((2.5 + exp(4.823529411764706 + 0.058823529411764705 * var_chaste_interface__membrane__V)), (-1.0)) + 0.65 * pow((exp(0.5084745762711864 - 0.01694915254237288 * var_chaste_interface__membrane__V) + exp(-1.1764705882352942 - 0.11764705882352941 * var_chaste_interface__membrane__V)), (-1.0))), 1.0) * (pow((1.0 + exp(-1.1670467502850628 - 0.05701254275940707 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__transient_outward_K_current_oa_gate__oa); // 1 / millisecond
        const double var_transient_outward_K_current__i_to = 16.520000000000003 * pow(var_chaste_interface__transient_outward_K_current_oa_gate__oa, 3.0) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__transient_outward_K_current_oi_gate__oi; // picoA
        const double d_dt_chaste_interface_var_transient_outward_K_current_oi_gate__oi = 3.0 * pow((pow((35.56 + 1.0 * exp(-0.1693548387096775 - 0.13440860215053763 * var_chaste_interface__membrane__V)), (-1.0)) + pow((18.53 + 1.0 * exp(10.383561643835618 + 0.09132420091324202 * var_chaste_interface__membrane__V)), (-1.0))), 1.0) * (pow((1.0 + exp(8.132075471698114 + 0.18867924528301888 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__transient_outward_K_current_oi_gate__oi); // 1 / millisecond
        const double d_dt_chaste_interface_var_ultrarapid_delayed_rectifier_K_current_ua_gate__ua = 3.0 * pow((0.65 * pow((2.5 + exp(4.823529411764706 + 0.058823529411764705 * var_chaste_interface__membrane__V)), (-1.0)) + 0.65 * pow((exp(0.5084745762711864 - 0.01694915254237288 * var_chaste_interface__membrane__V) + exp(-1.1764705882352942 - 0.11764705882352941 * var_chaste_interface__membrane__V)), (-1.0))), 1.0) * (pow((1.0 + exp(-3.15625 - 0.10416666666666667 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ua_gate__ua); // 1 / millisecond
        const double var_ultrarapid_delayed_rectifier_K_current__i_Kur = 100.0 * pow(var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ua_gate__ua, 3.0) * (0.005 + 0.05 / (1.0 + exp(1.153846153846154 - 0.07692307692307693 * var_chaste_interface__membrane__V))) * (-var_time_independent_potassium_current__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ui_gate__ui; // picoA
        const double d_dt_chaste_interface_var_intracellular_ion_concentrations__K_i = 1.5165529300043888e-06 * var_sodium_potassium_pump__i_NaK - 7.582764650021944e-07 * var_rapid_delayed_rectifier_K_current__i_Kr - 7.582764650021944e-07 * var_slow_delayed_rectifier_K_current__i_Ks - 7.582764650021944e-07 * var_time_independent_potassium_current__i_K1 - 7.582764650021944e-07 * var_transient_outward_K_current__i_to - 7.582764650021944e-07 * var_ultrarapid_delayed_rectifier_K_current__i_Kur; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ultrarapid_delayed_rectifier_K_current_ui_gate__ui = 3.0 * pow((pow((21.0 + 1.0 * exp(6.607142857142857 - 0.03571428571428571 * var_chaste_interface__membrane__V)), (-1.0)) + 1.0 / exp(9.875 - 0.0625 * var_chaste_interface__membrane__V)), 1.0) * (pow((1.0 + exp(-3.618995633187773 + 0.036390101892285295 * var_chaste_interface__membrane__V)), (-1.0)) - var_chaste_interface__ultrarapid_delayed_rectifier_K_current_ui_gate__ui); // 1 / millisecond
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_membrane__V = -0.01 * var_L_type_Ca_channel__i_Ca_L - 0.01 * var_Na_Ca_exchanger_current__i_NaCa - 0.01 * var_background_currents__i_B_Ca - 0.01 * var_background_currents__i_B_Na - 0.01 * var_fast_sodium_current__i_Na - 0.01 * var_rapid_delayed_rectifier_K_current__i_Kr - 0.01 * var_sarcolemmal_calcium_pump_current__i_CaP - 0.01 * var_slow_delayed_rectifier_K_current__i_Ks - 0.01 * var_sodium_potassium_pump__i_NaK - 0.01 * var_time_independent_potassium_current__i_K1 - 0.01 * var_transient_outward_K_current__i_to - 0.01 * var_ultrarapid_delayed_rectifier_K_current__i_Kur - 1.0 * GetIntracellularAreaStimulus(var_chaste_interface__environment__time) / HeartConfig::Instance()->GetCapacitance(); // millivolt / millisecond
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V;
        rDY[1] = d_dt_chaste_interface_var_fast_sodium_current_m_gate__m;
        rDY[2] = d_dt_chaste_interface_var_fast_sodium_current_h_gate__h;
        rDY[3] = d_dt_chaste_interface_var_fast_sodium_current_j_gate__j;
        rDY[4] = d_dt_chaste_interface_var_transient_outward_K_current_oa_gate__oa;
        rDY[5] = d_dt_chaste_interface_var_transient_outward_K_current_oi_gate__oi;
        rDY[6] = d_dt_chaste_interface_var_ultrarapid_delayed_rectifier_K_current_ua_gate__ua;
        rDY[7] = d_dt_chaste_interface_var_ultrarapid_delayed_rectifier_K_current_ui_gate__ui;
        rDY[8] = d_dt_chaste_interface_var_rapid_delayed_rectifier_K_current_xr_gate__xr;
        rDY[9] = d_dt_chaste_interface_var_slow_delayed_rectifier_K_current_xs_gate__xs;
        rDY[10] = d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d;
        rDY[11] = d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f;
        rDY[12] = d_dt_chaste_interface_var_L_type_Ca_channel_f_Ca_gate__f_Ca;
        rDY[13] = d_dt_chaste_interface_var_Ca_release_current_from_JSR_u_gate__u;
        rDY[14] = d_dt_chaste_interface_var_Ca_release_current_from_JSR_v_gate__v;
        rDY[15] = d_dt_chaste_interface_var_Ca_release_current_from_JSR_w_gate__w;
        rDY[16] = d_dt_chaste_interface_var_intracellular_ion_concentrations__Na_i;
        rDY[17] = d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_i;
        rDY[18] = d_dt_chaste_interface_var_intracellular_ion_concentrations__K_i;
        rDY[19] = d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_rel;
        rDY[20] = d_dt_chaste_interface_var_intracellular_ion_concentrations__Ca_up;
    }

template<>
void OdeSystemInformation<Cellcourtemanche_ramirez_nattel_model_1998FromCellML>::Initialise(void)
{
    this->mSystemName = "courtemanche_ramirez_nattel_model_1998";
    this->mFreeVariableName = "environment__time";
    this->mFreeVariableUnits = "millisecond";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-81.18);
    
    // rY[1]:
    this->mVariableNames.push_back("fast_sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.002908);
    
    // rY[2]:
    this->mVariableNames.push_back("fast_sodium_current_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9649);
    
    // rY[3]:
    this->mVariableNames.push_back("fast_sodium_current_j_gate__j");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9775);
    
    // rY[4]:
    this->mVariableNames.push_back("transient_outward_K_current_oa_gate__oa");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.03043);
    
    // rY[5]:
    this->mVariableNames.push_back("transient_outward_K_current_oi_gate__oi");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9992);
    
    // rY[6]:
    this->mVariableNames.push_back("ultrarapid_delayed_rectifier_K_current_ua_gate__ua");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.004966);
    
    // rY[7]:
    this->mVariableNames.push_back("ultrarapid_delayed_rectifier_K_current_ui_gate__ui");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9986);
    
    // rY[8]:
    this->mVariableNames.push_back("rapid_delayed_rectifier_K_current_xr_gate__xr");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(3.296e-05);
    
    // rY[9]:
    this->mVariableNames.push_back("slow_delayed_rectifier_K_current_xs_gate__xs");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.01869);
    
    // rY[10]:
    this->mVariableNames.push_back("L_type_Ca_channel_d_gate__d");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0001367);
    
    // rY[11]:
    this->mVariableNames.push_back("L_type_Ca_channel_f_gate__f");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9996);
    
    // rY[12]:
    this->mVariableNames.push_back("L_type_Ca_channel_f_Ca_gate__f_Ca");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.7755);
    
    // rY[13]:
    this->mVariableNames.push_back("Ca_release_current_from_JSR_u_gate__u");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(2.35e-112);
    
    // rY[14]:
    this->mVariableNames.push_back("Ca_release_current_from_JSR_v_gate__v");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);
    
    // rY[15]:
    this->mVariableNames.push_back("Ca_release_current_from_JSR_w_gate__w");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9992);
    
    // rY[16]:
    this->mVariableNames.push_back("intracellular_ion_concentrations__Na_i");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(11.17);
    
    // rY[17]:
    this->mVariableNames.push_back("intracellular_ion_concentrations__Ca_i");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.0001013);
    
    // rY[18]:
    this->mVariableNames.push_back("intracellular_ion_concentrations__K_i");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(139.0);
    
    // rY[19]:
    this->mVariableNames.push_back("intracellular_ion_concentrations__Ca_rel");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(1.488);
    
    // rY[20]:
    this->mVariableNames.push_back("intracellular_ion_concentrations__Ca_up");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(1.488);
    
    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellcourtemanche_ramirez_nattel_model_1998FromCellML)
