/*
 * GetThdynCombGasZachV1.c
 *
 * Code generation for function 'GetThdynCombGasZachV1'
 *
 * C source code generated on: Wed Jan 07 22:45:23 2015
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThdynCombGasZachV1.h"

/* Function Definitions */
void GetThdynCombGasZachV1(real_T P, real_T T, real_T F, real_T fs, real_T *R,
  real_T *h, real_T *s, real_T *u, real_T *RF, real_T *RP, real_T *RT, real_T
  *uF, real_T *uP, real_T *uT, real_T *sF, real_T *sP, real_T *sT, real_T *Cp,
  real_T *Cv, real_T *K)
{
  real_T PP;
  real_T TT;
  real_T V;
  real_T VF;
  real_T EP2;
  real_T EP3;
  real_T EP4;
  real_T EP5;
  real_T PAT1;
  real_T y;
  real_T FC2;
  real_T FC2F;
  real_T b_y;
  real_T FC3;
  real_T FC3F;
  real_T c_y;
  real_T FC4;
  real_T FC4F;
  real_T FC5;
  real_T FC6;
  real_T FC6F;
  real_T FC6T;
  real_T FC7;
  real_T FC7P;
  real_T FC7T;
  real_T z;
  real_T FC8;
  real_T FC8F;
  real_T FC8T;
  real_T ZZT1;

  /* The routine calculates the thermodynamic property of the combustion gas */
  /* given pressure, temperature and the fuel air equivalent ratio. */
  /*  Input */
  /*    P : Pressure (Pa) */
  /*    T : Temperature (K) */
  /*    F : Fuel-air equivalent ratio */
  /*  Output */
  /*    R : Gas constant */
  /*    h :	Specific enthalpy */
  /*    s : Specific Entropy */
  /*    u : Specific internal energy */
  /*    RF : Partial derivative of R w.r.t. F */
  /*    RP : Partial derivative of R w.r.t. P */
  /*    RT : Partial derivative of R w.r.t. T */
  /*    uF : Partial derivative of u w.r.t. F */
  /*    uP : Partial derivative of u w.r.t. P */
  /*    uT : Partial derivative of u w.r.t. T */
  /*    sF : Partial derivative of s w.r.t. F */
  /*    sP : Partial derivative of s w.r.t. P */
  /*    sT : Partial derivative of s w.r.t. T */
  /*    CP : Specific heat at constant pressure */
  /*    CV : Specific heat at constant volume */
  /*    K  : Ratio of specific heats */
  /*  FC0 = 1.01972e-5; */
  PP = 1.01972E-5 * P;
  TT = 0.001 * T;
  V = (1.0 - F) / (1.0 + fs * F);
  VF = -(1.0 + fs * V) / (1.0 + fs * F);
  EP2 = 0.477182 + 0.185214 * V;
  EP3 = -0.287367 - 0.0694862 * V;
  EP4 = 0.0742561 + 0.0164041 * V;
  EP5 = -0.00916344 - 0.00204537 * V;
  PAT1 = (0.131438 - 0.383504 * V) + TT * (2.0 * EP2 + TT * (3.0 * EP3 + TT *
    (4.0 * EP4 + TT * (5.0 * EP5 + TT * 6.0 * (0.000439896 + 0.00010161 * V)))));
  y = 9.00711E-5 * V;
  FC2 = 0.000277105 - 9.00711E-5 * V;
  FC2F = -9.00711E-5 * VF;
  b_y = 9.8367E-5 * V;
  FC3 = 0.000642217 - 9.8367E-5 * V;
  FC3F = -9.8367E-5 * VF;
  c_y = 0.006131 * V;
  FC4 = 0.008868 - 0.006131 * V;
  FC4F = -0.006131 * VF;
  FC5 = TT * TT;
  FC6 = exp((0.008868 - c_y) / FC5) / TT;
  FC6F = FC4F * FC6 / FC5;
  FC6T = -FC6 / T * (1.0 + 2.0 * (0.008868 - c_y) / FC5);
  FC7 = PP / TT;
  FC7P = 1.01972E-5 / TT;
  FC7T = -FC7 / TT * 0.001;
  z = (0.008868 - c_y) / FC5;
  FC8 = 1.0 + FC4 / FC5;
  FC8F = FC4F / FC5;
  FC8T = -FC4 * 2.0E-6 * T / (FC5 * FC5);
  FC4F = FC7 * ((0.000642217 - b_y) - (0.000277105 - y) * FC6) + 1.0;

  /*  Verified */
  ZZT1 = FC7 * ((0.000277105 - y) * FC6 * ((1.0 + z) + 1.0) - (0.000642217 - b_y))
    / TT;
  EP3 = ((3.514956 - 0.005026 * V) + TT * ((0.131438 - 0.383504 * V) + TT * (EP2
           + TT * (EP3 + TT * (EP4 + TT * (EP5 + TT * (0.000439896 + 0.00010161 *
    V))))))) - ZZT1 * TT;
  FC4 = ((((3.5566 - 0.0659 * V) * log(T) + ((2.972979 + 0.55314 * V) + TT *
            ((0.0583837 - 0.485001 * V) + TT * ((0.871349 + 0.0698183 * V) + TT *
              ((-0.451556 - 0.0028772 * V) + TT * ((0.109164 - 0.000693663 * V)
    + TT * ((0.0129754 + 9.20231E-5 * V) + TT * (0.000608234 - 2.99679E-6 * V))))))))
          - (-0.805214 + V * (-0.400981 + V * (5.76989 + 0.060056 * V)))) - log
         (PP)) - FC7 * (0.000277105 - y) * FC6 * (1.0 + z);
  EP4 = 8314.7 * (F / 3.0 + 4.773384) / (9.344254 * F + 138.2266);
  EP2 = (2771.5666666666671 - 9.344254 * EP4) / (9.344254 * F + 138.2266);
  *R = EP4 * FC4F;
  *h = EP4 * T * EP3;
  *s = EP4 * FC4;
  *u = *h - *R * T;
  *RF = EP2 * FC4F + EP4 * (FC7 * ((FC3F - FC2F * FC6) - FC2 * FC6F));
  *RP = EP4 * (FC7P * (FC3 - FC2 * FC6));
  *RT = EP4 * (-FC7 * ((FC3 - FC2 * FC6) * 0.001 / TT + FC2 * FC6T));
  *uF = (EP2 * T * EP3 + EP4 * T * ((-0.005026 + TT * (-0.383504 + TT *
            (0.185214 + TT * (-0.0694862 + TT * (0.0164041 + TT * (-0.00204537 +
    TT * 0.00010161)))))) * VF - FC7 * ((((0.000277105 - y) * FC8F * FC6 - FC3F)
            + (0.000277105 - y) * ((1.0 + z) + 1.0) * FC6F) + FC2F * ((1.0 + z)
            + 1.0) * FC6) / TT * TT)) - *RF * T;
  *uP = EP4 * T * (-ZZT1 * TT / PP * 1.01972E-5) - *RP * T;
  *uT = (EP4 * (EP3 + T * ((PAT1 * 0.001 - ((FC7T * ((0.000277105 - y) * FC6 *
               ((1.0 + z) + 1.0) - (0.000642217 - b_y)) / TT + FC7 *
              ((0.000277105 - y) * FC6T * ((1.0 + z) + 1.0) + (0.000277105 - y) *
               FC6 * FC8T) / TT) - FC7 * ((0.000277105 - y) * FC6 * ((1.0 + z) +
    1.0) - (0.000642217 - b_y)) / (TT * TT) * 0.001) * TT) - ZZT1 * 0.001)) -
         *RT * T) - *R;
  *sF = EP2 * FC4 + EP4 * (((((-0.0659 * VF * log(T) + (0.55314 + TT *
    (-0.485001 + TT * (0.0698183 + TT * (-0.0028772 + TT * (-0.000693663 + TT *
                                    (9.20231E-5 - 2.99679E-6 * TT)))))) * VF) -
                              (-0.400981 + V * (11.53978 + 0.180168 * V)) * VF)
    - FC7 * FC2F * FC6 * (1.0 + z)) - FC7 * (0.000277105 - y) * FC6F * (1.0 + z))
    - FC7 * (0.000277105 - y) * FC6 * FC8F);
  *sP = EP4 * (-1.01972E-5 / PP - FC7P * (0.000277105 - y) * FC6 * (1.0 + z));
  *sT = EP4 * (((((3.5566 - 0.0659 * V) / T + ((0.0583837 - 0.485001 * V) + TT *
                   ((1.742698 + 0.1396366 * V) + TT * ((-1.354668 - 0.0086316 *
    V) + TT * ((0.436656 - 0.002774652 * V) + TT * ((0.064877 + 0.0004601155 * V)
    + TT * (0.003649404 - 1.798074E-5 * V)))))) * 0.001) - FC7T * (0.000277105 -
    y) * FC6 * (1.0 + z)) - FC7 * (0.000277105 - y) * FC6T * (1.0 + z)) - FC7 *
               (0.000277105 - y) * FC6 * FC8T);
  *Cp = EP4 * (EP3 + TT * (-FC7 / TT * (FC3 - 4.0 * (0.000277105 - y) * FC6 *
    (FC8 * FC8 + (0.008868 - c_y) / FC5)) + PAT1));
  *Cv = *uT + *uP * (*R / T + *RT) / (*R / P - *RP);
  *K = *Cp / *Cv;
}

/* End of code generation (GetThdynCombGasZachV1.c) */
