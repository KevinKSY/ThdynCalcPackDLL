/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetT_atm_p.cpp
 *
 * Code generation for function 'GetT_atm_p'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"

/* Function Definitions */
double GetT_atm_p(double h, double F, double T_prev)
{
  double T;
  double dT;
  double T_err;
  double unusedUa;
  double unusedU9;
  double Cp;
  double unusedU8;
  double unusedU7;
  double unusedU6;
  double unusedU5;
  double unusedU4;
  double unusedU3;
  double unusedU2;
  double unusedU1;
  double h_temp;
  double unusedU0;

  /* Calculate the temperature from given enthalpy, F for atmospheric pressure */
  /*  */
  /*    The calculation of the internal energy is based on the NASA 7 */
  /*    coefficient polynomial and T is found by using Newton-Raphson method. */
  /*    The gas is assumed to be idea gas. */
  /*  */
  /*    Input */
  /*  */
  /*    Output */
  /*        T : Temperature (K) */
  /*  */
  /*  Created by Kevin Koosup Yum on 14 March 2014 */
  /* % Check for valid inputs */
  /* % Calculate the temperature */
  T = T_prev;
  dT = 0.0;
  T_err = 1.0;
  while (T_err > 0.0001) {
    T -= dT;
    GetThdynCombGasZach(100000.0, T, F, &unusedU0, &h_temp, &unusedU1, &unusedU2,
                        &unusedU3, &unusedU4, &unusedU5, &unusedU6, &unusedU7,
                        &unusedU8, &Cp, &unusedU9, &unusedUa);
    dT = (h_temp - h) / Cp;
    T_err = fabs(dT) / T;
  }

  return T;
}

/* End of code generation (GetT_atm_p.cpp) */
