/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThermalPropertyHCVaporReal.cpp
 *
 * Code generation for function 'GetThermalPropertyHCVaporReal'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetCompCombGas.h"
#include "GetCorrAirComp.h"
#include "GetDensityHCVapor.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "GetEquilGrill.h"
#include "GetEquilOlikara.h"
#include "GetFuelPropertyN_Dodecane.h"
#include "GetHTCoeffHTX.h"
#include "GetIdealNozzleFlow.h"
#include "GetIdealNozzleFlowPTF.h"
#include "GetMEMbZach.h"
#include "GetPTF.h"
#include "GetPTFV1.h"
#include "GetPTx.h"
#include "GetTFromPhF.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"
#include "GetThdynCombGasZachV1.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetThermoDynPropPartial.h"
#include "GetTotalStaticPT.h"
#include "GetViscosityHCVapor.h"
#include "dNOx.h"
#include "rdivide.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
void GetThermalPropertyHCVaporReal(double p, double T, double MW, double T_CR,
  double p_CR, double W, double *rho_v, double *Cp_v, double *Cv_v, double
  *lambda)
{
  double p_R;
  double T_R;
  double v_R_ideal;
  double TT[5];
  int i13;
  double d14;
  int i;
  static const double b[4] = { 0.1181193, -0.265728, -0.15479, -0.030323 };

  double b_TT[3];
  double d15;
  static const double b_b[3] = { 0.0236744, -0.0186984, 0.0 };

  double D;
  double d16;
  static const double c_b[4] = { 0.2026579, -0.331511, -0.027655, -0.203488 };

  double d17;
  static const double d_b[3] = { 0.0313385, -0.0503618, 0.016901 };

  double D_h;
  double VV[6];
  double VV_h[6];
  double V_R_error;
  double V_R;
  double c43;
  int j;
  double c41;
  double y;
  double varargin_1;
  double V_R_temp;
  double z0;
  double V_R_h;
  double c41_h;
  double c43_h;
  static const double e_b[5] = { -0.077548, 4.5022582138, -1.70019347497797,
    0.282256664878756, -0.0122278061244889 };

  double dprdTr;
  double C_v_pe0;
  double Cp_pe0;
  double dprdTr_h;
  double C_v_peh;
  double L;
  double p_R4;
  double T_r5;
  double T_r9;
  double T_r16;
  double C_v_p;
  double expo;

  /* The function calculates the density, isobaric and isochronic specific heat  */
  /* capacity of the real hydrocarbon gases and thermal conductivity based on  */
  /* the %procudre 7A.1, 7D3.6, 7E1.6, 12B1.5 and 12B4.1 in API Technical Book  */
  /* of Petroleum Refining. */
  /*  Input */
  /*    p : pressure in Pa */
  /*    T : Temperature in K */
  /*    MW : Molecular weight in kg/kmol */
  /*    T_CR : Critical temperature in K */
  /*    p_CR : Critical pressure in Pa */
  /*    W : Acentric factor  */
  /*  Output */
  /*    rho_v : Density of real gas in kg/m3 */
  /*    Cp_v : Isobaric specific heat capacity of the real gas in J/kg/K */
  /*    Cv_v : Isochoric specific heat capacity of the real gas in J/kg/K */
  /*    lambda : Thermal conductivity of the vapor in W/mK */
  /*  Reference */
  /*    API Technical Data Book - Petroleum Refining(1985)  */
  /*  */
  /*  Created by Kevin Koosup Yum, 3 September 2013 */
  /* % Consants */
  /*  Gas constant in J/kmolK */
  p_R = p / p_CR;
  T_R = T / T_CR;
  v_R_ideal = rdivide(8314.0 * T, p) / (8314.0 * T_CR / p_CR);
  for (i13 = 0; i13 < 5; i13++) {
    TT[i13] = 0.0;
  }

  TT[0] = 1.0;
  d14 = 0.0;
  for (i = 0; i < 4; i++) {
    TT[i + 1] = TT[i] * T_R;
    d14 += 1.0 / TT[i] * b[i];
  }

  for (i13 = 0; i13 < 2; i13++) {
    b_TT[i13] = TT[i13];
  }

  b_TT[2] = TT[3];
  d15 = 0.0;
  for (i13 = 0; i13 < 3; i13++) {
    d15 += 1.0 / b_TT[i13] * b_b[i13];
  }

  D = 1.55488E-5 + rdivide(6.23689E-5, T_R);
  d16 = 0.0;
  for (i13 = 0; i13 < 4; i13++) {
    d16 += 1.0 / TT[i13] * c_b[i13];
  }

  for (i13 = 0; i13 < 2; i13++) {
    b_TT[i13] = TT[i13];
  }

  b_TT[2] = TT[3];
  d17 = 0.0;
  for (i13 = 0; i13 < 3; i13++) {
    d17 += 1.0 / b_TT[i13] * d_b[i13];
  }

  D_h = 4.8736E-5 + rdivide(7.40336E-6, T_R);
  for (i = 0; i < 6; i++) {
    VV[i] = 0.0;
    VV_h[i] = 0.0;
  }

  /* % Calculate the density of vapor */
  /* Simple fluid calculation */
  V_R_error = 1.0;
  V_R = v_R_ideal * 0.8;
  c43 = 0.0;
  while (V_R_error > 0.001) {
    VV[0] = V_R;
    for (j = 0; j < 5; j++) {
      VV[j + 1] = VV[j] * V_R;
    }

    c41 = 0.042724 / TT[3] / VV[1];
    y = 0.060167 / VV[1];
    c43 = exp(-0.060167 / VV[1]);
    varargin_1 = 0.1 * V_R;
    y = V_R - (p_R / T_R * V_R - ((((1.0 + d14 / V_R) + d15 / VV[1]) + D / VV[4])
                + c41 * (0.65392 + y) * c43)) / (p_R / T_R - (((((-d14 / VV[1] -
      2.0 * d15 / VV[2]) - 5.0 * D / VV[5]) + -0.085448 / TT[3] / VV[2] *
      (0.65392 + y) * c43) + c41 * (-0.120334 / VV[2]) * c43) + c41 * (0.65392 +
      y) * (0.120334 / VV[2] * c43)));
    if ((varargin_1 >= y) || rtIsNaN(y)) {
      V_R_temp = varargin_1;
    } else {
      V_R_temp = y;
    }

    V_R_error = fabs(V_R_temp - V_R) / V_R;
    V_R = V_R_temp;
  }

  z0 = p_R * V_R / T_R;

  /* Heavy Reference fluid calculation */
  V_R_h = v_R_ideal * 0.8;
  V_R_error = 1.0;
  while (V_R_error > 0.001) {
    VV_h[0] = V_R_h;
    for (j = 0; j < 5; j++) {
      VV_h[j + 1] = VV_h[j] * V_R_h;
    }

    c41_h = 0.041577 / TT[3] / VV_h[1];
    y = 0.03754 / VV_h[1];
    c43_h = exp(-0.03754 / VV_h[1]);
    varargin_1 = 0.1 * V_R_h;
    y = V_R_h - (p_R / T_R * V_R_h - ((((1.0 + d16 / V_R_h) + d17 / VV_h[1]) +
      D_h / VV_h[4]) + c41_h * (1.226 + y) * c43_h)) / (p_R / T_R - (((((-d16 /
      VV_h[1] - 2.0 * d17 / VV_h[2]) - 5.0 * D_h / VV_h[5]) + -0.083154 / TT[3] /
      VV_h[2] * (1.226 + y) * c43_h) + c41_h * (-0.07508 / VV_h[2]) * c43_h) +
      c41_h * (1.226 + y) * (0.07508 / VV_h[2] * c43)));
    if ((varargin_1 >= y) || rtIsNaN(y)) {
      V_R_temp = varargin_1;
    } else {
      V_R_temp = y;
    }

    V_R_error = fabs(V_R_temp - V_R_h) / V_R_h;
    V_R_h = V_R_temp;
  }

  *rho_v = 1.0 / ((z0 + W / 0.3978 * (p_R * V_R_h / T_R - z0)) * 8314.0 * T / p)
    * MW;

  /* % Calculate the CP and Cv */
  y = 0.0;
  for (i13 = 0; i13 < 5; i13++) {
    y += TT[i13] * e_b[i13];
  }

  dprdTr = rdivide(1.0, VV[0]) * (1.0 + ((((0.1181193 + (-0.15479 * TT[1] +
    -0.060646) / TT[3]) * VV[3] + (0.0236744 - 0.0 / TT[3]) * VV[2]) +
    1.55488E-5) - 0.085448 / TT[3] * VV[2] * ((0.65392 + 0.060167 / VV[1]) * exp
    (-0.060167 / VV[1]))) / VV[4]);
  C_v_pe0 = (2.0 * (-0.15479 + -0.090969 / TT[1]) / TT[2] / VV[0] + 0.0 / TT[3] /
             VV[1]) + 6.0 * (0.042724 / (2.0 * TT[3] * 0.060167) *
    (1.6539199999999998 - (1.6539199999999998 + 0.060167 / VV[1]) * exp
     (-0.060167 / VV[1])));
  Cp_pe0 = (1.0 + T_R * (dprdTr * dprdTr) / (-TT[1] / VV[1] * (1.0 + (((2.0 *
    d14 * VV[3] + 3.0 * d15 * VV[2]) + 6.0 * D) + 0.042724 / TT[3] * VV[2] *
    (1.96176 + (5.0 - 2.0 * (0.65392 + 0.060167 / VV[1])) * 0.060167 / VV[1]) *
    exp(-0.060167 / VV[1])) / VV[4]))) + C_v_pe0;
  dprdTr_h = 1.0 / VV_h[0] * (1.0 + ((((0.2026579 + (-0.027655 * TT[1] +
    -0.406976) / TT[3]) * VV_h[3] + (0.0313385 - 0.033802 / TT[3]) * VV_h[2]) +
    4.8736E-5) - 0.083154 / TT[3] * VV_h[2] * ((1.226 + 0.03754 / VV_h[1]) * exp
    (-0.03754 / VV_h[1]))) / VV_h[4]);
  C_v_peh = (2.0 * (-0.027655 + -0.610464 / TT[1]) / TT[2] / VV_h[0] + 0.050703 /
             TT[3] / VV_h[1]) + 6.0 * (0.041577 / (2.0 * TT[3] * 0.03754) *
    (2.226 - (2.226 + 0.03754 / VV_h[1]) * exp(-0.03754 / VV_h[1])));
  *Cp_v = y - 8.314 / MW * (Cp_pe0 + W / 0.3978 * (((1.0 + T_R * (dprdTr_h *
    dprdTr_h) / (-TT[1] / VV_h[1] * (1.0 + (((2.0 * d16 * VV_h[3] + 3.0 * d17 *
    VV_h[2]) + 6.0 * D_h) + 0.041577 / TT[3] * VV_h[2] * (3.678 + (5.0 - 2.0 *
    (1.226 + 0.03754 / VV_h[1])) * 0.03754 / VV_h[1]) * exp(-0.03754 / VV_h[1]))
    / VV_h[4]))) + C_v_peh) - Cp_pe0));

  /*  in kJ/kgK */
  *Cv_v = y - 8.314 / MW * (1.0 + (C_v_pe0 + W / 0.3978 * (C_v_peh - C_v_pe0)));

  /*  in kJ/kgK */
  /* % Calculate Thermal Conductivity */
  L = 23.9712 * rt_powd_snf(T_CR, 0.1667) * sqrt(MW) / rt_powd_snf(p_CR / 1000.0,
    0.6667);
  if (T_R < 1.0) {
    *lambda = 0.0004911 * T_R * *Cp_v * MW / L;
  } else {
    *lambda = 0.0001104 * rt_powd_snf(14.52 * T_R - 5.14, 0.6667) * *Cp_v * MW /
      L;
  }

  if (p > 345000.0) {
    p_R4 = rt_powd_snf(p_R, 4.0);

    /* p_r5 = p_r4*p_r; */
    T_r5 = TT[4] * T_R;
    T_r9 = T_r5 * TT[4];
    T_r16 = T_r9 * T_r5 * TT[2];
    C_v_p = 20.79 - 8.314 * (1.0 + C_v_pe0);
    expo = exp(-0.0617 * exp(1.91 / T_r9) * rt_powd_snf(p_R, 2.29 * exp(1.34 /
      T_r16)));

    /* noncyclic compound */
    *lambda *= (C_v_p * (1.0 + (4.18 + (0.537 * p_R * T_R * (1.0 - expo) + 0.51 *
      p_R * expo) * T_R) / TT[4]) + (*Cv_v * MW - C_v_p) * (1.0 + (p_R4 / (2.44 *
      (T_r16 * TT[4]) + p_R4) + 0.012 * p_R * TT[4]) / T_r5)) / (*Cv_v * MW);
  }

  *Cp_v *= 1000.0;
  *Cv_v *= 1000.0;
}

/* End of code generation (GetThermalPropertyHCVaporReal.cpp) */
