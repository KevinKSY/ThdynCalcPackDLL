/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ThdynPack_rtwutil.cpp
 *
 * Code generation for function 'ThdynPack_rtwutil'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThermoDynProp.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
double rt_powd_snf(double u0, double u1)
{
  double y;
  double d20;
  double d21;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d20 = fabs(u0);
    d21 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d20 == 1.0) {
        y = rtNaN;
      } else if (d20 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d21 == 0.0) {
      y = 1.0;
    } else if (d21 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* End of code generation (ThdynPack_rtwutil.cpp) */
