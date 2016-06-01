/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetViscosityHCVapor.h
 *
 * Code generation for function 'GetViscosityHCVapor'
 *
 */

#ifndef __GETVISCOSITYHCVAPOR_H__
#define __GETVISCOSITYHCVAPOR_H__

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "ThdynPack_types.h"

/* Function Declarations */
extern double GetViscosityHCVapor(double p, double T, double p_CR, double T_CR,
  double V_CR, double Z_CR, double rho_R, double MW);

#endif

/* End of code generation (GetViscosityHCVapor.h) */
