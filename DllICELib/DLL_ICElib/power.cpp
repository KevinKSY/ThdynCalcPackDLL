/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.cpp
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "power.h"
#include "ThdynPack_data.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
void power(const double a_data[], const int a_size[2], const double b_data[],
           const int b_size[2], double y_data[], int y_size[2])
{
  int loop_ub;
  int i11;
  double x_data[1];
  double b_y_data[1];
  int k;
  int b_k;
  loop_ub = a_size[0] * a_size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    x_data[i11] = a_data[i11];
  }

  loop_ub = b_size[0] * b_size[1];
  for (i11 = 0; i11 < loop_ub; i11++) {
    b_y_data[i11] = b_data[i11];
  }

  y_size[0] = 1;
  if (a_size[1] <= b_size[1]) {
    y_size[1] = (signed char)a_size[1];
  } else {
    y_size[1] = 0;
  }

  loop_ub = a_size[1];

//#pragma omp parallel for \
// num_threads(omp_get_max_threads()) \
// private(b_k)

  for (k = 1; k <= loop_ub; k++) {
    b_k = k;
    y_data[b_k - 1] = rt_powd_snf(x_data[b_k - 1], b_y_data[b_k - 1]);
  }
}

/* End of code generation (power.cpp) */
