/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThdynCombGasZach.h
 *
 * Code generation for function 'GetThdynCombGasZach'
 *
 */

#ifndef __GETTHDYNCOMBGASZACH_H__
#define __GETTHDYNCOMBGASZACH_H__

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
extern void GetThdynCombGasZach(double P, double T, double F, double *R, double *
  h, double *s, double *u, double *RF, double *RP, double *RT, double *uF,
  double *uP, double *uT, double *Cp, double *Cv, double *K);

#endif

/* End of code generation (GetThdynCombGasZach.h) */
