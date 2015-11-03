/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetAirViscosity.cpp
 *
 * Code generation for function 'GetAirViscosity'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirViscosity.h"

/* Function Definitions */
double GetAirViscosity(double rho, double T)
{
  double rho_r;
  double T_r;
  double TT[6];
  int i4;
  double rhor[4];
  int i;
  double d3;
  static const double b[6] = { 0.128517, -1.0, -0.709661, 0.662534, -0.197846,
    0.00770147 };

  double d4;
  static const double b_b[4] = { 0.465601, 1.26469, -0.511425, 0.2746 };

  /* The function calculates the air viscosity based on correlation */
  /* proposed by Kadoya.  */
  /*  Theory */
  /*    \mu\left(p,T\right) = H \left(\mu_0(T_r) + \Delta\mu(\rho_r)\right) */
  /*    \mu_0(T) = A_1 T + A_{0.5} T^{0.5} + \sum_{i=0}^{-4} A_i T_r^i */
  /*    \mu(\rho_r) = \sum_{i=1}^{4} B_i rho_r^i */
  /*    T_r = T/T_{ref}     \rho_r = rho/rho_{ref} */
  /*     */
  /*  Input */
  /*    rho : pressure in kg/m3 */
  /*    T : Temperature in K */
  /*  Output */
  /*    mu_a : viscosity of the air in Pa-s */
  /*  Validity : 300~2000K and upto 100MPa.  */
  /*  Ref */
  /*    Kadoya, K., N. Matsunaga, et al. (1985). "Viscosity and Thermal  */
  /*    Conductivity of Dry Air in the Gaseous Phase." J. Phys. Chem. Ref. Data 14(4). */
  /*  Created by Kevin Koosup Yum (NTNU) on 23 May, 2013 */
  rho_r = rho / 314.3;
  T_r = T / 132.5;

  /* Universal Gas constant J/(molK) */
  for (i4 = 0; i4 < 6; i4++) {
    TT[i4] = 0.0;
  }

  for (i4 = 0; i4 < 4; i4++) {
    rhor[i4] = 0.0;
  }

  TT[0] = T_r;
  rhor[0] = rho_r;
  for (i = 0; i < 3; i++) {
    TT[i + 1] = TT[i] / T_r;
    rhor[i + 1] = rhor[i] * rho_r;
  }

  TT[4] = TT[3] / T_r;
  d3 = 0.0;
  for (i4 = 0; i4 < 6; i4++) {
    d3 += TT[i4] * b[i4];
  }

  d4 = 0.0;
  for (i4 = 0; i4 < 4; i4++) {
    d4 += rhor[i4] * b_b[i4];
  }

  return 6.1609 * ((d3 + 2.60661 * sqrt(T_r)) + d4) / 1.0E+6;
}

/* End of code generation (GetAirViscosity.cpp) */
