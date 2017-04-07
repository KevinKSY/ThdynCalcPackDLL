/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetIdealNozzleFlow.h
 *
 * Code generation for function 'GetIdealNozzleFlow'
 *
 */

#ifndef __GETIDEALNOZZLEFLOW_H__
#define __GETIDEALNOZZLEFLOW_H__

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
extern void GetIdealNozzleFlow(double Cd, double A, double p_in, double p_out,
  double T_in, const double X_in[12], double *m_dot, double *h_dot, double
  N_dot[12]);

#endif

/* End of code generation (GetIdealNozzleFlow.h) */
