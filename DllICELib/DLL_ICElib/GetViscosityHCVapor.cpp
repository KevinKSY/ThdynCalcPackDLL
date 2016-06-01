/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetViscosityHCVapor.cpp
 *
 * Code generation for function 'GetViscosityHCVapor'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetViscosityHCVapor.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
double GetViscosityHCVapor(double p, double T, double p_CR, double T_CR, double
  V_CR, double Z_CR, double rho_R, double MW)
{
  double mu_v;
  double sigma;
  double T_term;
  double TT[7];
  int i;
  double d19;
  static const double a[7] = { 0.91426362, -1.068936, 0.68077797, -0.21208677,
    0.034487186, -0.0028188225, 9.1590342E-5 };

  double mu_lp;

  /* The function calculates the viscosity of hydrocarbon vapor. This routine */
  /* follows the procedure 11B4.2 from API Technical Book of Petroleum Refining */
  /*  Input */
  /*    p : Pressure of the gas (Pa) */
  /*    T : Temperature of the gas (Kelvin) */
  /*    p_CR : Critical pressure of the gas in Pa */
  /*    T_CR : Critical temperature of the gas in Kelvin */
  /*    V_CR : Critical volume of the gas (m3/kg) */
  /*    Z_CR : Critical compressibility of the gas */
  /*    rho_R : Reduced density (rho/rho_CR) */
  /*    MW : Molecular weight of the gas (kg/kmol) */
  /*  Output */
  /*    mu_v : Viscosity of the gas in Pa-s */
  /*  Comment */
  /*    Error is 5.5% in average. If experimental densities are used, the error */
  /*    can be reduced to 0.5%. Only valid for all pressure  above the */
  /*    critical temperature. Below critical temperature, it may be applied up */
  /*    to the saturation pressure. */
  /*  Reference */
  /*    Technical Data Book - Petroleum Refining(1985) Americal Petroleum Institute. */
  /*  Created by Kevin Koosup Yum, 23 August 2013 */
  /*  Revision */
  /*    - 2 Sept 2013, Kevin Koosup Yum  */
  /*      Modified to have an output in Pa-s instead of microPa-s  */
  /* % Convert the input p, T array into a column vector */
  /* % */
  sigma = 0.01866 * rt_powd_snf(MW * (V_CR * 1000.0), 0.333) / rt_powd_snf(Z_CR,
    1.2);
  T_term = log(10.0 * (T / (65.3 * T_CR * rt_powd_snf(Z_CR, 3.6))));
  for (i = 0; i < 7; i++) {
    TT[i] = 0.0;
  }

  TT[0] = T_term;
  for (i = 0; i < 6; i++) {
    TT[i + 1] = TT[i] * T_term;
  }

  d19 = 0.0;
  for (i = 0; i < 7; i++) {
    d19 += a[i] * TT[i];
  }

  mu_lp = 0.02669 * sqrt(MW * T) / (sigma * sigma * (1.0 / d19));
  if (p / p_CR <= 0.6) {
    mu_v = mu_lp;
  } else {
    mu_v = mu_lp + 1.0 / (0.2173 * rt_powd_snf(T_CR, 0.16666666666666666) /
                          (sqrt(MW) * rt_powd_snf(p_CR / 1.0E+6,
      0.66666666666666663))) * (0.108 * (exp(1.439 * rho_R) - exp(-1.11 *
      rt_powd_snf(rho_R, 1.858))));
  }

  mu_v /= 1.0E+6;
  return mu_v;
}

/* End of code generation (GetViscosityHCVapor.cpp) */
