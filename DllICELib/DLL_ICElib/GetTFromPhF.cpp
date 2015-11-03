/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetTFromPhF.cpp
 *
 * Code generation for function 'GetTFromPhF'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetTFromPhF.h"
#include "GetThdynCombGasZachV1.h"

/* Function Definitions */
double GetTFromPhF(double p, double h, double F, double fs)
{
  double T;
  double dT;
  double T_err;
  double unusedUd;
  double unusedUc;
  double Cp;
  double unusedUb;
  double unusedUa;
  double unusedU9;
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

  /* Calculate the temperature from pressure(p), enthalpy(h) and fuel air  */
  /* equivalent ratio(F) given with stoichiometric fuel air ratio(fs). */
  /*  */
  /*    The calculation of the thermodynamic properties are based on Zacharias */
  /*    method. T is found by using Newton-Raphson method. */
  /*    The gas is assumed to be idea gas. */
  /*  */
  /*    Input */
  /*        p : pressure [Pa] */
  /*        h : specific enthalpy (J/kg) */
  /*        F : Fuel air equivalent ratio (m_f/m_a/fs) */
  /*        fs : stoichiometric fuel air ratio (m_f/m_a)_stoich */
  /*    Output */
  /*        T : Temperature (K) */
  /*  */
  /*  Created by Kevin Koosup Yum on 10 Sept, 2015 */
  T = 300.0;

  /* Initial temperature */
  dT = 0.0;
  T_err = 1.0;
  while (T_err > 0.0001) {
    T -= dT;
    GetThdynCombGasZachV1(p, T, F, fs, &unusedU0, &h_temp, &unusedU1, &unusedU2,
                          &unusedU3, &unusedU4, &unusedU5, &unusedU6, &unusedU7,
                          &unusedU8, &unusedU9, &unusedUa, &unusedUb, &Cp,
                          &unusedUc, &unusedUd);
    dT = (h_temp - h) / Cp;
    T_err = fabs(dT) / T;
  }

  return T;
}

/* End of code generation (GetTFromPhF.cpp) */
