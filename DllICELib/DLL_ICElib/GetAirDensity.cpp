/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetAirDensity.cpp
 *
 * Code generation for function 'GetAirDensity'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
double GetAirDensity(double p, double T)
{
  double rho_a;
  double rho_ideal;
  double TT[6];
  int i;
  double rho_error;
  double rho;
  double tau;
  int j;
  double varargin_2;
  static const double a[6] = { -3.4600925E-8, -4.5776295E-7, -3.4932E-6,
    -3.9930515E-5, 4.4292095E-5, -4.5598149999999997E-7 };

  double d0;
  static const double b_a[4] = { 1.0518311175000001E-9, -2.3202380725E-9,
    1.8055242775E-9, 5.028921625E-10 };

  double varargin_1;
  double rho_new;

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
  for (j = 0; j < 5; j++) {
    TT[j + 1] = TT[j] * tau;
  }

  while (rho_error > 0.001) {
    varargin_2 = 0.0;
    for (i = 0; i < 6; i++) {
      varargin_2 += a[i] * TT[i];
    }

    d0 = 0.0;
    for (i = 0; i < 4; i++) {
      d0 += b_a[i] * TT[1 + i];
    }

    varargin_1 = 0.1 * rho;
    varargin_2 = rho + -(((rho_ideal / rho - 1.0) - varargin_2 * rho) - d0 *
                         (rho * rho)) / ((-rho_ideal / (rho * rho) - varargin_2)
      - 2.0 * d0 * rho);
    if ((varargin_1 >= varargin_2) || rtIsNaN(varargin_2)) {
      rho_new = varargin_1;
    } else {
      rho_new = varargin_2;
    }

    rho_error = fabs(rho_new - rho) / rho;
    rho = rho_new;
  }

  rho_a = rho * 28.97 / 1000.0;

  /* end */
  return rho_a;
}

/* End of code generation (GetAirDensity.cpp) */
