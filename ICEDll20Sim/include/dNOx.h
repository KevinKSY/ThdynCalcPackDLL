/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dNOx.h
 *
 * Code generation for function 'dNOx'
 *
 */

#ifndef __DNOX_H__
#define __DNOX_H__

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
extern double dNOx(double p, double T, double F, double V, double NOmol, double
                   T_L, double T_H, const double FC[4], const double xAir[12]);

#endif

/* End of code generation (dNOx.h) */
