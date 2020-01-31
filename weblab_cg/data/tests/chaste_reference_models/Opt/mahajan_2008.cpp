//! @file
//! 
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//! 
//! Model: mahajan_shiferaw_model_2008
//! 
//! Processed by weblab_cg: https://github.com/ModellingWebLab/weblab-cg
//!     (translator: weblab_cg, model type: normal, options: )
//! on 2020-01-29 22:58:16
//! 
//! <autogenerated>

#include "mahajan_2008.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

    boost::shared_ptr<RegularStimulus> Cellmahajan_2008FromCellML::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__cell__stim_amplitude = -15.0 * HeartConfig::Instance()->GetCapacitance(); // nA_per_nF
        const double var_chaste_interface__cell__stim_duration = 3.0; // millisecond
        const double var_chaste_interface__cell__stim_offset = 0.0; // millisecond
        const double var_chaste_interface__cell__stim_period = 400.0; // millisecond
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__cell__stim_amplitude),
                var_chaste_interface__cell__stim_duration,
                var_chaste_interface__cell__stim_period,
                var_chaste_interface__cell__stim_offset
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }
    
    double Cellmahajan_2008FromCellML::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }
    
    Cellmahajan_2008FromCellML::Cellmahajan_2008FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                26,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        // 
        this->mpSystemInfo = OdeSystemInformation<Cellmahajan_2008FromCellML>::Instance();
        Init();
        
        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
        this->mParameters[0] = 1.0; // (var_IKr__ScaleFactorGkr) [dimensionless]
        this->mParameters[1] = 1.0; // (var_IKs__ScaleFactorGks) [dimensionless]
        this->mParameters[2] = 1.0; // (var_Ito__ScaleFactorIto) [dimensionless]
    }
    
    Cellmahajan_2008FromCellML::~Cellmahajan_2008FromCellML()
    {
    }

    double Cellmahajan_2008FromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__cell__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -87.169816169406
        double var_chaste_interface__Ca__Ca_i_converted = rY[1];
        // Units: millimolar; Initial value: 0.000256752008084
        double var_chaste_interface__INa__xm = rY[2];
        // Units: dimensionless; Initial value: 0.001075453357
        double var_chaste_interface__INa__xh = rY[3];
        // Units: dimensionless; Initial value: 0.990691306716
        double var_chaste_interface__INa__xj = rY[4];
        // Units: dimensionless; Initial value: 0.993888937283
        double var_chaste_interface__ICaL__c1 = rY[5];
        // Units: dimensionless; Initial value: 1.8211252e-05
        double var_chaste_interface__ICaL__c2 = rY[6];
        // Units: dimensionless; Initial value: 0.979322592773
        double var_chaste_interface__ICaL__xi1ca = rY[7];
        // Units: dimensionless; Initial value: 0.001208153482
        double var_chaste_interface__ICaL__xi1ba = rY[8];
        // Units: dimensionless; Initial value: 3.3616596e-05
        double var_chaste_interface__ICaL__xi2ca = rY[9];
        // Units: dimensionless; Initial value: 0.004173008466
        double var_chaste_interface__ICaL__xi2ba = rY[10];
        // Units: dimensionless; Initial value: 0.015242594688
        double var_chaste_interface__IKr__xr = rY[11];
        // Units: dimensionless; Initial value: 0.007074239331
        double var_chaste_interface__IKs__xs1 = rY[12];
        // Units: dimensionless; Initial value: 0.048267587131
        double var_chaste_interface__IKs__xs2 = rY[13];
        // Units: dimensionless; Initial value: 0.105468807033
        double var_chaste_interface__Ito__xtos = rY[14];
        // Units: dimensionless; Initial value: 0.00364776906
        double var_chaste_interface__Ito__ytos = rY[15];
        // Units: dimensionless; Initial value: 0.174403618112
        double var_chaste_interface__Ito__xtof = rY[16];
        // Units: dimensionless; Initial value: 0.003643592594
        double var_chaste_interface__Ito__ytof = rY[17];
        // Units: dimensionless; Initial value: 0.993331326442
        double var_chaste_interface__Na__Na_i = rY[20];
        // Units: mM; Initial value: 11.441712311614
        double var_chaste_interface__Ca__Ca_submem = rY[22];
        // Units: uM; Initial value: 0.226941113355
        
        const double var_Ca__csm = 0.001 * var_chaste_interface__Ca__Ca_submem; // mM
        const double var_cell__Itotal = -2912.0 * (1.0 - var_chaste_interface__ICaL__c1 - var_chaste_interface__ICaL__c2 - var_chaste_interface__ICaL__xi1ba - var_chaste_interface__ICaL__xi1ca - var_chaste_interface__ICaL__xi2ba - var_chaste_interface__ICaL__xi2ca) * ((0.07535393607176037 * fabs(var_chaste_interface__cell__V) < 0.001) ? (-0.06396051882171601 + 0.10420416882000001 * var_Ca__csm * exp(0.07535393607176037 * var_chaste_interface__cell__V)) : (0.007852194275673206 * (-0.6138 + var_Ca__csm * exp(0.07535393607176037 * var_chaste_interface__cell__V)) * var_chaste_interface__cell__V / (-1.0 + exp(0.07535393607176037 * var_chaste_interface__cell__V)))) - 1.1739130434782612 * var_chaste_interface__Na__Na_i / ((12.0 + var_chaste_interface__Na__Na_i) * (1.0 + 0.1245 * exp(-0.0037676968035880187 * var_chaste_interface__cell__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0208023774145616)) * exp(-0.037676968035880186 * var_chaste_interface__cell__V))) - 0.306 * (86.39876398597339 + var_chaste_interface__cell__V) / ((1.0 + exp(6.483327710654654 + 0.2385 * var_chaste_interface__cell__V)) * (1.02 / (1.0 + exp(6.483327710654654 + 0.2385 * var_chaste_interface__cell__V)) + (1.0 * exp(-31.36351882386614 + 0.06175 * var_chaste_interface__cell__V) + 0.49124 * exp(7.379381043353383 + 0.08032 * var_chaste_interface__cell__V)) / (1.0 + exp(-46.87935221798611 - 0.5143 * var_chaste_interface__cell__V)))) - 0.04 * (86.39876398597339 + var_chaste_interface__cell__V) * var_chaste_interface__Ito__xtof * var_chaste_interface__Ito__ytof - 12.0 * pow(var_chaste_interface__INa__xm, 3) * (-26.541413816729868 * log(136.0 / var_chaste_interface__Na__Na_i) + var_chaste_interface__cell__V) * var_chaste_interface__INa__xh * var_chaste_interface__INa__xj - 0.0125 * (86.39876398597339 + var_chaste_interface__cell__V) * mParameters[0] * var_chaste_interface__IKr__xr / (1.0 + exp(1.4732142857142858 + 0.044642857142857144 * var_chaste_interface__cell__V)) - 6.72 * (1.8 * pow(var_chaste_interface__Na__Na_i, 3.0) * exp(0.013186938812558065 * var_chaste_interface__cell__V) - 2515456.0 * var_Ca__csm * exp(-0.02449002922332212 * var_chaste_interface__cell__V)) / ((1.0 + 0.026999999999999996 * pow(1 / var_chaste_interface__Ca__Ca_submem, 3.0)) * (1.0 + 0.2 * exp(-0.02449002922332212 * var_chaste_interface__cell__V)) * (12405.2022 + 4115811.375 * var_Ca__csm + 7.966356166238639 * pow(var_chaste_interface__Na__Na_i, 3.0))) - 0.11 * (86.39876398597339 + var_chaste_interface__cell__V) * (0.5 / (1.0 + exp(3.35 + 0.1 * var_chaste_interface__cell__V)) + var_chaste_interface__Ito__ytos) * mParameters[2] * var_chaste_interface__Ito__xtos - 0.1386 * (1.0 + 0.8 / (1.0 + 1.25e-10 * pow(1 / var_chaste_interface__Ca__Ca_i_converted, 3.0))) * (-26.541413816729868 * log(7.89288 / (140.0 + 0.01833 * var_chaste_interface__Na__Na_i)) + var_chaste_interface__cell__V) * mParameters[1] * var_chaste_interface__IKs__xs1 * var_chaste_interface__IKs__xs2; // nA_per_nF
        const double var_chaste_interface__i_ionic = HeartConfig::Instance()->GetCapacitance() * var_cell__Itotal; // uA_per_cm2
        
        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }
    
    void Cellmahajan_2008FromCellML::EvaluateYDerivatives(double var_chaste_interface__Environment__time, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__cell__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: -87.169816169406
        double var_chaste_interface__Ca__Ca_i_converted = rY[1];
        // Units: millimolar; Initial value: 0.000256752008084
        double var_chaste_interface__INa__xm = rY[2];
        // Units: dimensionless; Initial value: 0.001075453357
        double var_chaste_interface__INa__xh = rY[3];
        // Units: dimensionless; Initial value: 0.990691306716
        double var_chaste_interface__INa__xj = rY[4];
        // Units: dimensionless; Initial value: 0.993888937283
        double var_chaste_interface__ICaL__c1 = rY[5];
        // Units: dimensionless; Initial value: 1.8211252e-05
        double var_chaste_interface__ICaL__c2 = rY[6];
        // Units: dimensionless; Initial value: 0.979322592773
        double var_chaste_interface__ICaL__xi1ca = rY[7];
        // Units: dimensionless; Initial value: 0.001208153482
        double var_chaste_interface__ICaL__xi1ba = rY[8];
        // Units: dimensionless; Initial value: 3.3616596e-05
        double var_chaste_interface__ICaL__xi2ca = rY[9];
        // Units: dimensionless; Initial value: 0.004173008466
        double var_chaste_interface__ICaL__xi2ba = rY[10];
        // Units: dimensionless; Initial value: 0.015242594688
        double var_chaste_interface__IKr__xr = rY[11];
        // Units: dimensionless; Initial value: 0.007074239331
        double var_chaste_interface__IKs__xs1 = rY[12];
        // Units: dimensionless; Initial value: 0.048267587131
        double var_chaste_interface__IKs__xs2 = rY[13];
        // Units: dimensionless; Initial value: 0.105468807033
        double var_chaste_interface__Ito__xtos = rY[14];
        // Units: dimensionless; Initial value: 0.00364776906
        double var_chaste_interface__Ito__ytos = rY[15];
        // Units: dimensionless; Initial value: 0.174403618112
        double var_chaste_interface__Ito__xtof = rY[16];
        // Units: dimensionless; Initial value: 0.003643592594
        double var_chaste_interface__Ito__ytof = rY[17];
        // Units: dimensionless; Initial value: 0.993331326442
        double var_chaste_interface__Irel__Ca_JSR = rY[18];
        // Units: uM; Initial value: 97.505463697266
        double var_chaste_interface__Irel__xir = rY[19];
        // Units: uM_per_ms; Initial value: 0.006679257264
        double var_chaste_interface__Na__Na_i = rY[20];
        // Units: mM; Initial value: 11.441712311614
        double var_chaste_interface__Ca__Ca_dyad = rY[21];
        // Units: uM; Initial value: 1.716573130685
        double var_chaste_interface__Ca__Ca_submem = rY[22];
        // Units: uM; Initial value: 0.226941113355
        double var_chaste_interface__Ca__Ca_NSR = rY[23];
        // Units: uM; Initial value: 104.450004990523
        double var_chaste_interface__Ca__tropi = rY[24];
        // Units: uM; Initial value: 22.171689894953
        double var_chaste_interface__Ca__trops = rY[25];
        // Units: uM; Initial value: 19.864701949854
        
        // Mathematics
        double d_dt_chaste_interface_var_cell__V;
        const double var_Ca__Ca_i = 1000.0 * var_chaste_interface__Ca__Ca_i_converted; // uM
        const double var_Ca__csm = 0.001 * var_chaste_interface__Ca__Ca_submem; // mM
        const double var_Ca__jd = 0.25 * var_chaste_interface__Ca__Ca_submem - 0.25 * var_Ca__Ca_i; // uM_per_ms
        const double var_Ca__xbi = -0.0196 * var_chaste_interface__Ca__tropi + 0.0327 * (70.0 - var_chaste_interface__Ca__tropi) * var_Ca__Ca_i; // uM_per_ms
        const double var_Ca__xbs = -0.0196 * var_chaste_interface__Ca__trops + 0.0327 * (70.0 - var_chaste_interface__Ca__trops) * var_chaste_interface__Ca__Ca_submem; // uM_per_ms
        const double d_dt_chaste_interface_var_Ca__tropi = var_Ca__xbi; // uM / ms
        const double d_dt_chaste_interface_var_Ca__trops = var_Ca__xbs; // uM / ms
        const double var_ICaL__fca = 1.0 / (1.0 + 27.0 * pow(1 / var_chaste_interface__Ca__Ca_dyad, 3.0)); // dimensionless
        const double var_ICaL__k1 = 0.024168 * var_ICaL__fca; // per_ms
        const double var_ICaL__s1 = 0.0182688 * var_ICaL__fca; // per_ms
        const double var_ICaL__po = 1.0 - var_chaste_interface__ICaL__c1 - var_chaste_interface__ICaL__c2 - var_chaste_interface__ICaL__xi1ba - var_chaste_interface__ICaL__xi1ca - var_chaste_interface__ICaL__xi2ba - var_chaste_interface__ICaL__xi2ca; // dimensionless
        const double var_Ileak_Iup_Ixfer__jleak = 2.069e-05 * pow(var_chaste_interface__Ca__Ca_NSR, 2) * (-var_Ca__Ca_i + 16.667 * var_chaste_interface__Ca__Ca_NSR) / (2500.0 + pow(var_chaste_interface__Ca__Ca_NSR, 2)); // uM_per_ms
        const double var_Ileak_Iup_Ixfer__jup = 0.4 * pow(var_Ca__Ca_i, 2) / (0.25 + pow(var_Ca__Ca_i, 2)); // uM_per_ms
        const double d_dt_chaste_interface_var_Ca__Ca_i_converted = 0.001 * (-var_Ca__xbi - var_Ileak_Iup_Ixfer__jup + var_Ca__jd + var_Ileak_Iup_Ixfer__jleak) / (1.0 + 4.5 / pow((0.3 + var_Ca__Ca_i), 2) + 3.230769230769231 / pow((1 + 0.07692307692307693 * var_Ca__Ca_i), 2) + 3.4285714285714284 / pow((1 + 0.14285714285714285 * var_Ca__Ca_i), 2) + 28.2 / pow((0.6 + var_Ca__Ca_i), 2)); // millimolar / ms
        const double var_Irel__Qr = 0.011111111111111112 * (((var_chaste_interface__Irel__Ca_JSR > 50.0) && (var_chaste_interface__Irel__Ca_JSR < 90.0)) ? (-50.0 + 1.0 * var_chaste_interface__Irel__Ca_JSR) : ((var_chaste_interface__Irel__Ca_JSR >= 90.0) ? (-977.0000000000001 + 11.3 * var_chaste_interface__Irel__Ca_JSR) : (0.0))) * var_chaste_interface__Ca__Ca_NSR; // uM_per_ms
        const double d_dt_chaste_interface_var_Irel__Ca_JSR = 0.01 * var_chaste_interface__Ca__Ca_NSR - 0.01 * var_chaste_interface__Irel__Ca_JSR; // uM / ms
        const double var_Ca__dCa_JSR = -var_Ileak_Iup_Ixfer__jleak - var_chaste_interface__Irel__xir + var_Ileak_Iup_Ixfer__jup; // uM_per_ms
        const double d_dt_chaste_interface_var_Ca__Ca_NSR = var_Ca__dCa_JSR; // uM / ms
        const double var_ICaL__Pr = 1.0 - 1.0 / (1.0 + exp(-10.0 - 0.25 * var_chaste_interface__cell__V)); // dimensionless
        const double var_ICaL__Ps = 1.0 / (1.0 + exp(-3.53356890459364 - 0.08833922261484099 * var_chaste_interface__cell__V)); // dimensionless
        const double var_ICaL__k3 = 0.3333333333333333 - 0.3333333333333333 / (1.0 + exp(-13.333333333333332 - 0.3333333333333333 * var_chaste_interface__cell__V)); // per_ms
        const double var_ICaL__k3t = var_ICaL__k3; // per_ms
        const double var_ICaL__poinf = 1.0 / (1.0 + exp(-0.125 * var_chaste_interface__cell__V)); // dimensionless
        const double var_ICaL__alpha = 1.0 * var_ICaL__poinf; // per_ms
        const double var_ICaL__beta = 1.0 - 1.0 * var_ICaL__poinf; // per_ms
        const double d_dt_chaste_interface_var_ICaL__c1 = 3.0 * var_ICaL__po + 0.00224 * var_chaste_interface__ICaL__xi1ba + 0.000103615 * var_chaste_interface__ICaL__xi1ca + var_ICaL__alpha * var_chaste_interface__ICaL__c2 - (0.30413 + var_ICaL__beta + var_ICaL__k1) * var_chaste_interface__ICaL__c1; // 1 / ms
        const double var_ICaL__recov = 10.0 + 4954.0 * exp(0.06410256410256411 * var_chaste_interface__cell__V); // ms
        const double var_ICaL__tauba = 450.0 + (-450.0 + var_ICaL__recov) * var_ICaL__Pr; // ms
        const double var_ICaL__k5t = (1.0 - var_ICaL__Ps) / var_ICaL__tauba; // per_ms
        const double var_ICaL__k6t = var_ICaL__Ps / var_ICaL__tauba; // per_ms
        const double var_ICaL__k4t = 1.84375 * var_ICaL__alpha * var_ICaL__k3t * var_ICaL__k5t / (var_ICaL__beta * var_ICaL__k6t); // per_ms
        const double d_dt_chaste_interface_var_ICaL__xi1ba = 0.00413 * var_chaste_interface__ICaL__c1 + 0.00195 * var_ICaL__po + var_ICaL__k4t * var_chaste_interface__ICaL__xi2ba - (0.0023457627118644068 + var_ICaL__k3t) * var_chaste_interface__ICaL__xi1ba; // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__xi2ba = var_chaste_interface__ICaL__c2 * var_ICaL__k6t + var_ICaL__k3t * var_chaste_interface__ICaL__xi1ba - (var_ICaL__k4t + var_ICaL__k5t) * var_chaste_interface__ICaL__xi2ba; // 1 / ms
        const double var_ICaL__tauca = 0.1 + 78.0329 / (1.0 + 0.000725253737564415 * pow(var_chaste_interface__Ca__Ca_dyad, 4.0)) + (-0.1 - 78.0329 / (1.0 + 0.000725253737564415 * pow(var_chaste_interface__Ca__Ca_dyad, 4.0)) + var_ICaL__recov) * var_ICaL__Pr; // ms
        const double var_ICaL__k5 = (1.0 - var_ICaL__Ps) / var_ICaL__tauca; // per_ms
        const double var_ICaL__k6 = var_ICaL__Ps * var_ICaL__fca / var_ICaL__tauca; // per_ms
        const double d_dt_chaste_interface_var_ICaL__c2 = var_ICaL__beta * var_chaste_interface__ICaL__c1 + var_ICaL__k5 * var_chaste_interface__ICaL__xi2ca + var_ICaL__k5t * var_chaste_interface__ICaL__xi2ba - (var_ICaL__alpha + var_ICaL__k6 + var_ICaL__k6t) * var_chaste_interface__ICaL__c2; // 1 / ms
        const double var_ICaL__k4 = 9651.112290691502 * var_ICaL__alpha * var_ICaL__k1 * var_ICaL__k3 * var_ICaL__k5 / (var_ICaL__beta * var_ICaL__k6); // per_ms
        const double d_dt_chaste_interface_var_ICaL__xi1ca = var_chaste_interface__ICaL__c1 * var_ICaL__k1 + var_ICaL__k4 * var_chaste_interface__ICaL__xi2ca + var_ICaL__po * var_ICaL__s1 - (0.000103615 + 1.0361499999999999e-05 * var_ICaL__s1 / var_ICaL__k1 + var_ICaL__k3) * var_chaste_interface__ICaL__xi1ca; // 1 / ms
        const double d_dt_chaste_interface_var_ICaL__xi2ca = var_chaste_interface__ICaL__c2 * var_ICaL__k6 + var_ICaL__k3 * var_chaste_interface__ICaL__xi1ca - (var_ICaL__k4 + var_ICaL__k5) * var_chaste_interface__ICaL__xi2ca; // 1 / ms
        const double var_ICaL__rxa = ((0.07535393607176037 * fabs(var_chaste_interface__cell__V) < 0.001) ? (-0.06396051882171601 + 0.10420416882000001 * var_Ca__csm * exp(0.07535393607176037 * var_chaste_interface__cell__V)) : (0.007852194275673206 * (-0.6138 + var_Ca__csm * exp(0.07535393607176037 * var_chaste_interface__cell__V)) * var_chaste_interface__cell__V / (-1.0 + exp(0.07535393607176037 * var_chaste_interface__cell__V)))); // mA_per_cm2
        const double var_ICaL__jca = 182.0 * var_ICaL__po * var_ICaL__rxa; // uM_per_ms
        const double d_dt_chaste_interface_var_IKr__xr = (-var_chaste_interface__IKr__xr + 1.0 / (1.0 + exp(-6.666666666666667 - 0.13333333333333333 * var_chaste_interface__cell__V))) * (1.0 * ((fabs(10.0 + var_chaste_interface__cell__V) > 0.001) ? (0.00061 * (10.0 + var_chaste_interface__cell__V) / (-1.0 + exp(1.45 + 0.145 * var_chaste_interface__cell__V))) : (0.004206896551724138)) + 1.0 * ((fabs(7.0 + var_chaste_interface__cell__V) > 0.001) ? (0.00138 * (7.0 + var_chaste_interface__cell__V) / (1.0 - exp(-0.861 - 0.123 * var_chaste_interface__cell__V))) : (0.011219512195121953))); // 1 / ms
        const double var_IKs__tauxs1 = ((fabs(30.0 + var_chaste_interface__cell__V) < 0.014556040756914121) ? (417.9462526610798) : (1.0 / (0.000131 * (30.0 + var_chaste_interface__cell__V) / (-1.0 + exp(2.061 + 0.0687 * var_chaste_interface__cell__V)) + 7.19e-05 * (30.0 + var_chaste_interface__cell__V) / (1.0 - exp(-4.4399999999999995 - 0.148 * var_chaste_interface__cell__V))))); // ms
        const double var_IKs__xs1ss = 1.0 / (1.0 + exp(0.08982035928143713 - 0.059880239520958084 * var_chaste_interface__cell__V)); // dimensionless
        const double d_dt_chaste_interface_var_IKs__xs1 = (-var_chaste_interface__IKs__xs1 + var_IKs__xs1ss) / var_IKs__tauxs1; // 1 / ms
        const double d_dt_chaste_interface_var_IKs__xs2 = 0.25 * (-var_chaste_interface__IKs__xs2 + var_IKs__xs1ss) / var_IKs__tauxs1; // 1 / ms
        const double d_dt_chaste_interface_var_INa__xh = (1.0 - var_chaste_interface__INa__xh) * ((var_chaste_interface__cell__V < -40.0) ? (0.135 * exp(-11.764705882352942 - 0.14705882352941177 * var_chaste_interface__cell__V)) : (0.0)) - ((var_chaste_interface__cell__V < -40.0) ? (310000.0 * exp(0.35 * var_chaste_interface__cell__V) + 3.56 * exp(0.079 * var_chaste_interface__cell__V)) : (7.692307692307692 / (1.0 + exp(-0.9603603603603604 - 0.0900900900900901 * var_chaste_interface__cell__V)))) * var_chaste_interface__INa__xh; // 1 / ms
        const double d_dt_chaste_interface_var_INa__xj = (1.0 - var_chaste_interface__INa__xj) * ((var_chaste_interface__cell__V < -40.0) ? (1.0 * (37.78 + var_chaste_interface__cell__V) * (-127140.0 * exp(0.2444 * var_chaste_interface__cell__V) - 3.474e-05 * exp(-0.04391 * var_chaste_interface__cell__V)) / (1.0 + exp(24.640530000000002 + 0.311 * var_chaste_interface__cell__V))) : (0.0)) - ((var_chaste_interface__cell__V < -40.0) ? (0.1212 * exp(-0.01052 * var_chaste_interface__cell__V) / (1.0 + exp(-5.5312920000000005 - 0.1378 * var_chaste_interface__cell__V))) : (0.3 * exp(-2.535e-07 * var_chaste_interface__cell__V) / (1.0 + exp(-3.2 - 0.1 * var_chaste_interface__cell__V)))) * var_chaste_interface__INa__xj; // 1 / ms
        const double d_dt_chaste_interface_var_INa__xm = (1.0 - var_chaste_interface__INa__xm) * ((fabs(47.13 + var_chaste_interface__cell__V) > 0.001) ? (0.32 * (47.13 + var_chaste_interface__cell__V) / (1.0 - exp(-4.713 - 0.1 * var_chaste_interface__cell__V))) : (3.2)) - 0.08 * var_chaste_interface__INa__xm * exp(-0.09090909090909091 * var_chaste_interface__cell__V); // 1 / ms
        const double var_INaCa__jNaCa = 0.84 * (1.8 * pow(var_chaste_interface__Na__Na_i, 3.0) * exp(0.013186938812558065 * var_chaste_interface__cell__V) - 2515456.0 * var_Ca__csm * exp(-0.02449002922332212 * var_chaste_interface__cell__V)) / ((1.0 + 0.026999999999999996 * pow(1 / var_chaste_interface__Ca__Ca_submem, 3.0)) * (1.0 + 0.2 * exp(-0.02449002922332212 * var_chaste_interface__cell__V)) * (12405.2022 + 4115811.375 * var_Ca__csm + 7.966356166238639 * pow(var_chaste_interface__Na__Na_i, 3.0))); // uM_per_ms
        const double d_dt_chaste_interface_var_Ca__Ca_submem = 1.0 * (-var_Ca__xbs + 50.0 * var_INaCa__jNaCa + 50.0 * var_chaste_interface__Irel__xir - 50.0 * var_Ca__jd - 50.0 * var_ICaL__jca) / (1.0 + 4.5 / pow((0.3 + var_chaste_interface__Ca__Ca_submem), 2) + 3.230769230769231 / pow((1 + 0.07692307692307693 * var_chaste_interface__Ca__Ca_submem), 2) + 3.4285714285714284 / pow((1 + 0.14285714285714285 * var_chaste_interface__Ca__Ca_submem), 2) + 28.2 / pow((0.6 + var_chaste_interface__Ca__Ca_submem), 2)); // uM / ms
        const double var_INaK__xiNaK = 1.1739130434782612 * var_chaste_interface__Na__Na_i / ((12.0 + var_chaste_interface__Na__Na_i) * (1.0 + 0.1245 * exp(-0.0037676968035880187 * var_chaste_interface__cell__V) + 0.0365 * (-0.14285714285714285 + 0.14285714285714285 * exp(2.0208023774145616)) * exp(-0.037676968035880186 * var_chaste_interface__cell__V))); // nA_per_nF
        const double d_dt_chaste_interface_var_Irel__xir = -0.03333333333333333 * (1.0 - 30.0 * var_Ca__dCa_JSR / var_chaste_interface__Ca__Ca_NSR) * var_chaste_interface__Irel__xir + 2.58079 * fabs(var_ICaL__rxa) * var_ICaL__po * var_Irel__Qr * exp(-1.5 - 0.05 * var_chaste_interface__cell__V) / (1.0 + exp(-1.5 - 0.05 * var_chaste_interface__cell__V)); // uM_per_ms / ms
        const double d_dt_chaste_interface_var_Ca__Ca_dyad = 2.0 * var_chaste_interface__Ca__Ca_submem - 2.0 * var_chaste_interface__Ca__Ca_dyad + 9000.0 * fabs(var_ICaL__rxa) * var_ICaL__po + 26841.8 * fabs(var_ICaL__rxa) * var_ICaL__po * var_Irel__Qr * exp(-10.728 - 0.3576 * var_chaste_interface__cell__V) / (1.0 + exp(-10.728 - 0.3576 * var_chaste_interface__cell__V)); // uM / ms
        const double var_Ito__rt1 = -0.2 - 0.06666666666666667 * var_chaste_interface__cell__V; // dimensionless
        const double var_Ito__rt2 = 3.35 + 0.1 * var_chaste_interface__cell__V; // dimensionless
        const double var_Ito__xtos_inf = 1.0 / (1.0 + exp(var_Ito__rt1)); // dimensionless
        const double d_dt_chaste_interface_var_Ito__xtos = (-var_chaste_interface__Ito__xtos + var_Ito__xtos_inf) / (0.5 + 9.0 / (1.0 + exp(-var_Ito__rt1))); // 1 / ms
        const double d_dt_chaste_interface_var_Ito__xtof = (-var_chaste_interface__Ito__xtof + var_Ito__xtos_inf) / (1.5 + 3.5 * exp(-0.0011111111111111111 * pow(var_chaste_interface__cell__V, 2))); // 1 / ms
        const double var_Ito__ytos_inf = 1.0 / (1.0 + exp(var_Ito__rt2)); // dimensionless
        const double d_dt_chaste_interface_var_Ito__ytos = (-var_chaste_interface__Ito__ytos + var_Ito__ytos_inf) / (30.0 + 3000.0 / (1.0 + exp(6.0 + 0.1 * var_chaste_interface__cell__V))); // 1 / ms
        const double d_dt_chaste_interface_var_Ito__ytof = (-var_chaste_interface__Ito__ytof + var_Ito__ytos_inf) / (20.0 + 20.0 / (1.0 + exp(3.35 + 0.1 * var_chaste_interface__cell__V))); // 1 / ms
        const double var_INaCa__xiNaCa = 8.0 * var_INaCa__jNaCa; // nA_per_nF
        const double var_INa__xina = 12.0 * pow(var_chaste_interface__INa__xm, 3) * (-26.541413816729868 * log(136.0 / var_chaste_interface__Na__Na_i) + var_chaste_interface__cell__V) * var_chaste_interface__INa__xh * var_chaste_interface__INa__xj; // nA_per_nF
        const double d_dt_chaste_interface_var_Na__Na_i = -0.000125 * var_INa__xina - 0.000375 * var_INaCa__xiNaCa - 0.000375 * var_INaK__xiNaK; // mM / ms
        
        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_cell__V = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_cell__V = -var_INa__xina - var_INaCa__xiNaCa - var_INaK__xiNaK - 16.0 * var_ICaL__jca - GetIntracellularAreaStimulus(var_chaste_interface__Environment__time) / HeartConfig::Instance()->GetCapacitance() - 0.306 * (86.39876398597339 + var_chaste_interface__cell__V) / ((1.0 + exp(6.483327710654654 + 0.2385 * var_chaste_interface__cell__V)) * (1.02 / (1.0 + exp(6.483327710654654 + 0.2385 * var_chaste_interface__cell__V)) + (1.0 * exp(-31.36351882386614 + 0.06175 * var_chaste_interface__cell__V) + 0.49124 * exp(7.379381043353383 + 0.08032 * var_chaste_interface__cell__V)) / (1.0 + exp(-46.87935221798611 - 0.5143 * var_chaste_interface__cell__V)))) - 0.04 * (86.39876398597339 + var_chaste_interface__cell__V) * var_chaste_interface__Ito__xtof * var_chaste_interface__Ito__ytof - 0.0125 * (86.39876398597339 + var_chaste_interface__cell__V) * mParameters[0] * var_chaste_interface__IKr__xr / (1.0 + exp(1.4732142857142858 + 0.044642857142857144 * var_chaste_interface__cell__V)) - 0.11 * (86.39876398597339 + var_chaste_interface__cell__V) * (0.5 / (1.0 + exp(var_Ito__rt2)) + var_chaste_interface__Ito__ytos) * mParameters[2] * var_chaste_interface__Ito__xtos - 0.1386 * (1.0 + 0.8 / (1.0 + 0.125 * pow(1 / var_Ca__Ca_i, 3.0))) * (-26.541413816729868 * log(7.89288 / (140.0 + 0.01833 * var_chaste_interface__Na__Na_i)) + var_chaste_interface__cell__V) * mParameters[1] * var_chaste_interface__IKs__xs1 * var_chaste_interface__IKs__xs2; // mV / ms
        }
        
        rDY[0] = d_dt_chaste_interface_var_cell__V;
        rDY[1] = d_dt_chaste_interface_var_Ca__Ca_i_converted;
        rDY[2] = d_dt_chaste_interface_var_INa__xm;
        rDY[3] = d_dt_chaste_interface_var_INa__xh;
        rDY[4] = d_dt_chaste_interface_var_INa__xj;
        rDY[5] = d_dt_chaste_interface_var_ICaL__c1;
        rDY[6] = d_dt_chaste_interface_var_ICaL__c2;
        rDY[7] = d_dt_chaste_interface_var_ICaL__xi1ca;
        rDY[8] = d_dt_chaste_interface_var_ICaL__xi1ba;
        rDY[9] = d_dt_chaste_interface_var_ICaL__xi2ca;
        rDY[10] = d_dt_chaste_interface_var_ICaL__xi2ba;
        rDY[11] = d_dt_chaste_interface_var_IKr__xr;
        rDY[12] = d_dt_chaste_interface_var_IKs__xs1;
        rDY[13] = d_dt_chaste_interface_var_IKs__xs2;
        rDY[14] = d_dt_chaste_interface_var_Ito__xtos;
        rDY[15] = d_dt_chaste_interface_var_Ito__ytos;
        rDY[16] = d_dt_chaste_interface_var_Ito__xtof;
        rDY[17] = d_dt_chaste_interface_var_Ito__ytof;
        rDY[18] = d_dt_chaste_interface_var_Irel__Ca_JSR;
        rDY[19] = d_dt_chaste_interface_var_Irel__xir;
        rDY[20] = d_dt_chaste_interface_var_Na__Na_i;
        rDY[21] = d_dt_chaste_interface_var_Ca__Ca_dyad;
        rDY[22] = d_dt_chaste_interface_var_Ca__Ca_submem;
        rDY[23] = d_dt_chaste_interface_var_Ca__Ca_NSR;
        rDY[24] = d_dt_chaste_interface_var_Ca__tropi;
        rDY[25] = d_dt_chaste_interface_var_Ca__trops;
    }

