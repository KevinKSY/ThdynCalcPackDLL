/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetDiffusivityHCVaporToAir.h
 *
 * Code generation for function 'GetDiffusivityHCVaporToAir'
 *
 */

#ifndef __GETDIFFUSIVITYHCVAPORTOAIR_H__
#define __GETDIFFUSIVITYHCVAPORTOAIR_H__

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
extern double GetDiffusivityHCVaporToAir(double p, double T, double MW, double C,
  double H, double O, double N, boolean_T Aromatic);

#endif

/* End of code generation (GetDiffusivityHCVaporToAir.h) */
