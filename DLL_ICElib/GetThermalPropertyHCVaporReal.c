/*
 * GetThermalPropertyHCVaporReal.c
 *
 * Code generation for function 'GetThermalPropertyHCVaporReal'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetViscosityHCVapor.h"
#include "rdivide.h"
#include "GetCompCombGas_rtwutil.h"

/* Function Definitions */
void GetThermalPropertyHCVaporReal(real_T p, real_T T, real_T MW, real_T T_CR,
  real_T p_CR, real_T W, real_T *rho_v, real_T *Cp_v, real_T *Cv_v, real_T
  *lambda)
{
  real_T p_R;
  real_T T_R;
  real_T v_R_ideal;
  real_T TT[5];
  int32_T i;
  real_T B;
  static const real_T b[4] = { 0.1181193, -0.265728, -0.15479, -0.030323 };

  real_T b_TT[3];
  real_T C;
  static const real_T b_b[3] = { 0.0236744, -0.0186984, 0.0 };

  real_T D;
  real_T B_h;
  static const real_T c_b[4] = { 0.2026579, -0.331511, -0.027655, -0.203488 };

  real_T C_h;
  static const real_T d_b[3] = { 0.0313385, -0.0503618, 0.016901 };

  real_T D_h;
  real_T VV[6];
  real_T VV_h[6];
  real_T V_R_error;
  real_T V_R;
  real_T c43;
  real_T C_v_pe0;
  real_T u0;
  real_T dprdTr;
  real_T z0;
  static const real_T e_b[5] = { -0.077548, 4.5022582138, -1.70019347497797,
    0.282256664878756, -0.0122278061244889 };

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
  for (i = 0; i < 5; i++) {
    TT[i] = 0.0;
  }

  TT[0] = 1.0;
  for (i = 0; i < 4; i++) {
    TT[1 + i] = TT[i] * T_R;
  }

  B = 0.0;
  for (i = 0; i < 4; i++) {
    B += 1.0 / TT[i] * b[i];
  }

  for (i = 0; i < 2; i++) {
    b_TT[i] = TT[i];
  }

  b_TT[2] = TT[3];
  C = 0.0;
  for (i = 0; i < 3; i++) {
    C += 1.0 / b_TT[i] * b_b[i];
  }

  D = 1.55488E-5 + rdivide(6.23689E-5, T_R);
  B_h = 0.0;
  for (i = 0; i < 4; i++) {
    B_h += 1.0 / TT[i] * c_b[i];
  }

  for (i = 0; i < 2; i++) {
    b_TT[i] = TT[i];
  }

  b_TT[2] = TT[3];
  C_h = 0.0;
  for (i = 0; i < 3; i++) {
    C_h += 1.0 / b_TT[i] * d_b[i];
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
    for (i = 0; i < 5; i++) {
      VV[1 + i] = VV[i] * V_R;
    }

    V_R_error = 0.042724 / TT[3] / VV[1];
    C_v_pe0 = 0.060167 / VV[1];
    c43 = exp(-0.060167 / VV[1]);
    u0 = 0.1 * V_R;
    dprdTr = V_R - (p_R / T_R * V_R - ((((1.0 + B / V_R) + C / VV[1]) + D / VV[4])
      + V_R_error * (0.65392 + C_v_pe0) * c43)) / (p_R / T_R - (((((-B / VV[1] -
      2.0 * C / VV[2]) - 5.0 * D / VV[5]) + -0.085448 / TT[3] / VV[2] * (0.65392
      + C_v_pe0) * c43) + V_R_error * (-0.120334 / VV[2]) * c43) + V_R_error *
      (0.65392 + C_v_pe0) * (0.120334 / VV[2] * c43)));
    if ((u0 >= dprdTr) || rtIsNaN(dprdTr)) {
      dprdTr = u0;
    }

    V_R_error = fabs(dprdTr - V_R) / V_R;
    V_R = dprdTr;
  }

  z0 = p_R * V_R / T_R;

  /* Heavy Reference fluid calculation */
  v_R_ideal *= 0.8;
  V_R_error = 1.0;
  while (V_R_error > 0.001) {
    VV_h[0] = v_R_ideal;
    for (i = 0; i < 5; i++) {
      VV_h[1 + i] = VV_h[i] * v_R_ideal;
    }

    dprdTr = 0.041577 / TT[3] / VV_h[1];
    C_v_pe0 = 0.03754 / VV_h[1];
    V_R = exp(-0.03754 / VV_h[1]);
    u0 = 0.1 * v_R_ideal;
    dprdTr = v_R_ideal - (p_R / T_R * v_R_ideal - ((((1.0 + B_h / v_R_ideal) +
      C_h / VV_h[1]) + D_h / VV_h[4]) + dprdTr * (1.226 + C_v_pe0) * V_R)) /
      (p_R / T_R - (((((-B_h / VV_h[1] - 2.0 * C_h / VV_h[2]) - 5.0 * D_h /
                       VV_h[5]) + -0.083154 / TT[3] / VV_h[2] * (1.226 + C_v_pe0)
                      * V_R) + dprdTr * (-0.07508 / VV_h[2]) * V_R) + dprdTr *
                    (1.226 + C_v_pe0) * (0.07508 / VV_h[2] * c43)));
    if ((u0 >= dprdTr) || rtIsNaN(dprdTr)) {
      dprdTr = u0;
    }

    V_R_error = fabs(dprdTr - v_R_ideal) / v_R_ideal;
    v_R_ideal = dprdTr;
  }

  *rho_v = 1.0 / ((z0 + W / 0.3978 * (p_R * v_R_ideal / T_R - z0)) * 8314.0 * T /
                  p) * MW;

  /* % Calculate the CP and Cv */
  v_R_ideal = 0.0;
  for (i = 0; i < 5; i++) {
    v_R_ideal += TT[i] * e_b[i];
  }

  dprdTr = rdivide(1.0, VV[0]) * (1.0 + ((((0.1181193 + (-0.15479 * TT[1] +
    -0.060646) / TT[3]) * VV[3] + (0.0236744 - 0.0 / TT[3]) * VV[2]) +
    1.55488E-5) - 0.085448 / TT[3] * VV[2] * ((0.65392 + 0.060167 / VV[1]) * exp
                                    (-0.060167 / VV[1]))) / VV[4]);
  C_v_pe0 = (2.0 * (-0.15479 + -0.090969 / TT[1]) / TT[2] / VV[0] + 0.0 / TT[3] /
             VV[1]) + 6.0 * (0.042724 / (2.0 * TT[3] * 0.060167) *
    (1.6539199999999998 - (1.6539199999999998 + 0.060167 / VV[1]) * exp
     (-0.060167 / VV[1])));
  dprdTr = (1.0 + T_R * (dprdTr * dprdTr) / (-TT[1] / VV[1] * (1.0 + (((2.0 * B *
    VV[3] + 3.0 * C * VV[2]) + 6.0 * D) + 0.042724 / TT[3] * VV[2] * (1.96176 +
                (5.0 - 2.0 * (0.65392 + 0.060167 / VV[1])) * 0.060167 / VV[1]) *
    exp(-0.060167 / VV[1])) / VV[4]))) + C_v_pe0;
  V_R_error = 1.0 / VV_h[0] * (1.0 + ((((0.2026579 + (-0.027655 * TT[1] +
    -0.406976) / TT[3]) * VV_h[3] + (0.0313385 - 0.033802 / TT[3]) * VV_h[2]) +
    4.8736E-5) - 0.083154 / TT[3] * VV_h[2] * ((1.226 + 0.03754 / VV_h[1]) * exp
                                 (-0.03754 / VV_h[1]))) / VV_h[4]);
  V_R = (2.0 * (-0.027655 + -0.610464 / TT[1]) / TT[2] / VV_h[0] + 0.050703 /
         TT[3] / VV_h[1]) + 6.0 * (0.041577 / (2.0 * TT[3] * 0.03754) * (2.226 -
                                    (2.226 + 0.03754 / VV_h[1]) * exp(-0.03754 /
    VV_h[1])));
  *Cp_v = v_R_ideal - 8.314 / MW * (dprdTr + W / 0.3978 * (((1.0 + T_R *
    (V_R_error * V_R_error) / (-TT[1] / VV_h[1] * (1.0 + (((2.0 * B_h * VV_h[3]
    + 3.0 * C_h * VV_h[2]) + 6.0 * D_h) + 0.041577 / TT[3] * VV_h[2] * (3.678 +
    (5.0 - 2.0 * (1.226 + 0.03754 / VV_h[1])) * 0.03754 / VV_h[1]) * exp
    (-0.03754 / VV_h[1])) / VV_h[4]))) + V_R) - dprdTr));

  /*  in kJ/kgK */
  *Cv_v = v_R_ideal - 8.314 / MW * (1.0 + (C_v_pe0 + W / 0.3978 * (V_R - C_v_pe0)));

  /*  in kJ/kgK */
  /* % Calculate Thermal Conductivity */
  dprdTr = 23.9712 * rt_powd_snf(T_CR, 0.1667) * sqrt(MW) / rt_powd_snf(p_CR /
    1000.0, 0.6667);
  if (T_R < 1.0) {
    *lambda = 0.0004911 * T_R * *Cp_v * MW / dprdTr;
  } else {
    *lambda = 0.0001104 * rt_powd_snf(14.52 * T_R - 5.14, 0.6667) * *Cp_v * MW /
      dprdTr;
  }

  if (p > 345000.0) {
    V_R_error = rt_powd_snf(p_R, 4.0);

    /* p_r5 = p_r4*p_r; */
    V_R = TT[4] * T_R;
    dprdTr = V_R * TT[4];
    v_R_ideal = dprdTr * V_R * TT[2];
    dprdTr = exp(-0.0617 * exp(1.91 / dprdTr) * rt_powd_snf(p_R, 2.29 * exp(1.34
      / v_R_ideal)));

    /* noncyclic compound */
    *lambda *= ((20.79 - 8.314 * (1.0 + C_v_pe0)) * (1.0 + (4.18 + (0.537 * p_R *
      T_R * (1.0 - dprdTr) + 0.51 * p_R * dprdTr) * T_R) / TT[4]) + (*Cv_v * MW
      - (20.79 - 8.314 * (1.0 + C_v_pe0))) * (1.0 + (V_R_error / (2.44 *
      (v_R_ideal * TT[4]) + V_R_error) + 0.012 * p_R * TT[4]) / V_R)) / (*Cv_v *
      MW);
  }

  *Cp_v *= 1000.0;
  *Cv_v *= 1000.0;
}

/* End of code generation (GetThermalPropertyHCVaporReal.c) */
