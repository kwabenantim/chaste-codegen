//! @file
//!
//! This source file was generated from CellML by chaste_codegen version 0.0.1
//!
//! Model: dokos_model_1996
//!
//! Processed by chaste_codegen: https://github.com/ModellingWebLab/chaste-codegen
//!     (translator: chaste_codegen, model type: normal)
//! on 2020-02-18 14:13:39
//!
//! <autogenerated>

#include "dokos_model_1996.hpp"
#include <cmath>
#include <cassert>
#include <memory>
#include "Exception.hpp"
#include "OdeSystemInformation.hpp"
#include "RegularStimulus.hpp"
#include "HeartConfig.hpp"
#include "IsNan.hpp"
#include "MathsCustomFunctions.hpp"

    double Celldokos_model_1996FromCellML::GetIntracellularCalciumConcentration()
    {
        return mStateVariables[1];
    }

    Celldokos_model_1996FromCellML::Celldokos_model_1996FromCellML(boost::shared_ptr<AbstractIvpOdeSolver> pSolver, boost::shared_ptr<AbstractStimulusFunction> pIntracellularStimulus)
        : AbstractCardiacCell(
                pSolver,
                18,
                0,
                pIntracellularStimulus)
    {
        // Time units: millisecond
        //
        this->mpSystemInfo = OdeSystemInformation<Celldokos_model_1996FromCellML>::Instance();
        Init();
        
    }

    Celldokos_model_1996FromCellML::~Celldokos_model_1996FromCellML()
    {
    }

    double Celldokos_model_1996FromCellML::GetIIonic(const std::vector<double>* pStateVariables)
    {
        // For state variable interpolation (SVI) we read in interpolated state variables,
        // otherwise for ionic current interpolation (ICI) we use the state variables of this model (node).
        if (!pStateVariables) pStateVariables = &rGetStateVariables();
        const std::vector<double>& rY = *pStateVariables;
        double var_chaste_interface__membrane__E = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -64.9
        double var_chaste_interface__ion_concentrations__Cai = rY[1];
        // Units: millimolar; Initial value: 3.4e-05
        double var_chaste_interface__L_type_calcium_current_d_gate__dL = rY[2];
        // Units: dimensionless; Initial value: 0.0001
        double var_chaste_interface__L_type_calcium_current_f_gate__fL = rY[3];
        // Units: dimensionless; Initial value: 0.1505
        double var_chaste_interface__L_type_calcium_current_f2_gate__fL2 = rY[4];
        // Units: dimensionless; Initial value: 0.219
        double var_chaste_interface__T_type_calcium_current_d_gate__dT = rY[5];
        // Units: dimensionless; Initial value: 0.001
        double var_chaste_interface__T_type_calcium_current_f_gate__fT = rY[6];
        // Units: dimensionless; Initial value: 0.1328
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[7];
        // Units: dimensionless; Initial value: 0.0139
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[8];
        // Units: dimensionless; Initial value: 0.0087
        double var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x = rY[9];
        // Units: dimensionless; Initial value: 0.5682
        double var_chaste_interface__hyperpolarising_activated_current_y_gate__y = rY[10];
        // Units: dimensionless; Initial value: 0.0287
        double var_chaste_interface__ion_concentrations__Cao = rY[11];
        // Units: millimolar; Initial value: 2.0004
        double var_chaste_interface__ion_concentrations__Nai = rY[14];
        // Units: millimolar; Initial value: 7.4994
        double var_chaste_interface__ion_concentrations__Nao = rY[15];
        // Units: millimolar; Initial value: 139.9929
        double var_chaste_interface__ion_concentrations__Ki = rY[16];
        // Units: millimolar; Initial value: 140.0073
        double var_chaste_interface__ion_concentrations__Ko = rY[17];
        // Units: millimolar; Initial value: 5.4243
        
        const double var_reversal_potentials__E_Ca = 13.356880329847826 * log(var_chaste_interface__ion_concentrations__Cao / var_chaste_interface__ion_concentrations__Cai); // millivolt
        const double var_reversal_potentials__E_Na = 26.713760659695652 * log(var_chaste_interface__ion_concentrations__Nao / var_chaste_interface__ion_concentrations__Nai); // millivolt
        const double var_sodium_calcium_exchange_current__di = 1.0 + 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai + 0.0011051656880977081 * pow(var_chaste_interface__ion_concentrations__Nai, 2.0) + 0.0025297242600556538 * var_chaste_interface__ion_concentrations__Nai + 4.1799004844845232e-5 * pow(var_chaste_interface__ion_concentrations__Nai, 3.0) + 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai * exp(-0.0051246996536338553 * var_chaste_interface__membrane__E) + 1.8271247633873429 * var_chaste_interface__ion_concentrations__Cai * var_chaste_interface__ion_concentrations__Nai; // dimensionless
        const double var_sodium_calcium_exchange_current__do = 1.0 + 2.3464309350494597e-7 * pow(var_chaste_interface__ion_concentrations__Nao, 3.0) + 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao + 1.094140745013563e-6 * pow(var_chaste_interface__ion_concentrations__Nao, 2.0) + 0.00061425061425061424 * var_chaste_interface__ion_concentrations__Nao + 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao * exp(0); // dimensionless
        const double var_sodium_calcium_exchange_current__k12 = 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai * exp(-0.0051246996536338553 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__di; // dimensionless
        const double var_sodium_calcium_exchange_current__k14 = (0.0011051656880977081 * pow(var_chaste_interface__ion_concentrations__Nai, 2.0) + 4.1799004844845232e-5 * pow(var_chaste_interface__ion_concentrations__Nai, 3.0)) * exp(0.0080763619450073352 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__di; // dimensionless
        const double var_sodium_calcium_exchange_current__k21 = 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao * exp(0) / var_sodium_calcium_exchange_current__do; // dimensionless
        const double var_sodium_calcium_exchange_current__k23 = (2.3464309350494597e-7 * pow(var_chaste_interface__ion_concentrations__Nao, 3.0) + 1.094140745013563e-6 * pow(var_chaste_interface__ion_concentrations__Nao, 2.0)) * exp(-0.0080763619450073352 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__do; // dimensionless
        const double var_sodium_calcium_exchange_current__k32 = exp(0.0080763619450073352 * var_chaste_interface__membrane__E); // dimensionless
        const double var_sodium_calcium_exchange_current__k34 = var_chaste_interface__ion_concentrations__Nao / (4.6630000000000003 + var_chaste_interface__ion_concentrations__Nao); // dimensionless
        const double var_sodium_calcium_exchange_current__k41 = exp(-0.0080763619450073352 * var_chaste_interface__membrane__E); // dimensionless
        const double var_sodium_calcium_exchange_current__k43 = var_chaste_interface__ion_concentrations__Nai / (26.440000000000001 + var_chaste_interface__ion_concentrations__Nai); // dimensionless
        const double var_membrane__i_tot = 0.00024000000000000001 * var_chaste_interface__membrane__E - 0.00024000000000000001 * var_reversal_potentials__E_Na + 4.0 * (((var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k32 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k41) * var_sodium_calcium_exchange_current__k21 - ((var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k34 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k21 * var_sodium_calcium_exchange_current__k32) * var_sodium_calcium_exchange_current__k12) / ((var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k23 * var_sodium_calcium_exchange_current__k34 + (var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k32 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k14 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k34 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k14 * var_sodium_calcium_exchange_current__k21 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k23 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k21 * var_sodium_calcium_exchange_current__k32) + 6.9999999999999994e-5 * pow(var_chaste_interface__ion_concentrations__Ko, 0.40999999999999998) * (-var_chaste_interface__ion_concentrations__Ko * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Ki) + 0.25 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__E) * var_chaste_interface__fast_sodium_current_h_gate__h + 0.00025999999999999998 * pow(var_chaste_interface__ion_concentrations__Ko, 0.58999999999999997) * (-var_chaste_interface__ion_concentrations__Ko * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Ki) * var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x + 0.085000000000000006 * (75.0 - var_reversal_potentials__E_Ca + var_chaste_interface__membrane__E) * var_chaste_interface__T_type_calcium_current_d_gate__dT * var_chaste_interface__T_type_calcium_current_f_gate__fT + 9.0999999999999993e-6 * pow(var_chaste_interface__ion_concentrations__Ko, 0.58999999999999997) * (-var_chaste_interface__ion_concentrations__Nao * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Nai) * var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x + 0.0080999999999999996 * pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__E) * var_chaste_interface__hyperpolarising_activated_current_y_gate__y / (71.36612580598495 + pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001)) + 0.40000000000000002 * (75.0 - var_reversal_potentials__E_Ca + var_chaste_interface__membrane__E) * var_chaste_interface__L_type_calcium_current_d_gate__dL * var_chaste_interface__L_type_calcium_current_f2_gate__fL2 * var_chaste_interface__L_type_calcium_current_f_gate__fL + 0.0135 * pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001) * (-26.713760659695652 * log(var_chaste_interface__ion_concentrations__Ko / var_chaste_interface__ion_concentrations__Ki) + var_chaste_interface__membrane__E) * var_chaste_interface__hyperpolarising_activated_current_y_gate__y / (71.36612580598495 + pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001)) + 0.22600000000000001 * (1.0 - 0.035938096628557313 * pow((-1 + 0.025000000000000001 * var_chaste_interface__membrane__E), 2.0)) * var_chaste_interface__ion_concentrations__Ko * var_chaste_interface__ion_concentrations__Nai / ((1.0 + var_chaste_interface__ion_concentrations__Ko) * (40.0 + var_chaste_interface__ion_concentrations__Nai)); // picoA
        const double var_chaste_interface__i_ionic = 31.25 * HeartConfig::Instance()->GetCapacitance() * var_membrane__i_tot; // uA_per_cm2

        const double i_ionic = var_chaste_interface__i_ionic;
        EXCEPT_IF_NOT(!std::isnan(i_ionic));
        return i_ionic;
    }

    void Celldokos_model_1996FromCellML::EvaluateYDerivatives(double var_chaste_interface__environment__time_converted, const std::vector<double>& rY, std::vector<double>& rDY)
    {
        // Inputs:
        // Time units: millisecond
        double var_chaste_interface__membrane__E = (mSetVoltageDerivativeToZero ? this->mFixedVoltage : rY[0]);
        // Units: millivolt; Initial value: -64.9
        double var_chaste_interface__ion_concentrations__Cai = rY[1];
        // Units: millimolar; Initial value: 3.4e-05
        double var_chaste_interface__L_type_calcium_current_d_gate__dL = rY[2];
        // Units: dimensionless; Initial value: 0.0001
        double var_chaste_interface__L_type_calcium_current_f_gate__fL = rY[3];
        // Units: dimensionless; Initial value: 0.1505
        double var_chaste_interface__L_type_calcium_current_f2_gate__fL2 = rY[4];
        // Units: dimensionless; Initial value: 0.219
        double var_chaste_interface__T_type_calcium_current_d_gate__dT = rY[5];
        // Units: dimensionless; Initial value: 0.001
        double var_chaste_interface__T_type_calcium_current_f_gate__fT = rY[6];
        // Units: dimensionless; Initial value: 0.1328
        double var_chaste_interface__fast_sodium_current_m_gate__m = rY[7];
        // Units: dimensionless; Initial value: 0.0139
        double var_chaste_interface__fast_sodium_current_h_gate__h = rY[8];
        // Units: dimensionless; Initial value: 0.0087
        double var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x = rY[9];
        // Units: dimensionless; Initial value: 0.5682
        double var_chaste_interface__hyperpolarising_activated_current_y_gate__y = rY[10];
        // Units: dimensionless; Initial value: 0.0287
        double var_chaste_interface__ion_concentrations__Cao = rY[11];
        // Units: millimolar; Initial value: 2.0004
        double var_chaste_interface__ion_concentrations__Caup = rY[12];
        // Units: millimolar; Initial value: 0.5832
        double var_chaste_interface__ion_concentrations__Carel = rY[13];
        // Units: millimolar; Initial value: 0.1101
        double var_chaste_interface__ion_concentrations__Nai = rY[14];
        // Units: millimolar; Initial value: 7.4994
        double var_chaste_interface__ion_concentrations__Nao = rY[15];
        // Units: millimolar; Initial value: 139.9929
        double var_chaste_interface__ion_concentrations__Ki = rY[16];
        // Units: millimolar; Initial value: 140.0073
        double var_chaste_interface__ion_concentrations__Ko = rY[17];
        // Units: millimolar; Initial value: 5.4243

        // Mathematics
        double d_dt_chaste_interface_var_membrane__E;
        const double d_dt_chaste_interface_var_L_type_calcium_current_f2_gate__fL2 = 0.0030000000000000001 - 0.0030000000000000001 * var_chaste_interface__L_type_calcium_current_f2_gate__fL2 - 40.0 * var_chaste_interface__L_type_calcium_current_f2_gate__fL2 * var_chaste_interface__ion_concentrations__Cai; // 1 / millisecond
        const double d_dt_chaste_interface_var_L_type_calcium_current_d_gate__dL = 0.5 / (1.0 + exp(-1.0 - 0.15151515151515152 * var_chaste_interface__membrane__E)) - 0.5 * var_chaste_interface__L_type_calcium_current_d_gate__dL; // 1 / millisecond
        const double d_dt_chaste_interface_var_L_type_calcium_current_f_gate__fL = 0.001 * (-var_chaste_interface__L_type_calcium_current_f_gate__fL + 1.0 / (1.0 + exp(4.166666666666667 + 0.16666666666666666 * var_chaste_interface__membrane__E))) / (0.031 + 1.0 / (1.0 + exp(4.6419753086419755 + 0.1234567901234568 * var_chaste_interface__membrane__E))); // 1 / millisecond
        const double d_dt_chaste_interface_var_T_type_calcium_current_d_gate__dT = 0.001 * (-var_chaste_interface__T_type_calcium_current_d_gate__dT + 1.0 / (1.0 + exp(-3.7704918032786887 - 0.16393442622950821 * var_chaste_interface__membrane__E))) / (0.00059999999999999995 + 0.0054000000000000003 / (1.0 + exp(3.0 + 0.029999999999999999 * var_chaste_interface__membrane__E))); // 1 / millisecond
        const double d_dt_chaste_interface_var_T_type_calcium_current_f_gate__fT = 0.001 * (-var_chaste_interface__T_type_calcium_current_f_gate__fT + 1.0 / (1.0 + exp(11.363636363636365 + 0.15151515151515152 * var_chaste_interface__membrane__E))) / (0.001 + 0.040000000000000001 / (1.0 + exp(5.2000000000000002 + 0.080000000000000002 * var_chaste_interface__membrane__E))); // 1 / millisecond
        const double var_background_potassium_current__i_bK = 6.9999999999999994e-5 * pow(var_chaste_interface__ion_concentrations__Ko, 0.40999999999999998) * (-var_chaste_interface__ion_concentrations__Ko * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Ki); // picoA
        const double var_delayed_rectifying_potassium_current__i_KK = 0.00025999999999999998 * pow(var_chaste_interface__ion_concentrations__Ko, 0.58999999999999997) * (-var_chaste_interface__ion_concentrations__Ko * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Ki) * var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x; // picoA
        const double var_delayed_rectifying_potassium_current__i_KNa = 9.0999999999999993e-6 * pow(var_chaste_interface__ion_concentrations__Ko, 0.58999999999999997) * (-var_chaste_interface__ion_concentrations__Nao * exp(-0.037433890822745473 * var_chaste_interface__membrane__E) + var_chaste_interface__ion_concentrations__Nai) * var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x; // picoA
        const double d_dt_chaste_interface_var_delayed_rectifying_potassium_current_x_gate__x = 0.001 * (-var_chaste_interface__delayed_rectifying_potassium_current_x_gate__x + 1.0 / (1.0 + exp(-3.3918918918918921 - 0.13513513513513511 * var_chaste_interface__membrane__E))) * (17.0 * exp(0.039800000000000002 * var_chaste_interface__membrane__E) + 0.21099999999999999 * exp(-0.050999999999999997 * var_chaste_interface__membrane__E)); // 1 / millisecond
        const double d_dt_chaste_interface_var_fast_sodium_current_h_gate__h = 0.032399999999999998 * (1.0 - var_chaste_interface__fast_sodium_current_h_gate__h) * exp(-13.076000000000002 - 0.14000000000000001 * var_chaste_interface__membrane__E) - 0.70899999999999996 * var_chaste_interface__fast_sodium_current_h_gate__h / (1.0 + 4.2000000000000002 * exp(-2.7239999999999998 - 0.059999999999999998 * var_chaste_interface__membrane__E)); // 1 / millisecond
        const double d_dt_chaste_interface_var_fast_sodium_current_m_gate__m = -8.0 * var_chaste_interface__fast_sodium_current_m_gate__m * exp(-8.4299999999999997 - 0.14999999999999999 * var_chaste_interface__membrane__E) + 0.20000000000000001 * (1.0 - var_chaste_interface__fast_sodium_current_m_gate__m) * (34.299999999999997 + var_chaste_interface__membrane__E) / (1.0 - exp(-3.0869999999999997 - 0.089999999999999997 * var_chaste_interface__membrane__E)); // 1 / millisecond
        const double d_dt_chaste_interface_var_hyperpolarising_activated_current_y_gate__y = 0.00035999999999999997 * (1.0 - var_chaste_interface__hyperpolarising_activated_current_y_gate__y) * (137.80000000000001 + var_chaste_interface__membrane__E) / (-1.0 + exp(9.0948000000000011 + 0.066000000000000003 * var_chaste_interface__membrane__E)) - 0.0001 * (76.299999999999997 + var_chaste_interface__membrane__E) * var_chaste_interface__hyperpolarising_activated_current_y_gate__y / (1.0 - exp(-16.023 - 0.20999999999999999 * var_chaste_interface__membrane__E)); // 1 / millisecond
        const double var_reversal_potentials__E_Ca = 13.356880329847826 * log(var_chaste_interface__ion_concentrations__Cao / var_chaste_interface__ion_concentrations__Cai); // millivolt
        const double var_L_type_calcium_current__i_CaL = 0.40000000000000002 * (75.0 - var_reversal_potentials__E_Ca + var_chaste_interface__membrane__E) * var_chaste_interface__L_type_calcium_current_d_gate__dL * var_chaste_interface__L_type_calcium_current_f2_gate__fL2 * var_chaste_interface__L_type_calcium_current_f_gate__fL; // picoA
        const double var_T_type_calcium_current__i_CaT = 0.085000000000000006 * (75.0 - var_reversal_potentials__E_Ca + var_chaste_interface__membrane__E) * var_chaste_interface__T_type_calcium_current_d_gate__dT * var_chaste_interface__T_type_calcium_current_f_gate__fT; // picoA
        const double var_hyperpolarising_activated_current__i_fK = 0.0135 * pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001) * (-26.713760659695652 * log(var_chaste_interface__ion_concentrations__Ko / var_chaste_interface__ion_concentrations__Ki) + var_chaste_interface__membrane__E) * var_chaste_interface__hyperpolarising_activated_current_y_gate__y / (71.36612580598495 + pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001)); // picoA
        const double var_reversal_potentials__E_Na = 26.713760659695652 * log(var_chaste_interface__ion_concentrations__Nao / var_chaste_interface__ion_concentrations__Nai); // millivolt
        const double var_background_sodium_current__i_bNa = 0.00024000000000000001 * var_chaste_interface__membrane__E - 0.00024000000000000001 * var_reversal_potentials__E_Na; // picoA
        const double var_fast_sodium_current__i_Na = 0.25 * pow(var_chaste_interface__fast_sodium_current_m_gate__m, 3.0) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__E) * var_chaste_interface__fast_sodium_current_h_gate__h; // picoA
        const double var_hyperpolarising_activated_current__i_fNa = 0.0080999999999999996 * pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001) * (-var_reversal_potentials__E_Na + var_chaste_interface__membrane__E) * var_chaste_interface__hyperpolarising_activated_current_y_gate__y / (71.36612580598495 + pow(var_chaste_interface__ion_concentrations__Ko, 1.8300000000000001)); // picoA
        const double var_sarcoplasmic_reticulum_kinetics__i_up = 0.0212 * pow(var_chaste_interface__ion_concentrations__Cai, 2.0) / (2.4999999999999999e-7 + pow(var_chaste_interface__ion_concentrations__Cai, 2.0)); // picoA
        const double var_sarcoplasmic_reticulum_kinetics__i_rel = 0.57891204900000004 * pow(var_chaste_interface__ion_concentrations__Cai, 2.0) * var_chaste_interface__ion_concentrations__Carel / (9.9999999999999995e-7 + pow(var_chaste_interface__ion_concentrations__Cai, 2.0)); // picoA
        const double var_sarcoplasmic_reticulum_kinetics__i_tr = 0.0072364006125 * var_chaste_interface__ion_concentrations__Caup; // picoA
        const double d_dt_chaste_interface_var_ion_concentrations__Carel = 0.34547562163453949 * var_sarcoplasmic_reticulum_kinetics__i_tr - 0.34547562163453949 * var_sarcoplasmic_reticulum_kinetics__i_rel; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ion_concentrations__Caup = 0.14806098070051693 * var_sarcoplasmic_reticulum_kinetics__i_up - 0.14806098070051693 * var_sarcoplasmic_reticulum_kinetics__i_tr; // millimolar / millisecond
        const double var_sodium_calcium_exchange_current__di = 1.0 + 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai + 0.0011051656880977081 * pow(var_chaste_interface__ion_concentrations__Nai, 2.0) + 0.0025297242600556538 * var_chaste_interface__ion_concentrations__Nai + 4.1799004844845232e-5 * pow(var_chaste_interface__ion_concentrations__Nai, 3.0) + 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai * exp(-0.0051246996536338553 * var_chaste_interface__membrane__E) + 1.8271247633873429 * var_chaste_interface__ion_concentrations__Cai * var_chaste_interface__ion_concentrations__Nai; // dimensionless
        const double var_sodium_calcium_exchange_current__do = 1.0 + 2.3464309350494597e-7 * pow(var_chaste_interface__ion_concentrations__Nao, 3.0) + 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao + 1.094140745013563e-6 * pow(var_chaste_interface__ion_concentrations__Nao, 2.0) + 0.00061425061425061424 * var_chaste_interface__ion_concentrations__Nao + 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao * exp(0); // dimensionless
        const double var_sodium_calcium_exchange_current__k12 = 48.309178743961354 * var_chaste_interface__ion_concentrations__Cai * exp(-0.0051246996536338553 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__di; // dimensionless
        const double var_sodium_calcium_exchange_current__k14 = (0.0011051656880977081 * pow(var_chaste_interface__ion_concentrations__Nai, 2.0) + 4.1799004844845232e-5 * pow(var_chaste_interface__ion_concentrations__Nai, 3.0)) * exp(0.0080763619450073352 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__di; // dimensionless
        const double var_sodium_calcium_exchange_current__k21 = 0.27300027300027302 * var_chaste_interface__ion_concentrations__Cao * exp(0) / var_sodium_calcium_exchange_current__do; // dimensionless
        const double var_sodium_calcium_exchange_current__k23 = (2.3464309350494597e-7 * pow(var_chaste_interface__ion_concentrations__Nao, 3.0) + 1.094140745013563e-6 * pow(var_chaste_interface__ion_concentrations__Nao, 2.0)) * exp(-0.0080763619450073352 * var_chaste_interface__membrane__E) / var_sodium_calcium_exchange_current__do; // dimensionless
        const double var_sodium_calcium_exchange_current__k32 = exp(0.0080763619450073352 * var_chaste_interface__membrane__E); // dimensionless
        const double var_sodium_calcium_exchange_current__k34 = var_chaste_interface__ion_concentrations__Nao / (4.6630000000000003 + var_chaste_interface__ion_concentrations__Nao); // dimensionless
        const double var_sodium_calcium_exchange_current__k41 = exp(-0.0080763619450073352 * var_chaste_interface__membrane__E); // dimensionless
        const double var_sodium_calcium_exchange_current__k43 = var_chaste_interface__ion_concentrations__Nai / (26.440000000000001 + var_chaste_interface__ion_concentrations__Nai); // dimensionless
        const double var_sodium_calcium_exchange_current__i_NaCa = 4.0 * (((var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k32 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k41) * var_sodium_calcium_exchange_current__k21 - ((var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k34 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k21 * var_sodium_calcium_exchange_current__k32) * var_sodium_calcium_exchange_current__k12) / ((var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k23 * var_sodium_calcium_exchange_current__k34 + (var_sodium_calcium_exchange_current__k12 + var_sodium_calcium_exchange_current__k14) * var_sodium_calcium_exchange_current__k32 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k14 * var_sodium_calcium_exchange_current__k43 + (var_sodium_calcium_exchange_current__k21 + var_sodium_calcium_exchange_current__k23) * var_sodium_calcium_exchange_current__k34 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k41 + (var_sodium_calcium_exchange_current__k32 + var_sodium_calcium_exchange_current__k34) * var_sodium_calcium_exchange_current__k14 * var_sodium_calcium_exchange_current__k21 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k12 * var_sodium_calcium_exchange_current__k23 + (var_sodium_calcium_exchange_current__k41 + var_sodium_calcium_exchange_current__k43) * var_sodium_calcium_exchange_current__k21 * var_sodium_calcium_exchange_current__k32); // picoA
        const double d_dt_chaste_interface_var_ion_concentrations__Cai = 0.0020728537298072371 * var_sarcoplasmic_reticulum_kinetics__i_rel + 0.0041457074596144743 * var_sodium_calcium_exchange_current__i_NaCa - 0.0020728537298072371 * var_L_type_calcium_current__i_CaL - 0.0020728537298072371 * var_T_type_calcium_current__i_CaT - 0.0020728537298072371 * var_sarcoplasmic_reticulum_kinetics__i_up; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ion_concentrations__Cao = 0.02 + 0.010364268649036185 * var_L_type_calcium_current__i_CaL + 0.010364268649036185 * var_T_type_calcium_current__i_CaT - 0.01 * var_chaste_interface__ion_concentrations__Cao - 0.020728537298072371 * var_sodium_calcium_exchange_current__i_NaCa; // millimolar / millisecond
        const double var_sodium_potassium_pump__i_p = 0.22600000000000001 * (1.0 - 0.035938096628557313 * pow((-1 + 0.025000000000000001 * var_chaste_interface__membrane__E), 2.0)) * var_chaste_interface__ion_concentrations__Ko * var_chaste_interface__ion_concentrations__Nai / ((1.0 + var_chaste_interface__ion_concentrations__Ko) * (40.0 + var_chaste_interface__ion_concentrations__Nai)); // picoA
        const double d_dt_chaste_interface_var_ion_concentrations__Ki = 0.0082914149192289486 * var_sodium_potassium_pump__i_p - 0.0041457074596144743 * var_background_potassium_current__i_bK - 0.0041457074596144743 * var_delayed_rectifying_potassium_current__i_KK - 0.0041457074596144743 * var_hyperpolarising_activated_current__i_fK; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ion_concentrations__Ko = 0.053999999999999999 + 0.020728537298072371 * var_background_potassium_current__i_bK + 0.020728537298072371 * var_delayed_rectifying_potassium_current__i_KK + 0.020728537298072371 * var_hyperpolarising_activated_current__i_fK - 0.01 * var_chaste_interface__ion_concentrations__Ko - 0.041457074596144741 * var_sodium_potassium_pump__i_p; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ion_concentrations__Nai = -0.0041457074596144743 * var_background_sodium_current__i_bNa - 0.0041457074596144743 * var_delayed_rectifying_potassium_current__i_KNa - 0.0041457074596144743 * var_fast_sodium_current__i_Na - 0.0041457074596144743 * var_hyperpolarising_activated_current__i_fNa - 0.012437122378843422 * var_sodium_calcium_exchange_current__i_NaCa - 0.012437122378843422 * var_sodium_potassium_pump__i_p; // millimolar / millisecond
        const double d_dt_chaste_interface_var_ion_concentrations__Nao = 1.4000000000000001 + 0.020728537298072371 * var_background_sodium_current__i_bNa + 0.020728537298072371 * var_delayed_rectifying_potassium_current__i_KNa + 0.020728537298072371 * var_fast_sodium_current__i_Na + 0.020728537298072371 * var_hyperpolarising_activated_current__i_fNa + 0.062185611894217112 * var_sodium_calcium_exchange_current__i_NaCa + 0.062185611894217112 * var_sodium_potassium_pump__i_p - 0.01 * var_chaste_interface__ion_concentrations__Nao; // millimolar / millisecond

        if (mSetVoltageDerivativeToZero)
        {
            d_dt_chaste_interface_var_membrane__E = 0.0;
        }
        else
        {
            d_dt_chaste_interface_var_membrane__E = -31.25 * var_L_type_calcium_current__i_CaL - 31.25 * var_T_type_calcium_current__i_CaT - 31.25 * var_background_potassium_current__i_bK - 31.25 * var_background_sodium_current__i_bNa - 31.25 * var_delayed_rectifying_potassium_current__i_KK - 31.25 * var_delayed_rectifying_potassium_current__i_KNa - 31.25 * var_fast_sodium_current__i_Na - 31.25 * var_hyperpolarising_activated_current__i_fK - 31.25 * var_hyperpolarising_activated_current__i_fNa - 31.25 * var_sodium_calcium_exchange_current__i_NaCa - 31.25 * var_sodium_potassium_pump__i_p; // millivolt / millisecond
        }
        
        rDY[0] = d_dt_chaste_interface_var_membrane__E;
        rDY[1] = d_dt_chaste_interface_var_ion_concentrations__Cai;
        rDY[2] = d_dt_chaste_interface_var_L_type_calcium_current_d_gate__dL;
        rDY[3] = d_dt_chaste_interface_var_L_type_calcium_current_f_gate__fL;
        rDY[4] = d_dt_chaste_interface_var_L_type_calcium_current_f2_gate__fL2;
        rDY[5] = d_dt_chaste_interface_var_T_type_calcium_current_d_gate__dT;
        rDY[6] = d_dt_chaste_interface_var_T_type_calcium_current_f_gate__fT;
        rDY[7] = d_dt_chaste_interface_var_fast_sodium_current_m_gate__m;
        rDY[8] = d_dt_chaste_interface_var_fast_sodium_current_h_gate__h;
        rDY[9] = d_dt_chaste_interface_var_delayed_rectifying_potassium_current_x_gate__x;
        rDY[10] = d_dt_chaste_interface_var_hyperpolarising_activated_current_y_gate__y;
        rDY[11] = d_dt_chaste_interface_var_ion_concentrations__Cao;
        rDY[12] = d_dt_chaste_interface_var_ion_concentrations__Caup;
        rDY[13] = d_dt_chaste_interface_var_ion_concentrations__Carel;
        rDY[14] = d_dt_chaste_interface_var_ion_concentrations__Nai;
        rDY[15] = d_dt_chaste_interface_var_ion_concentrations__Nao;
        rDY[16] = d_dt_chaste_interface_var_ion_concentrations__Ki;
        rDY[17] = d_dt_chaste_interface_var_ion_concentrations__Ko;
    }

template<>
void OdeSystemInformation<Celldokos_model_1996FromCellML>::Initialise(void)
{
    this->mSystemName = "dokos_model_1996";
    this->mFreeVariableName = "environment__time_converted";
    this->mFreeVariableUnits = "millisecond";

    // rY[0]:
    this->mVariableNames.push_back("membrane_voltage");
    this->mVariableUnits.push_back("millivolt");
    this->mInitialConditions.push_back(-64.9);

    // rY[1]:
    this->mVariableNames.push_back("cytosolic_calcium_concentration");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(3.4e-05);

    // rY[2]:
    this->mVariableNames.push_back("L_type_calcium_current_d_gate__dL");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0001);

    // rY[3]:
    this->mVariableNames.push_back("L_type_calcium_current_f_gate__fL");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.1505);

    // rY[4]:
    this->mVariableNames.push_back("L_type_calcium_current_f2_gate__fL2");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.219);

    // rY[5]:
    this->mVariableNames.push_back("T_type_calcium_current_d_gate__dT");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.001);

    // rY[6]:
    this->mVariableNames.push_back("T_type_calcium_current_f_gate__fT");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.1328);

    // rY[7]:
    this->mVariableNames.push_back("fast_sodium_current_m_gate__m");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0139);

    // rY[8]:
    this->mVariableNames.push_back("fast_sodium_current_h_gate__h");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0087);

    // rY[9]:
    this->mVariableNames.push_back("delayed_rectifying_potassium_current_x_gate__x");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.5682);

    // rY[10]:
    this->mVariableNames.push_back("hyperpolarising_activated_current_y_gate__y");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0287);

    // rY[11]:
    this->mVariableNames.push_back("ion_concentrations__Cao");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(2.0004);

    // rY[12]:
    this->mVariableNames.push_back("ion_concentrations__Caup");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.5832);

    // rY[13]:
    this->mVariableNames.push_back("ion_concentrations__Carel");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(0.1101);

    // rY[14]:
    this->mVariableNames.push_back("ion_concentrations__Nai");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(7.4994);

    // rY[15]:
    this->mVariableNames.push_back("ion_concentrations__Nao");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(139.9929);

    // rY[16]:
    this->mVariableNames.push_back("ion_concentrations__Ki");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(140.0073);

    // rY[17]:
    this->mVariableNames.push_back("ion_concentrations__Ko");
    this->mVariableUnits.push_back("millimolar");
    this->mInitialConditions.push_back(5.4243);

    this->mInitialised = true;
}


// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(Celldokos_model_1996FromCellML)

