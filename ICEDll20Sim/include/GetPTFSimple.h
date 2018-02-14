/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetPTFV1.h
 *
 * Code generation for function 'GetPTFV1'
 *
 */

#ifndef __GETPTFSIMPLE_H__
#define __GETPTFSIMPLE_H__

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
extern void GetPTFSimple(double m, double m_b, double E, double V, double p_prev,
                     double T_prev, double fs, double *p, double *T, double *F);

#endif

/* End of code generation (GetPTFV1.h) */
