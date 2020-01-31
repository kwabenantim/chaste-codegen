//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: zhang_SAN_model_2000_all
//! 
//! Processed by weblab_cg: https://github.com/ModellingWebLab/weblab-cg
//!     (translator: weblab_cg, model type: normal, options: )
//! on 2020-01-29 23:15:47
//! 
//! <autogenerated>

#include "zhang_SAN_model_2000_all.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"
    
    Cellzhang_SAN_model_2000_allFromCellML::Cellzhang_SAN_model_2000_allFromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                15,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellzhang_SAN_model_2000_allFromCellML>::Instance();
        Init();
        
    }
    
    Cellzhang_SAN_model_2000_allFromCellML::~Cellzhang_SAN_model_2000_allFromCellML()
    {
    }

    double Cellzhang_SAN_model_2000_allFromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -39.013558536
        double var_chaste_interface__sodium_current_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.092361701692
        double var_chaste_interface__sodium_current_h_gate__h1 = rY[2];
        // Units: dimensionless; Initial value: 0.015905380261
        double var_chaste_interface__sodium_current_h_gate__h2 = rY[3];
        // Units: dimensionless; Initial value: 0.01445216109
        double var_chaste_interface__L_type_Ca_channel_d_gate__d_L = rY[4];
        // Units: dimensionless; Initial value: 0.04804900895
        double var_chaste_interface__L_type_Ca_channel_f_gate__f_L = rY[5];
        // Units: dimensionless; Initial value: 0.48779845203
        double var_chaste_interface__T_type_Ca_channel_d_gate__d_T = rY[6];
        // Units: dimensionless; Initial value: 0.42074047435
        double var_chaste_interface__T_type_Ca_channel_f_gate__f_T = rY[7];
        // Units: dimensionless; Initial value: 0.038968420558
        double var_chaste_interface__four_AP_sensitive_currents_q_gate__q = rY[8];
        // Units: dimensionless; Initial value: 0.29760539675
        double var_chaste_interface__four_AP_sensitive_currents_r_gate__r = rY[9];
        // Units: dimensionless; Initial value: 0.064402950262
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_af_gate__P_af = rY[10];
        // Units: dimensionless; Initial value: 0.13034201158
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_as_gate__P_as = rY[11];
        // Units: dimensionless; Initial value: 0.46960956028
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_i_gate__P_i = rY[12];
        // Units: dimensionless; Initial value: 0.87993375273
        double var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs = rY[13];
        // Units: dimensionless; Initial value: 0.082293827208
        double var_chaste_interface__hyperpolarisation_activated_current_y_gate__y = rY[14];
        // Units: dimensionless; Initial value: 0.03889291759
        
        const double var_membrane__FCell = 0; // dimensionless
        const double var_L_type_Ca_channel__i_Ca_L = (0.0057938 + 0.060092679999999996 * var_membrane__FCell) * (-46.4 + var_chaste_interface__membrane__V) * (0.006 / (1.0 + exp(-2.3499999999999996 - 0.16666666666666666 * var_chaste_interface__membrane__V)) + var_chaste_interface__L_type_Ca_channel_d_gate__d_L * var_chaste_interface__L_type_Ca_channel_f_gate__f_L); // nanoA
        const double var_T_type_Ca_channel__i_Ca_T = (0.00427806 + 0.00960424 * var_membrane__FCell) * (-45.0 + var_chaste_interface__membrane__V) * var_chaste_interface__T_type_Ca_channel_d_gate__d_T * var_chaste_interface__T_type_Ca_channel_f_gate__f_T; // nanoA
        const double var_persistent_calcium_current__i_Ca_p = 0; // nanoA
        const double var_calcium_background_current__i_b_Ca = (1.3236e-05 + 2.9715999999999998e-05 * var_membrane__FCell) * (-131.78096240721493 + var_chaste_interface__membrane__V); // nanoA
        const double var_four_AP_sensitive_currents__i_sus = (6.645504e-05 + 0.01131730496 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__four_AP_sensitive_currents_r_gate__r; // nanoA
        const double var_four_AP_sensitive_currents__i_to = (0.004905 + 0.03159 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__four_AP_sensitive_currents_q_gate__q * var_chaste_interface__four_AP_sensitive_currents_r_gate__r; // nanoA
        const double var_hyperpolarisation_activated_current__i_f_K = (0.0005465 + 0.0063285 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__hyperpolarisation_activated_current_y_gate__y; // nanoA
        const double var_potassium_background_current__i_b_K = (2.523636e-05 + 5.6655639999999996e-05 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V); // nanoA
        const double var_rapid_delayed_rectifying_potassium_current__i_K_r = (86.63192939742034 + var_chaste_interface__membrane__V) * (0.00079704 + 0.01520296 * var_membrane__FCell) * (0.4 * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_as_gate__P_as + 0.6 * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_af_gate__P_af) * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_i_gate__P_i; // nanoA
        const double var_hyperpolarisation_activated_current__i_f_Na = (0.0005465 + 0.0063285 * var_membrane__FCell) * (-76.17187070529977 + var_chaste_interface__membrane__V) * var_chaste_interface__hyperpolarisation_activated_current_y_gate__y; // nanoA
        const double var_slow_delayed_rectifying_potassium_current__i_K_s = pow(var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs, 2.0) * (71.36532285219698 + var_chaste_interface__membrane__V) * (0.0003445 + 0.0100555 * var_membrane__FCell); // nanoA
        const double var_sodium_background_current__i_b_Na = (5.81818e-05 + 0.0001306182 * var_membrane__FCell) * (-76.17187070529977 + var_chaste_interface__membrane__V); // nanoA
        const double var_sodium_calcium_exchanger__i_NaCa = 0.8850810734263259 * (2.7229e-06 + 6.112940000000001e-06 * var_membrane__FCell) * (1024.0 * exp(0.018715 * var_chaste_interface__membrane__V) - 274.40000000000003 * exp(-0.018715 * var_chaste_interface__membrane__V)); // nanoA
        const double var_sodium_current__i_Na = 0.6133907402414893 * pow(var_chaste_interface__sodium_current_m_gate__m, 3.0) * (-1.0 + exp(-2.8622008809294686 + 0.03757556240154578 * var_chaste_interface__membrane__V)) * ((0.91307 - 0.09518 * exp(-2.169264 - 0.06306 * var_chaste_interface__membrane__V) / (1.0 + 1.662 * exp(-14.33887 - 0.2251 * var_chaste_interface__membrane__V))) * var_chaste_interface__sodium_current_h_gate__h1 + (0.08693 + 0.09518 * exp(-2.169264 - 0.06306 * var_chaste_interface__membrane__V) / (1.0 + 1.662 * exp(-14.33887 - 0.2251 * var_chaste_interface__membrane__V))) * var_chaste_interface__sodium_current_h_gate__h2) * var_membrane__FCell * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757556240154578 * var_chaste_interface__membrane__V)); // nanoA
        const double var_sodium_potassium_pump__i_p = 0.25965524392018957 * (0.04782545 + 0.10736815 * var_membrane__FCell) / (1.5 + exp(-1.5 - 0.025 * var_chaste_interface__membrane__V)); // nanoA
        const double var_chaste_interface__i_ionic = (0.001 * var_L_type_Ca_channel__i_Ca_L + 0.001 * var_T_type_Ca_channel__i_Ca_T + 0.001 * var_calcium_background_current__i_b_Ca + 0.001 * var_four_AP_sensitive_currents__i_sus + 0.001 * var_four_AP_sensitive_currents__i_to + 0.001 * var_hyperpolarisation_activated_current__i_f_K + 0.001 * var_hyperpolarisation_activated_current__i_f_Na + 0.001 * var_persistent_calcium_current__i_Ca_p + 0.001 * var_potassium_background_current__i_b_K + 0.001 * var_rapid_delayed_rectifying_potassium_current__i_K_r + 0.001 * var_slow_delayed_rectifying_potassium_current__i_K_s + 0.001 * var_sodium_background_current__i_b_Na + 0.001 * var_sodium_calcium_exchanger__i_NaCa + 0.001 * var_sodium_current__i_Na + 0.001 * var_sodium_potassium_pump__i_p) * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Cellzhang_SAN_model_2000_allFromCellML::EvaluateYDerivatives(double var_chaste_interface__environment__time_converted, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -39.013558536
        double var_chaste_interface__sodium_current_m_gate__m = rY[1];
        // Units: dimensionless; Initial value: 0.092361701692
        double var_chaste_interface__sodium_current_h_gate__h1 = rY[2];
        // Units: dimensionless; Initial value: 0.015905380261
        double var_chaste_interface__sodium_current_h_gate__h2 = rY[3];
        // Units: dimensionless; Initial value: 0.01445216109
        double var_chaste_interface__L_type_Ca_channel_d_gate__d_L = rY[4];
        // Units: dimensionless; Initial value: 0.04804900895
        double var_chaste_interface__L_type_Ca_channel_f_gate__f_L = rY[5];
        // Units: dimensionless; Initial value: 0.48779845203
        double var_chaste_interface__T_type_Ca_channel_d_gate__d_T = rY[6];
        // Units: dimensionless; Initial value: 0.42074047435
        double var_chaste_interface__T_type_Ca_channel_f_gate__f_T = rY[7];
        // Units: dimensionless; Initial value: 0.038968420558
        double var_chaste_interface__four_AP_sensitive_currents_q_gate__q = rY[8];
        // Units: dimensionless; Initial value: 0.29760539675
        double var_chaste_interface__four_AP_sensitive_currents_r_gate__r = rY[9];
        // Units: dimensionless; Initial value: 0.064402950262
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_af_gate__P_af = rY[10];
        // Units: dimensionless; Initial value: 0.13034201158
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_as_gate__P_as = rY[11];
        // Units: dimensionless; Initial value: 0.46960956028
        double var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_i_gate__P_i = rY[12];
        // Units: dimensionless; Initial value: 0.87993375273
        double var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs = rY[13];
        // Units: dimensionless; Initial value: 0.082293827208
        double var_chaste_interface__hyperpolarisation_activated_current_y_gate__y = rY[14];
        // Units: dimensionless; Initial value: 0.03889291759
        
        // Mathematics
        double d_dt_chaste_interface_var_membrane__V;
        const double d_dt_chaste_interface_var_T_type_Ca_channel_d_gate__d_T = 0.001 * (-var_chaste_interface__T_type_Ca_channel_d_gate__d_T + 1.0 / (1.0 + exp(-5.4411764705882355 - 0.14705882352941177 * var_chaste_interface__membrane__V))) * (1068.0 * exp(0.8766666666666667 + 0.03333333333333333 * var_chaste_interface__membrane__V) + 1068.0 * exp(-0.8766666666666667 - 0.03333333333333333 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_four_AP_sensitive_currents_r_gate__r = 0.001 * (-var_chaste_interface__four_AP_sensitive_currents_r_gate__r + 1.0 / (1.0 + exp(0.5548223350253807 - 0.050761421319796954 * var_chaste_interface__membrane__V))) / (0.0029775 + 0.019595 / (1.037 * exp(2.7585732000000003 + 0.09012 * var_chaste_interface__membrane__V) + 0.369 * exp(-2.83696 - 0.119 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double d_dt_chaste_interface_var_hyperpolarisation_activated_current_y_gate__y = 0.001 * (1.0 - var_chaste_interface__hyperpolarisation_activated_current_y_gate__y) * exp(-2.963199399173864 - 0.03755163349605708 * var_chaste_interface__membrane__V) - 0.001 * var_chaste_interface__hyperpolarisation_activated_current_y_gate__y * exp(3.535529411764706 + 0.047058823529411764 * var_chaste_interface__membrane__V); // 1 / millisecond
        const double var_membrane__FCell = 0; // dimensionless
        const double d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d_L = 0.001 * (-var_chaste_interface__L_type_Ca_channel_d_gate__d_L + 1.0 / (1.0 + exp(-3.716666666666667 - 0.13333333333333333 * var_membrane__FCell - 0.16666666666666666 * var_chaste_interface__membrane__V))) * (5.715 * (-5.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(-2.0 + 0.4 * var_chaste_interface__membrane__V)) - 14.195 * (35.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(-14.0 - 0.4 * var_chaste_interface__membrane__V)) - 42.45 * var_chaste_interface__membrane__V / (-1.0 + exp(-0.208 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f_L = 0.001 * (-var_chaste_interface__L_type_Ca_channel_f_gate__f_L + 1.0 / (1.0 + exp(9.0 + 0.2 * var_chaste_interface__membrane__V))) * (30.0 / (1.0 + exp(-7.0 - 0.25 * var_chaste_interface__membrane__V)) + 3.75 * (28.0 + var_chaste_interface__membrane__V) / (-1.0 + exp(7.0 + 0.25 * var_chaste_interface__membrane__V))) / (1.2 - 0.2 * var_membrane__FCell); // 1 / millisecond
        const double d_dt_chaste_interface_var_T_type_Ca_channel_f_gate__f_T = 0.001 * (-var_chaste_interface__T_type_Ca_channel_f_gate__f_T + 1.0 / (1.0 + exp(7.888888888888888 + 0.1111111111111111 * var_chaste_interface__membrane__V))) * (15.0 * exp(4.616384915474642 + 0.06501950585175552 * var_chaste_interface__membrane__V) + 15.3 * exp(-0.8523409363745499 - 0.012004801920768308 * var_chaste_interface__membrane__V - 0.008403361344537815 * var_membrane__FCell)); // 1 / millisecond
        const double d_dt_chaste_interface_var_four_AP_sensitive_currents_q_gate__q = 0.001 * (-var_chaste_interface__four_AP_sensitive_currents_q_gate__q + 1.0 / (1.0 + exp(4.53206106870229 + 0.07633587786259542 * var_chaste_interface__membrane__V))) / (0.010103333333333332 + 0.06516666666666666 / (0.5686 * exp(-3.1827900000000002 - 0.8161 * var_membrane__FCell - 0.08161 * var_chaste_interface__membrane__V) + 0.7174 * exp(1.0 * (0.2719 - 0.1719 * var_membrane__FCell) * (40.93 + 10.0 * var_membrane__FCell + var_chaste_interface__membrane__V)))); // 1 / millisecond
        const double var_rapid_delayed_rectifying_potassium_current_P_af_gate__P_af_infinity = 1.0 / (1.0 + exp(-1.3396226415094339 - 0.09433962264150944 * var_chaste_interface__membrane__V)); // dimensionless
        const double d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_af_gate__P_af = 0.001 * (-var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_af_gate__P_af + var_rapid_delayed_rectifying_potassium_current_P_af_gate__P_af_infinity) * (0.96 * exp(0.4 - 0.044444444444444446 * var_chaste_interface__membrane__V) + 37.2 * exp(-0.5660377358490566 + 0.06289308176100629 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_as_gate__P_as = 0.001 * (-var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_as_gate__P_as + var_rapid_delayed_rectifying_potassium_current_P_af_gate__P_af_infinity) * (4.2 * exp(-0.5294117647058824 + 0.058823529411764705 * var_chaste_interface__membrane__V) + 0.15 * exp(0.41666666666666663 - 0.046296296296296294 * var_chaste_interface__membrane__V)); // 1 / millisecond
        const double d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_i_gate__P_i = 0.5 / (1.0 + exp(1.8415841584158419 + 0.09900990099009901 * var_chaste_interface__membrane__V)) - 0.5 * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_i_gate__P_i; // 1 / millisecond
        const double d_dt_chaste_interface_var_slow_delayed_rectifying_potassium_current_xs_gate__xs = 0.014 * (1.0 - var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs) / (1.0 + exp(4.444444444444445 - 0.1111111111111111 * var_chaste_interface__membrane__V)) - 0.001 * var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs * exp(-0.022222222222222223 * var_chaste_interface__membrane__V); // 1 / millisecond
        const double var_sodium_current_h_gate__h1_infinity = 1.0 / (1.0 + exp(10.328125 + 0.15625 * var_chaste_interface__membrane__V)); // dimensionless
        const double d_dt_chaste_interface_var_sodium_current_h_gate__h1 = 0.001 * (-var_chaste_interface__sodium_current_h_gate__h1 + var_sodium_current_h_gate__h1_infinity) / (0.0005977 + 3.717e-06 * exp(-4.816464999999999 - 0.2815 * var_chaste_interface__membrane__V) / (1.0 + 0.003732 * exp(-12.936576 - 0.3426 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double d_dt_chaste_interface_var_sodium_current_h_gate__h2 = 0.001 * (-var_chaste_interface__sodium_current_h_gate__h2 + var_sodium_current_h_gate__h1_infinity) / (0.003556 + 3.186e-08 * exp(-11.69172 - 0.6219 * var_chaste_interface__membrane__V) / (1.0 + 7.189e-05 * exp(-22.768981 - 0.6683 * var_chaste_interface__membrane__V))); // 1 / millisecond
        const double d_dt_chaste_interface_var_sodium_current_m_gate__m = 0.001 * (-var_chaste_interface__sodium_current_m_gate__m + 1.0 * pow(1 / (1.0 + exp(-5.553113553113553 - 0.18315018315018314 * var_chaste_interface__membrane__V)), 0.3333333333333333)) / (4.569e-05 + 0.0006247 / (0.6274 * exp(5.35057813 + 0.0823 * var_chaste_interface__membrane__V) + 0.8322166 * exp(-19.034003092000003 - 0.33566 * var_chaste_interface__membrane__V))); // 1 / millisecond
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_membrane__V = -0.001 * ((2.523636e-05 + 5.6655639999999996e-05 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) + (1.3236e-05 + 2.9715999999999998e-05 * var_membrane__FCell) * (-131.78096240721493 + var_chaste_interface__membrane__V) + (5.81818e-05 + 0.0001306182 * var_membrane__FCell) * (-76.17187070529977 + var_chaste_interface__membrane__V) + 0.8850810734263259 * (2.7229e-06 + 6.112940000000001e-06 * var_membrane__FCell) * (1024.0 * exp(0.018715 * var_chaste_interface__membrane__V) - 274.40000000000003 * exp(-0.018715 * var_chaste_interface__membrane__V)) + 0.25965524392018957 * (0.04782545 + 0.10736815 * var_membrane__FCell) / (1.5 + exp(-1.5 - 0.025 * var_chaste_interface__membrane__V)) + pow(var_chaste_interface__slow_delayed_rectifying_potassium_current_xs_gate__xs, 2.0) * (71.36532285219698 + var_chaste_interface__membrane__V) * (0.0003445 + 0.0100555 * var_membrane__FCell) + (0.0057938 + 0.060092679999999996 * var_membrane__FCell) * (-46.4 + var_chaste_interface__membrane__V) * (0.006 / (1.0 + exp(-2.3499999999999996 - 0.16666666666666666 * var_chaste_interface__membrane__V)) + var_chaste_interface__L_type_Ca_channel_d_gate__d_L * var_chaste_interface__L_type_Ca_channel_f_gate__f_L) + (6.645504e-05 + 0.01131730496 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__four_AP_sensitive_currents_r_gate__r + (0.0005465 + 0.0063285 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__hyperpolarisation_activated_current_y_gate__y + (0.0005465 + 0.0063285 * var_membrane__FCell) * (-76.17187070529977 + var_chaste_interface__membrane__V) * var_chaste_interface__hyperpolarisation_activated_current_y_gate__y + (0.00427806 + 0.00960424 * var_membrane__FCell) * (-45.0 + var_chaste_interface__membrane__V) * var_chaste_interface__T_type_Ca_channel_d_gate__d_T * var_chaste_interface__T_type_Ca_channel_f_gate__f_T + (0.004905 + 0.03159 * var_membrane__FCell) * (86.63192939742034 + var_chaste_interface__membrane__V) * var_chaste_interface__four_AP_sensitive_currents_q_gate__q * var_chaste_interface__four_AP_sensitive_currents_r_gate__r + (86.63192939742034 + var_chaste_interface__membrane__V) * (0.00079704 + 0.01520296 * var_membrane__FCell) * (0.4 * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_as_gate__P_as + 0.6 * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_af_gate__P_af) * var_chaste_interface__rapid_delayed_rectifying_potassium_current_P_i_gate__P_i + 0.6133907402414893 * pow(var_chaste_interface__sodium_current_m_gate__m, 3.0) * (-1.0 + exp(-2.8622008809294686 + 0.03757556240154578 * var_chaste_interface__membrane__V)) * ((0.91307 - 0.09518 * exp(-2.169264 - 0.06306 * var_chaste_interface__membrane__V) / (1.0 + 1.662 * exp(-14.33887 - 0.2251 * var_chaste_interface__membrane__V))) * var_chaste_interface__sodium_current_h_gate__h1 + (0.08693 + 0.09518 * exp(-2.169264 - 0.06306 * var_chaste_interface__membrane__V) / (1.0 + 1.662 * exp(-14.33887 - 0.2251 * var_chaste_interface__membrane__V))) * var_chaste_interface__sodium_current_h_gate__h2) * var_membrane__FCell * var_chaste_interface__membrane__V / (-1.0 + exp(0.03757556240154578 * var_chaste_interface__membrane__V))) / (2e-05 + 4.4999999999999996e-05 * var_membrane__FCell); // millivolt / millisecond
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__V;
        rDY[1] = d_dt_chaste_interface_var_sodium_current_m_gate__m;
        rDY[2] = d_dt_chaste_interface_var_sodium_current_h_gate__h1;
        rDY[3] = d_dt_chaste_interface_var_sodium_current_h_gate__h2;
        rDY[4] = d_dt_chaste_interface_var_L_type_Ca_channel_d_gate__d_L;
        rDY[5] = d_dt_chaste_interface_var_L_type_Ca_channel_f_gate__f_L;
        rDY[6] = d_dt_chaste_interface_var_T_type_Ca_channel_d_gate__d_T;
        rDY[7] = d_dt_chaste_interface_var_T_type_Ca_channel_f_gate__f_T;
        rDY[8] = d_dt_chaste_interface_var_four_AP_sensitive_currents_q_gate__q;
        rDY[9] = d_dt_chaste_interface_var_four_AP_sensitive_currents_r_gate__r;
        rDY[10] = d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_af_gate__P_af;
        rDY[11] = d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_as_gate__P_as;
        rDY[12] = d_dt_chaste_interface_var_rapid_delayed_rectifying_potassium_current_P_i_gate__P_i;
        rDY[13] = d_dt_chaste_interface_var_slow_delayed_rectifying_potassium_current_xs_gate__xs;
        rDY[14] = d_dt_chaste_interface_var_hyperpolarisation_activated_current_y_gate__y;
    }

template<>
void OdeSystemInformation<Cellzhang_SAN_model_2000_allFromCellML>::Initialise(void)
{
    this->mSystemName = "zhang_SAN_model_2000_all";
    this->mFreeVariableName = "environment__time_converted";
    this->mFreeVariableUnits = "millisecond";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-39.013558536);
    
    // rY[1]:
    this->mVariableNames.push_back("sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.092361701692);
    
    // rY[2]:
    this->mVariableNames.push_back("sodium_current_h_gate__h1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.015905380261);
    
    // rY[3]:
    this->mVariableNames.push_back("sodium_current_h_gate__h2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.01445216109);
    
    // rY[4]:
    this->mVariableNames.push_back("L_type_Ca_channel_d_gate__d_L");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.04804900895);
    
    // rY[5]:
    this->mVariableNames.push_back("L_type_Ca_channel_f_gate__f_L");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.48779845203);
    
    // rY[6]:
    this->mVariableNames.push_back("T_type_Ca_channel_d_gate__d_T");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.42074047435);
    
    // rY[7]:
    this->mVariableNames.push_back("T_type_Ca_channel_f_gate__f_T");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.038968420558);
    
    // rY[8]:
    this->mVariableNames.push_back("four_AP_sensitive_currents_q_gate__q");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.29760539675);
    
    // rY[9]:
    this->mVariableNames.push_back("four_AP_sensitive_currents_r_gate__r");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.064402950262);
    
    // rY[10]:
    this->mVariableNames.push_back("rapid_delayed_rectifying_potassium_current_P_af_gate__P_af");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.13034201158);
    
    // rY[11]:
    this->mVariableNames.push_back("rapid_delayed_rectifying_potassium_current_P_as_gate__P_as");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.46960956028);
    
    // rY[12]:
    this->mVariableNames.push_back("rapid_delayed_rectifying_potassium_current_P_i_gate__P_i");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.87993375273);
    
    // rY[13]:
    this->mVariableNames.push_back("slow_delayed_rectifying_potassium_current_xs_gate__xs");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.082293827208);
    
    // rY[14]:
    this->mVariableNames.push_back("hyperpolarisation_activated_current_y_gate__y");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.03889291759);
    
    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellzhang_SAN_model_2000_allFromCellML)
