/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rdivide.h
 *
 * Code generation for function 'rdivide'
 *
 */

#ifndef __RDIVIDE_H__
#define __RDIVIDE_H__

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
extern void b_rdivide(const double x_data[], const int x_size[2], const double
                      y_data[], double z_data[], int z_size[2]);
extern double rdivide(double x, double y);

#endif

/* End of code generation (rdivide.h) */
