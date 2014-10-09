/*
 * GetAirDensity.c
 *
 * Code generation for function 'GetAirDensity'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetCompCombGas_rtwutil.h"


/* Function Definitions */
real_T GetAirDensity(real_T p, real_T T)
{
  real_T rho_a;
  real_T rho_ideal;
  real_T TT[6];
  int32_T i;
  real_T rho_error;
  real_T rho;
  real_T tau;
  static const real_T dv0[6] = { -3.4600925E-8, -4.5776295E-7, -3.4932E-6,
    -3.9930515E-5, 4.4292095E-5, -4.5598149999999997E-7 };

  static const real_T dv1[4] = { 1.0518311175000001E-9, -2.3202380725E-9,
    1.8055242775E-9, 5.028921625E-10 };

  real_T u0;

  /* The function calculates the air density based on equation of state */
  /* proposed by Kadoya.  */
  /*  Input */
  /*    p : pressure in Pa */
  /*    T : Temperature in K */
  /*  Output */
  /*    rho_a : density of the air */
  /*  Validity : 300~2000K and upto 100MPa.  */
  /*  Ref */
  /*    Kadoya, K., N. Matsunaga, et al. (1985). "Viscosity and Thermal  */
  /*    Conductivity of Dry Air in the Gaseous Phase." J. Phys. Chem. Ref. Data 14(4). */
  /*  Created by Kevin Koosup Yum (NTNU) on 23 May, 2013 */
  /* Universal Gas constant J/(molK) */
  rho_ideal = p / T / 8.314;

  /*  (K) */
  /*  (10e-6m3/mol) */
  for (i = 0; i < 6; i++) {
    TT[i] = 0.0;
  }

  rho_error = 1.0;
  rho = rho_ideal;
  tau = T / 340.0;
  TT[0] = 1.0 / rt_powd_snf(tau, 4.0);
  for (i = 0; i < 5; i++) {
    TT[1 + i] = TT[i] * tau;
  }

  while (rho_error > 0.001) {
    tau = 0.0;
    for (i = 0; i < 6; i++) {
      tau += dv0[i] * TT[i];
    }

    rho_error = 0.0;
    for (i = 0; i < 4; i++) {
      rho_error += dv1[i] * TT[1 + i];
    }

    u0 = 0.1 * rho;
    tau = rho + -(((rho_ideal / rho - 1.0) - tau * rho) - rho_error * (rho * rho))
      / ((-rho_ideal / (rho * rho) - tau) - 2.0 * rho_error * rho);
    if ((u0 >= tau) || rtIsNaN(tau)) {
      tau = u0;
    }

    rho_error = fabs(tau - rho) / rho;
    rho = tau;
  }

  rho_a = rho * 28.97 / 1000.0;

  /* end */
  return rho_a;
}

/* End of code generation (GetAirDensity.c) */
