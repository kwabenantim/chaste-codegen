//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: hund_rudy_2004
//! 
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: normal)
//! on 2020-01-29 23:07:17
//! 
//! <autogenerated>

#include "hund_rudy_2004_a.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

    boost::shared_ptr<RegularStimulus> Cellhund_rudy_2004_aFromCellML::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__cell__stim_amplitude = -15.0 * HeartConfig::Instance()->GetCapacitance(); // uA_per_uF
        const double var_chaste_interface__cell__stim_duration = 3.0; // millisecond
        const double var_chaste_interface__cell__stim_offset = 0.0; // millisecond
        const double var_chaste_interface__cell__stim_period = 1000.0; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__cell__stim_amplitude),
                var_chaste_interface__cell__stim_duration,
                var_chaste_interface__cell__stim_period,
                var_chaste_interface__cell__stim_offset
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }
    
    double Cellhund_rudy_2004_aFromCellML::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }
    
    Cellhund_rudy_2004_aFromCellML::Cellhund_rudy_2004_aFromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                29,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellhund_rudy_2004_aFromCellML>::Instance();
        Init();
        
        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
    }
    
    Cellhund_rudy_2004_aFromCellML::~Cellhund_rudy_2004_aFromCellML()
    {
    }

    double Cellhund_rudy_2004_aFromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__cell__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -85.781844107117
        double var_chaste_interface__Ca__Ca_i = rY[1];
        // Units: mM; Initial value: 0.00012131666
        double var_chaste_interface__INa__H = rY[2];
        // Units: dimensionless; Initial value: 0.987317750543
        double var_chaste_interface__INa__m = rY[3];
        // Units: dimensionless; Initial value: 0.001356538159
        double var_chaste_interface__INa__J = rY[4];
        // Units: dimensionless; Initial value: 0.991924983076
        double var_chaste_interface__ICaL__d = rY[5];
        // Units: dimensionless; Initial value: 1.64013e-06
        double var_chaste_interface__ICaL__dp = rY[6];
        // Units: dimensionless; Initial value: 8.98230672628
        double var_chaste_interface__ICaL__f = rY[7];
        // Units: dimensionless; Initial value: 0.999961508634
        double var_chaste_interface__ICaL__fca = rY[8];
        // Units: dimensionless; Initial value: 0.97836624923
        double var_chaste_interface__ICaL__fca2 = rY[9];
        // Units: dimensionless; Initial value: 0.893052931249
        double var_chaste_interface__ICaL__f2 = rY[10];
        // Units: dimensionless; Initial value: 0.992234519148
        double var_chaste_interface__IKr__xr = rY[11];
        // Units: dimensionless; Initial value: 7.24074e-06
        double var_chaste_interface__IKs__xs1 = rY[12];
        // Units: dimensionless; Initial value: 0.019883138161
        double var_chaste_interface__IKs__xs2 = rY[13];
        // Units: dimensionless; Initial value: 0.019890650554
        double var_chaste_interface__Ito__ydv = rY[14];
        // Units: dimensionless; Initial value: 0.013970786703
        double var_chaste_interface__Ito__ydv2 = rY[15];
        // Units: dimensionless; Initial value: 0.99996472752
        double var_chaste_interface__Ito__zdv = rY[16];
        // Units: dimensionless; Initial value: 0.829206149767
        double var_chaste_interface__Ito2__AA = rY[17];
        // Units: dimensionless; Initial value: 0.000816605172
        double var_chaste_interface__INal__mL = rY[18];
        // Units: dimensionless; Initial value: 0.001356538159
        double var_chaste_interface__INal__hL = rY[19];
        // Units: dimensionless; Initial value: 0.26130711759
        double var_chaste_interface__Na__Na_i = rY[23];
        // Units: mM; Initial value: 12.972433387269
        double var_chaste_interface__K__K_i = rY[24];
        // Units: mM; Initial value: 135.469546216758
        double var_chaste_interface__Cl__Cl_i = rY[25];
        // Units: mM; Initial value: 15.59207157178
        double var_chaste_interface__Ca__Ca_ss = rY[28];
        // Units: mM; Initial value: 0.00012271265
        
        const double var_INaCa__ca_i_NaCa = 1.5 * var_chaste_interface__Ca__Ca_i; // mM
        const double var_INaCa__INaCa = 4.5 * (1.8 * pow(var_chaste_interface__Na__Na_i, 3.0) * exp(0.01310255922773 * var_chaste_interface__cell__V) - 2744000.0 * var_INaCa__ca_i_NaCa * exp(-0.024333324280070002 * var_chaste_interface__cell__V)) / ((1.0 + 0.27 * exp(-0.024333324280070002 * var_chaste_interface__cell__V)) * (1.0 + 1.5625e-08 * pow(1 / var_INaCa__ca_i_NaCa, 2.0)) * (13227.9606 + 4344355.375 * var_INaCa__ca_i_NaCa + 8.408493299091228 * pow(var_chaste_interface__Na__Na_i, 3.0))); // uA_per_uF
        const double var_INaK__INaK = 0.48423913043478267 / ((1.0 + 100.0 * pow(1 / var_chaste_interface__Na__Na_i, 2.0)) * (1.0 + 0.1245 * exp(-0.00374358835078 * var_chaste_interface__cell__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.0374358835078 * var_chaste_interface__cell__V))); // uA_per_uF
        const double var_cell__caiont = -2.0 * var_INaCa__INaCa + 0.0575 * var_chaste_interface__Ca__Ca_i / (0.0005 + var_chaste_interface__Ca__Ca_i) + 0.0028824983370005666 * (-0.6138 + var_chaste_interface__Ca__Ca_i * exp(0.0748717670156 * var_chaste_interface__cell__V)) * var_chaste_interface__cell__V / (-1.0 + exp(0.0748717670156 * var_chaste_interface__cell__V)) + 3.5108651860830804 * pow(var_chaste_interface__ICaL__d, var_chaste_interface__ICaL__dp) * (-15.0 + var_chaste_interface__cell__V) * (-0.6138 + 1.0 * var_chaste_interface__Ca__Ca_ss * exp(-1.123076505234 + 0.0748717670156 * var_chaste_interface__cell__V)) * var_chaste_interface__ICaL__f * var_chaste_interface__ICaL__f2 * var_chaste_interface__ICaL__fca * var_chaste_interface__ICaL__fca2 / (-1.0 + exp(-1.123076505234 + 0.0748717670156 * var_chaste_interface__cell__V)); // uA_per_uF
        const double var_cell__clont = 0.000225 * var_chaste_interface__cell__V + 0.00601027620873753 * log(100.0 / var_chaste_interface__Cl__Cl_i) + 0.001444800488100033 * (-100.0 * exp(0.0374358835078 * var_chaste_interface__cell__V) + var_chaste_interface__Cl__Cl_i) * var_chaste_interface__Ito2__AA * var_chaste_interface__cell__V / (1.0 - exp(0.0374358835078 * var_chaste_interface__cell__V)); // uA_per_uF
        const double var_reversal_potentials__EK = 26.712338705500134 * log(5.4 / var_chaste_interface__K__K_i); // mV
        const double var_reversal_potentials__ENa = 26.712338705500134 * log(140.0 / var_chaste_interface__Na__Na_i); // mV
        const double var_cell__naiont = 3.0 * var_INaCa__INaCa + 3.0 * var_INaK__INaK + 0.0065 * pow(var_chaste_interface__INal__mL, 3.0) * (-var_reversal_potentials__ENa + var_chaste_interface__cell__V) * var_chaste_interface__INal__hL + 8.25 * pow(var_chaste_interface__INa__m, 3) * (-var_reversal_potentials__ENa + var_chaste_interface__cell__V) * var_chaste_interface__INa__H * var_chaste_interface__INa__J; // uA_per_uF
        const double var_cell__kiont = -2.0 * var_INaK__INaK + 0.00276 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) / (1.0 + exp(1.2521739130434784 - 0.16722408026755853 * var_chaste_interface__cell__V)) + 0.51 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) / ((1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__cell__V - 0.2385 * var_reversal_potentials__EK)) * (1.02 / (1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__cell__V - 0.2385 * var_reversal_potentials__EK)) + (1.0 * exp(-36.6986425 + 0.06175 * var_chaste_interface__cell__V - 0.06175 * var_reversal_potentials__EK) + 0.49124 * exp(0.43983232 + 0.08032 * var_chaste_interface__cell__V - 0.08032 * var_reversal_potentials__EK)) / (1.0 + exp(-2.4444679 + 0.5143 * var_reversal_potentials__EK - 0.5143 * var_chaste_interface__cell__V)))) + 0.0138542 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) * var_chaste_interface__IKr__xr / (1.0 + exp(0.6493506493506493 + 0.06493506493506493 * var_chaste_interface__cell__V)) + (0.0248975 + 0.014938499999999999 / (1.0 + 6.481821026062645e-07 * pow(1 / var_chaste_interface__Ca__Ca_i, 1.4))) * (-26.712338705500134 * log(7.966200000000001 / (0.01833 * var_chaste_interface__Na__Na_i + var_chaste_interface__K__K_i)) + var_chaste_interface__cell__V) * var_chaste_interface__IKs__xs1 * var_chaste_interface__IKs__xs2 + 0.19 * pow(var_chaste_interface__Ito__ydv, 3.0) * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) * var_chaste_interface__Ito__ydv2 * var_chaste_interface__Ito__zdv * exp(0.0033333333333333335 * var_chaste_interface__cell__V); // uA_per_uF
        const double var_chaste_interface__i_ionic = (var_cell__caiont + var_cell__clont + var_cell__kiont + var_cell__naiont) * HeartConfig::Instance()->GetCapacitance(); // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Cellhund_rudy_2004_aFromCellML::EvaluateYDerivatives(double var_chaste_interface__Environment__time, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__cell__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -85.781844107117
        double var_chaste_interface__Ca__Ca_i = rY[1];
        // Units: mM; Initial value: 0.00012131666
        double var_chaste_interface__INa__H = rY[2];
        // Units: dimensionless; Initial value: 0.987317750543
        double var_chaste_interface__INa__m = rY[3];
        // Units: dimensionless; Initial value: 0.001356538159
        double var_chaste_interface__INa__J = rY[4];
        // Units: dimensionless; Initial value: 0.991924983076
        double var_chaste_interface__ICaL__d = rY[5];
        // Units: dimensionless; Initial value: 1.64013e-06
        double var_chaste_interface__ICaL__dp = rY[6];
        // Units: dimensionless; Initial value: 8.98230672628
        double var_chaste_interface__ICaL__f = rY[7];
        // Units: dimensionless; Initial value: 0.999961508634
        double var_chaste_interface__ICaL__fca = rY[8];
        // Units: dimensionless; Initial value: 0.97836624923
        double var_chaste_interface__ICaL__fca2 = rY[9];
        // Units: dimensionless; Initial value: 0.893052931249
        double var_chaste_interface__ICaL__f2 = rY[10];
        // Units: dimensionless; Initial value: 0.992234519148
        double var_chaste_interface__IKr__xr = rY[11];
        // Units: dimensionless; Initial value: 7.24074e-06
        double var_chaste_interface__IKs__xs1 = rY[12];
        // Units: dimensionless; Initial value: 0.019883138161
        double var_chaste_interface__IKs__xs2 = rY[13];
        // Units: dimensionless; Initial value: 0.019890650554
        double var_chaste_interface__Ito__ydv = rY[14];
        // Units: dimensionless; Initial value: 0.013970786703
        double var_chaste_interface__Ito__ydv2 = rY[15];
        // Units: dimensionless; Initial value: 0.99996472752
        double var_chaste_interface__Ito__zdv = rY[16];
        // Units: dimensionless; Initial value: 0.829206149767
        double var_chaste_interface__Ito2__AA = rY[17];
        // Units: dimensionless; Initial value: 0.000816605172
        double var_chaste_interface__INal__mL = rY[18];
        // Units: dimensionless; Initial value: 0.001356538159
        double var_chaste_interface__INal__hL = rY[19];
        // Units: dimensionless; Initial value: 0.26130711759
        double var_chaste_interface__Irel__CaMKtrap = rY[20];
        // Units: dimensionless; Initial value: 0.021123704774
        double var_chaste_interface__Irel__ro = rY[21];
        // Units: dimensionless; Initial value: 0.0
        double var_chaste_interface__Irel__ri = rY[22];
        // Units: dimensionless; Initial value: 0.862666650318
        double var_chaste_interface__Na__Na_i = rY[23];
        // Units: mM; Initial value: 12.972433387269
        double var_chaste_interface__K__K_i = rY[24];
        // Units: mM; Initial value: 135.469546216758
        double var_chaste_interface__Cl__Cl_i = rY[25];
        // Units: mM; Initial value: 15.59207157178
        double var_chaste_interface__Ca__Ca_jsr = rY[26];
        // Units: mM; Initial value: 1.737580994071
        double var_chaste_interface__Ca__Ca_nsr = rY[27];
        // Units: mM; Initial value: 1.832822335168
        double var_chaste_interface__Ca__Ca_ss = rY[28];
        // Units: mM; Initial value: 0.00012271265
        
        // Mathematics
        double d_dt_chaste_interface_var_cell__V;
        const double var_INaCa__ca_i_NaCa = 1.5 * var_chaste_interface__Ca__Ca_i; // mM
        const double var_Idiff_Itr__idiff = 5.0 * var_chaste_interface__Ca__Ca_ss - 5.0 * var_chaste_interface__Ca__Ca_i; // mM_per_ms
        const double var_Idiff_Itr__itr = 0.008333333333333333 * var_chaste_interface__Ca__Ca_nsr - 0.008333333333333333 * var_chaste_interface__Ca__Ca_jsr; // mM_per_ms
        const double var_IpCa__IpCa = 0.0575 * var_chaste_interface__Ca__Ca_i / (0.0005 + var_chaste_interface__Ca__Ca_i); // uA_per_uF
        const double var_Irel__CaMKactive = 0.05 * (1.0 - var_chaste_interface__Irel__CaMKtrap) / (1.0 + 0.0015 / var_chaste_interface__Ca__Ca_ss) + var_chaste_interface__Irel__CaMKtrap; // dimensionless
        const double d_dt_chaste_interface_var_Irel__CaMKtrap = -0.00068 * var_chaste_interface__Irel__CaMKtrap + 0.05 * (-var_chaste_interface__Irel__CaMKtrap + var_Irel__CaMKactive) * var_Irel__CaMKactive; // 1 / ms
        const double d_dt_chaste_interface_var_Ito2__AA = 1.0 / (1.0 + 0.1502 / var_chaste_interface__Ca__Ca_ss) - 1.0 * var_chaste_interface__Ito2__AA; // 1 / ms
        const double var_Iup_Ileak__iup = 0.004375 * (1.0 + 0.75 * var_Irel__CaMKactive / (0.15 + var_Irel__CaMKactive)) * var_chaste_interface__Ca__Ca_i / (0.00092 - 0.00017 * var_Irel__CaMKactive / (0.15 + var_Irel__CaMKactive) + var_chaste_interface__Ca__Ca_i); // mM_per_ms
        const double var_Iup_Ileak__ileak = 0.0002916666666666667 * var_chaste_interface__Ca__Ca_nsr; // mM_per_ms
        const double d_dt_chaste_interface_var_ICaL__dp = 0.9 - 0.1 * var_chaste_interface__ICaL__dp - 0.8 / (1.0 + exp(-19.11764705882353 - 0.29411764705882354 * var_chaste_interface__cell__V)); // 1 / ms
        const double var_ICaL__ibarca = 3.5108651860830804 * (-15.0 + var_chaste_interface__cell__V) * (-0.6138 + 1.0 * var_chaste_interface__Ca__Ca_ss * exp(-1.123076505234 + 0.0748717670156 * var_chaste_interface__cell__V)) / (-1.0 + exp(-1.123076505234 + 0.0748717670156 * var_chaste_interface__cell__V)); // uA_per_uF
        const double var_ICaL__ICaL = pow(var_chaste_interface__ICaL__d, var_chaste_interface__ICaL__dp) * var_chaste_interface__ICaL__f * var_chaste_interface__ICaL__f2 * var_chaste_interface__ICaL__fca * var_chaste_interface__ICaL__fca2 * var_ICaL__ibarca; // uA_per_uF
        const double d_dt_chaste_interface_var_ICaL__fca = (0.15 - var_chaste_interface__ICaL__fca + 0.55 / (1.0 + 333.3333333333333 * var_chaste_interface__Ca__Ca_ss) + 0.3 / (1.0 - 20.0 * var_ICaL__ICaL)) / (0.5 + 1.0 / (1.0 + 333.3333333333333 * var_chaste_interface__Ca__Ca_ss) + 10.0 * var_Irel__CaMKactive / (0.15 + var_Irel__CaMKactive)); // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__d = (-var_chaste_interface__ICaL__d + 1.0 / (1.0 + exp(0.5934718100890207 - 0.14836795252225518 * var_chaste_interface__cell__V))) / (0.59 + 0.8 * exp(0.6759999999999999 + 0.052 * var_chaste_interface__cell__V) / (1.0 + exp(1.7160000000000002 + 0.132 * var_chaste_interface__cell__V))); // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__f = (0.0529 + 0.2411 * exp(-0.19019454876899997 * pow((-1 + 0.10318426646304972 * var_chaste_interface__cell__V), 2.0))) * (0.3 - var_chaste_interface__ICaL__f + 0.7 / (1.0 + exp(2.4457142857142857 + 0.14285714285714285 * var_chaste_interface__cell__V))); // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__f2 = (0.0054 + 0.0423 * exp(-1.20074125971556 * pow((-1 + 0.05384275761067379 * var_chaste_interface__cell__V), 2.0))) * (0.23 - var_chaste_interface__ICaL__f2 + 0.77 / (1.0 + exp(2.4457142857142857 + 0.14285714285714285 * var_chaste_interface__cell__V))); // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__fca2 = (-var_chaste_interface__ICaL__fca2 + 1.0 / (1.0 - 100.0 * var_ICaL__ICaL)) / (125.0 + 300.0 / (1.0 + exp(-4.375 - 25.0 * var_ICaL__ICaL))); // 1 / ms
        const double var_ICab__ICab = 0.0028824983370005666 * (-0.6138 + var_chaste_interface__Ca__Ca_i * exp(0.0748717670156 * var_chaste_interface__cell__V)) * var_chaste_interface__cell__V / (-1.0 + exp(0.0748717670156 * var_chaste_interface__cell__V)); // uA_per_uF
        const double d_dt_chaste_interface_var_IKr__xr = (-var_chaste_interface__IKr__xr + 1.0 / (1.0 + exp(-2.3729411764705883 - 0.23529411764705882 * var_chaste_interface__cell__V))) * (0.0003 * (38.3608 + var_chaste_interface__cell__V) / (-1.0 + exp(5.83851376 + 0.1522 * var_chaste_interface__cell__V)) + 0.0006 * (-1.7384 + var_chaste_interface__cell__V) / (1.0 - exp(0.2364224 - 0.136 * var_chaste_interface__cell__V))); // 1 / ms
        const double var_IKs__tauxs = 1.0 / (7.61e-05 * (44.6 + var_chaste_interface__cell__V) / (1.0 - exp(-444.66200000000003 - 9.97 * var_chaste_interface__cell__V)) + 0.00036 * (-0.55 + var_chaste_interface__cell__V) / (-1.0 + exp(-0.0704 + 0.128 * var_chaste_interface__cell__V))); // ms
        const double var_IKs__xss = 1.0 / (1.0 + exp(0.4251012145748988 - 0.04048582995951417 * var_chaste_interface__cell__V)); // dimensionless
        const double d_dt_chaste_interface_var_IKs__xs1 = (-var_chaste_interface__IKs__xs1 + var_IKs__xss) / var_IKs__tauxs; // 1 / ms
        const double d_dt_chaste_interface_var_IKs__xs2 = 0.5 * (-var_chaste_interface__IKs__xs2 + var_IKs__xss) / var_IKs__tauxs; // 1 / ms
        const double d_dt_chaste_interface_var_INa__H = (1.0 - var_chaste_interface__INa__H) * ((var_chaste_interface__cell__V >= -40.0) ? (0.0) : (0.135 * exp(-11.764705882352942 - 0.14705882352941177 * var_chaste_interface__cell__V))) - ((var_chaste_interface__cell__V >= -40.0) ? (7.692307692307692 / (1.0 + exp(-0.9603603603603604 - 0.0900900900900901 * var_chaste_interface__cell__V))) : (310000.0 * exp(0.35 * var_chaste_interface__cell__V) + 3.56 * exp(0.079 * var_chaste_interface__cell__V))) * var_chaste_interface__INa__H; // 1 / ms
        const double d_dt_chaste_interface_var_INa__J = (1.0 - var_chaste_interface__INa__J) * ((var_chaste_interface__cell__V >= -40.0) ? (0.0) : (1.0 * (37.78 + var_chaste_interface__cell__V) * (-127140.0 * exp(0.2444 * var_chaste_interface__cell__V) - 3.474e-05 * exp(-0.04391 * var_chaste_interface__cell__V)) / (1.0 + exp(24.640530000000002 + 0.311 * var_chaste_interface__cell__V)))) - ((var_chaste_interface__cell__V >= -40.0) ? (0.3 * exp(-2.535e-07 * var_chaste_interface__cell__V) / (1.0 + exp(-3.2 - 0.1 * var_chaste_interface__cell__V))) : (0.1212 * exp(-0.01052 * var_chaste_interface__cell__V) / (1.0 + exp(-5.5312920000000005 - 0.1378 * var_chaste_interface__cell__V)))) * var_chaste_interface__INa__J; // 1 / ms
        const double d_dt_chaste_interface_var_INa__m = -0.08 * var_chaste_interface__INa__m * exp(-0.09090909090909091 * var_chaste_interface__cell__V) + 0.32 * (1.0 - var_chaste_interface__INa__m) * (47.13 + var_chaste_interface__cell__V) / (1.0 - exp(-4.713 - 0.1 * var_chaste_interface__cell__V)); // 1 / ms
        const double var_INaCa__INaCa = 4.5 * (1.8 * pow(var_chaste_interface__Na__Na_i, 3.0) * exp(0.01310255922773 * var_chaste_interface__cell__V) - 2744000.0 * var_INaCa__ca_i_NaCa * exp(-0.024333324280070002 * var_chaste_interface__cell__V)) / ((1.0 + 0.27 * exp(-0.024333324280070002 * var_chaste_interface__cell__V)) * (1.0 + 1.5625e-08 * pow(1 / var_INaCa__ca_i_NaCa, 2.0)) * (13227.9606 + 4344355.375 * var_INaCa__ca_i_NaCa + 8.408493299091228 * pow(var_chaste_interface__Na__Na_i, 3.0))); // uA_per_uF
        const double var_INaK__INaK = 0.48423913043478267 / ((1.0 + 100.0 * pow(1 / var_chaste_interface__Na__Na_i, 2.0)) * (1.0 + 0.1245 * exp(-0.00374358835078 * var_chaste_interface__cell__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0802377414561666)) * exp(-0.0374358835078 * var_chaste_interface__cell__V))); // uA_per_uF
        const double d_dt_chaste_interface_var_INal__mL = -0.08 * var_chaste_interface__INal__mL * exp(-0.09090909090909091 * var_chaste_interface__cell__V) + 0.32 * (1.0 - var_chaste_interface__INal__mL) * (47.13 + var_chaste_interface__cell__V) / (1.0 - exp(-4.713 - 0.1 * var_chaste_interface__cell__V)); // 1 / ms
        const double d_dt_chaste_interface_var_INal__hL = 0.0016666666666666668 / (1.0 + exp(14.918032786885247 + 0.1639344262295082 * var_chaste_interface__cell__V)) - 0.0016666666666666668 * var_chaste_interface__INal__hL; // 1 / ms
        const double var_Irel__cafac = 1.0 / (1.0 + exp(3.333333333333334 + 66.66666666666667 * var_ICaL__ICaL)); // dimensionless
        const double d_dt_chaste_interface_var_Irel__ro = -0.3333333333333333 * var_chaste_interface__Irel__ro + 0.3333333333333333 * pow(var_chaste_interface__Ca__Ca_jsr, 1.9) / ((1.0 + 1.0 * pow(1 / var_ICaL__ICaL, 2.0)) * (pow(var_chaste_interface__Ca__Ca_jsr, 1.9) + 1644.653177341652 * pow((var_chaste_interface__Ca__Ca_ss / (0.0028 + var_chaste_interface__Ca__Ca_ss)), 1.9))); // 1 / ms
        const double d_dt_chaste_interface_var_Irel__ri = (-var_chaste_interface__Irel__ri + 1.0 / (1.0 + exp(-16.0 + 80.0 * var_Irel__cafac + 40000.0 * var_chaste_interface__Ca__Ca_ss))) / (3.0 + (350.0 - 10.0 * var_Irel__CaMKactive / (0.15 + var_Irel__CaMKactive)) / (1.0 + exp(-15.0 + 15.0 * var_Irel__cafac + 5000.0 * var_chaste_interface__Ca__Ca_ss)) + 10.0 * var_Irel__CaMKactive / (0.15 + var_Irel__CaMKactive)); // 1 / ms
        const double var_Irel__irelcicr = 3000.0 * (-var_chaste_interface__Ca__Ca_ss + var_chaste_interface__Ca__Ca_jsr) * var_chaste_interface__Irel__ri * var_chaste_interface__Irel__ro / (1.0 + exp(2.6 + 0.2 * var_ICaL__ibarca)); // mM_per_ms
        const double d_dt_chaste_interface_var_Ca__Ca_jsr = 1.0 * (-var_Irel__irelcicr + var_Idiff_Itr__itr) / (1.0 + 8.0 * pow((0.8 + var_chaste_interface__Ca__Ca_jsr), (-2.0))); // mM / ms
        const double d_dt_chaste_interface_var_Ito__ydv = 25.0 * (1.0 - var_chaste_interface__Ito__ydv) * exp(-1.6 + 0.04 * var_chaste_interface__cell__V) / (1.0 + exp(-1.6 + 0.04 * var_chaste_interface__cell__V)) - 25.0 * var_chaste_interface__Ito__ydv * exp(-3.6 - 0.04 * var_chaste_interface__cell__V) / (1.0 + exp(-3.6 - 0.04 * var_chaste_interface__cell__V)); // 1 / ms
        const double d_dt_chaste_interface_var_Ito__ydv2 = 0.03 * (1.0 - var_chaste_interface__Ito__ydv2) / (1.0 + exp(12.0 + 0.2 * var_chaste_interface__cell__V)) - 0.2 * var_chaste_interface__Ito__ydv2 * exp(5.0 + 0.2 * var_chaste_interface__cell__V) / (1.0 + exp(5.0 + 0.2 * var_chaste_interface__cell__V)); // 1 / ms
        const double d_dt_chaste_interface_var_Ito__zdv = 0.00225 * (1.0 - var_chaste_interface__Ito__zdv) / (1.0 + exp(12.0 + 0.2 * var_chaste_interface__cell__V)) - 0.1 * var_chaste_interface__Ito__zdv * exp(5.0 + 0.2 * var_chaste_interface__cell__V) / (1.0 + exp(5.0 + 0.2 * var_chaste_interface__cell__V)); // 1 / ms
        const double var_cell__i_Stim = GetIntracellularAreaStimulus(var_chaste_interface__Environment__time) / HeartConfig::Instance()->GetCapacitance(); // uA_per_uF
        const double var_cell__AF = 5.0619267243613e-10 * M_PI; // uF_mole_per_C
        const double var_cell__vcell = 1.2100000000000001e-05 * M_PI; // uL
        const double var_cell__vjsr = 0.0048 * var_cell__vcell; // uL
        const double var_cell__vmyo = 0.68 * var_cell__vcell; // uL
        const double var_cell__vnsr = 0.0552 * var_cell__vcell; // uL
        const double d_dt_chaste_interface_var_Ca__Ca_nsr = -var_Iup_Ileak__ileak - var_Idiff_Itr__itr * var_cell__vjsr / var_cell__vnsr + var_Iup_Ileak__iup; // mM / ms
        const double var_cell__vss = 0.02 * var_cell__vcell; // uL
        const double d_dt_chaste_interface_var_Ca__Ca_i = 1.0 * ((-var_Iup_Ileak__iup + var_Iup_Ileak__ileak) * var_cell__vnsr / var_cell__vmyo + var_Idiff_Itr__idiff * var_cell__vss / var_cell__vmyo + 0.5 * (-var_ICab__ICab - var_IpCa__IpCa + 2.0 * var_INaCa__INaCa) * var_cell__AF / var_cell__vmyo) / (1.0 + 0.00011900000000000002 * pow((0.00238 + var_chaste_interface__Ca__Ca_i), (-2.0)) + 3.5000000000000004e-05 * pow((0.0005 + var_chaste_interface__Ca__Ca_i), (-2.0))); // mM / ms
        const double d_dt_chaste_interface_var_Ca__Ca_ss = 1.0 * (-var_Idiff_Itr__idiff + var_Irel__irelcicr * var_cell__vjsr / var_cell__vss - 0.5 * var_ICaL__ICaL * var_cell__AF / var_cell__vss) / (1.0 + 0.0097788 * pow((0.0087 + var_chaste_interface__Ca__Ca_ss), (-2.0)) + 4.089e-05 * pow((0.00087 + var_chaste_interface__Ca__Ca_ss), (-2.0))); // mM / ms
        const double var_reversal_potentials__ECl = -26.712338705500134 * log(100.0 / var_chaste_interface__Cl__Cl_i); // mV
        const double var_cell__clont = 0.5 * var_cell__i_Stim + 0.000225 * var_chaste_interface__cell__V - 0.000225 * var_reversal_potentials__ECl + 0.001444800488100033 * (-100.0 * exp(0.0374358835078 * var_chaste_interface__cell__V) + var_chaste_interface__Cl__Cl_i) * var_chaste_interface__Ito2__AA * var_chaste_interface__cell__V / (1.0 - exp(0.0374358835078 * var_chaste_interface__cell__V)); // uA_per_uF
        const double var_reversal_potentials__EK = 26.712338705500134 * log(5.4 / var_chaste_interface__K__K_i); // mV
        const double var_K__CTKCl = 7.0756e-06 * (-var_reversal_potentials__ECl + var_reversal_potentials__EK) / (87.8251 - var_reversal_potentials__ECl + var_reversal_potentials__EK); // mM_per_ms
        const double var_reversal_potentials__ENa = 26.712338705500134 * log(140.0 / var_chaste_interface__Na__Na_i); // mV
        const double var_Na__CTNaCl = 9.8443e-06 * pow((-var_reversal_potentials__ECl + var_reversal_potentials__ENa), 4.0) / (59494197.640692554 + pow((-var_reversal_potentials__ECl + var_reversal_potentials__ENa), 4.0)); // mM_per_ms
        const double d_dt_chaste_interface_var_Cl__Cl_i = var_cell__AF * var_cell__clont / var_cell__vmyo + var_K__CTKCl + var_Na__CTNaCl; // mM / ms
        const double var_cell__naiont = 3.0 * var_INaCa__INaCa + 3.0 * var_INaK__INaK + 0.0065 * pow(var_chaste_interface__INal__mL, 3.0) * (-var_reversal_potentials__ENa + var_chaste_interface__cell__V) * var_chaste_interface__INal__hL + 8.25 * pow(var_chaste_interface__INa__m, 3) * (-var_reversal_potentials__ENa + var_chaste_interface__cell__V) * var_chaste_interface__INa__H * var_chaste_interface__INa__J; // uA_per_uF
        const double d_dt_chaste_interface_var_Na__Na_i = -var_cell__AF * var_cell__naiont / var_cell__vmyo + var_Na__CTNaCl; // mM / ms
        const double var_cell__kiont = 0.5 * var_cell__i_Stim - 2.0 * var_INaK__INaK + 0.00276 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) / (1.0 + exp(1.2521739130434784 - 0.16722408026755853 * var_chaste_interface__cell__V)) + 0.51 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) / ((1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__cell__V - 0.2385 * var_reversal_potentials__EK)) * (1.02 / (1.0 + exp(-14.1227775 + 0.2385 * var_chaste_interface__cell__V - 0.2385 * var_reversal_potentials__EK)) + (1.0 * exp(-36.6986425 + 0.06175 * var_chaste_interface__cell__V - 0.06175 * var_reversal_potentials__EK) + 0.49124 * exp(0.43983232 + 0.08032 * var_chaste_interface__cell__V - 0.08032 * var_reversal_potentials__EK)) / (1.0 + exp(-2.4444679 + 0.5143 * var_reversal_potentials__EK - 0.5143 * var_chaste_interface__cell__V)))) + 0.0138542 * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) * var_chaste_interface__IKr__xr / (1.0 + exp(0.6493506493506493 + 0.06493506493506493 * var_chaste_interface__cell__V)) + (0.0248975 + 0.014938499999999999 / (1.0 + 6.481821026062645e-07 * pow(1 / var_chaste_interface__Ca__Ca_i, 1.4))) * (-26.712338705500134 * log(7.966200000000001 / (0.01833 * var_chaste_interface__Na__Na_i + var_chaste_interface__K__K_i)) + var_chaste_interface__cell__V) * var_chaste_interface__IKs__xs1 * var_chaste_interface__IKs__xs2 + 0.19 * pow(var_chaste_interface__Ito__ydv, 3.0) * (-var_reversal_potentials__EK + var_chaste_interface__cell__V) * var_chaste_interface__Ito__ydv2 * var_chaste_interface__Ito__zdv * exp(0.0033333333333333335 * var_chaste_interface__cell__V); // uA_per_uF
        const double d_dt_chaste_interface_var_K__K_i = -var_cell__AF * var_cell__kiont / var_cell__vmyo + var_K__CTKCl; // mM / ms
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_cell__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_cell__V = -var_ICaL__ICaL - var_ICab__ICab - var_IpCa__IpCa - var_cell__clont - var_cell__kiont - var_cell__naiont + 2.0 * var_INaCa__INaCa; // mV / ms
        }
        
        rDY[0] = d_dt_chaste_interface_var_cell__V;
        rDY[1] = d_dt_chaste_interface_var_Ca__Ca_i;
        rDY[2] = d_dt_chaste_interface_var_INa__H;
        rDY[3] = d_dt_chaste_interface_var_INa__m;
        rDY[4] = d_dt_chaste_interface_var_INa__J;
        rDY[5] = d_dt_chaste_interface_var_ICaL__d;
        rDY[6] = d_dt_chaste_interface_var_ICaL__dp;
        rDY[7] = d_dt_chaste_interface_var_ICaL__f;
        rDY[8] = d_dt_chaste_interface_var_ICaL__fca;
        rDY[9] = d_dt_chaste_interface_var_ICaL__fca2;
        rDY[10] = d_dt_chaste_interface_var_ICaL__f2;
        rDY[11] = d_dt_chaste_interface_var_IKr__xr;
        rDY[12] = d_dt_chaste_interface_var_IKs__xs1;
        rDY[13] = d_dt_chaste_interface_var_IKs__xs2;
        rDY[14] = d_dt_chaste_interface_var_Ito__ydv;
        rDY[15] = d_dt_chaste_interface_var_Ito__ydv2;
        rDY[16] = d_dt_chaste_interface_var_Ito__zdv;
        rDY[17] = d_dt_chaste_interface_var_Ito2__AA;
        rDY[18] = d_dt_chaste_interface_var_INal__mL;
        rDY[19] = d_dt_chaste_interface_var_INal__hL;
        rDY[20] = d_dt_chaste_interface_var_Irel__CaMKtrap;
        rDY[21] = d_dt_chaste_interface_var_Irel__ro;
        rDY[22] = d_dt_chaste_interface_var_Irel__ri;
        rDY[23] = d_dt_chaste_interface_var_Na__Na_i;
        rDY[24] = d_dt_chaste_interface_var_K__K_i;
        rDY[25] = d_dt_chaste_interface_var_Cl__Cl_i;
        rDY[26] = d_dt_chaste_interface_var_Ca__Ca_jsr;
        rDY[27] = d_dt_chaste_interface_var_Ca__Ca_nsr;
        rDY[28] = d_dt_chaste_interface_var_Ca__Ca_ss;
    }

