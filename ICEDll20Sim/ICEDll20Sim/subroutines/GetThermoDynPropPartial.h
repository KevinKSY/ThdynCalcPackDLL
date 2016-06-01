/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThermoDynPropPartial.h
 *
 * Code generation for function 'GetThermoDynPropPartial'
 *
 */

#ifndef __GETTHERMODYNPROPPARTIAL_H__
#define __GETTHERMODYNPROPPARTIAL_H__

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
extern void GetThermoDynPropPartial(double P, double T, const double x[12],
  const double dx[36], double *R, double *h, double *s, double *u, double *RP,
  double *RT, double *RF, double *uP, double *uT, double *uF, double *sP, double
  *sT, double *sF, double *Cp, double *Cv);

#endif

/* End of code generation (GetThermoDynPropPartial.h) */
