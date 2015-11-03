/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThermalPropertyHCVaporReal.h
 *
 * Code generation for function 'GetThermalPropertyHCVaporReal'
 *
 */

#ifndef __GETTHERMALPROPERTYHCVAPORREAL_H__
#define __GETTHERMALPROPERTYHCVAPORREAL_H__

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
extern void GetThermalPropertyHCVaporReal(double p, double T, double MW, double
  T_CR, double p_CR, double W, double *rho_v, double *Cp_v, double *Cv_v, double
  *lambda);

#endif

/* End of code generation (GetThermalPropertyHCVaporReal.h) */
