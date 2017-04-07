/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThermoDynProp.h
 *
 * Code generation for function 'GetThermoDynProp'
 *
 */

#ifndef __GETTHERMODYNPROP_H__
#define __GETTHERMODYNPROP_H__

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
extern void GetThermoDynProp(double P, double T, const double x[12], double *R,
  double *Cp, double *Cv, double *u, double *ht, double *s, double *rho);

#endif

/* End of code generation (GetThermoDynProp.h) */
