/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetPTx.h
 *
 * Code generation for function 'GetPTx'
 *
 */

#ifndef __GETPTX_H__
#define __GETPTX_H__

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
extern void GetPTx(double m, const double N[12], double E, double V, double
                   T_prev, double *P, double *T, double x[12]);

#endif

/* End of code generation (GetPTx.h) */
