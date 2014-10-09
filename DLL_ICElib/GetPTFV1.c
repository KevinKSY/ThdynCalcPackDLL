/*
 * GetPTF.c
 *
 * Code generation for function 'GetPTF'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThdynCombGasZach.h"
#include "GetPTFV1.h"

/* Function Definitions */
void GetPTFV1(real_T m, real_T m_b, real_T E, real_T V, real_T T_prev, 
        real_T R_prev, real_T u_prev, real_T Cv_prev, real_T fs,
        real_T *p, real_T *T, real_T *F)
{
  real_T err_p;
  real_T R;
  real_T unusedU15;
  real_T unusedU14;
  real_T unusedU13;
  real_T uT;
  real_T unusedU12;
  real_T unusedU11;
  real_T unusedU10;
  real_T unusedUf;
  real_T unusedUe;
  real_T unusedU16;
  real_T unusedU17;
  real_T unusedU18;
  real_T u_temp;
  real_T T_err;

  /* Calculate the pressure, temperature and composition of the combustion gas  */
  /* from given mass, internal energy, volume, mass of fuel burned and stoichiometric fuel/air ratio.  */
  /*  */
  /*    The calculation of the internal energy is based on the Zacharias' method
  /*     and T is found by using Newton-Raphson method.
  /*    The gas is assumed to be ideal gas. */
  /*  */
  /*    Input */
  /*        m : mass of the control volume (kg)
  /*		m_b : mass of fuel burned (kg)
  /*        E : Internal energy of the gas */
  /*        V : Volume of the gas */
  /*		fs : stoichiometric fuel/air ratio
  /*    Output */
  /*        P : Pressure (Pa) */
  /*        T : Temperature (K) */
  /*        rho : Density (kg/m3) */
  /*        F :  Fuel/air equivalent ratio
   /*  */
  /*  Created by Kevin Koosup Yum on 29 June */
  /* % Calculate F */
  *T = T_prev + (E/m - u_prev)/Cv_prev;
  *F = m_b / (m - m_b) / fs;

  /* % Calculate the initial pressure */
  *p = m * R_prev * T[0] / V;
  err_p = 1.0;
  while (err_p > 0.01) {
    GetThdynCombGasZachV1(*p, T[0], *F, fs, &err_p, &T_err, &u_temp, &unusedUe,
                        &unusedUf, &unusedU10, &unusedU11, &unusedU12, 
                        &unusedU13, &uT, &unusedU14, &unusedU15, &unusedU16,
                        &unusedU17, &unusedU18, &R);
    T_err = m * err_p * T[0] / V;
    err_p = fabs(*p - T_err) / *p;
    *p = T_err;
  }

  err_p = 1.0;
  R = 0.0;
  while (err_p > 0.0001) {
    /* % Calculate the temperature */
    err_p = 0.0;
    T_err = 1.0;
    while (T_err > 0.0001) {
      *T -= err_p;
      GetThdynCombGasZachV1(*p, *T, *F, fs, &R, &err_p, &T_err, &u_temp, &unusedUe,
                          &unusedUf, &unusedU10, &unusedU11, &unusedU12, &uT,
                          &unusedU13, &unusedU14, &unusedU15, &unusedU16,
                          &unusedU17, &unusedU18);
      err_p = (u_temp - E / m) / uT;
      T_err = fabs(err_p) / *T;
    }

    T_err = m / V * R * *T;
    err_p = fabs(*p - T_err) / *p;
    *p = T_err;
  }
}

/* End of code generation (GetPTF.c) */
