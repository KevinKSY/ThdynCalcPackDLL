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

#ifndef __GETPTFV1_H__
#define __GETPTFV1_H__

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
extern void GetPTFV1(double m, double m_b, double E, double V, double T_prev,
                     double R_prev, double u_prev, double Cv_prev, double fs,
                     double *p, double *T, double *F);

#endif

/* End of code generation (GetPTFV1.h) */
