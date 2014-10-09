/*
 * GetAirThermalConduct.c
 *
 * Code generation for function 'GetAirThermalConduct'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirThermalConduct.h"

/* Function Definitions */
real_T GetAirThermalConduct(real_T rho, real_T T)
{
  real_T rho_r;
  real_T T_r;
  real_T TT[6];
  int32_T i;
  real_T rhor[5];
  static const real_T b[6] = { 0.239503, 1.0, -1.92615, 2.00383, -1.07553,
    0.229414 };

  real_T y;
  static const real_T b_b[5] = { 0.402287, 0.356603, -0.163159, 0.138059,
    -0.020172 };

  /* The function calculates the air thermal conductivity based on correlation */
  /* proposed by Kadoya.  */
  /*  Theory */
  /*    \lambda\left(T,\rho\right) = \Lambda \left(\lambda_0(T_r) + \Delta\lambda(\rho_r)\right) */
  /*    \lambda_0(T_r) = C_1 T + C_{0.5} T^{0.5} + \sum_{i=0}^{-4} C_i T_r^i */
  /*    \Delta\lambda(\rho_r) = \sum_{i=1}^{5} B_i rho_r^i */
  /*    T_r = T/T_{ref}     \rho_r = rho/rho_{ref} */
  /*     */
  /*  Input */
  /*    rho : pressure in kg/m3 */
  /*    T : Temperature in K */
  /*  Output */
  /*    lambda_a : thermal conductivity of the air in W/(mK) */
  /*  Validity : +-1% in high temperature (>370K) */
  /*  Ref */
  /*    Kadoya, K., N. Matsunaga, et al. (1985). "Viscosity and Thermal  */
  /*    Conductivity of Dry Air in the Gaseous Phase." J. Phys. Chem. Ref. Data 14(4). */
  /*  Created by Kevin Koosup Yum (NTNU) on 29 August, 2013 */
  rho_r = rho / 314.3;
  T_r = T / 132.5;
  for (i = 0; i < 6; i++) {
    TT[i] = 0.0;
  }

  for (i = 0; i < 5; i++) {
    rhor[i] = 0.0;
  }

  TT[0] = T_r;
  rhor[0] = rho_r;
  for (i = 0; i < 4; i++) {
    TT[1 + i] = TT[i] / T_r;
    rhor[1 + i] = rhor[i] * rho_r;
  }

  TT[5] = TT[4] / T_r;
  rho_r = 0.0;
  for (i = 0; i < 6; i++) {
    rho_r += TT[i] * b[i];
  }

  y = 0.0;
  for (i = 0; i < 5; i++) {
    y += rhor[i] * b_b[i];
  }

  return 0.0259778 * ((rho_r + 0.00649768 * sqrt(T_r)) + y);
}

/* End of code generation (GetAirThermalConduct.c) */