template<>
void OdeSystemInformation<Cellmahajan_2008FromCellML>::Initialise(void)
{
    this->mSystemName = "mahajan_shiferaw_model_2008";
    this->mFreeVariableName = "Environment__time";
    this->mFreeVariableUnits = "ms";
    
    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("mV");
    this->mInitialConditions.push_back(-87.169816169406);
    
    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.000256752008084);
    
    // rY[2]:
    this->mVariableNames.push_back("INa__xm");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001075453357);
    
    // rY[3]:
    this->mVariableNames.push_back("INa__xh");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.990691306716);
    
    // rY[4]:
    this->mVariableNames.push_back("INa__xj");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.993888937283);
    
    // rY[5]:
    this->mVariableNames.push_back("ICaL__c1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.8211252e-05);
    
    // rY[6]:
    this->mVariableNames.push_back("ICaL__c2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.979322592773);
    
    // rY[7]:
    this->mVariableNames.push_back("ICaL__xi1ca");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001208153482);
    
    // rY[8]:
    this->mVariableNames.push_back("ICaL__xi1ba");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(3.3616596e-05);
    
    // rY[9]:
    this->mVariableNames.push_back("ICaL__xi2ca");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.004173008466);
    
    // rY[10]:
    this->mVariableNames.push_back("ICaL__xi2ba");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.015242594688);
    
    // rY[11]:
    this->mVariableNames.push_back("IKr__xr");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.007074239331);
    
    // rY[12]:
    this->mVariableNames.push_back("IKs__xs1");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.048267587131);
    
    // rY[13]:
    this->mVariableNames.push_back("IKs__xs2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.105468807033);
    
    // rY[14]:
    this->mVariableNames.push_back("Ito__xtos");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.00364776906);
    
    // rY[15]:
    this->mVariableNames.push_back("Ito__ytos");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.174403618112);
    
    // rY[16]:
    this->mVariableNames.push_back("Ito__xtof");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.003643592594);
    
    // rY[17]:
    this->mVariableNames.push_back("Ito__ytof");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.993331326442);
    
    // rY[18]:
    this->mVariableNames.push_back("Irel__Ca_JSR");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(97.505463697266);
    
    // rY[19]:
    this->mVariableNames.push_back("Irel__xir");
    this->mVariableUnits.push_back("uM_per_ms");
    this->mInitialConditions.push_back(0.006679257264);
    
    // rY[20]:
    this->mVariableNames.push_back("Na__Na_i");
    this->mVariableUnits.push_back("mM");
    this->mInitialConditions.push_back(11.441712311614);
    
    // rY[21]:
    this->mVariableNames.push_back("Ca__Ca_dyad");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(1.716573130685);
    
    // rY[22]:
    this->mVariableNames.push_back("Ca__Ca_submem");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(0.226941113355);
    
    // rY[23]:
    this->mVariableNames.push_back("Ca__Ca_NSR");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(104.450004990523);
    
    // rY[24]:
    this->mVariableNames.push_back("Ca__tropi");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(22.171689894953);
    
    // rY[25]:
    this->mVariableNames.push_back("Ca__trops");
    this->mVariableUnits.push_back("uM");
    this->mInitialConditions.push_back(19.864701949854);
    
    // mParameters[0]:
    this->mParameterNames.push_back("ScaleFactorGkr");
    this->mParameterUnits.push_back("dimensionless");

    // mParameters[1]:
    this->mParameterNames.push_back("ScaleFactorGks");
    this->mParameterUnits.push_back("dimensionless");

    // mParameters[2]:
    this->mParameterNames.push_back("ScaleFactorIto");
    this->mParameterUnits.push_back("dimensionless");

    this->mInitialised = true;    
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellmahajan_2008FromCellML)
