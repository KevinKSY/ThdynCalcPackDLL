/*
 * GetCompleteComb.c
 *
 * Code generation for function 'GetCompleteComb'
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

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void GetCompleteComb(real_T F, const real_T Fc[5], const real_T Ac[11], real_T
                     x[12])
{
  real_T N_L;
  real_T Fa;
  real_T Fb;
  real_T n_H_2;
  real_T n_H_2O;
  real_T n_N_2;
  real_T n_CO;
  real_T n_O_2;

  /* Calculate the composition of combustion gas under no dissociation.  */
  /*  */
  /*  Ref : Valland, H. (2012). Computation of Thermodynamic Properties of  */
  /*        Combustion Products and Fuel-Air Processes. TMR9  Internal  */
  /*        Combustion Engines, Advanced Course Lecture Note. Trondheim,  */
  /*        Department of Marine Technology, NTNU. */
  /*  */
  /*  Chemical reaction considered */
  /*   F*C_n H_m O_l N_k + N_L (O_2 + b1 N_2 + b2 Ar + b3 CO + b4 CO_2 +  */
  /*        b5 H_2O + b6 H_2 + b7 H + b8 O + b9 N + b10 OH + b11 NO)) */
  /*     => n_H_2O H_2O + n_CO_2 CO_2 + n_N_2 N_2 + n_Ar Ar (F=1) */
  /*     => n_CO CO + n_H_2O H_2O + n_N_2 N_2 + n_Ar Ar (F=Fa) */
  /*     => n_CO CO + n_H_2 H_2 + n_N_2 N_2 + n_Ar Ar (F=Fb) */
  /*     => n_O_2 O2 + n_H_2O H_2O + n_CO_2 CO_2 + n_N_2 N_2 + n_Ar Ar (F<=1) */
  /*     => n_CO CO + n_H_2O H_2O + n_CO_2 CO_2 + n_N_2 N_2 + n_Ar Ar (1<F<Fa) */
  /*     => n_H_2 H_2 + n_CO CO + n_H_2O H_2O + n_N_2 N_2 + n_Ar Ar (Fa<F<=Fb) */
  /*     => n_H_2 H_2 + n_CO CO + n_N_2 N_2 + n_Ar Ar (F>Fb) */
  /*   */
  /*  Input */
  /*    F : air fuel equivalent ratio */
  /*    Fc : Fuel atomic composition in C, H, O, N  */
  /*         Fc(1) = C, Fc(2) = H, Fc(3) = O, Fc(4) = N */
  /*    Ac : Composition of air as the ratio of mole to one mole of O2 */
  /*         Ac(1) = n_N2/n_O2,  Ac(2) = n_Ar/n_O2,  Ac(3) = n_CO/n_O2 */
  /*         Ac(4) = n_CO2/n_O2, Ac(5) = n_H2O/n_O2, Ac(6) = n_H2/n_O2 */
  /*         Ac(7) = n_H/n_O2,   Ac(8) = n_O/n_O2,   Ac(9) = n_N/n_O2 */
  /*         Ac(10) = n_OH/n_O2, Ac(11) = n_NO/n_O3 */
  /*  Output */
  /*    x : Composition of exhaust gas in mole fraction of the component */
  /*        x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;  x(5) = x_OH; */
  /*        x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;  x(9) = x_H2O; x(10) = x_CO2; */
  /*        x(11) = x_N2; x(12) = x_Ar */
  /*  */
  /*  Created by Kevin Koosup Yum on 25 June 2012 */
  memset(&x[0], 0, 12U * sizeof(real_T));
  N_L = ((Fc[1] - 2.0 * Fc[2]) + 4.0 * Fc[0]) / ((((((2.0 * Ac[7] - 2.0 * Ac[5])
    - Ac[6]) - 2.0 * Ac[2]) + Ac[9]) + 2.0 * Ac[10]) + 4.0);
  Fa = -((((((2.0 * Ac[3] - 2.0 * Ac[5]) - Ac[6]) + 2.0 * Ac[7]) + Ac[9]) + 2.0 *
          Ac[10]) + 4.0) / ((2.0 * Fc[2] - Fc[1]) - 2.0 * Fc[0]) * N_L;
  Fb = -(((((Ac[3] + Ac[4]) + Ac[7]) + Ac[9]) + Ac[10]) + 2.0) / (Fc[2] - Fc[0])
    * N_L;
  if (F <= 1.0) {
    n_H_2 = F * Fc[0] + (Ac[2] + Ac[3]) * N_L;
    n_H_2O = F * Fc[1] / 2.0 + (((Ac[4] + Ac[5]) + Ac[6] / 2.0) + Ac[9] / 2.0) *
      N_L;
    n_N_2 = F * Fc[3] / 2.0 + ((Ac[0] + Ac[8] / 2.0) + Ac[10] / 2.0) * N_L;
	n_O_2 = (1 - F)*(Fc[1] - 2*Fc[2] + 4*Fc[0])/4;
    Fa = Ac[1] * N_L;
    Fb = (((n_H_2 + n_H_2O) + n_N_2) + Fa) + n_O_2;
	x[7] = n_O_2 / Fb;
    x[9] = n_H_2 / Fb;
    x[8] = n_H_2O / Fb;
    x[10] = n_N_2 / Fb;
    x[11] = Fa / Fb;
  } else if (F <= Fa) {
    n_H_2 = (Fc[0] + N_L * (Ac[2] + Ac[3])) * ((Fa - F) / (Fa - 1.0));
    n_CO = (F - 1.0) * ((Fc[1] - 2.0 * Fc[2]) + 4.0 * Fc[0]) / 2.0;
    n_H_2O = F * Fc[1] / 2.0 + (((Ac[4] + Ac[5]) + Ac[6] / 2.0) + Ac[9] / 2.0) *
      N_L;
    n_N_2 = F * Fc[3] / 2.0 + ((Ac[0] + Ac[8] / 2.0) + Ac[10] / 2.0) * N_L;
    Fa = Ac[1] * N_L;
    Fb = (((n_H_2 + n_H_2O) + n_CO) + n_N_2) + Fa;
    x[9] = n_H_2 / Fb;
    x[8] = n_H_2O / Fb;
    x[5] = n_CO / Fb;
    x[10] = n_N_2 / Fb;
    x[11] = Fa / Fb;
  } else {
    if (F <= Fb) {
      n_CO = F * Fc[0] + (Ac[2] + Ac[3]) * N_L;
      n_H_2 = (Fb * Fc[1] / 2.0 + (((Ac[4] + Ac[5]) + Ac[6] / 2.0) + Ac[9] / 2.0)
               * N_L) / (Fb - Fa) * (F - Fa);
      n_H_2O = (Fa * Fc[1] / 2.0 + (((Ac[4] + Ac[5]) + Ac[6] / 2.0) + Ac[9] /
                 2.0) * N_L) * ((Fb - F) / (Fb - Fa));
      n_N_2 = F * Fc[3] / 2.0 + ((Ac[0] + Ac[8] / 2.0) + Ac[10] / 2.0) * N_L;
      Fa = Ac[1] * N_L;
      Fb = (((n_CO + n_H_2) + n_H_2O) + n_N_2) + Fa;
      x[3] = n_H_2 / Fb;
      x[8] = n_H_2O / Fb;
      x[5] = n_CO / Fb;
      x[10] = n_N_2 / Fb;
      x[11] = Fa / Fb;
    }
  }
}

/* End of code generation (GetCompleteComb.c) */
