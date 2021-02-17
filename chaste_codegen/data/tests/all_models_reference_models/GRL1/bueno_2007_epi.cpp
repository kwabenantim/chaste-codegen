//! @file
//!
//! This source file was generated from CellML by chaste_codegen version (version omitted as unimportant)
//!
//! Model: bueno_2007
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: GeneralizedRushLarsenFirstOrder)
//! on (date omitted as unimportant)
//!
//! <autogenerated>

#include "bueno_2007_epi.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"



    boost::shared_ptr<RegularStimulus> Cellbueno_2007_epiFromCellMLGRL1::UseCellMLDefaultStimulus()
    {
        // Use the default stimulus specified by CellML metadata
        const double var_chaste_interface__membrane__IstimAmplitude = -0.5; // uA_per_cm2
        const double var_chaste_interface__membrane__IstimPeriod = 1000.0; // ms
        const double var_chaste_interface__membrane__IstimPulseDuration = 1.0; // ms
        const double var_chaste_interface__membrane__IstimStart = 10.0; // ms
        boost::shared_ptr<RegularStimulus> p_cellml_stim(new RegularStimulus(
                -fabs(var_chaste_interface__membrane__IstimAmplitude),
                var_chaste_interface__membrane__IstimPulseDuration,
                var_chaste_interface__membrane__IstimPeriod,
                var_chaste_interface__membrane__IstimStart
                ));
        mpIntracellularStimulus = p_cellml_stim;
        return p_cellml_stim;
    }

    Cellbueno_2007_epiFromCellMLGRL1::Cellbueno_2007_epiFromCellMLGRL1(boost::shared_ptr<AbstractIvpOdeSolver> /* unused; should be empty */, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractGeneralizedRushLarsenCardiacCell(
                4,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        //
        this->mpSystemInfo = OdeSystemInformation<Cellbueno_2007_epiFromCellMLGRL1>::Instance();
        Init();

        // We have a default stimulus specified in the CellML file metadata
        this->mHasDefaultStimulusFromCellML = true;
        
        this->mParameters[0] = 1.0; // (var_membrane__C) [uF_per_cm2]
    }

    Cellbueno_2007_epiFromCellMLGRL1::~Cellbueno_2007_epiFromCellMLGRL1()
    {
    }

    
    double Cellbueno_2007_epiFromCellMLGRL1::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_w_gate__w = rY[2];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_s_gate__s = rY[3];
        // Units: dimensionless; Initial value: 0.0
        
        const double var_fast_inward_current__tau_fi = 0.11; // cm2_per_uA
        const double var_fast_inward_current__u_u = 1.55; // dimensionless
        const double var_m__u_m = 0.29999999999999999; // dimensionless
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_m__m = ((var_m__u_m > var_membrane__u) ? (0) : (1.0)); // dimensionless
        const double var_fast_inward_current__i_fi = -(-var_m__u_m + var_membrane__u) * (-var_membrane__u + var_fast_inward_current__u_u) * var_chaste_interface__fast_inward_current_v_gate__v * var_m__m / var_fast_inward_current__tau_fi; // uA_per_cm2
        const double var_p__u_p = 0.13; // dimensionless
        const double var_p__p = ((var_membrane__u < var_p__u_p) ? (0) : (1.0)); // dimensionless
        const double var_r__u_r = 0.0060000000000000001; // dimensionless
        const double var_r__r = ((var_membrane__u < var_r__u_r) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current__tau_si = 1.8875; // cm2_per_uA
        const double var_slow_inward_current__i_si = -var_p__p * var_chaste_interface__slow_inward_current_s_gate__s * var_chaste_interface__slow_inward_current_w_gate__w / var_slow_inward_current__tau_si; // uA_per_cm2
        const double var_slow_outward_current__k_so = 2.0457999999999998; // dimensionless
        const double var_slow_outward_current__tau_o1 = 400.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o2 = 6.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o = (1.0 - var_r__r) * var_slow_outward_current__tau_o1 + var_r__r * var_slow_outward_current__tau_o2; // cm2_per_uA
        const double var_slow_outward_current__tau_so1 = 30.0181; // cm2_per_uA
        const double var_slow_outward_current__tau_so2 = 0.99570000000000003; // cm2_per_uA
        const double var_slow_outward_current__u_so = 0.65000000000000002; // dimensionless
        const double var_slow_outward_current__tau_so = 0.5 * (1.0 + tanh((-var_slow_outward_current__u_so + var_membrane__u) * var_slow_outward_current__k_so)) * (-var_slow_outward_current__tau_so1 + var_slow_outward_current__tau_so2) + var_slow_outward_current__tau_so1; // cm2_per_uA
        const double var_slow_outward_current__i_so = var_p__p / var_slow_outward_current__tau_so + (1.0 - var_p__p) * var_membrane__u / var_slow_outward_current__tau_o; // uA_per_cm2
        const double var_chaste_interface__i_ionic = var_fast_inward_current__i_fi + var_slow_inward_current__i_si + var_slow_outward_current__i_so; // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }

    void Cellbueno_2007_epiFromCellMLGRL1::UpdateTransmembranePotential(double var_chaste_interface__environment__time)
    {
        std::vector<double>& rY = rGetStateVariables();
        unsigned v_index = GetVoltageIndex();
        const double delta = 1e-8;

        double d_dt_chaste_interface_var_membrane__V;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_w_gate__w = rY[2];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_s_gate__s = rY[3];
        // Units: dimensionless; Initial value: 0.0
        

        // Mathematics
        const double var_fast_inward_current__tau_fi = 0.11; // cm2_per_uA
        const double var_fast_inward_current__u_u = 1.55; // dimensionless
        const double var_m__u_m = 0.29999999999999999; // dimensionless
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__i_stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // uA_per_cm2
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_m__m = ((var_m__u_m > var_membrane__u) ? (0) : (1.0)); // dimensionless
        const double var_fast_inward_current__i_fi = -(-var_m__u_m + var_membrane__u) * (-var_membrane__u + var_fast_inward_current__u_u) * var_chaste_interface__fast_inward_current_v_gate__v * var_m__m / var_fast_inward_current__tau_fi; // uA_per_cm2
        const double var_p__u_p = 0.13; // dimensionless
        const double var_p__p = ((var_membrane__u < var_p__u_p) ? (0) : (1.0)); // dimensionless
        const double var_r__u_r = 0.0060000000000000001; // dimensionless
        const double var_r__r = ((var_membrane__u < var_r__u_r) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current__tau_si = 1.8875; // cm2_per_uA
        const double var_slow_inward_current__i_si = -var_p__p * var_chaste_interface__slow_inward_current_s_gate__s * var_chaste_interface__slow_inward_current_w_gate__w / var_slow_inward_current__tau_si; // uA_per_cm2
        const double var_slow_outward_current__k_so = 2.0457999999999998; // dimensionless
        const double var_slow_outward_current__tau_o1 = 400.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o2 = 6.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o = (1.0 - var_r__r) * var_slow_outward_current__tau_o1 + var_r__r * var_slow_outward_current__tau_o2; // cm2_per_uA
        const double var_slow_outward_current__tau_so1 = 30.0181; // cm2_per_uA
        const double var_slow_outward_current__tau_so2 = 0.99570000000000003; // cm2_per_uA
        const double var_slow_outward_current__u_so = 0.65000000000000002; // dimensionless
        const double var_slow_outward_current__tau_so = 0.5 * (1.0 + tanh((-var_slow_outward_current__u_so + var_membrane__u) * var_slow_outward_current__k_so)) * (-var_slow_outward_current__tau_so1 + var_slow_outward_current__tau_so2) + var_slow_outward_current__tau_so1; // cm2_per_uA
        const double var_slow_outward_current__i_so = var_p__p / var_slow_outward_current__tau_so + (1.0 - var_p__p) * var_membrane__u / var_slow_outward_current__tau_o; // uA_per_cm2
        d_dt_chaste_interface_var_membrane__V = -(var_fast_inward_current__i_fi + var_membrane__i_stim + var_slow_inward_current__i_si + var_slow_outward_current__i_so) / mParameters[0]; // mV / ms

        double evalF = d_dt_chaste_interface_var_membrane__V;
        mEvalF[0] = d_dt_chaste_interface_var_membrane__V;
        double partialF = EvaluatePartialDerivative0(var_chaste_interface__environment__time, rY, delta, true);
        if (fabs(partialF) < delta)
        {
            rY[v_index] += evalF*mDt;
        }
        else
        {
            rY[v_index] += (evalF/partialF)*(exp(partialF*mDt)-1.0);
        }
    }

    void Cellbueno_2007_epiFromCellMLGRL1::ComputeOneStepExceptVoltage(double var_chaste_interface__environment__time)
    {
        std::vector<double>& rY = rGetStateVariables();
        const double delta = 1e-8;

        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_w_gate__w = rY[2];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_s_gate__s = rY[3];
        // Units: dimensionless; Initial value: 0.0
        

        // Mathematics
        const double var_fast_inward_current_v_gate__tau_v1_minus = 60.0; // ms
        const double var_fast_inward_current_v_gate__tau_v2_minus = 1150.0; // ms
        const double var_fast_inward_current_v_gate__tau_v_plus = 1.4505999999999999; // ms
        const double var_m__u_m = 0.29999999999999999; // dimensionless
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_m__m = ((var_m__u_m > var_membrane__u) ? (0) : (1.0)); // dimensionless
        const double var_p__u_p = 0.13; // dimensionless
        const double var_p__p = ((var_membrane__u < var_p__u_p) ? (0) : (1.0)); // dimensionless
        const double var_q__u_q = 0.0060000000000000001; // dimensionless
        const double var_fast_inward_current_v_gate__v_inf = ((var_membrane__u < var_q__u_q) ? (1.0) : (0)); // dimensionless
        const double var_q__q = ((var_membrane__u < var_q__u_q) ? (0) : (1.0)); // dimensionless
        const double var_fast_inward_current_v_gate__tau_v_minus = (1.0 - var_q__q) * var_fast_inward_current_v_gate__tau_v1_minus + var_fast_inward_current_v_gate__tau_v2_minus * var_q__q; // ms
        const double d_dt_chaste_interface_var_fast_inward_current_v_gate__v = (1.0 - var_m__m) * (-var_chaste_interface__fast_inward_current_v_gate__v + var_fast_inward_current_v_gate__v_inf) / var_fast_inward_current_v_gate__tau_v_minus - var_chaste_interface__fast_inward_current_v_gate__v * var_m__m / var_fast_inward_current_v_gate__tau_v_plus; // 1 / ms
        const double var_r__u_r = 0.0060000000000000001; // dimensionless
        const double var_r__r = ((var_membrane__u < var_r__u_r) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current_s_gate__k_s = 2.0994000000000002; // dimensionless
        const double var_slow_inward_current_s_gate__tau_s1 = 2.7342; // ms
        const double var_slow_inward_current_s_gate__tau_s2 = 16.0; // ms
        const double var_slow_inward_current_s_gate__tau_s = (1.0 - var_p__p) * var_slow_inward_current_s_gate__tau_s1 + var_p__p * var_slow_inward_current_s_gate__tau_s2; // ms
        const double var_slow_inward_current_s_gate__u_s = 0.90869999999999995; // dimensionless
        const double d_dt_chaste_interface_var_slow_inward_current_s_gate__s = (0.5 - var_chaste_interface__slow_inward_current_s_gate__s + 0.5 * tanh((-var_slow_inward_current_s_gate__u_s + var_membrane__u) * var_slow_inward_current_s_gate__k_s)) / var_slow_inward_current_s_gate__tau_s; // 1 / ms
        const double var_slow_inward_current_w_gate__k_w_minus = 65.0; // dimensionless
        const double var_slow_inward_current_w_gate__tau_w1_minus = 60.0; // ms
        const double var_slow_inward_current_w_gate__tau_w2_minus = 15.0; // ms
        const double var_slow_inward_current_w_gate__tau_w_plus = 200.0; // ms
        const double var_slow_inward_current_w_gate__tau_winf = 0.070000000000000007; // ms
        const double var_slow_inward_current_w_gate__u_w_minus = 0.029999999999999999; // dimensionless
        const double var_slow_inward_current_w_gate__tau_w_minus = 0.5 * (1.0 + tanh((-var_slow_inward_current_w_gate__u_w_minus + var_membrane__u) * var_slow_inward_current_w_gate__k_w_minus)) * (-var_slow_inward_current_w_gate__tau_w1_minus + var_slow_inward_current_w_gate__tau_w2_minus) + var_slow_inward_current_w_gate__tau_w1_minus; // ms
        const double var_slow_inward_current_w_gate__wstar_inf = 0.93999999999999995; // dimensionless
        const double var_slow_inward_current_w_gate__w_inf = (1.0 - var_r__r) * (1.0 - var_membrane__u / var_slow_inward_current_w_gate__tau_winf) + var_r__r * var_slow_inward_current_w_gate__wstar_inf; // dimensionless
        const double d_dt_chaste_interface_var_slow_inward_current_w_gate__w = (1.0 - var_r__r) * (-var_chaste_interface__slow_inward_current_w_gate__w + var_slow_inward_current_w_gate__w_inf) / var_slow_inward_current_w_gate__tau_w_minus - var_r__r * var_chaste_interface__slow_inward_current_w_gate__w / var_slow_inward_current_w_gate__tau_w_plus; // 1 / ms
        
        mEvalF[1] = d_dt_chaste_interface_var_fast_inward_current_v_gate__v;
        mPartialF[1] = EvaluatePartialDerivative1(var_chaste_interface__environment__time, rY, delta);
        mEvalF[2] = d_dt_chaste_interface_var_slow_inward_current_w_gate__w;
        mPartialF[2] = EvaluatePartialDerivative2(var_chaste_interface__environment__time, rY, delta);
        mEvalF[3] = d_dt_chaste_interface_var_slow_inward_current_s_gate__s;
        mPartialF[3] = EvaluatePartialDerivative3(var_chaste_interface__environment__time, rY, delta);
        
        {
            if (fabs(mPartialF[1]) < delta){
                rY[1] += mDt*d_dt_chaste_interface_var_fast_inward_current_v_gate__v;
            }
            else
            {
                rY[1] += (d_dt_chaste_interface_var_fast_inward_current_v_gate__v/mPartialF[1])*(exp(mPartialF[1]*mDt)-1.0);
            }
            
        }
        {
            if (fabs(mPartialF[2]) < delta){
                rY[2] += mDt*d_dt_chaste_interface_var_slow_inward_current_w_gate__w;
            }
            else
            {
                rY[2] += (d_dt_chaste_interface_var_slow_inward_current_w_gate__w/mPartialF[2])*(exp(mPartialF[2]*mDt)-1.0);
            }
            
        }
        {
            if (fabs(mPartialF[3]) < delta){
                rY[3] += mDt*d_dt_chaste_interface_var_slow_inward_current_s_gate__s;
            }
            else
            {
                rY[3] += (d_dt_chaste_interface_var_slow_inward_current_s_gate__s/mPartialF[3])*(exp(mPartialF[3]*mDt)-1.0);
            }
            
        }        
        
    }
   
    
    double Cellbueno_2007_epiFromCellMLGRL1::EvaluateYDerivative0(double var_chaste_interface__environment__time, std::vector<double>& rY)
    {
        double d_dt_chaste_interface_var_membrane__V;
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_w_gate__w = rY[2];
        // Units: dimensionless; Initial value: 1.0
        double var_chaste_interface__slow_inward_current_s_gate__s = rY[3];
        // Units: dimensionless; Initial value: 0.0
        

        // Mathematics
        const double var_fast_inward_current__tau_fi = 0.11; // cm2_per_uA
        const double var_fast_inward_current__u_u = 1.55; // dimensionless
        const double var_m__u_m = 0.29999999999999999; // dimensionless
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__i_stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // uA_per_cm2
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_m__m = ((var_m__u_m > var_membrane__u) ? (0) : (1.0)); // dimensionless
        const double var_fast_inward_current__i_fi = -(-var_m__u_m + var_membrane__u) * (-var_membrane__u + var_fast_inward_current__u_u) * var_chaste_interface__fast_inward_current_v_gate__v * var_m__m / var_fast_inward_current__tau_fi; // uA_per_cm2
        const double var_p__u_p = 0.13; // dimensionless
        const double var_p__p = ((var_membrane__u < var_p__u_p) ? (0) : (1.0)); // dimensionless
        const double var_r__u_r = 0.0060000000000000001; // dimensionless
        const double var_r__r = ((var_membrane__u < var_r__u_r) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current__tau_si = 1.8875; // cm2_per_uA
        const double var_slow_inward_current__i_si = -var_p__p * var_chaste_interface__slow_inward_current_s_gate__s * var_chaste_interface__slow_inward_current_w_gate__w / var_slow_inward_current__tau_si; // uA_per_cm2
        const double var_slow_outward_current__k_so = 2.0457999999999998; // dimensionless
        const double var_slow_outward_current__tau_o1 = 400.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o2 = 6.0; // cm2_per_uA
        const double var_slow_outward_current__tau_o = (1.0 - var_r__r) * var_slow_outward_current__tau_o1 + var_r__r * var_slow_outward_current__tau_o2; // cm2_per_uA
        const double var_slow_outward_current__tau_so1 = 30.0181; // cm2_per_uA
        const double var_slow_outward_current__tau_so2 = 0.99570000000000003; // cm2_per_uA
        const double var_slow_outward_current__u_so = 0.65000000000000002; // dimensionless
        const double var_slow_outward_current__tau_so = 0.5 * (1.0 + tanh((-var_slow_outward_current__u_so + var_membrane__u) * var_slow_outward_current__k_so)) * (-var_slow_outward_current__tau_so1 + var_slow_outward_current__tau_so2) + var_slow_outward_current__tau_so1; // cm2_per_uA
        const double var_slow_outward_current__i_so = var_p__p / var_slow_outward_current__tau_so + (1.0 - var_p__p) * var_membrane__u / var_slow_outward_current__tau_o; // uA_per_cm2
        d_dt_chaste_interface_var_membrane__V = -(var_fast_inward_current__i_fi + var_membrane__i_stim + var_slow_inward_current__i_si + var_slow_outward_current__i_so) / mParameters[0]; // mV / ms

        return d_dt_chaste_interface_var_membrane__V;
    }

    double Cellbueno_2007_epiFromCellMLGRL1::EvaluatePartialDerivative0(double var_chaste_interface__environment__time, std::vector<double>& rY, double delta, bool forceNumerical)
    {
        double partialF;
        if (!forceNumerical && this->mUseAnalyticJacobian)
        {
            double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
            // Units: mV; Initial value: 0.0
            double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
            // Units: dimensionless; Initial value: 1.0
            

            const double var_x0 = var_chaste_interface__membrane__V;
            const double var_x1 = ((var_x0 < 0.0060000000000000001) ? (0) : (1.0));
            const double var_x2 = ((var_x0 < 0.13) ? (0) : (1.0));
            const double var_x3 = 9.0909090909090917 * var_chaste_interface__membrane__V;
            const double var_x4 = ((var_x0 < 0.29999999999999999) ? (0) : (1.0));
            const double var_x5 = var_x4 * var_chaste_interface__fast_inward_current_v_gate__v;
            const double var_x6 = -14.090909090909092 + var_x3;
            const double var_x7 = tanh(-1.3297699999999999 + 2.0457999999999998 * var_chaste_interface__membrane__V);
            const double var_x8 = 1 / mParameters[0];
            const double var_x9 = var_x8;
            
            partialF = -var_x9 * (var_x5 * var_x6 + var_x5 * (-2.7272727272727271 + var_x3) + (1.0 - var_x2) / (400.0 - 394.0 * var_x1) + 0.0041586275611754688 * var_x2 * (29.687012959999997 - 29.687012959999997 * pow(var_x7, 2)) / pow((1 - 0.93578987418504023 * var_x7), 2));
        }
        else
        {
            const double y_save = rY[0];
            rY[0] += delta;
            const double temp = EvaluateYDerivative0(var_chaste_interface__environment__time, rY);
            partialF = (temp-mEvalF[0])/delta;
            rY[0] = y_save;
        }
        return partialF;
    }
    double Cellbueno_2007_epiFromCellMLGRL1::EvaluateYDerivative1(double var_chaste_interface__environment__time, std::vector<double>& rY)
    {
        
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__fast_inward_current_v_gate__v = rY[1];
        // Units: dimensionless; Initial value: 1.0
        

        // Mathematics
        const double var_fast_inward_current_v_gate__tau_v1_minus = 60.0; // ms
        const double var_fast_inward_current_v_gate__tau_v2_minus = 1150.0; // ms
        const double var_fast_inward_current_v_gate__tau_v_plus = 1.4505999999999999; // ms
        const double var_m__u_m = 0.29999999999999999; // dimensionless
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_m__m = ((var_m__u_m > var_membrane__u) ? (0) : (1.0)); // dimensionless
        const double var_q__u_q = 0.0060000000000000001; // dimensionless
        const double var_fast_inward_current_v_gate__v_inf = ((var_membrane__u < var_q__u_q) ? (1.0) : (0)); // dimensionless
        const double var_q__q = ((var_membrane__u < var_q__u_q) ? (0) : (1.0)); // dimensionless
        const double var_fast_inward_current_v_gate__tau_v_minus = (1.0 - var_q__q) * var_fast_inward_current_v_gate__tau_v1_minus + var_fast_inward_current_v_gate__tau_v2_minus * var_q__q; // ms
        const double d_dt_chaste_interface_var_fast_inward_current_v_gate__v = (1.0 - var_m__m) * (-var_chaste_interface__fast_inward_current_v_gate__v + var_fast_inward_current_v_gate__v_inf) / var_fast_inward_current_v_gate__tau_v_minus - var_chaste_interface__fast_inward_current_v_gate__v * var_m__m / var_fast_inward_current_v_gate__tau_v_plus; // 1 / ms

        return d_dt_chaste_interface_var_fast_inward_current_v_gate__v;
    }

    double Cellbueno_2007_epiFromCellMLGRL1::EvaluatePartialDerivative1(double var_chaste_interface__environment__time, std::vector<double>& rY, double delta, bool forceNumerical)
    {
        double partialF;
        if (!forceNumerical && this->mUseAnalyticJacobian)
        {
            double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
            // Units: mV; Initial value: 0.0
            

            const double var_x0 = var_chaste_interface__membrane__V;
            const double var_x1 = ((var_x0 < 0.0060000000000000001) ? (0) : (1.0));
            const double var_x4 = ((var_x0 < 0.29999999999999999) ? (0) : (1.0));
            
            partialF = -0.68936991589687036 * var_x4 - (1.0 - var_x4) / (60.0 + 1090.0 * var_x1);
        }
        else
        {
            const double y_save = rY[1];
            rY[1] += delta;
            const double temp = EvaluateYDerivative1(var_chaste_interface__environment__time, rY);
            partialF = (temp-mEvalF[1])/delta;
            rY[1] = y_save;
        }
        return partialF;
    }
    double Cellbueno_2007_epiFromCellMLGRL1::EvaluateYDerivative2(double var_chaste_interface__environment__time, std::vector<double>& rY)
    {
        
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__slow_inward_current_w_gate__w = rY[2];
        // Units: dimensionless; Initial value: 1.0
        

        // Mathematics
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_r__u_r = 0.0060000000000000001; // dimensionless
        const double var_r__r = ((var_membrane__u < var_r__u_r) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current_w_gate__k_w_minus = 65.0; // dimensionless
        const double var_slow_inward_current_w_gate__tau_w1_minus = 60.0; // ms
        const double var_slow_inward_current_w_gate__tau_w2_minus = 15.0; // ms
        const double var_slow_inward_current_w_gate__tau_w_plus = 200.0; // ms
        const double var_slow_inward_current_w_gate__tau_winf = 0.070000000000000007; // ms
        const double var_slow_inward_current_w_gate__u_w_minus = 0.029999999999999999; // dimensionless
        const double var_slow_inward_current_w_gate__tau_w_minus = 0.5 * (1.0 + tanh((-var_slow_inward_current_w_gate__u_w_minus + var_membrane__u) * var_slow_inward_current_w_gate__k_w_minus)) * (-var_slow_inward_current_w_gate__tau_w1_minus + var_slow_inward_current_w_gate__tau_w2_minus) + var_slow_inward_current_w_gate__tau_w1_minus; // ms
        const double var_slow_inward_current_w_gate__wstar_inf = 0.93999999999999995; // dimensionless
        const double var_slow_inward_current_w_gate__w_inf = (1.0 - var_r__r) * (1.0 - var_membrane__u / var_slow_inward_current_w_gate__tau_winf) + var_r__r * var_slow_inward_current_w_gate__wstar_inf; // dimensionless
        const double d_dt_chaste_interface_var_slow_inward_current_w_gate__w = (1.0 - var_r__r) * (-var_chaste_interface__slow_inward_current_w_gate__w + var_slow_inward_current_w_gate__w_inf) / var_slow_inward_current_w_gate__tau_w_minus - var_r__r * var_chaste_interface__slow_inward_current_w_gate__w / var_slow_inward_current_w_gate__tau_w_plus; // 1 / ms

        return d_dt_chaste_interface_var_slow_inward_current_w_gate__w;
    }

    double Cellbueno_2007_epiFromCellMLGRL1::EvaluatePartialDerivative2(double var_chaste_interface__environment__time, std::vector<double>& rY, double delta, bool forceNumerical)
    {
        double partialF;
        if (!forceNumerical && this->mUseAnalyticJacobian)
        {
            double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
            // Units: mV; Initial value: 0.0
            

            const double var_x0 = var_chaste_interface__membrane__V;
            const double var_x1 = ((var_x0 < 0.0060000000000000001) ? (0) : (1.0));
            const double var_x11 = tanh(-1.95 + 65.0 * var_chaste_interface__membrane__V);
            const double var_x12 = 1.0 - var_x1;
            const double var_x13 = var_x12 / (37.5 - 22.5 * var_x11);
            
            partialF = -var_x13 - 0.0050000000000000001 * var_x1;
        }
        else
        {
            const double y_save = rY[2];
            rY[2] += delta;
            const double temp = EvaluateYDerivative2(var_chaste_interface__environment__time, rY);
            partialF = (temp-mEvalF[2])/delta;
            rY[2] = y_save;
        }
        return partialF;
    }
    double Cellbueno_2007_epiFromCellMLGRL1::EvaluateYDerivative3(double var_chaste_interface__environment__time, std::vector<double>& rY)
    {
        
        double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: mV; Initial value: 0.0
        double var_chaste_interface__slow_inward_current_s_gate__s = rY[3];
        // Units: dimensionless; Initial value: 0.0
        

        // Mathematics
        const double var_membrane__alpha = 1.0; // per_mV
        const double var_membrane__u = var_chaste_interface__membrane__V * var_membrane__alpha; // dimensionless
        const double var_p__u_p = 0.13; // dimensionless
        const double var_p__p = ((var_membrane__u < var_p__u_p) ? (0) : (1.0)); // dimensionless
        const double var_slow_inward_current_s_gate__k_s = 2.0994000000000002; // dimensionless
        const double var_slow_inward_current_s_gate__tau_s1 = 2.7342; // ms
        const double var_slow_inward_current_s_gate__tau_s2 = 16.0; // ms
        const double var_slow_inward_current_s_gate__tau_s = (1.0 - var_p__p) * var_slow_inward_current_s_gate__tau_s1 + var_p__p * var_slow_inward_current_s_gate__tau_s2; // ms
        const double var_slow_inward_current_s_gate__u_s = 0.90869999999999995; // dimensionless
        const double d_dt_chaste_interface_var_slow_inward_current_s_gate__s = (0.5 - var_chaste_interface__slow_inward_current_s_gate__s + 0.5 * tanh((-var_slow_inward_current_s_gate__u_s + var_membrane__u) * var_slow_inward_current_s_gate__k_s)) / var_slow_inward_current_s_gate__tau_s; // 1 / ms

        return d_dt_chaste_interface_var_slow_inward_current_s_gate__s;
    }

    double Cellbueno_2007_epiFromCellMLGRL1::EvaluatePartialDerivative3(double var_chaste_interface__environment__time, std::vector<double>& rY, double delta, bool forceNumerical)
    {
        double partialF;
        if (!forceNumerical && this->mUseAnalyticJacobian)
        {
            double var_chaste_interface__membrane__V = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
            // Units: mV; Initial value: 0.0
            

            const double var_x0 = var_chaste_interface__membrane__V;
            const double var_x2 = ((var_x0 < 0.13) ? (0) : (1.0));
            const double var_x14 = 1 / (2.7342 + 13.2658 * var_x2);
            
            partialF = -var_x14;
        }
        else
        {
            const double y_save = rY[3];
            rY[3] += delta;
            const double temp = EvaluateYDerivative3(var_chaste_interface__environment__time, rY);
            partialF = (temp-mEvalF[3])/delta;
            rY[3] = y_save;
        }
        return partialF;
    }

    std::vector<double> Cellbueno_2007_epiFromCellMLGRL1::ComputeDerivedQuantities(double var_chaste_interface__environment__time, const std::vector<double> & rY)
    {
        // Inputs:
        // Time units: millisecond
        
        // Mathematics
        const double var_membrane__i_stim = GetIntracellularAreaStimulus(var_chaste_interface__environment__time); // uA_per_cm2

        std::vector<double> dqs(2);
        dqs[0] = var_membrane__i_stim;
        dqs[1] = var_chaste_interface__environment__time;
        return dqs;
    }

template<>
void OdeSystemInformation<Cellbueno_2007_epiFromCellMLGRL1>::Initialise(void)
{
    this->mSystemName = "bueno_2007";
    this->mFreeVariableName = "time";
    this->mFreeVariableUnits = "ms";

    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("mV");
    this->mInitialConditions.push_back(0.0);

    // rY[1]:
    this->mVariableNames.push_back("fast_inward_current_v_gate__v");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[2]:
    this->mVariableNames.push_back("slow_inward_current_w_gate__w");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(1.0);

    // rY[3]:
    this->mVariableNames.push_back("slow_inward_current_s_gate__s");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    // mParameters[0]:
    this->mParameterNames.push_back("membrane_capacitance");
    this->mParameterUnits.push_back("uF_per_cm2");

    // Derived Quantity index [0]:
    this->mDerivedQuantityNames.push_back("membrane_stimulus_current");
    this->mDerivedQuantityUnits.push_back("uA_per_cm2");

    // Derived Quantity index [1]:
    this->mDerivedQuantityNames.push_back("time");
    this->mDerivedQuantityUnits.push_back("ms");

    this->mInitialised = true;
}

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Cellbueno_2007_epiFromCellMLGRL1)

