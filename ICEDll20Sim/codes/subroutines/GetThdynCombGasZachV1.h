/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThdynCombGasZachV1.h
 *
 * Code generation for function 'GetThdynCombGasZachV1'
 *
 */

#ifndef __GETTHDYNCOMBGASZACHV1_H__
#define __GETTHDYNCOMBGASZACHV1_H__

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
extern void GetThdynCombGasZachV1(double P, double T, double F, double fs,
  double *R, double *h, double *s, double *u, double *RF, double *RP, double *RT,
  double *uF, double *uP, double *uT, double *sF, double *sP, double *sT, double
  *Cp, double *Cv, double *K);
extern void b_GetThdynCombGasZachV1(double P, double T, double F, double fs,
  double *R, double *h, double *s, double *u, double *RF, double *RP, double *RT,
  double *uF, double *uP, double *uT, double *sF, double *sP, double *sT);

#endif

/* End of code generation (GetThdynCombGasZachV1.h) */
