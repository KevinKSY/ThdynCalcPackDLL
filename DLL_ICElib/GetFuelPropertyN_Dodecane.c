/*
 * GetFuelPropertyN_Dodecane.c
 *
 * Code generation for function 'GetFuelPropertyN_Dodecane'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetFuelPropertyN_Dodecane.h"
#include "GetCompCombGas_rtwutil.h"

/* Function Definitions */
void GetFuelPropertyN_Dodecane(real_T p, real_T T, real_T *p_v, real_T *rho_l,
  real_T *h_l, real_T *Cp_l, real_T *h_fg, real_T *mu_l, real_T *lambda_l,
  real_T *sigma_l)
{
  real_T T_R[8];
  int32_T i;
  real_T p_R[4];
  real_T TT[4];
  real_T Dvisc;
  static const real_T dv6[4] = { 14.50170196, -14.9159925, -8.86263462,
    0.414336894 };

  real_T dv7[5];
  real_T y[4];
  int32_T i4;
  static const real_T a[20] = { 1105.3, -1329.8, 1663.7, -1069.7, -31.164,
    147.71, -246.21, 169.74, 1.4274, -5.4041, 8.6951, -7.685, -0.0052975,
    -0.055594, 0.099981, 0.064605, -0.00046749, 0.0035522, -0.0058678, 0.0014729
  };

  real_T T_RB;
  real_T T_RB2;
  real_T T_RB3;
  static const real_T dv8[4] = { 3331.5840000000003, -6193.63, 9064.86,
    -3179.248 };

  real_T b_TT[8];
  static const real_T dv9[8] = { 2.140406765E+7, -2.394932736E+8, 1.154699081E+9,
    -3.051087445E+9, 4.767135466E+9, -4.406307056E+9, 2.232100727E+9,
    -4.784187787E+8 };

  real_T c_TT[6];
  static const real_T dv10[6] = { 3.21248, -0.0381521, 0.000240018, -8.33717E-7,
    1.4875E-9, -1.05978E-12 };

  /* The function calculates the thermodynamic and transportation property of */
  /* the liquid n-dodecane fuel */
  /*    input */
  /*        p : Pressure of the liquid fuel in Pa */
  /*        T : Liquid fuel temperature in Kelvin  */
  /*    Output */
  /*        p_v : vapor pressure of the liquid in Pa  */
  /*        rho_l : density of the fuel in kg/m3 */
  /*        h_l : specific enthalpy of the fuel in J/kg (0 at 0K) */
  /*        Cp_l : isobaric specific heat capacity in J/kg/K */
  /*        h_fg : specific latent heat of vaporization in J/kg */
  /*        mu_l : dynamic viscosity in Ns/m2 */
  /*        lambda_l : Thermal conductivity in W/m/K */
  /*        sigma_l : Surface tension in N/m */
  /*  */
  /*    Created by Kevin Koosup Yum (NTNU) on 22 August */
  /*  */
  /*  Ref */
  /*    Kouremenos, D. A., C. D. Rakopoulos, et al. (1990). "A FORTRAN program  */
  /*    for calculating the thermodynamic and transport properties of diesel  */
  /*    fuel." Advances in Engineering Software (1978) 12(4): 190-196. */
  /* % Constants for the fuel N-dodecane */
  /* Boiling temperature at 1 atm in K */
  /* Critical temperature in K */
  /* Critical pressure in Pa */
  /* Accentric factor */
  /* % Calculation of reduced temperature and pressure */
  memset(&T_R[0], 0, sizeof(real_T) << 3);
  T_R[0] = T / 658.1;
  for (i = 0; i < 6; i++) {
    T_R[1 + i] = T_R[i] * T_R[0];
  }

  T_R[7] = log(T_R[0]);
  for (i = 0; i < 4; i++) {
    p_R[i] = 0.0;
  }

  p_R[0] = p / 1.817E+6;
  for (i = 0; i < 3; i++) {
    p_R[1 + i] = p_R[i] * p_R[0];
  }

  /* % Calculation of vapor pressure */
  TT[0] = 1.0;
  TT[1] = 1.0 / T_R[0];
  TT[2] = T_R[7];
  TT[3] = T_R[5];
  Dvisc = 0.0;
  for (i = 0; i < 4; i++) {
    Dvisc += dv6[i] * TT[i];
  }

  *p_v = exp(Dvisc) * 1.817E+6;

  /* % Calculation of liquid density */
  TT[0] = 1.0;
  for (i = 0; i < 3; i++) {
    TT[i + 1] = T_R[i];
  }

  dv7[0] = 1.0;
  for (i = 0; i < 4; i++) {
    dv7[i + 1] = p_R[i];
  }

  *rho_l = 0.0;
  for (i = 0; i < 4; i++) {
    y[i] = 0.0;
    for (i4 = 0; i4 < 5; i4++) {
      y[i] += a[i + (i4 << 2)] * dv7[i4];
    }

    *rho_l += y[i] * TT[i];
  }

  /* % Liquid specific enthalpy */
  T_RB = T / 489.43;
  T_RB2 = T_RB * T_RB;
  T_RB3 = T_RB2 * T_RB;
  TT[0] = 1.0;
  TT[1] = T_RB / 2.0;
  TT[2] = T_RB2 / 3.0;
  TT[3] = T_RB3 / 4.0;
  Dvisc = 0.0;
  for (i = 0; i < 4; i++) {
    Dvisc += dv8[i] * TT[i];
  }

  *h_l = Dvisc * T;

  /* % Liquid specific isobaric heat capacity */
  TT[0] = 1.0;
  TT[1] = T_RB;
  TT[2] = T_RB2;
  TT[3] = T_RB3;
  *Cp_l = 0.0;
  for (i = 0; i < 4; i++) {
    *Cp_l += dv8[i] * TT[i];
  }

  /* % Latent heat of vaporization */
  if (T_R[0] <= 0.4) {
    *h_fg = 52138.6 * rt_powd_snf(658.1 - T, 0.38);
  } else {
    b_TT[0] = 1.0;
    for (i = 0; i < 7; i++) {
      b_TT[i + 1] = T_R[i];
    }

    *h_fg = 0.0;
    for (i = 0; i < 8; i++) {
      *h_fg += dv9[i] * b_TT[i];
    }
  }

  /* % Liquid absolute viscosity */
  if (T < 493.57500000000005) {
    T_RB = (T - 273.15) * 9.0 / 5.0 + 32.0;
  } else {
    T_RB = 428.76500000000016;
  }

  c_TT[0] = 1.0;
  c_TT[1] = T_RB;
  c_TT[2] = T_RB * T_RB;
  c_TT[3] = rt_powd_snf(T_RB, 3.0);
  c_TT[4] = rt_powd_snf(T_RB, 4.0);
  c_TT[5] = rt_powd_snf(T_RB, 5.0);
  Dvisc = 0.0;
  for (i = 0; i < 6; i++) {
    Dvisc += dv10[i] * c_TT[i];
  }

  *mu_l = Dvisc * exp(p / 6894.757 * (0.0239 + 0.01638 * rt_powd_snf(Dvisc,
    0.278)) / 1000.0) / 1000.0;

  /* % Liquid thermal conductivity */
  if (p_R[0] <= 1.894) {
    *lambda_l = 1.729578 * (0.07727 - 4.558E-5 * T_RB);
  } else {
    *lambda_l = 1.729578 * (0.07727 - 4.558E-5 * T_RB) * (((17.77 + 0.65 * p_R[0])
      - 7.764 * T_R[0]) - 2.054 * T_R[1] / exp(p_R[0] * 0.2)) / ((18.42 - 7.764 *
      T_R[0]) - 1.681673 * T_R[1]);
  }

  /* % Liquid surface tension */
  if (T_R[0] <= 0.99) {
    *sigma_l = 0.0528806 * rt_powd_snf(1.0 - T_R[0], 1.232);
  } else {
    *sigma_l = 1.0E-5;
  }
}

/* End of code generation (GetFuelPropertyN_Dodecane.c) */
