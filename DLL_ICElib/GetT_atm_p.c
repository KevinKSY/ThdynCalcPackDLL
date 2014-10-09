/*
 * GetT_atm_p.c
 *
 * Code generation for function 'GetT_atm_p'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"


/* Function Definitions */
real_T GetT_atm_p(real_T h, real_T F, real_T T_prev)
{
  real_T T;
  real_T dT;
  real_T T_err;
  real_T unusedUa;
  real_T unusedU9;
  real_T Cp;
  real_T unusedU8;
  real_T unusedU7;
  real_T unusedU6;
  real_T unusedU5;
  real_T unusedU4;
  real_T unusedU3;
  real_T unusedU2;
  real_T unusedU1;

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
    GetThdynCombGasZach(100000.0, T, F, &dT, &T_err, &unusedU1, &unusedU2,
                        &unusedU3, &unusedU4, &unusedU5, &unusedU6, &unusedU7,
                        &unusedU8, &Cp, &unusedU9, &unusedUa);
    dT = (T_err - h) / Cp;
    T_err = fabs(dT) / T;
  }

  return T;
}

/* End of code generation (GetT_atm_p.c) */
