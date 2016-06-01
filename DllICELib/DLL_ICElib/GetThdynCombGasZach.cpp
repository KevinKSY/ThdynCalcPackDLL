/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThdynCombGasZach.cpp
 *
 * Code generation for function 'GetThdynCombGasZach'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThdynCombGasZach.h"


/* Function Definitions */
void GetThdynCombGasZach(double P, double T, double F, double *R, double *h,
  double *s, double *u, double *RF, double *RP, double *RT, double *uF, double
  *uP, double *uT, double *Cp, double *Cv, double *K)
{
  double PP;
  double TT;
  double V;
  double EP1;
  double EP2;
  double EP3;
  double EP4;
  double EP5;
  double EP6;
  double FC2;
  double FC3;
  double FC4;
  double FC5;
  double FC6;
  double FC7;
  double z;
  double FC8;
  double ZZ;
  double ZZV;
  double ZZT;
  double ZZP;
  double HH;
  double HHT;
  double FC11;
  double FC21;
  double FC31;

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
  /*    uP : Partial derivative of U w.r.t. P */
  /*    uT : Partial derivative of U w.r.t. T */
  /*    CP : Specific heat at constant pressure */
  /*    CV : Specific heat at constant volume */
  /*    K  : Ratio of specific heats */
  PP = 1.01972E-5 * P;
  TT = 0.001 * T;
  V = (1.0 - F) / (1.0 + 0.0698 * F);
  EP1 = 0.131438 - 0.383504 * V;
  EP2 = 0.477182 + 0.185214 * V;
  EP3 = -0.287367 - 0.0694862 * V;
  EP4 = 0.0742561 + 0.0164041 * V;
  EP5 = -0.00916344 - 0.00204537 * V;
  EP6 = 0.000439896 + 0.00010161 * V;
  FC2 = 0.000277105 - 9.00711E-5 * V;
  FC3 = 0.000642217 - 9.8367E-5 * V;
  FC4 = 0.008868 - 0.006131 * V;
  FC5 = TT * TT;
  FC6 = exp(FC4 / FC5) / TT;
  FC7 = PP / TT;
  z = FC4 / FC5;
  FC8 = 1.0 + FC4 / FC5;
  ZZ = FC7 * (FC3 - FC2 * FC6) + 1.0;
  ZZV = FC7 * (9.8367E-5 - FC6 * (9.00711E-5 - 0.0006131 * FC2 / FC5));
  ZZT = FC7 * (FC2 * FC6 * ((1.0 + z) + 1.0) - FC3) / TT;
  ZZP = (FC3 - FC2 * FC6) / TT;
  HH = ((3.514956 - 0.005026 * V) + TT * (EP1 + TT * (EP2 + TT * (EP3 + TT *
           (EP4 + TT * (EP5 + TT * EP6)))))) - ZZT * TT;
  HHT = -FC7 / TT * (FC3 - 4.0 * FC2 * FC6 * ((1.0 + z) * (1.0 + z) + FC4 / FC5))
    + (EP1 + TT * (2.0 * EP2 + TT * (3.0 * EP3 + TT * (4.0 * EP4 + TT * (5.0 *
           EP5 + TT * 6.0 * EP6)))));
  FC11 = 8314.7 * (F / 3.0 + 4.773384) / (9.344254 * F + 138.2266);
  FC21 = -1.471965 * (F / 3.0 + 4.773384) / (9.344254 * F + 138.2266);
  FC31 = -1.0698 / ((1.0 + 0.0698 * F) * (1.0 + 698.0 * F));
  *R = FC11 * ZZ;
  *h = FC11 * T * HH;
  *s = FC11 * (((((3.5566 - 0.0659 * V) * log(T) + ((2.972979 + 0.55314 * V) +
    TT * ((0.0583837 - 0.485001 * V) + TT * ((0.871349 + 0.0698183 * V) + TT *
    ((-0.451556 - 0.0028772 * V) + TT * ((0.109164 - 0.000693663 * V) + TT *
    ((0.0129754 + 9.20231E-5 * V) + TT * (0.000608234 - 2.99679E-6 * V)))))))) -
                 (-0.805214 + V * (-0.400981 + V * (5.76989 + 0.060056 * V)))) -
                log(PP)) - FC7 * FC2 * FC6 * FC8);
  *u = *h - *R * T;
  *RF = FC11 * (ZZV * FC31 - ZZ * FC21);
  *RP = FC11 * ZZP * 1.02E-5;
  *RT = FC11 * ZZT * 0.001;
  *uF = FC11 * T * (((FC7 * (-9.8367E-5 - 2.0 * FC6 * (FC8 * (-9.00711E-5 -
    0.006131 * FC2 / FC5) - 0.006131 * FC2 / FC5)) + (-0.00506 + TT * (-0.383504
    + TT * (0.185214 + TT * (-0.0694862 + TT * (0.0164041 + TT * (-0.00204537 +
    TT * 0.00010161))))))) - ZZV) * FC31 - (HH - ZZ) * FC21);
  *uP = FC11 * T * (-ZZT * TT / PP - ZZP) * 1.02E-5;
  *uT = FC11 * ((HH - ZZ) + TT * (HHT - ZZT));
  *Cp = FC11 * (HH + TT * HHT);
  *Cv = *uT + *uP * (*R / T + *RT) / (*R / P - *RP);
  *K = *Cp / *Cv;
}

/* End of code generation (GetThdynCombGasZach.cpp) */
