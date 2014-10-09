/*
 * GetThermoDynProp.h
 *
 * Code generation for function 'GetThermoDynProp'
 *
 * C source code generated on: Tue Jul 31 11:27:42 2012
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
#include "GetCompCombGas_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
#ifdef __cplusplus
extern "C" {
#endif
extern void GetThermoDynProp(real_T P, real_T T, const real_T x[12], real_T *R, real_T *Cp, real_T *Cv, real_T *u, real_T *ht, real_T *s, real_T *rho);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (GetThermoDynProp.h) */
