/*
 * GetEquilGrill.c
 *
 * Code generation for function 'GetEquilGrill'
 *
 * C source code generated on: Tue Jul 31 11:27:42 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetCompCombGas.h"
#include "GetPTx.h"
#include "GetROHRDyn.h"
#include "GetThermoDynProp.h"
#include "GetTxV.h"
#include "GetEquilGrill.h"
#include "sum.h"
#include "GetCompCombGas_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void GetEquilGrill(real_T P, real_T T, real_T F, const real_T Fc[5], const
                   real_T Ac[11], real_T x[12])
{
  real_T N_L_F;
  real_T r3;
  real_T N_c_o;
  real_T N_o_n;
  real_T N_h_o;
  real_T N_ar_o;
  real_T N_n_temp;
  real_T sq_p_o2;
  real_T dv0[7];
  real_T dv1[7];
  real_T dv2[7];
  int32_T i1;
  real_T Kp[7];
  int32_T i2;
  static const real_T A[49] = { -1.03358475, -0.713156555, -0.939654715,
    0.458365335, 0.04605626, 2.086272015, 0.242455215, 0.00041329901,
    0.0003554990101, 0.00052355955, -0.0003659311185, -0.0001643783885,
    -0.00181840082, -0.00106154604, -7.3200285E-8, -6.63844473E-8,
    -1.272921115E-7, 1.502251815E-7, 1.12232102E-7, 5.567935775E-7,
    4.395287975E-7, 7.7049255E-12, 5.33506445E-12, 9.07426575E-12,
    -2.40750645E-11, -1.985775365E-11, -6.87337801E-11, -7.12431331E-11,
    -3.44398075E-16, -1.70012546E-16, -2.6767772E-16, 1.428934585E-15,
    1.07961455E-15, 2.93063671E-15, 3.81434486E-15, -25880.18791, -29834.000625,
    -56595.749344, -4712.324615, -10991.394289, 28464.849555, 34150.798375,
    -0.06547535, -3.21461365, -1.71366569, -4.6494238, -1.72538045, -6.19918548,
    9.65967412 };

  real_T N_o_sol;
  real_T Ksq4;
  real_T Ksq5;
  real_T Ksq6;
  real_T Ksq7;
  real_T sq_p_h2_2;
  real_T sq_p_h2;
  real_T sq_p_n2;
  real_T b_Kp[12];

  /* Calculate the mole fraction of the exhaust gas given P,T,F, fuel and */
  /* air composition using Grill's Method with some modification for */
  /* user-defined gas composition */
  /*  */
  /* Chemical reaction considered */
  /*   x13(C_n H_m O_l N_k + N_L/F (O_2 + b1 N_2 + b2 Ar + b3 CO + b4 CO_2 +  */
  /*      b5 H_2O + b6 H_2 + b7 H + b8 O + b9 N + b10 OH + b11 NO)) */
  /*            => x1 H + x2 O + x3 N + x4 H2 + x5 OH + x6 x_CO + x7 NO +  */
  /*               x8 O2 + x9 H2O + x10 CO2 + x11 N2 + x12 Ar */
  /*  */
  /* Ref : Grill, M., A. Schmid, et al. (2007). Calculating the Properties of  */
  /*       User-Defined Working Fluids for Real Working-Process Simulations.  */
  /*       2007 World Congress. Detroit, Michigan, SAE International. */
  /*  Input */
  /*    P : Pressure in Pa */
  /*    T : Temperature in Kelvin */
  /*    F : air fuel equivalent ratio */
  /*    Fc : Fuel atomic composition in C, H, O, N  */
  /*         Fc(1) = C, Fc(2) = H, Fc(3) = O, Fc(4) = N */
  /*    Ac : no. of moles of N2, Ar, CO, CO2,  */
  /*         H2O, H2 as in the ratio of no. of moes of O2 */
  /*         Ac(1) = n_N2/n_O2,  Ac(2) = n_Ar/n_O2,  Ac(3) = n_CO/n_O2 */
  /*         Ac(4) = n_CO2/n_O2, Ac(5) = n_H2O/n_O2, Ac(6) = n_H2/n_O2 */
  /*         Ac(7) = n_H/n_O2,   Ac(8) = n_O/n_O2,   Ac(9) = n_N/n_O2 */
  /*         Ac(10) = n_OH/n_O2, Ac(11) = n_NO/n_O3 */
  /*  Output */
  /*    x : Composition of exhaust gas in mole fraction of the component */
  /*        x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;  x(5) = x_OH; */
  /*        x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;  x(9) = x_H2O; x(10) = x_CO2; */
  /*        x(11) = x_N2; x(12) = x_Ar */
  /*  */
  /*  */
  /*  Created by Kevin Koosup Yum on 22 June 2012 */
  P /= 100000.0;
  if (F == 0) {
        F = 1e-8;
      }
  N_L_F = ((Fc[1] - 2.0 * Fc[2]) + Fc[0] * 4.0) / ((((((2.0 * Ac[7] - 2.0 * Ac[5])
    - Ac[6]) - 2.0 * Ac[2]) + Ac[9]) + 2.0 * Ac[10]) + 4.0) / F;

  /* r0 in fortran code */
  /* No. of C, R3 in fortran */
  /* No. of H, R4 in fortran */
  r3 = 0.5 * Fc[2] + N_L_F * ((((((1.0 + 0.5 * Ac[2]) + Ac[3]) + Ac[4] / 2.0) +
    0.5 * Ac[7]) + 0.5 * Ac[9]) + 0.5 * Ac[10]);

  /* No. of O2, R in fortran */
  /* No of N2, R1 in fortran */
  /* No of Ar, R2 in fortran */
  N_c_o = (Fc[0] + N_L_F * (Ac[2] + Ac[3])) / (2.0 * r3);
  N_o_n = r3 / (0.5 * Fc[3] + N_L_F * ((Ac[0] + 0.5 * Ac[8]) + 0.5 * Ac[10]));
  N_h_o = (Fc[1] + 2.0 * N_L_F * (((Ac[4] + Ac[5]) + Ac[6] * 0.5) + Ac[9] * 0.5))
    / (2.0 * r3);
  N_ar_o = N_L_F * Ac[1] / (2.0 * r3);
  N_n_temp = 2.0 * Ac[0] / (sum(Ac) + 1.0) * P;
  sq_p_o2 = 0.0245 / rt_powd_snf(F, 2.0);

  /* Calculate Kp for dissociation using NASA 7 Polynomial Fit (1000~6000K) */
  /*  Input  */
  /*        T : Temperature(Kelvin) */
  /*  Output */
  /*    Kp_NASA7 (equilibrium constant for 7 reactions) */
  /*        1; 0.5H2 <-> H              2; 0.5O2 <-> O   */
  /*        3; 0.5O2 <-> O              4; 0.5H2 + 0.5O2 <-> OH */
  /*        5; 0.5N2 + 0.5O2 <-> NO     6; H2 + 0.5O2 <-> H2O */
  /*        7; CO + 0.5H2 <-> CO2 */
  /*  */
  /*  Created by Kevin Koosup Yum, 3 April 2012 */
  dv0[0] = 1.0;
  dv0[1] = T / 2.0;
  dv0[2] = rt_powd_snf(T, 2.0) / 3.0;
  dv0[3] = rt_powd_snf(T, 3.0) / 4.0;
  dv0[4] = rt_powd_snf(T, 4.0) / 5.0;
  dv0[5] = 1.0 / T;
  dv0[6] = 0.0;
  dv1[0] = log(T);
  dv1[1] = T;
  dv1[2] = rt_powd_snf(T, 2.0) / 2.0;
  dv1[3] = rt_powd_snf(T, 3.0) / 3.0;
  dv1[4] = rt_powd_snf(T, 4.0) / 4.0;
  dv1[5] = 0.0;
  dv1[6] = 1.0;
  for (i1 = 0; i1 < 7; i1++) {
    dv2[i1] = dv0[i1] - dv1[i1];
  }

  for (i1 = 0; i1 < 7; i1++) {
    Kp[i1] = 0.0;
    for (i2 = 0; i2 < 7; i2++) {
      Kp[i1] += A[i1 + 7 * i2] * dv2[i2];
    }

    Kp[i1] = exp(Kp[i1]);
  }

  N_L_F = 1.0;
  r3 = 0.0;
  N_o_sol = N_o_n * N_n_temp;
  while (N_L_F > 0.001) {
    N_n_temp += r3;
    N_o_sol = N_o_n * N_n_temp;
    N_L_F = 1.0;
    r3 = 0.0;
    while (N_L_F > 0.001) {
      sq_p_o2 += r3;
      Ksq4 = Kp[3] * sq_p_o2;
      Ksq5 = Kp[4] * sq_p_o2;
      Ksq6 = Kp[5] * sq_p_o2;
      Ksq7 = Kp[6] * sq_p_o2;
      N_L_F = 8.0 * N_h_o * N_o_sol;
      r3 = rt_powd_snf(N_L_F * (1.0 + Ksq6) + rt_powd_snf(Ksq4 + Kp[0], 2.0),
                       0.5);
      sq_p_h2_2 = 4.0 * (Ksq6 + 1.0);
      sq_p_h2 = -((Kp[0] + Ksq4) - r3) / sq_p_h2_2;
      N_L_F = Kp[5] * -sq_p_h2 / (sq_p_h2_2 / 4.0) - (Kp[3] - 0.5 * (2.0 * Kp[3]
        * (Kp[0] + Ksq4) + Kp[5] * N_L_F) / r3) / sq_p_h2_2;
      r3 = rt_powd_snf(rt_powd_snf(Ksq5 + Kp[2], 2.0) + 8.0 / N_o_n * N_o_sol,
                       0.5);
      sq_p_n2 = ((r3 - Ksq5) - Kp[2]) / 4.0;
      sq_p_h2_2 = N_c_o * N_o_sol;
      N_L_F = -((((((sq_p_h2_2 * (2.0 - 1.0 / (Ksq7 + 1.0)) + 2.0 * rt_powd_snf
                     (sq_p_o2, 2.0)) + Ksq6 * rt_powd_snf(sq_p_h2, 2.0)) + Ksq4 *
                   sq_p_h2) + Kp[1] * sq_p_o2) + Ksq5 * sq_p_n2) - N_o_sol) /
        ((((((((sq_p_h2_2 * Kp[6] / rt_powd_snf(Ksq7 + 1.0, 2.0) + 4.0 * sq_p_o2)
               + Kp[5] * rt_powd_snf(sq_p_h2, 2.0)) + Ksq6 * 2.0 * sq_p_h2 *
              N_L_F) + Kp[3] * sq_p_h2) + Ksq4 * N_L_F) + Kp[1]) + Kp[4] *
          sq_p_n2) + Ksq5 * (((Ksq5 + Kp[2]) * Kp[4] / r3 - Kp[4]) / 4.0));
      r3 = -0.9 * sq_p_o2;
      if ((N_L_F >= r3) || rtIsNaN(r3)) {
        r3 = N_L_F;
      }

      N_L_F = fabs(r3 / sq_p_o2);
    }

    Ksq4 = Kp[3] * sq_p_o2;
    Ksq5 = Kp[4] * sq_p_o2;
    Ksq6 = Kp[5] * sq_p_o2;
    sq_p_h2 = -((Kp[0] + Ksq4) - rt_powd_snf(8.0 * N_h_o * N_o_sol * (1.0 + Ksq6)
      + rt_powd_snf(Ksq4 + Kp[0], 2.0), 0.5)) / (4.0 * (Ksq6 + 1.0));
    sq_p_n2 = ((rt_powd_snf(rt_powd_snf(Ksq5 + Kp[2], 2.0) + 8.0 / N_o_n *
      N_o_sol, 0.5) - Ksq5) - Kp[2]) / 4.0;
    N_L_F = N_c_o * N_o_sol / (1.0 / (Kp[6] * sq_p_o2) + 1.0);
    r3 = rt_powd_snf(sq_p_h2, 2.0);
    r3 = (((((((((((P - N_L_F) - N_L_F / (Kp[6] * sq_p_o2)) - rt_powd_snf
                  (sq_p_o2, 2.0)) - Ksq6 * r3) - r3) - Ksq4 * sq_p_h2) - Kp[0] *
              sq_p_h2) - Kp[1] * sq_p_o2) - rt_powd_snf(sq_p_n2, 2.0)) - Kp[2] *
           sq_p_n2) - Ksq5 * sq_p_n2) - N_ar_o * N_o_sol;
    N_L_F = fabs(r3 / N_n_temp);
  }

  Ksq4 = Kp[3] * sq_p_o2;
  Ksq5 = Kp[4] * sq_p_o2;
  Ksq6 = Kp[5] * sq_p_o2;
  sq_p_h2 = -((Kp[0] + Ksq4) - rt_powd_snf(8.0 * N_h_o * N_o_sol * (1.0 + Ksq6)
    + rt_powd_snf(Ksq4 + Kp[0], 2.0), 0.5)) / (4.0 * (Ksq6 + 1.0));
  sq_p_n2 = ((rt_powd_snf(rt_powd_snf(Ksq5 + Kp[2], 2.0) + 8.0 / N_o_n * N_o_sol,
    0.5) - Ksq5) - Kp[2]) / 4.0;
  N_L_F = N_c_o * N_o_sol / (1.0 / (Kp[6] * sq_p_o2) + 1.0);
  r3 = rt_powd_snf(sq_p_h2, 2.0);
  b_Kp[0] = Kp[0] * sq_p_h2;
  b_Kp[1] = Kp[1] * sq_p_o2;
  b_Kp[2] = Kp[2] * sq_p_n2;
  b_Kp[3] = r3;
  b_Kp[4] = Ksq4 * sq_p_h2;
  b_Kp[5] = N_L_F / (Kp[6] * sq_p_o2);
  b_Kp[6] = Ksq5 * sq_p_n2;
  b_Kp[7] = rt_powd_snf(sq_p_o2, 2.0);
  b_Kp[8] = Ksq6 * r3;
  b_Kp[9] = N_L_F;
  b_Kp[10] = rt_powd_snf(sq_p_n2, 2.0);
  b_Kp[11] = N_ar_o * N_o_sol;
  for (i1 = 0; i1 < 12; i1++) {
    x[i1] = b_Kp[i1] / P;
  }
}

/* End of code generation (GetEquilGrill.c) */
