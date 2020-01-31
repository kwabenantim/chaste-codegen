//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: demir_model_1994
//! 
//! Processed by weblab_cg: https://github.com/ModellingWebLab/weblab-cg
//!     (translator: weblab_cg, model type: normal, options: )
//! on 2020-01-29 22:55:02
//! 
//! <autogenerated>

#include "demir_model_1994.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"
    
    double Celldemir_model_1994FromCellML::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }
    
    Celldemir_model_1994FromCellML::Celldemir_model_1994FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                27,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Celldemir_model_1994FromCellML>::Instance();
        Init();
        
    }
    
    Celldemir_model_1994FromCellML::~Celldemir_model_1994FromCellML()
    {
    }

    double Celldemir_model_1994FromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -49.54105
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i = rY[1];
        // Units: millimolar; Initial value: 0.0003787018
        double var_chaste_interface__sodium_current_m_gate__m = rY[2];
        // Units: dimensionless; Initial value: 0.250113
        double var_chaste_interface__sodium_current_h_gate__h1 = rY[3];
        // Units: dimensionless; Initial value: 0.001386897
        double var_chaste_interface__sodium_current_h_gate__h2 = rY[4];
        // Units: dimensionless; Initial value: 0.002065463
        double var_chaste_interface__L_type_Ca_channel_d_gate__d_L = rY[5];
        // Units: dimensionless; Initial value: 0.002572773
        double var_chaste_interface__L_type_Ca_channel_f_gate__f_L = rY[6];
        // Units: dimensionless; Initial value: 0.98651
        double var_chaste_interface__T_type_Ca_channel_d_gate__d_T = rY[7];
        // Units: dimensionless; Initial value: 0.02012114
        double var_chaste_interface__T_type_Ca_channel_f_gate__f_T = rY[8];
        // Units: dimensionless; Initial value: 0.1945111
        double var_chaste_interface__delayed_rectifying_potassium_current_P_a_gate__P_a = rY[9];
        // Units: dimensionless; Initial value: 0.02302278
        double var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i = rY[10];
        // Units: dimensionless; Initial value: 0.3777728
        double var_chaste_interface__hyperpolarisation_activated_current_y_gate__y = rY[11];
        // Units: dimensionless; Initial value: 0.09227776
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i = rY[12];
        // Units: millimolar; Initial value: 9.701621
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__K_i = rY[13];
        // Units: millimolar; Initial value: 140.7347
        double var_chaste_interface__cleft_space_equations__Na_c = rY[18];
        // Units: millimolar; Initial value: 139.9988
        double var_chaste_interface__cleft_space_equations__Ca_c = rY[19];
        // Units: millimolar; Initial value: 2.00474
        double var_chaste_interface__cleft_space_equations__K_c = rY[20];
        // Units: millimolar; Initial value: 5.389014
        
        const double var_calcium_pump_current__i_Ca_P = 0.02869 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i / (0.0004 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i); // nanoA
        const double var_L_type_Ca_channel__i_Ca_L = 0.02115 * (-46.4 + var_chaste_interface__membrane__V) * (0.095 / (1.0 + exp(-2.3499999999999996 - 0.16666666666666666 * var_chaste_interface__membrane__V)) + var_chaste_interface__L_type_Ca_channel_d_gate__d_L * var_chaste_interface__L_type_Ca_channel_f_gate__f_L); // nanoA
        const double var_T_type_Ca_channel__i_Ca_T = 0.02521 * (-45.0 + var_chaste_interface__membrane__V) * var_chaste_interface__T_type_Ca_channel_d_gate__d_T * var_chaste_interface__T_type_Ca_channel_f_gate__f_T; // nanoA
        const double var_hyperpolarisation_activated_current__i_f = 0.0128821 * pow(var_chaste_interface__hyperpolarisation_activated_current_y_gate__y, 2.0) * (85.0 + var_chaste_interface__membrane__V) + 0.0067478 * pow(var_chaste_interface__hyperpolarisation_activated_current_y_gate__y, 2.0) * (-75.0 + var_chaste_interface__membrane__V); // nanoA
        const double var_reversal_potentials__E_K = 26.71376065969565 * log(var_chaste_interface__cleft_space_equations__K_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__K_i); // millivolt
        const double var_delayed_rectifying_potassium_current__i_K = 0.018743278268729353 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__delayed_rectifying_potassium_current_P_a_gate__P_a * var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i; // nanoA
        const double var_reversal_potentials__E_Na = 26.71376065969565 * log(var_chaste_interface__cleft_space_equations__Na_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i); // millivolt
        const double var_linear_background_current__i_B = 0.0002658 * var_chaste_interface__membrane__V - 6.94e-05 * var_reversal_potentials__E_K - 0.00016 * var_reversal_potentials__E_Na - 0.00048619044400646084 * log(var_chaste_interface__cleft_space_equations__Ca_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i); // nanoA
        const double var_sodium_calcium_pump__i_NaCa = 1.248e-05 * (pow(var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i, 3.0) * var_chaste_interface__cleft_space_equations__Ca_c * exp(0.018715 * var_chaste_interface__membrane__V) - pow(var_chaste_interface__cleft_space_equations__Na_c, 3.0) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i * exp(-0.018715 * var_chaste_interface__membrane__V)) / (1.0 + 0.0001 * pow(var_chaste_interface__cleft_space_equations__Na_c, 3.0) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i + 0.0001 * pow(var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i, 3.0) * var_chaste_interface__cleft_space_equations__Ca_c); // nanoA
        const double var_sodium_current__i_Na = 12.424666784589716 * pow(var_chaste_interface__sodium_current_m_gate__m, 3.0) * (-1.0 + exp(0.03743389082274547 * var_chaste_interface__membrane__V - 0.03743389082274547 * var_reversal_potentials__E_Na)) * var_chaste_interface__cleft_space_equations__Na_c * var_chaste_interface__membrane__V * var_chaste_interface__sodium_current_h_gate__h1 * var_chaste_interface__sodium_current_h_gate__h2 / (-1.0 + exp(0.03743389082274547 * var_chaste_interface__membrane__V)); // nanoA
        const double var_sodium_potassium_pump__i_NaK = 0.35072000000000003 * pow((var_chaste_interface__cleft_space_equations__K_c / (0.621 + var_chaste_interface__cleft_space_equations__K_c)), 2.0) * pow((var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i / (5.46 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i)), 3.0) / (1.5 + exp(-1.5 - 0.025 * var_chaste_interface__membrane__V)); // nanoA
        const double var_chaste_interface__i_ionic = 18181.81818181818 * (0.001 * var_L_type_Ca_channel__i_Ca_L + 0.001 * var_T_type_Ca_channel__i_Ca_T + 0.001 * var_calcium_pump_current__i_Ca_P + 0.001 * var_delayed_rectifying_potassium_current__i_K + 0.001 * var_hyperpolarisation_activated_current__i_f + 0.001 * var_linear_background_current__i_B + 0.001 * var_sodium_calcium_pump__i_NaCa + 0.001 * var_sodium_current__i_Na + 0.001 * var_sodium_potassium_pump__i_NaK) * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Celldemir_model_1994FromCellML::EvaluateYDerivatives(double var_chaste_interface__environment__time_converted, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -49.54105
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i = rY[1];
        // Units: millimolar; Initial value: 0.0003787018
        double var_chaste_interface__sodium_current_m_gate__m = rY[2];
        // Units: dimensionless; Initial value: 0.250113
        double var_chaste_interface__sodium_current_h_gate__h1 = rY[3];
        // Units: dimensionless; Initial value: 0.001386897
        double var_chaste_interface__sodium_current_h_gate__h2 = rY[4];
        // Units: dimensionless; Initial value: 0.002065463
        double var_chaste_interface__L_type_Ca_channel_d_gate__d_L = rY[5];
        // Units: dimensionless; Initial value: 0.002572773
        double var_chaste_interface__L_type_Ca_channel_f_gate__f_L = rY[6];
        // Units: dimensionless; Initial value: 0.98651
        double var_chaste_interface__T_type_Ca_channel_d_gate__d_T = rY[7];
        // Units: dimensionless; Initial value: 0.02012114
        double var_chaste_interface__T_type_Ca_channel_f_gate__f_T = rY[8];
        // Units: dimensionless; Initial value: 0.1945111
        double var_chaste_interface__delayed_rectifying_potassium_current_P_a_gate__P_a = rY[9];
        // Units: dimensionless; Initial value: 0.02302278
        double var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i = rY[10];
        // Units: dimensionless; Initial value: 0.3777728
        double var_chaste_interface__hyperpolarisation_activated_current_y_gate__y = rY[11];
        // Units: dimensionless; Initial value: 0.09227776
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i = rY[12];
        // Units: millimolar; Initial value: 9.701621
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__K_i = rY[13];
        // Units: millimolar; Initial value: 140.7347
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Calmod = rY[14];
        // Units: dimensionless; Initial value: 0.1411678
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Trop = rY[15];
        // Units: dimensionless; Initial value: 0.07331396
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop = rY[16];
        // Units: dimensionless; Initial value: 0.7618549
        double var_chaste_interface__intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop = rY[17];
        // Units: dimensionless; Initial value: 0.2097049
        double var_chaste_interface__cleft_space_equations__Na_c = rY[18];
        // Units: millimolar; Initial value: 139.9988
        double var_chaste_interface__cleft_space_equations__Ca_c = rY[19];
        // Units: millimolar; Initial value: 2.00474
        double var_chaste_interface__cleft_space_equations__K_c = rY[20];
        // Units: millimolar; Initial value: 5.389014
        double var_chaste_interface__SR_Ca_uptake_and_release__Ca_up = rY[21];
        // Units: millimolar; Initial value: 16.95311
        double var_chaste_interface__SR_Ca_uptake_and_release__Ca_rel = rY[22];
        // Units: millimolar; Initial value: 16.85024
        double var_chaste_interface__SR_Ca_uptake_and_release__Ca_Calse = rY[23];
        // Units: dimensionless; Initial value: 0.9528726
        double var_chaste_interface__SR_Ca_uptake_and_release__F1 = rY[24];
        // Units: dimensionless; Initial value: 0.1133251
        double var_chaste_interface__SR_Ca_uptake_and_release__F2 = rY[25];
        // Units: dimensionless; Initial value: 0.0007594214
        double var_chaste_interface__SR_Ca_uptake_and_release__F3 = rY[26];
        // Units: dimensionless; Initial value: 0.8859153
        
        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double var_SR_Ca_uptake_and_release__i_rel = 0.5 * pow((var_chaste_interface__SR_Ca_uptake_and_release__F2 / (0.25 + var_chaste_interface__SR_Ca_uptake_and_release__F2)), 2.0) * var_chaste_interface__SR_Ca_uptake_and_release__Ca_rel; // nanoA
        const double var_SR_Ca_uptake_and_release__phi_Calse = -641.0 * var_chaste_interface__SR_Ca_uptake_and_release__Ca_Calse + 770.0 * (1.0 - var_chaste_interface__SR_Ca_uptake_and_release__Ca_Calse) * var_chaste_interface__SR_Ca_uptake_and_release__Ca_rel; // per_second
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_Calse = 0.001 * var_SR_Ca_uptake_and_release__phi_Calse; // 1 / millisecond
        const double var_SR_Ca_uptake_and_release__i_up = (0.08 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i - 1.4727272727272728e-07 * var_chaste_interface__SR_Ca_uptake_and_release__Ca_up) / (9.5e-05 + 2.0454545454545457e-06 * var_chaste_interface__SR_Ca_uptake_and_release__Ca_up + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i); // nanoA
        const double var_SR_Ca_uptake_and_release__r_inact = 40.0 + 240.0 * pow((var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i / (0.004 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i)), 4.0); // per_second
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F3 = -0.00096 * var_chaste_interface__SR_Ca_uptake_and_release__F3 + 0.001 * var_chaste_interface__SR_Ca_uptake_and_release__F2 * var_SR_Ca_uptake_and_release__r_inact; // 1 / millisecond
        const double var_calcium_pump_current__i_Ca_P = 0.02869 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i / (0.0004 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i); // nanoA
        const double var_intracellular_concentrations_and_buffer_equations__phi_C = -307.0 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Calmod + 129000.0 * (1.0 - var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Calmod) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i; // per_second
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Calmod = 0.001 * var_intracellular_concentrations_and_buffer_equations__phi_C; // 1 / millisecond
        const double var_intracellular_concentrations_and_buffer_equations__phi_TC = -252.0 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Trop + 50500.0 * (1.0 - var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Trop) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i; // per_second
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Trop = 0.001 * var_intracellular_concentrations_and_buffer_equations__phi_TC; // 1 / millisecond
        const double var_intracellular_concentrations_and_buffer_equations__phi_TMgC = -4.25 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop + 129000.0 * (1.0 - var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop - var_chaste_interface__intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i; // per_second
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop = 0.001 * var_intracellular_concentrations_and_buffer_equations__phi_TMgC; // 1 / millisecond
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop = 3.225 - 3.654 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop - 3.225 * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop; // 1 / millisecond
        const double var_SR_Ca_uptake_and_release__i_tr = 0.05700838747761728 * var_chaste_interface__SR_Ca_uptake_and_release__Ca_up - 0.05700838747761728 * var_chaste_interface__SR_Ca_uptake_and_release__Ca_rel; // nanoA
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_rel = 2.4589804690256463 * var_SR_Ca_uptake_and_release__i_tr - 2.4589804690256463 * var_SR_Ca_uptake_and_release__i_rel - 0.01148 * var_SR_Ca_uptake_and_release__phi_Calse; // millimolar / millisecond
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_up = 0.2733137811198317 * var_SR_Ca_uptake_and_release__i_up - 0.2733137811198317 * var_SR_Ca_uptake_and_release__i_tr; // millimolar / millisecond
        const double var_L_type_Ca_channel_d_gate__d_L_infinity = 1.0 / (1.0 + exp(-2.3499999999999996 - 0.16666666666666666 * var_chaste_interface__membrane__V)); // dimensionless
        const double var_L_type_Ca_channel__i_Ca_L = 0.02115 * (-46.4 + var_chaste_interface__membrane__V) * (0.095 * var_L_type_Ca_channel_d_gate__d_L_infinity + var_chaste_interface__L_type_Ca_channel_d_gate__d_L * var_chaste_interface__L_type_Ca_channel_f_gate__f_L); // nanoA
        const double d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d_L = 0.001 * (-var_chaste_interface__L_type_Ca_channel_d_gate__d_L + var_L_type_Ca_channel_d_gate__d_L_infinity) * (11.43 * (-5.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(-2.0 + 0.4 * var_chaste_interface__membrane__V)) - 28.39 * (35.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(-14.0 - 0.4 * var_chaste_interface__membrane__V)) - 84.9 * var_chaste_interface__membrane__V / (-1.0 + exp(-0.208 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f_L = 0.001 * (-var_chaste_interface__L_type_Ca_channel_f_gate__f_L + 1.0 / (1.0 + exp(6.0 + 0.2 * var_chaste_interface__membrane__V))) * (30.0 / (1.0 + exp(-7.0 - 0.25 * var_chaste_interface__membrane__V)) + 3.75 * (28.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(7.0 + 0.25 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double var_SR_Ca_uptake_and_release__r_act = 240.0 * pow((var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i / (0.004 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i)), 4.0) + 240.0 * exp(-3.2 + 0.08 * var_chaste_interface__membrane__V); // per_second
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F1 = 0.00096 * var_chaste_interface__SR_Ca_uptake_and_release__F3 - 0.001 * var_chaste_interface__SR_Ca_uptake_and_release__F1 * var_SR_Ca_uptake_and_release__r_act; // 1 / millisecond
        const double d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F2 = 0.001 * var_chaste_interface__SR_Ca_uptake_and_release__F1 * var_SR_Ca_uptake_and_release__r_act - 0.001 * var_chaste_interface__SR_Ca_uptake_and_release__F2 * var_SR_Ca_uptake_and_release__r_inact; // 1 / millisecond
        const double var_T_type_Ca_channel__i_Ca_T = 0.02521 * (-45.0 + var_chaste_interface__membrane__V) * var_chaste_interface__T_type_Ca_channel_d_gate__d_T * var_chaste_interface__T_type_Ca_channel_f_gate__f_T; // nanoA
        const double d_dt_chaste_interface_var_T_type_Ca_channel_d_gate__d_T = 0.001 * (-var_chaste_interface__T_type_Ca_channel_d_gate__d_T + 1.0 / (1.0 + exp(-4.383333333333333 - 0.16666666666666666 * var_chaste_interface__membrane__V))) * (1068.0 * exp(0.8766666666666667 + 0.03333333333333333 * var_chaste_interface__membrane__V) + 1068.0 * exp(-0.8766666666666667 - 0.03333333333333333 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_T_type_Ca_channel_f_gate__f_T = 0.001 * (-var_chaste_interface__T_type_Ca_channel_f_gate__f_T + 1.0 / (1.0 + exp(11.017857142857144 + 0.17857142857142858 * var_chaste_interface__membrane__V))) * (15.0 * exp(4.011703511053316 + 0.06501950585175552 * var_chaste_interface__membrane__V) + 15.3 * exp(-0.7406962785114046 - 0.012004801920768308 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_delayed_rectifying_potassium_current_P_a_gate__P_a = 0.001 * (-var_chaste_interface__delayed_rectifying_potassium_current_P_a_gate__P_a + 1.0 / (1.0 + exp(-0.689189189189189 - 0.13513513513513511 * var_chaste_interface__membrane__V))) * (17.0 * exp(0.0398 * var_chaste_interface__membrane__V) + 2.11 * exp(-0.051 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_delayed_rectifying_potassium_current_P_i_gate__P_i = 0.1 * (1.0 - var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i) * exp(-0.0183 * var_chaste_interface__membrane__V) - 0.656 * var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i * exp(0.00942 * var_chaste_interface__membrane__V); // 1 / millisecond
        const double var_hyperpolarisation_activated_current__i_f_K = 0.0128821 * pow(var_chaste_interface__hyperpolarisation_activated_current_y_gate__y, 2.0) * (85.0 + var_chaste_interface__membrane__V); // nanoA
        const double var_hyperpolarisation_activated_current__i_f_Na = 0.0067478 * pow(var_chaste_interface__hyperpolarisation_activated_current_y_gate__y, 2.0) * (-75.0 + var_chaste_interface__membrane__V); // nanoA
        const double d_dt_chaste_interface_var_hyperpolarisation_activated_current_y_gate__y = 0.001 * (-var_chaste_interface__hyperpolarisation_activated_current_y_gate__y + 1.0 / (1.0 + exp(8.022222222222222 + 0.1111111111111111 * var_chaste_interface__membrane__V))) * (1.6483 * exp(-2.2219482120838476 - 0.04110152075626799 * var_chaste_interface__membrane__V) + 14.01055 / (0.7 + exp(-10.90909090909091 - 0.18181818181818182 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double var_linear_background_current__i_B_Ca = 3.64e-05 * var_chaste_interface__membrane__V - 0.00048619044400646084 * log(var_chaste_interface__cleft_space_equations__Ca_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i); // nanoA
        const double var_reversal_potentials__E_K = 26.71376065969565 * log(var_chaste_interface__cleft_space_equations__K_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__K_i); // millivolt
        const double var_delayed_rectifying_potassium_current__i_K = 0.018743278268729353 * (-var_reversal_potentials__E_K + var_chaste_interface__membrane__V) * var_chaste_interface__delayed_rectifying_potassium_current_P_a_gate__P_a * var_chaste_interface__delayed_rectifying_potassium_current_P_i_gate__P_i; // nanoA
        const double var_linear_background_current__i_B_K = 6.94e-05 * var_chaste_interface__membrane__V - 6.94e-05 * var_reversal_potentials__E_K; // nanoA
        const double var_reversal_potentials__E_Na = 26.71376065969565 * log(var_chaste_interface__cleft_space_equations__Na_c / var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i); // millivolt
        const double var_linear_background_current__i_B_Na = 0.00016 * var_chaste_interface__membrane__V - 0.00016 * var_reversal_potentials__E_Na; // nanoA
        const double var_sodium_calcium_pump__i_NaCa = 1.248e-05 * (pow(var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i, 3.0) * var_chaste_interface__cleft_space_equations__Ca_c * exp(0.018715 * var_chaste_interface__membrane__V) - pow(var_chaste_interface__cleft_space_equations__Na_c, 3.0) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i * exp(-0.018715 * var_chaste_interface__membrane__V)) / (1.0 + 0.0001 * pow(var_chaste_interface__cleft_space_equations__Na_c, 3.0) * var_chaste_interface__intracellular_concentrations_and_buffer_equations__Ca_i + 0.0001 * pow(var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i, 3.0) * var_chaste_interface__cleft_space_equations__Ca_c); // nanoA
        const double d_dt_chaste_interface_var_cleft_space_equations__Ca_c = 0.2 + 0.010896176395982466 * var_L_type_Ca_channel__i_Ca_L + 0.010896176395982466 * var_T_type_Ca_channel__i_Ca_T + 0.010896176395982466 * var_calcium_pump_current__i_Ca_P + 0.010896176395982466 * var_linear_background_current__i_B_Ca - 0.021792352791964932 * var_sodium_calcium_pump__i_NaCa - 0.1 * var_chaste_interface__cleft_space_equations__Ca_c; // millimolar / millisecond
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_i = 0.0031868386878572373 * var_SR_Ca_uptake_and_release__i_rel + 0.006373677375714475 * var_sodium_calcium_pump__i_NaCa - 0.0031868386878572373 * var_L_type_Ca_channel__i_Ca_L - 0.0031868386878572373 * var_SR_Ca_uptake_and_release__i_up - 0.0031868386878572373 * var_T_type_Ca_channel__i_Ca_T - 0.0031868386878572373 * var_calcium_pump_current__i_Ca_P - 0.0031868386878572373 * var_linear_background_current__i_B_Ca - 8.999999999999999e-05 * var_intracellular_concentrations_and_buffer_equations__phi_C - 3.1e-05 * var_intracellular_concentrations_and_buffer_equations__phi_TC - 6.2e-05 * var_intracellular_concentrations_and_buffer_equations__phi_TMgC; // millimolar / millisecond
        const double var_sodium_current_h_gate__alpha_h1 = 165.0 * exp(-8.03968253968254 - 0.07936507936507936 * var_chaste_interface__membrane__V); // per_second
        const double var_sodium_current_h_gate__beta_h1 = 12360.0 / (1.0 + 320.0 * exp(-8.03968253968254 - 0.07936507936507936 * var_chaste_interface__membrane__V)); // per_second
        const double var_sodium_current_h_gate__h1_infinity = var_sodium_current_h_gate__alpha_h1 / (var_sodium_current_h_gate__alpha_h1 + var_sodium_current_h_gate__beta_h1); // dimensionless
        const double var_sodium_current_h_gate__tau_h1 = 1.0 / (var_sodium_current_h_gate__alpha_h1 + var_sodium_current_h_gate__beta_h1); // second
        const double d_dt_chaste_interface_var_sodium_current_h_gate__h1 = 0.001 * (-var_chaste_interface__sodium_current_h_gate__h1 + var_sodium_current_h_gate__h1_infinity) / var_sodium_current_h_gate__tau_h1; // 1 / millisecond
        const double d_dt_chaste_interface_var_sodium_current_h_gate__h2 = 5e-05 * (-var_chaste_interface__sodium_current_h_gate__h2 + var_sodium_current_h_gate__h1_infinity) / var_sodium_current_h_gate__tau_h1; // 1 / millisecond
        const double var_sodium_current_m_gate__alpha_m = -824.0 * (51.9 + var_chaste_interface__membrane__V) / (-1.0 + exp(-5.831460674157303 - 0.11235955056179775 * var_chaste_interface__membrane__V)); // per_second
        const double var_sodium_current_m_gate__beta_m = 32960.0 * exp(-5.831460674157303 - 0.11235955056179775 * var_chaste_interface__membrane__V); // per_second
        const double var_sodium_current__i_Na = 12.424666784589716 * pow(var_chaste_interface__sodium_current_m_gate__m, 3.0) * (-1.0 + exp(0.03743389082274547 * var_chaste_interface__membrane__V - 0.03743389082274547 * var_reversal_potentials__E_Na)) * var_chaste_interface__cleft_space_equations__Na_c * var_chaste_interface__membrane__V * var_chaste_interface__sodium_current_h_gate__h1 * var_chaste_interface__sodium_current_h_gate__h2 / (-1.0 + exp(0.03743389082274547 * var_chaste_interface__membrane__V)); // nanoA
        const double d_dt_chaste_interface_var_sodium_current_m_gate__m = 0.001 * (-var_chaste_interface__sodium_current_m_gate__m + var_sodium_current_m_gate__alpha_m / (var_sodium_current_m_gate__alpha_m + var_sodium_current_m_gate__beta_m)) / (1.5e-05 + 1.0 / (var_sodium_current_m_gate__alpha_m + var_sodium_current_m_gate__beta_m)); // 1 / millisecond
        const double var_sodium_potassium_pump__i_NaK = 0.35072000000000003 * pow((var_chaste_interface__cleft_space_equations__K_c / (0.621 + var_chaste_interface__cleft_space_equations__K_c)), 2.0) * pow((var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i / (5.46 + var_chaste_interface__intracellular_concentrations_and_buffer_equations__Na_i)), 3.0) / (1.5 + exp(-1.5 - 0.025 * var_chaste_interface__membrane__V)); // nanoA
        const double d_dt_chaste_interface_var_cleft_space_equations__K_c = 0.54 + 0.021792352791964932 * var_delayed_rectifying_potassium_current__i_K + 0.021792352791964932 * var_hyperpolarisation_activated_current__i_f_K + 0.021792352791964932 * var_linear_background_current__i_B_K - 0.043584705583929864 * var_sodium_potassium_pump__i_NaK - 0.1 * var_chaste_interface__cleft_space_equations__K_c; // millimolar / millisecond
        const double d_dt_chaste_interface_var_cleft_space_equations__Na_c = 14.0 + 0.021792352791964932 * var_hyperpolarisation_activated_current__i_f_Na + 0.021792352791964932 * var_linear_background_current__i_B_Na + 0.021792352791964932 * var_sodium_current__i_Na + 0.06537705837589479 * var_sodium_calcium_pump__i_NaCa + 0.06537705837589479 * var_sodium_potassium_pump__i_NaK - 0.1 * var_chaste_interface__cleft_space_equations__Na_c; // millimolar / millisecond
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__K_i = 0.01274735475142895 * var_sodium_potassium_pump__i_NaK - 0.006373677375714475 * var_delayed_rectifying_potassium_current__i_K - 0.006373677375714475 * var_hyperpolarisation_activated_current__i_f_K - 0.006373677375714475 * var_linear_background_current__i_B_K; // millimolar / millisecond
        const double d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Na_i = -0.006373677375714475 * var_hyperpolarisation_activated_current__i_f_Na - 0.006373677375714475 * var_linear_background_current__i_B_Na - 0.006373677375714475 * var_sodium_current__i_Na - 0.019121032127143424 * var_sodium_calcium_pump__i_NaCa - 0.019121032127143424 * var_sodium_potassium_pump__i_NaK; // millimolar / millisecond
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_membrane__V = -18.18181818181818 * var_L_type_Ca_channel__i_Ca_L - 18.18181818181818 * var_T_type_Ca_channel__i_Ca_T - 18.18181818181818 * var_calcium_pump_current__i_Ca_P - 18.18181818181818 * var_delayed_rectifying_potassium_current__i_K - 18.18181818181818 * var_hyperpolarisation_activated_current__i_f_K - 18.18181818181818 * var_hyperpolarisation_activated_current__i_f_Na - 18.18181818181818 * var_linear_background_current__i_B_Ca - 18.18181818181818 * var_linear_background_current__i_B_K - 18.18181818181818 * var_linear_background_current__i_B_Na - 18.18181818181818 * var_sodium_calcium_pump__i_NaCa - 18.18181818181818 * var_sodium_current__i_Na - 18.18181818181818 * var_sodium_potassium_pump__i_NaK; // millivolt / millisecond
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V;
        rDY[1] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_i;
        rDY[2] = d_dt_chaste_interface_var_sodium_current_m_gate__m;
        rDY[3] = d_dt_chaste_interface_var_sodium_current_h_gate__h1;
        rDY[4] = d_dt_chaste_interface_var_sodium_current_h_gate__h2;
        rDY[5] = d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d_L;
        rDY[6] = d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f_L;
        rDY[7] = d_dt_chaste_interface_var_T_type_Ca_channel_d_gate__d_T;
        rDY[8] = d_dt_chaste_interface_var_T_type_Ca_channel_f_gate__f_T;
        rDY[9] = d_dt_chaste_interface_var_delayed_rectifying_potassium_current_P_a_gate__P_a;
        rDY[10] = d_dt_chaste_interface_var_delayed_rectifying_potassium_current_P_i_gate__P_i;
        rDY[11] = d_dt_chaste_interface_var_hyperpolarisation_activated_current_y_gate__y;
        rDY[12] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Na_i;
        rDY[13] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__K_i;
        rDY[14] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Calmod;
        rDY[15] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Trop;
        rDY[16] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop;
        rDY[17] = d_dt_chaste_interface_var_intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop;
        rDY[18] = d_dt_chaste_interface_var_cleft_space_equations__Na_c;
        rDY[19] = d_dt_chaste_interface_var_cleft_space_equations__Ca_c;
        rDY[20] = d_dt_chaste_interface_var_cleft_space_equations__K_c;
        rDY[21] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_up;
        rDY[22] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_rel;
        rDY[23] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__Ca_Calse;
        rDY[24] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F1;
        rDY[25] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F2;
        rDY[26] = d_dt_chaste_interface_var_SR_Ca_uptake_and_release__F3;
    }

template<>
void OdeSystemInformation<Celldemir_model_1994FromCellML>::Initialise(void)
{
    this->mSystemName = "demir_model_1994";
    this->mFreeVariableName = "time";
    this->mFreeVariableUnits = "millisecond";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-49.54105);
    
    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.0003787018);
    
    // rY[2]:
    this->mVariableNames.push_back("sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.250113);
    
    // rY[3]:
    this->mVariableNames.push_back("sodium_current_h_gate__h1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001386897);
    
    // rY[4]:
    this->mVariableNames.push_back("sodium_current_h_gate__h2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.002065463);
    
    // rY[5]:
    this->mVariableNames.push_back("L_type_Ca_channel_d_gate__d_L");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.002572773);
    
    // rY[6]:
    this->mVariableNames.push_back("L_type_Ca_channel_f_gate__f_L");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.98651);
    
    // rY[7]:
    this->mVariableNames.push_back("T_type_Ca_channel_d_gate__d_T");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.02012114);
    
    // rY[8]:
    this->mVariableNames.push_back("T_type_Ca_channel_f_gate__f_T");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.1945111);
    
    // rY[9]:
    this->mVariableNames.push_back("delayed_rectifying_potassium_current_P_a_gate__P_a");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.02302278);
    
    // rY[10]:
    this->mVariableNames.push_back("delayed_rectifying_potassium_current_P_i_gate__P_i");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.3777728);
    
    // rY[11]:
    this->mVariableNames.push_back("hyperpolarisation_activated_current_y_gate__y");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.09227776);
    
    // rY[12]:
    this->mVariableNames.push_back("cytosolic_sodium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(9.701621);
    
    // rY[13]:
    this->mVariableNames.push_back("cytosolic_potassium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(140.7347);
    
    // rY[14]:
    this->mVariableNames.push_back("intracellular_concentrations_and_buffer_equations__Ca_Calmod");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.1411678);
    
    // rY[15]:
    this->mVariableNames.push_back("intracellular_concentrations_and_buffer_equations__Ca_Trop");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.07331396);
    
    // rY[16]:
    this->mVariableNames.push_back("intracellular_concentrations_and_buffer_equations__Ca_Mg_Trop");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.7618549);
    
    // rY[17]:
    this->mVariableNames.push_back("intracellular_concentrations_and_buffer_equations__Mg_Mg_Trop");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.2097049);
    
    // rY[18]:
    this->mVariableNames.push_back("extracellular_sodium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(139.9988);
    
    // rY[19]:
    this->mVariableNames.push_back("extracellular_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(2.00474);
    
    // rY[20]:
    this->mVariableNames.push_back("extracellular_potassium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(5.389014);
    
    // rY[21]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__Ca_up");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(16.95311);
    
    // rY[22]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__Ca_rel");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(16.85024);
    
    // rY[23]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__Ca_Calse");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.9528726);
    
    // rY[24]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__F1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.1133251);
    
    // rY[25]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__F2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0007594214);
    
    // rY[26]:
    this->mVariableNames.push_back("SR_Ca_uptake_and_release__F3");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.8859153);
    
    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Celldemir_model_1994FromCellML)
