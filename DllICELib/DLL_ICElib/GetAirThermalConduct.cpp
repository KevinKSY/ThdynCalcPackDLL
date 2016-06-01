/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetAirThermalConduct.cpp
 *
 * Code generation for function 'GetAirThermalConduct'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirThermalConduct.h"

/* Function Definitions */
double GetAirThermalConduct(double rho, double T)
{
  double rho_r;
  double T_r;
  double TT[6];
  int i3;
  double rhor[5];
  int i;
  double d1;
  static const double b[6] = { 0.239503, 1.0, -1.92615, 2.00383, -1.07553,
    0.229414 };

  double d2;
  static const double b_b[5] = { 0.402287, 0.356603, -0.163159, 0.138059,
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
  for (i3 = 0; i3 < 6; i3++) {
    TT[i3] = 0.0;
  }

  for (i3 = 0; i3 < 5; i3++) {
    rhor[i3] = 0.0;
  }

  TT[0] = T_r;
  rhor[0] = rho_r;
  for (i = 0; i < 4; i++) {
    TT[i + 1] = TT[i] / T_r;
    rhor[i + 1] = rhor[i] * rho_r;
  }

  TT[5] = TT[4] / T_r;
  d1 = 0.0;
  for (i3 = 0; i3 < 6; i3++) {
    d1 += TT[i3] * b[i3];
  }

  d2 = 0.0;
  for (i3 = 0; i3 < 5; i3++) {
    d2 += rhor[i3] * b_b[i3];
  }

  return 0.0259778 * ((d1 + 0.00649768 * sqrt(T_r)) + d2);
}

/* End of code generation (GetAirThermalConduct.cpp) */
