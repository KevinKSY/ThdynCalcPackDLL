/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rdivide.cpp
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "rdivide.h"

/* Function Definitions */
void b_rdivide(const double x_data[], const int x_size[2], const double y_data[],
               double z_data[], int z_size[2])
{
  int loop_ub;
  int i10;
  z_size[0] = 1;
  z_size[1] = x_size[1];
  loop_ub = x_size[0] * x_size[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    z_data[i10] = x_data[i10] / y_data[i10];
  }
}

double rdivide(double x, double y)
{
  return x / y;
}

/* End of code generation (rdivide.cpp) */
