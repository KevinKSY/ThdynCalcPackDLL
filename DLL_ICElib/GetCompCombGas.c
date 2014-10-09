/*
 * GetCompCombGas.c
 *
 * Code generation for function 'GetCompCombGas'
 *
 * C source code generated on: Tue Jul 31 11:27:42 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetCompCombGas.h"
#include "GetPTx.h"
#include "GetROHRDyn.h"
#include "GetThermoDynProp.h"
#include "GetTxV.h"
#include "GetCompleteComb.h"
#include "GetEquilGrill.h"
#include "GetCompCombGas_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void GetCompCombGas(const real_T inarr_CompCG[5], const real_T Fc[4], const
                    real_T x_air[12], real_T x[12])
{
  real_T Ac[11];
  real_T x2[12];
  real_T q;
  int32_T i0;

  /* Calculate the composition of combustion gas with either no dissociation  */
  /* or full dissociation or partially dissociation;  */
  /*  For full dissociation case, the composition is calculated by */
  /*  GetEquilGrill(). For complete combustion case, the composition is */
  /*  calculated by GetCompleteComb(). For the partial dissociation case, the */
  /*  blending function is used. The transition region  */
  /*  */
  /*  Ref : Valland, H. (2012). Computation of Thermodynamic Properties of  */
  /*        Combustion Products and Fuel-Air Processes. TMR9  Internal  */
  /*        Combustion Engines, Advanced Course Lecture Note. Trondheim,  */
  /*        Department of Marine Technology, NTNU. */
  /*  */
  /*  Input */
  /*    P : Pressure of the gas (Pa) */
  /*    T : Temperature of the gas (K) */
  /*    F : fuel air equivalent ratio */
  /*    Fc : Fuel atomic composition in C, H, O, N  */
  /*         Fc(1) = C, Fc(2) = H, Fc(3) = O, Fc(4) = N */
  /*    x_air : Cylinder charge composition in mole fraction */
  /*        x_air(1) = x_H;   x_air(2) = x_O;   x_air(3) = x_N;    */
  /*        x_air(4) = x_H2;  x_air(5) = x_OH;  x_air(6) = x_CO;   */
  /*        x_air(7) = x_NO;  x_air(8) = x_O2;  x_air(9) = x_H2O;from  */
  /*        x_air(10) = x_CO2;x_air(11) = x_N2; x_air(12) = x_Ar */
  /*    T_L : Lower bound of the transition temperature range (K) */
  /*    T_H : Upper bound of the transition temperature range (K) */
  /*  Output */
  /*    x : Composition of exhaust gas in mole fraction of the component */
  /*        x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;  x(5) = x_OH; */
  /*        x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;  x(9) = x_H2O; x(10) = x_CO2; */
  /*        x(11) = x_N2; x(12) = x_Ar */
  /*  */
  /*  Created by Kevin Koosup Yum on 28 June 2012 */
  memset(&Ac[0], 0, 11U * sizeof(real_T));
  Ac[0] = x_air[10] / x_air[7];
  Ac[1] = x_air[11] / x_air[7];
  Ac[2] = x_air[5] / x_air[7];
  Ac[3] = x_air[9] / x_air[7];
  Ac[4] = x_air[8] / x_air[7];
  Ac[5] = x_air[3] / x_air[7];
  Ac[6] = x_air[0] / x_air[7];
  Ac[7] = x_air[1] / x_air[7];
  Ac[8] = x_air[2] / x_air[7];
  Ac[9] = x_air[4] / x_air[7];
  Ac[10] = x_air[6] / x_air[7];
  if (inarr_CompCG[1] <= inarr_CompCG[3]) {
    GetCompleteComb(inarr_CompCG[2], Fc, Ac, x);
  } else if (inarr_CompCG[1] < inarr_CompCG[4]) {
    GetEquilGrill(inarr_CompCG[0], inarr_CompCG[1], inarr_CompCG[2], Fc, Ac, x2);
    q = (inarr_CompCG[1] - inarr_CompCG[3]) / (inarr_CompCG[4] - inarr_CompCG[3]);
    q = 3.0 * rt_powd_snf(q, 2.0) - 2.0 * rt_powd_snf(q, 3.0);
    GetCompleteComb(inarr_CompCG[2], Fc, Ac, x);
    for (i0 = 0; i0 < 12; i0++) {
      x[i0] = (1.0 - q) * x[i0] + q * x2[i0];
    }
  } else {
    GetEquilGrill(inarr_CompCG[0], inarr_CompCG[1], inarr_CompCG[2], Fc, Ac, x);
  }
}

/* End of code generation (GetCompCombGas.c) */
