/*
 * GetHTCoeffHTX.c
 *
 * Code generation for function 'GetHTCoeffHTX'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetThdynCombGasZach.h"
#include "GetCompCombGas_rtwutil.h"
#include "GetHTCoeffHTX.h"

/* Function Definitions */
real_T GetHTCoeffHTX(real_T p, real_T m_dot, real_T T, real_T D, real_T A)
{
  real_T rho_a;
  real_T mu_a;
  real_T lambda;
  real_T unusedUb;
  real_T unusedUa;
  real_T d0;
  real_T unusedU9;
  real_T unusedU8;
  real_T unusedU7;
  real_T unusedU6;
  real_T unusedU5;
  real_T unusedU4;
  real_T unusedU3;
  real_T unusedU2;
  real_T unusedU1;
  real_T Re_D;
  real_T alpha;

  /*  Calculate the heat transfer coeff of convectivity for charge air cooler  */
  /*  exchanger */
  rho_a = GetAirDensity(p, T);
  mu_a = GetAirViscosity(rho_a, T);
  lambda = GetAirThermalConduct(rho_a, T);
  GetThdynCombGasZach(p, T, 0.0, &Re_D, &unusedU1, &unusedU2, &unusedU3,
                      &unusedU4, &unusedU5, &unusedU6, &unusedU7, &unusedU8,
                      &unusedU9, &d0, &unusedUa, &unusedUb);

  Re_D = m_dot / rho_a / A * D * rho_a / mu_a;
  rho_a = mu_a * d0 / lambda;

  alpha = (0.3 + 0.62 * sqrt(Re_D) * rt_powd_snf(rho_a, 0.333) / rt_powd_snf(1.0
           + rt_powd_snf(0.4 / rho_a, 0.666), 0.25) * rt_powd_snf(1.0 +
           rt_powd_snf(Re_D / 282000.0, 0.625), 0.8)) * lambda / D;

  return alpha;
}

/* End of code generation (GetHTCoeffHTX.c) */
