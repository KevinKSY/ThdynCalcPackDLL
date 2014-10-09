/*
 * GetAirViscosity.c
 *
 * Code generation for function 'GetAirViscosity'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirViscosity.h"

/* Function Definitions */
real_T GetAirViscosity(real_T rho, real_T T)
{
  real_T rho_r;
  real_T T_r;
  real_T TT[6];
  int32_T i;
  real_T rhor[4];
  static const real_T b[6] = { 0.128517, -1.0, -0.709661, 0.662534, -0.197846,
    0.00770147 };

  real_T y;
  static const real_T b_b[4] = { 0.465601, 1.26469, -0.511425, 0.2746 };

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
  for (i = 0; i < 6; i++) {
    TT[i] = 0.0;
  }

  for (i = 0; i < 4; i++) {
    rhor[i] = 0.0;
  }

  TT[0] = T_r;
  rhor[0] = rho_r;
  for (i = 0; i < 3; i++) {
    TT[1 + i] = TT[i] / T_r;
    rhor[1 + i] = rhor[i] * rho_r;
  }

  TT[4] = TT[3] / T_r;
  rho_r = 0.0;
  for (i = 0; i < 6; i++) {
    rho_r += TT[i] * b[i];
  }

  y = 0.0;
  for (i = 0; i < 4; i++) {
    y += rhor[i] * b_b[i];
  }

  return 6.1609 * ((rho_r + 2.60661 * sqrt(T_r)) + y) / 1.0E+6;
}

/* End of code generation (GetAirViscosity.c) */
