/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetFuelPropertyN_Dodecane.h
 *
 * Code generation for function 'GetFuelPropertyN_Dodecane'
 *
 */

#ifndef __GETFUELPROPERTYN_DODECANE_H__
#define __GETFUELPROPERTYN_DODECANE_H__

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
extern void GetFuelPropertyN_Dodecane(double p, double T, double *p_v, double
  *rho_l, double *h_l, double *Cp_l, double *h_fg, double *mu_l, double
  *lambda_l, double *sigma_l);

#endif

/* End of code generation (GetFuelPropertyN_Dodecane.h) */