template<>
void OdeSystemInformation<Cellhund_rudy_2004_aFromCellML>::Initialise(void)
{
    this->mSystemName = "hund_rudy_2004";
    this->mFreeVariableName = "Environment__time";
    this->mFreeVariableUnits = "ms";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("mV");
    this->mInitialConditions.push_back(-85.781844107117);
    
    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(0.00012131666);
    
    // rY[2]:
    this->mVariableNames.push_back("INa__H");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.987317750543);
    
    // rY[3]:
    this->mVariableNames.push_back("INa__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001356538159);
    
    // rY[4]:
    this->mVariableNames.push_back("INa__J");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.991924983076);
    
    // rY[5]:
    this->mVariableNames.push_back("ICaL__d");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.64013e-06);
    
    // rY[6]:
    this->mVariableNames.push_back("ICaL__dp");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(8.98230672628);
    
    // rY[7]:
    this->mVariableNames.push_back("ICaL__f");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.999961508634);
    
    // rY[8]:
    this->mVariableNames.push_back("ICaL__fca");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.97836624923);
    
    // rY[9]:
    this->mVariableNames.push_back("ICaL__fca2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.893052931249);
    
    // rY[10]:
    this->mVariableNames.push_back("ICaL__f2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.992234519148);
    
    // rY[11]:
    this->mVariableNames.push_back("IKr__xr");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(7.24074e-06);
    
    // rY[12]:
    this->mVariableNames.push_back("IKs__xs1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.019883138161);
    
    // rY[13]:
    this->mVariableNames.push_back("IKs__xs2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.019890650554);
    
    // rY[14]:
    this->mVariableNames.push_back("Ito__ydv");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.013970786703);
    
    // rY[15]:
    this->mVariableNames.push_back("Ito__ydv2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.99996472752);
    
    // rY[16]:
    this->mVariableNames.push_back("Ito__zdv");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.829206149767);
    
    // rY[17]:
    this->mVariableNames.push_back("Ito2__AA");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.000816605172);
    
    // rY[18]:
    this->mVariableNames.push_back("INal__mL");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001356538159);
    
    // rY[19]:
    this->mVariableNames.push_back("INal__hL");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.26130711759);
    
    // rY[20]:
    this->mVariableNames.push_back("Irel__CaMKtrap");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.021123704774);
    
    // rY[21]:
    this->mVariableNames.push_back("Irel__ro");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);
    
    // rY[22]:
    this->mVariableNames.push_back("Irel__ri");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.862666650318);
    
    // rY[23]:
    this->mVariableNames.push_back("Na__Na_i");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(12.972433387269);
    
    // rY[24]:
    this->mVariableNames.push_back("K__K_i");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(135.469546216758);
    
    // rY[25]:
    this->mVariableNames.push_back("Cl__Cl_i");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(15.59207157178);
    
    // rY[26]:
    this->mVariableNames.push_back("Ca__Ca_jsr");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(1.737580994071);
    
    // rY[27]:
    this->mVariableNames.push_back("Ca__Ca_nsr");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(1.832822335168);
    
    // rY[28]:
    this->mVariableNames.push_back("Ca__Ca_ss");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(0.00012271265);
    
    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellhund_rudy_2004_aFromCellML)
