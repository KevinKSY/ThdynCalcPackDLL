/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetIdealNozzleFlowPTF.h
 *
 * Code generation for function 'GetIdealNozzleFlowPTF'
 *
 */

#ifndef __GETIDEALNOZZLEFLOWPTF_H__
#define __GETIDEALNOZZLEFLOWPTF_H__

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
extern void GetIdealNozzleFlowPTF(double Cd, double A, double p_in, double p_out,
  double T_in, double F_in, double fs, double *m_dot, double *H_dot, double
  *m_b_dot);

#endif

/* End of code generation (GetIdealNozzleFlowPTF.h) */
