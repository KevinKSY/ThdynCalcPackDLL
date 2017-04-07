/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetCompCombGas.h
 *
 * Code generation for function 'GetCompCombGas'
 *
 */

#ifndef __GETCOMPCOMBGAS_H__
#define __GETCOMPCOMBGAS_H__

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
extern void GetCompCombGas(double P, double T, double F, double T_L, double T_H,
  const double Fc[4], const double x_air[12], double x[12]);

#endif

/* End of code generation (GetCompCombGas.h) */
