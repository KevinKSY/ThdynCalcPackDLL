/*
 * GetROHRDyn.h
 *
 * Code generation for function 'GetROHRDyn'
 *
 * C source code generated on: Tue Jul 31 11:27:42 2012
 *
 */

#ifndef __GETROHRDYN_H__
#define __GETROHRDYN_H__
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
extern void GetROHRDyn(const real_T inarr_ROHR[12], const real_T WiebePara[9], real_T outarr_ROHR[4], real_T WiebePara_new[9]);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (GetROHRDyn.h) */
