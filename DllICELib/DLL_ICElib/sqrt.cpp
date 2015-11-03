/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sqrt.cpp
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sqrt.h"

/* Function Definitions */
void b_sqrt(double x_data[], int x_size[2])
{
  int nx;
  int k;
  nx = x_size[1];
  k = 1;
  while (k <= nx) {
    x_data[0] = sqrt(x_data[0]);
    k = 2;
  }
}

/* End of code generation (sqrt.cpp) */
