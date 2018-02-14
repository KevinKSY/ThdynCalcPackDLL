/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetEquilOlikara.cpp
 *
 * Code generation for function 'GetEquilOlikara'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetCompCombGas.h"
#include "GetCorrAirComp.h"
#include "GetDensityHCVapor.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "GetEquilGrill.h"
#include "GetEquilOlikara.h"
#include "GetFuelPropertyN_Dodecane.h"
#include "GetHTCoeffHTX.h"
#include "GetIdealNozzleFlow.h"
#include "GetIdealNozzleFlowPTF.h"
#include "GetMEMbZach.h"
#include "GetPTF.h"
#include "GetPTFV1.h"
#include "GetPTx.h"
#include "GetTFromPhF.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"
#include "GetThdynCombGasZachV1.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetThermoDynPropPartial.h"
#include "GetTotalStaticPT.h"
#include "GetViscosityHCVapor.h"
#include "dNOx.h"
#include "mldivide.h"
#include "KpNASA7_upper.h"

/* Function Definitions */
void GetEquilOlikara(double P, double T, double F, const double Fc[4], const
                     double Ac[12], double x[12])
{
  double N_L_F;
  double r1;
  double r2;
  double r3;
  double r4;
  double r5;
  double D1;
  double D2;
  double D3;
  double D4;
  double P_sqrt;
  double Kp[7];
  double C1;
  double C2;
  double C3;
  double C5;
  double C7;
  double C9;
  double C10;
  double x13;
  double x8;
  double f_x8;
  double fun1;
  double fun2;
  double fun3;
  double fun4;
  double x8_sqrt;
  int j;
  boolean_T exitg2;
  double a;
  double b_a;
  double dx8;
  double x_temp[4];
  double x_err;
  int it;
  boolean_T exitg1;
  double x4_sqrt;
  double x11_sqrt;
  double y[4];
  int k;
  double varargin_2[4];
  double b_C1[16];
  double x_temp_new[4];
  double x1;
  double x2;
  double x3;
  double x5;
  double x7;
  double x9;
  double x10;

  /* Calculate the mole fraction of the exhaust gas given P,T,F, fuel and */
  /* air composition using Olikara's Method with some modification for */
  /* user-defined gas composition. */
  /* Ref : Olikara, C. and G. Borman (1975). "A Computer Program for  */
  /*       Calculating Properties of Equilibrium Combustion Products with  */
  /*       Some Applications to I.C. Engines." SAE Technical Paper 750468. */
  /*  */
  /* Chemical reaction considered */
  /*   x13(C_n H_m O_l N_k + N_L/F (O_2 + b1 N_2 + b2 Ar + b3 CO + b4 CO_2 +  */
  /*      b5 H_2O + b6 H_2 + b7 H + b8 O + b9 N + b10 OH + b11 NO)) */
  /*            => x1 H + x2 O + x3 N + x4 H2 + x5 OH + x6 x_CO + x7 NO +  */
  /*               x8 O2 + x9 H2O + x10 CO2 + x11 N2 + x12 Ar */
  /*  */
  /*  Input */
  /*    P : Pressure in bar */
  /*    T : Temperature in Kelvin */
  /*    F : air fuel equivalent ratio */
  /*    Fc : Fuel atomic composition in C, H, O, N  */
  /*         Fc(1) = C, Fc(2) = H, Fc(3) = O, Fc(4) = N */
  /*    Ac : Cylinder charge composition in no. of moles of N2, Ar, CO, CO2,  */
  /*         H2O, H2 as in the ratio of no. of moes of O2 */
  /*         Ac(1) = n_N2/n_O2,  Ac(2) = n_Ar/n_O2,  Ac(3) = n_CO/n_O2 */
  /*         Ac(4) = n_CO2/n_O2, Ac(5) = n_H2O/n_O2, Ac(6) = n_H2/n_O2 */
  /*         Ac(7) = n_H/n_O2,   Ac(8) = n_O/n_O2,   Ac(9) = n_N/n_O2 */
  /*         Ac(10) = n_OH/n_O2, Ac(11) = n_NO/n_O2 */
  /*  Output */
  /*    x : Composition of exhaust gas in mole fraction of the component */
  /*        x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;  x(5) = x_OH; */
  /*        x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;  x(9) = x_H2O; x(10) = x_CO2; */
  /*        x(11) = x_N2; x(12) = x_Ar */
  /*   */
  /*  A global variable "comb" should be defined before calling the function */
  /*  Assing comb = 0 at the start and end of the combustion and comb = 1  */
  /*  during the combustion */
  /*  */
  /*  Created by Kevin Koosup Yum on 22 June 2012 */
  /* % Calculate the molecular balance */
  N_L_F = ((Fc[1] - 2.0 * Fc[2]) + Fc[0] * 4.0) / ((((((2.0 * Ac[7] - 2.0 * Ac[5])
    - Ac[6]) - 2.0 * Ac[2]) + Ac[9]) + 2.0 * Ac[10]) + 4.0) / F;

  /* r0 in fortran code */
  r1 = Fc[0] + N_L_F * (Ac[2] + Ac[3]);

  /* No. of C, R3 in fortran */
  r2 = Fc[1] + 2.0 * N_L_F * (((Ac[4] + Ac[5]) + Ac[6] * 0.5) + Ac[9] * 0.5);

  /* No. of H, R4 in fortran */
  r3 = 0.5 * Fc[2] + N_L_F * ((((((1.0 + 0.5 * Ac[2]) + Ac[3]) + Ac[4] / 2.0) +
    0.5 * Ac[7]) + 0.5 * Ac[9]) + 0.5 * Ac[10]);

  /* No. of O2, R in fortran */
  r4 = 0.5 * Fc[3] + N_L_F * ((Ac[0] + 0.5 * Ac[8]) + 0.5 * Ac[10]);

  /* No of N2, R1 in fortran */
  r5 = N_L_F * Ac[1];

  /* No of Ar, R2 in fortran */
  D1 = r2 / r1;
  D2 = 2.0 * r3 / r1;
  D3 = 2.0 * r4 / r1;
  D4 = r5 / r1;
  P_sqrt = sqrt(P / 101325.0);

  /* % Calculate the equilibrium constant */
  KpNASA7_upper(T, Kp);
  C1 = Kp[0] / P_sqrt;
  C2 = Kp[1] / P_sqrt;
  C3 = Kp[2] / P_sqrt;
  C5 = Kp[3];
  C7 = Kp[4];
  C9 = Kp[5] * P_sqrt;
  C10 = Kp[6] * P_sqrt;

  /* % Calculate the initial point */
  if (F <= 1.0) {
    x13 = 1.0 / (((r2 / 4.0 + r3) + r4) + r5);
  } else {
    x13 = 1.0 / (((r1 + r2 / 2.0) + r4) + r5);
  }

  x8 = 10.0;
  f_x8 = 1.0;
  fun1 = 2.0 * C10 * r1;
  fun2 = C9 * r2 / 2.0;
  fun3 = 2.0 / x13;
  fun4 = 2.0 * r3;
  while (f_x8 > 0.0) {
    x8 *= 0.1;
    x8_sqrt = sqrt(x8);
    f_x8 = (((r1 + fun1 * x8_sqrt) / (1.0 + C10 * x8_sqrt) + fun2 * x8_sqrt /
             (1.0 + C9 * x8_sqrt)) + fun3 * x8) - fun4;
  }

  if (f_x8 < 0.0) {
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 20)) {
      x8_sqrt = sqrt(x8);
      a = 2.0 * C9 * x8_sqrt + 2.0;
      b_a = C10 * x8_sqrt + 1.0;
      dx8 = ((((r1 + 2.0 * C10 * r1 * x8_sqrt) / (1.0 + C10 * x8_sqrt) + C9 * r2
               * x8_sqrt / (2.0 * (1.0 + C9 * x8_sqrt))) + 2.0 * x8 / x13) - 2.0
             * r3) / ((((2.0 / x13 - C9 * C9 * r2 / (a * a)) + C10 * r1 /
                        (x8_sqrt * (C10 * x8_sqrt + 1.0))) + C9 * r2 / (2.0 *
        x8_sqrt * (2.0 * C9 * x8_sqrt + 2.0))) - C10 * (r1 + 2.0 * C10 * r1 *
        x8_sqrt) / (2.0 * x8_sqrt * (b_a * b_a)));
      if (dx8 > x8) {
        x8 *= 0.1;
      } else {
        x8 -= dx8;
      }

      if (fabs(dx8 / x8) < 0.01) {
        exitg2 = true;
      } else {
        j++;
      }
    }
  } else {
    x8_sqrt = sqrt(x8);
  }

  x_temp[0] = r2 * x13 / (2.0 * (1.0 + C9 * x8_sqrt));
  x_temp[1] = r1 * x13 / (1.0 + C10 * x8_sqrt);
  x_temp[2] = x8;
  x_temp[3] = r4 * x13;

  /* % Calculate the equilibrium mole fraction */
  x_err = 1.0;
  it = 0;
  exitg1 = false;
  while ((!exitg1) && (x_err > 0.001)) {
    it++;
    x4_sqrt = sqrt(x_temp[0]);
    x8_sqrt = sqrt(x_temp[2]);
    x11_sqrt = sqrt(x_temp[3]);
    for (k = 0; k < 4; k++) {
      y[k] = 0.01 * x_temp[k];
    }

    varargin_2[0] = ((((C1 * x4_sqrt + 2.0 * x_temp[0]) + C5 * x4_sqrt * x8_sqrt)
                      + 2.0 * C9 * x_temp[0] * x8_sqrt) - D1 * x_temp[1]) - D1 *
      C10 * x_temp[1] * x8_sqrt;
    varargin_2[1] = (((((C2 * x8_sqrt + C5 * x4_sqrt * x8_sqrt) + C9 * x_temp[0]
                        * x8_sqrt) + (1.0 - D2) * x_temp[1]) + (2.0 - D2) * C10 *
                      x_temp[1] * x8_sqrt) + 2.0 * x_temp[2]) + C7 * x8_sqrt *
      x11_sqrt;
    varargin_2[2] = (((-D3 * x_temp[1] - D3 * C10 * x_temp[1] * x8_sqrt) + C7 *
                      x8_sqrt * x11_sqrt) + C3 * x11_sqrt) + 2.0 * x_temp[3];
    varargin_2[3] = ((((((((((x_temp[0] + C9 * x_temp[0] * x8_sqrt) + C1 *
      x4_sqrt) + C5 * x4_sqrt * x8_sqrt) + (1.0 + D4) * x_temp[1]) + C2 *
                          x8_sqrt) + C10 * (1.0 + D4) * x_temp[1] * x8_sqrt) +
                        x_temp[2]) + C7 * x8_sqrt * x11_sqrt) + x_temp[3]) + C3 *
                     x11_sqrt) - 1.0;
    b_C1[0] = ((C1 / (2.0 * x4_sqrt) + 2.0 * C9 * x8_sqrt) + C5 * x8_sqrt / (2.0
                * x4_sqrt)) + 2.0;
    b_C1[4] = -D1 - C10 * D1 * x8_sqrt;
    b_C1[8] = (C5 * x4_sqrt / (2.0 * x8_sqrt) + C9 * x_temp[0] / x8_sqrt) - C10 *
      D1 * x_temp[1] / (2.0 * x8_sqrt);
    b_C1[12] = 0.0;
    b_C1[1] = C9 * x8_sqrt + C5 * x8_sqrt / (2.0 * x4_sqrt);
    b_C1[5] = (x8_sqrt * C10 * (2.0 - D2) - D2) + 1.0;
    b_C1[9] = ((((C2 + C5 * x4_sqrt) + C7 * x11_sqrt) + x_temp[1] * C10 * (2.0 -
      D2)) + C9 * x_temp[0]) / (2.0 * x8_sqrt) + 2.0;
    b_C1[13] = C7 * x8_sqrt / (2.0 * x11_sqrt);
    b_C1[2] = 0.0;
    b_C1[6] = -D3 - C10 * D3 * x8_sqrt;
    b_C1[10] = (C7 * x11_sqrt - C10 * D3 * x_temp[1]) / (2.0 * x8_sqrt);
    b_C1[14] = (C3 + C7 * x8_sqrt) / (2.0 * x11_sqrt) + 2.0;
    b_C1[3] = ((C1 + C5 * x8_sqrt) / (2.0 * x4_sqrt) + C9 * x8_sqrt) + 1.0;
    b_C1[7] = (D4 + C10 * x8_sqrt * (D4 + 1.0)) + 1.0;
    b_C1[11] = ((((C5 * x4_sqrt + C7 * x11_sqrt) + C9 * x_temp[0]) + C10 *
                 x_temp[1] * (D4 + 1.0)) + C2) / (2.0 * x8_sqrt) + 1.0;
    b_C1[15] = (C3 + C7 * x8_sqrt) / (2.0 * x11_sqrt) + 1.0;
    mldivide(b_C1, varargin_2);
    for (k = 0; k < 4; k++) {
      a = x_temp[k] - varargin_2[k];
      if ((y[k] >= a) || rtIsNaN(a)) {
        b_a = y[k];
      } else {
        b_a = a;
      }

      x_temp[k] = (x_temp[k] - b_a) / x_temp[k];
      varargin_2[k] = a;
      x_temp_new[k] = b_a;
    }

    for (k = 0; k < 4; k++) {
      y[k] = fabs(x_temp[k]);
    }

    x_err = y[0];
    for (k = 0; k < 3; k++) {
      x_err += y[k + 1];
    }

    for (k = 0; k < 4; k++) {
      x_temp[k] = x_temp_new[k];
    }

    if (it >= 1000) {
      exitg1 = true;
    }
  }

  x1 = C1 * sqrt(x_temp[0]);
  x2 = C2 * sqrt(x_temp[2]);
  x3 = C3 * sqrt(x_temp[3]);
  x5 = Kp[3] * sqrt(x_temp[0]) * sqrt(x_temp[2]);
  x7 = Kp[4] * sqrt(x_temp[2]) * sqrt(x_temp[3]);
  x9 = C9 * x_temp[0] * sqrt(x_temp[2]);
  x10 = C10 * x_temp[1] * sqrt(x_temp[2]);
  a = x_temp[0];
  for (k = 0; k < 3; k++) {
    a += x_temp[k + 1];
  }

  x[0] = x1;
  x[1] = x2;
  x[2] = x3;
  x[3] = x_temp[0];
  x[4] = x5;
  x[5] = x_temp[1];
  x[6] = x7;
  x[7] = x_temp[2];
  x[8] = x9;
  x[9] = x10;
  x[10] = x_temp[3];
  x[11] = 1.0 - (((((((x1 + x2) + x3) + x5) + x7) + x9) + x10) + a);
}

/* End of code generation (GetEquilOlikara.cpp) */
