/*
 * GetDensityHCVapor.c
 *
 * Code generation for function 'GetDensityHCVapor'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetDensityHCVapor.h"
#include "rdivide.h"

/* Function Definitions */
void GetDensityHCVapor(real_T p, real_T T, real_T p_CR, real_T T_CR, real_T MW,
  real_T W, real_T rho_v_data[1], int32_T rho_v_size[1])
{
  real_T p_R;
  real_T T_R;
  real_T v_R_ideal;
  real_T TT_data[4];
  int32_T ar;
  real_T z_data[4];
  real_T B_data_idx_0;
  int32_T ib;
  static const real_T B[4] = { 0.1181193, -0.265728, -0.15479, -0.030323 };

  real_T b_TT_data[3];
  real_T b_z_data[3];
  real_T C_data_idx_0;
  static const real_T b_B[3] = { 0.0236744, -0.0186984, 0.0 };

  real_T D;
  real_T B_h_data_idx_0;
  static const real_T c_B[4] = { 0.2026579, -0.331511, -0.027655, -0.203488 };

  real_T C_h_data_idx_0;
  static const real_T d_B[3] = { 0.0313385, -0.0503618, 0.016901 };

  real_T z;
  real_T D_h;
  real_T VV[6];
  real_T V_R_error;
  real_T V_R;
  real_T V_R_temp;
  real_T c43;
  real_T u0;

  /* The function calculates the density of hydrocarbon vapor.The calculation */
  /* is following the procedure 6B1.8 from API Technical Book of Petroleum */
  /* Refining */
  /*  Input */
  /*    p : Pressure of the gas in Pa */
  /*    T : Temperature of the gas in Kelvin */
  /*    p_CR : Critical pressure of the gas in Pa */
  /*    T_CR : Critical temperature of the gas on K */
  /*    MW : Molecular weight of the gas in kg/kmol */
  /*    W : Acentric factor of the gas */
  /*  Output */
  /*    rho_v : density of the gas in kg/m3 */
  /*  Comment */
  /*    Error is less than 1% in average. But near critical temperature, it may */
  /*    increase upto 30%. Due to iteration problem, this routine is only */
  /*    applicable from 1.0 for reduced temperature and pressure upto 20. */
  /*  Reference */
  /*    Technical Data Book :6B1.8 - Petroleum Refining(1985) Americal Petroleum Institute. */
  /*  Created by Kevin Koosup Yum, 27 August 2013 */
  /* Universal gas constant J/kmol-K */
  p_R = p / p_CR;
  T_R = T / T_CR;
  rho_v_size[0] = 1;
  v_R_ideal = rdivide(8314.0 * T, p) / (8314.0 * T_CR / p_CR);
  for (ar = 0; ar < 4; ar++) {
    TT_data[ar] = 0.0;
  }

  TT_data[0] = 1.0;
  for (ar = 0; ar < 3; ar++) {
    TT_data[ar + 1] = TT_data[ar] * T_R;
  }

  for (ar = 0; ar < 4; ar++) {
    z_data[ar] = 1.0 / TT_data[ar];
  }

  B_data_idx_0 = 0.0;
  ar = -1;
  for (ib = 0; ib + 1 < 5; ib++) {
    if (B[ib] != 0.0) {
      B_data_idx_0 += B[ib] * z_data[ar + 1];
    }

    ar++;
  }

  for (ar = 0; ar < 2; ar++) {
    b_TT_data[ar] = TT_data[ar];
  }

  b_TT_data[2] = TT_data[3];
  for (ar = 0; ar < 3; ar++) {
    b_z_data[ar] = 1.0 / b_TT_data[ar];
  }

  C_data_idx_0 = 0.0;
  ar = -1;
  for (ib = 0; ib + 1 < 4; ib++) {
    if (b_B[ib] != 0.0) {
      C_data_idx_0 += b_B[ib] * b_z_data[ar + 1];
    }

    ar++;
  }

  D = 1.55488E-5 + rdivide(6.23689E-5, T_R);
  for (ar = 0; ar < 4; ar++) {
    z_data[ar] = 1.0 / TT_data[ar];
  }

  B_h_data_idx_0 = 0.0;
  ar = -1;
  for (ib = 0; ib + 1 < 5; ib++) {
    if (c_B[ib] != 0.0) {
      B_h_data_idx_0 += c_B[ib] * z_data[ar + 1];
    }

    ar++;
  }

  for (ar = 0; ar < 2; ar++) {
    b_TT_data[ar] = TT_data[ar];
  }

  b_TT_data[2] = TT_data[3];
  for (ar = 0; ar < 3; ar++) {
    b_z_data[ar] = 1.0 / b_TT_data[ar];
  }

  C_h_data_idx_0 = 0.0;
  ar = -1;
  for (ib = 0; ib + 1 < 4; ib++) {
    if (d_B[ib] != 0.0) {
      C_h_data_idx_0 += d_B[ib] * b_z_data[ar + 1];
    }

    ar++;
  }

  z = 7.40336E-6 / T_R;
  D_h = 4.8736E-5 + 7.40336E-6 / T_R;
  for (ar = 0; ar < 6; ar++) {
    VV[ar] = 0.0;
  }

  /* Simple fluid calculation */
  V_R_error = 1.0;
  V_R = v_R_ideal * 0.8;
  while (V_R_error > 0.001) {
    VV[0] = V_R;
    for (ar = 0; ar < 5; ar++) {
      VV[1 + ar] = VV[ar] * V_R;
    }

    V_R_error = 0.042724 / TT_data[3] / VV[1];
    V_R_temp = 0.060167 / VV[1];
    c43 = exp(-0.060167 / VV[1]);
    u0 = 0.1 * V_R;
    V_R_error = V_R - (p_R / T_R * V_R - ((((1.0 + B_data_idx_0 / V_R) +
      C_data_idx_0 / VV[1]) + D / VV[4]) + V_R_error * (0.65392 + V_R_temp) *
      c43)) / (p_R / T_R - (((((-B_data_idx_0 / VV[1] - 2.0 * C_data_idx_0 / VV
      [2]) - 5.0 * D / VV[5]) + -0.085448 / TT_data[3] / VV[2] * (0.65392 +
      V_R_temp) * c43) + V_R_error * (-0.120334 / VV[2]) * c43) + V_R_error *
                (0.65392 + V_R_temp) * (0.120334 / VV[2] * c43)));
    if ((u0 >= V_R_error) || rtIsNaN(V_R_error)) {
      V_R_temp = u0;
    } else {
      V_R_temp = V_R_error;
    }

    V_R_error = fabs(V_R_temp - V_R) / V_R;
    V_R = V_R_temp;
  }

  B_data_idx_0 = p_R * V_R / T_R;

  /* Heavy Reference fluid calculation */
  V_R = v_R_ideal * 0.8;
  V_R_error = 1.0;
  while (V_R_error > 0.001) {
    VV[0] = V_R;
    for (ar = 0; ar < 5; ar++) {
      VV[1 + ar] = VV[ar] * V_R;
    }

    V_R_error = 0.041577 / TT_data[3] / VV[1];
    V_R_temp = 0.03754 / VV[1];
    c43 = exp(-0.03754 / VV[1]);
    u0 = 0.1 * V_R;
    V_R_error = V_R - (p_R / T_R * V_R - ((((1.0 + B_h_data_idx_0 / V_R) +
      C_h_data_idx_0 / VV[1]) + D_h / VV[4]) + V_R_error * (1.226 + V_R_temp) *
      c43)) / (p_R / T_R - (((((-B_h_data_idx_0 / VV[1] - 2.0 * C_h_data_idx_0 /
      VV[2]) - 5.0 * (4.8736E-5 + z) / VV[5]) + -0.083154 / TT_data[3] / VV[2] *
                  (1.226 + V_R_temp) * c43) + V_R_error * (-0.07508 / VV[2]) *
      c43) + V_R_error * (1.226 + V_R_temp) * (0.07508 / VV[2] * c43)));
    if ((u0 >= V_R_error) || rtIsNaN(V_R_error)) {
      V_R_temp = u0;
    } else {
      V_R_temp = V_R_error;
    }

    V_R_error = fabs(V_R_temp - V_R) / V_R;
    V_R = V_R_temp;
  }

  rho_v_data[0] = 1.0 / ((B_data_idx_0 + W / 0.3978 * (p_R * V_R / T_R -
    B_data_idx_0)) * 8314.0 * T / p) * MW;
}

/* End of code generation (GetDensityHCVapor.c) */
