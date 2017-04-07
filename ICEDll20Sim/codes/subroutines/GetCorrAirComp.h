/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetCorrAirComp.h
 *
 * Code generation for function 'GetCorrAirComp'
 *
 */

#ifndef __GETCORRAIRCOMP_H__
#define __GETCORRAIRCOMP_H__

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
extern void GetCorrAirComp(double T_amb, double p_amb, double humid, double Mf_a,
  double Mf_a_corr[5], double Wf_a_corr[5], double *MW, double *H_a);

#endif

/* End of code generation (GetCorrAirComp.h) */
