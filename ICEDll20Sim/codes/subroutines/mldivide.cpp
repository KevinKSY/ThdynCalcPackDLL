/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mldivide.cpp
 *
 * Code generation for function 'mldivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetCompCombGas.h"
#include "GetCorrAirComp.h"
#include "GetDensityHCVapor.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "GetEquilGrill.h"
#include "GetEquilOlikara.h"
#include "GetFuelPropertyN_Dodecane.h"
#include "GetHTCoeffHTX.h"
#include "GetIdealNozzleFlow.h"
#include "GetIdealNozzleFlowPTF.h"
#include "GetMEMbZach.h"
#include "GetPTF.h"
#include "GetPTFV1.h"
#include "GetPTx.h"
#include "GetTFromPhF.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"
#include "GetThdynCombGasZachV1.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetThermoDynPropPartial.h"
#include "GetTotalStaticPT.h"
#include "GetViscosityHCVapor.h"
#include "dNOx.h"
#include "mldivide.h"

/* Function Definitions */
void mldivide(const double A[16], double B[4])
{
  double b_A[16];
  signed char ipiv[4];
  int i16;
  int j;
  int c;
  int kAcol;
  int ix;
  double smax;
  int k;
  double s;
  int jy;
  int ijA;
  memcpy(&b_A[0], &A[0], sizeof(double) << 4);
  for (i16 = 0; i16 < 4; i16++) {
    ipiv[i16] = (signed char)(1 + i16);
  }

  for (j = 0; j < 3; j++) {
    c = j * 5;
    kAcol = 0;
    ix = c;
    smax = fabs(b_A[c]);
    for (k = 2; k <= 4 - j; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > smax) {
        kAcol = k - 1;
        smax = s;
      }
    }

    if (b_A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (signed char)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 4; k++) {
          smax = b_A[ix];
          b_A[ix] = b_A[kAcol];
          b_A[kAcol] = smax;
          ix += 4;
          kAcol += 4;
        }
      }

      i16 = (c - j) + 4;
      for (jy = c + 1; jy + 1 <= i16; jy++) {
        b_A[jy] /= b_A[c];
      }
    }

    kAcol = c;
    jy = c + 4;
    for (k = 1; k <= 3 - j; k++) {
      smax = b_A[jy];
      if (b_A[jy] != 0.0) {
        ix = c + 1;
        i16 = (kAcol - j) + 8;
        for (ijA = 5 + kAcol; ijA + 1 <= i16; ijA++) {
          b_A[ijA] += b_A[ix] * -smax;
          ix++;
        }
      }

      jy += 4;
      kAcol += 4;
    }

    if (ipiv[j] != j + 1) {
      smax = B[j];
      B[j] = B[ipiv[j] - 1];
      B[ipiv[j] - 1] = smax;
    }
  }

  for (k = 0; k < 4; k++) {
    kAcol = k << 2;
    if (B[k] != 0.0) {
      for (jy = k + 1; jy + 1 < 5; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }

  for (k = 3; k >= 0; k += -1) {
    kAcol = k << 2;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + kAcol];
      for (jy = 0; jy + 1 <= k; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }
}

/* End of code generation (mldivide.cpp) */
