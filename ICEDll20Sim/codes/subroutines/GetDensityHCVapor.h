/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetDensityHCVapor.h
 *
 * Code generation for function 'GetDensityHCVapor'
 *
 */

#ifndef __GETDENSITYHCVAPOR_H__
#define __GETDENSITYHCVAPOR_H__

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
extern void GetDensityHCVapor(double p, double T, double p_CR, double T_CR,
  double MW, double W, double rho_v_data[], int rho_v_size[1]);

#endif

/* End of code generation (GetDensityHCVapor.h) */
