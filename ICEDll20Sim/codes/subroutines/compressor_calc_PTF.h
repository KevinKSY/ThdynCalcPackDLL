/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetAirThermalConduct.h
 *
 * Code generation for function 'GetAirThermalConduct'
 *
 */

#ifndef __COMPRESSORPTF_H__
#define __COMPRESSORPTF_H__

/* Include files */
#include <Windows.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "ThdynPack_types.h"


/* Function Declarations */
extern void compressor_calc_PTF(const real_T *pu,
	const real_T *Tu,
	const real_T *Fu,
	const real_T *pd,
	const real_T *Td,
	const real_T *Fd,
	const real_T *omegat,
	real_T *dmu,
	real_T *deu,
	real_T *dmbu,
	real_T *dmd,
	real_T *ded,
	real_T *dmbd,
	real_T *Tqt,
	real_T *eta_ic,
	const real_T *flow_prev,
	const real_T *eta_prev,
	const real_T  *fs, const int_T  p_width0);
#endif

/* End of code generation (GetAirThermalConduct.h) */
