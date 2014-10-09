/*
 * GetViscosityHCVapor.c
 *
 * Code generation for function 'GetViscosityHCVapor'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetViscosityHCVapor.h"
#include "GetCompCombGas_rtwutil.h"

/* Function Definitions */
real_T GetViscosityHCVapor(real_T p, real_T T, real_T p_CR, real_T T_CR, real_T
  V_CR, real_T Z_CR, real_T rho_R, real_T MW)
{
  real_T mu_v;
  real_T sigma;
  real_T T_term;
  real_T TT[7];
  int32_T i;
  static const real_T dv53[7] = { 0.91426362, -1.068936, 0.68077797, -0.21208677,
    0.034487186, -0.0028188225, 9.1590342E-5 };

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
    TT[1 + i] = TT[i] * T_term;
  }

  T_term = 0.0;
  for (i = 0; i < 7; i++) {
    T_term += dv53[i] * TT[i];
  }

  mu_v = 0.02669 * sqrt(MW * T) / (sigma * sigma * (1.0 / T_term));
  if (p / p_CR <= 0.6) {
  } else {
    mu_v += 1.0 / (0.2173 * rt_powd_snf(T_CR, 0.16666666666666666) / (sqrt(MW) *
      rt_powd_snf(p_CR / 1.0E+6, 0.66666666666666663))) * (0.108 * (exp(1.439 *
      rho_R) - exp(-1.11 * rt_powd_snf(rho_R, 1.858))));
  }

  mu_v /= 1.0E+6;
  return mu_v;
}

/* End of code generation (GetViscosityHCVapor.c) */
