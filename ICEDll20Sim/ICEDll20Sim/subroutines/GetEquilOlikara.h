/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetEquilOlikara.h
 *
 * Code generation for function 'GetEquilOlikara'
 *
 */

#ifndef __GETEQUILOLIKARA_H__
#define __GETEQUILOLIKARA_H__

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
extern void GetEquilOlikara(double P, double T, double F, const double Fc[4],
  const double Ac[12], double x[12]);

#endif

/* End of code generation (GetEquilOlikara.h) */
