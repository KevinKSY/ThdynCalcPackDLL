/*
 * GetROHRDyn.c
 *
 * Code generation for function 'GetROHRDyn'
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
#include "Get3Wiebe.h"
#include "Get3WiebePara.h"
#include "GetCompCombGas_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static real_T rt_roundd_snf(real_T u);

/* Function Definitions */
static real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = -0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void GetROHRDyn(const double inarr_ROHR[12], const double WiebePara[9], double
                outarr_ROHR[4], double WiebePara_new[9])
{
  real_T n_new;
  real_T fir;
  real_T dmfdt;
  real_T dqfdt;
  real_T fiig_new;
  int32_T i;

  /* UNTITLED Summary of this function goes here */
  /*    Detailed explanation goes here */
  /*    Input */
  /*        inarr_ROHR(0) : Stroke (nstroke) */
  /*        inarr_ROHR(1) : Angle when start of diesel injection (fiinj) */
  /*        inarr_ROHR(2) : Crank angle (deg, 0 - infinity) (fir) */
  /*        inarr_ROHR(3) : Cylinder pressure (p) */
  /*        inarr_ROHR(4) : Cylinder temperature (T) */
  /*        inarr_ROHR(5) : Engine speed (rad/s) (omega) */
  /*        inarr_ROHR(6) : Mass of diesel pr injection (mqf) */
  /*        inarr_ROHR(7) : Lower heating value of diesel (Hn) */
  /*        inarr_ROHR(8) : Normalized Engine Load (0~1) (bmepnom) */
  /*        inarr_ROHR(9) : Normalized speed (0~1) (omeganom) */
  /*        inarr_ROHR(10) : combustion mode (n) */
  /*                        0:fuel injection not started,  */
  /*                        1:fuel injection started but no ignition */
  /*                        2:ignition started */
  /*                        5:No ignition due to low pressure and temperature */
  /*        inarr_ROHR(11) : CA at ignition */
  /*        WiebePara : 9 Parameters for 3 Wiebe functions (Refer to */
  /*                        GetWiebePara or Get3Wiebe) */
  /*    Output */
  /*        ourarr_ROHR(0) = fuel mass injection rate(dmf) (kg/s) */
  /*        ourarr_ROHR(1) = heat injection rate(dqf) (J/s) */
  /*        ourarr_ROHR(2) = Combustion mode (n_new) */
  /*        ourarr_ROHR(3) = CA at ignition (fiig_new) */
  /*        WiebePara_new :  9 Parameters for 3 Wiebe functions */
  /*  */
  /*  Created by Kevin Koosup Yum on 17 July 2012 */
  /* % */
  n_new = inarr_ROHR[0] * 180.0;
  if (n_new == 0.0) {
    fir = inarr_ROHR[2];
  } else if (n_new == floor(n_new)) {
    fir = inarr_ROHR[2] - floor(inarr_ROHR[2] / n_new) * n_new;
  } else {
    fir = inarr_ROHR[2] / n_new;
    if (fabs(fir - rt_roundd_snf(fir)) <= 2.2204460492503131E-16 * fabs(fir)) {
      fir = 0.0;
    } else {
      fir = (fir - floor(fir)) * n_new;
    }
  }

  /* % Reset and start new cycle */
  if ((fir < inarr_ROHR[1]) && (fir > 10.0) && (inarr_ROHR[10] == 5.0)) {
    n_new = 0.0;
    dmfdt = 0.0;
    dqfdt = 0.0;
    fiig_new = inarr_ROHR[11];
	for (i = 0; i < 9; i++) {
    WiebePara_new[i] = WiebePara[i];
	}
    /* % The fuel injection has started */
  } else if ((fir >= inarr_ROHR[1]) && (inarr_ROHR[10] == 0.0)) {
    if ((inarr_ROHR[3] < 1.0E+6) || (inarr_ROHR[4] < 400.0)) {
      /*  No ignition at low pressure/temperature */
      n_new = 5.0;
      dmfdt = 0.0;
      dqfdt = 0.0;
      fiig_new = inarr_ROHR[11];
	  for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}
    } else {
      /* This function calcuates the ignition delay using measured data. */
      /*    Input  */
      /*        p            - Cylinder pressure (Pa) */
      /*        T            - Cylinder temperature (K) */
      /*        omega        - Engine speed (rad/s) */
      /*    Output: */
      /*        ig_del       - Ignition delay (deg) */
      /*  */
      /*  Created by Kevin Koosup Yum on 16 July (Original by E. Pedersen) */
      n_new = 0.0002 * exp(4650.0 / inarr_ROHR[4]) * rt_powd_snf(inarr_ROHR[3] *
        1.0E-5, -1.19);
      if (n_new * inarr_ROHR[5] > 1.0471975511965976) {
        n_new = 3.1415926535897931 / (3.0 * inarr_ROHR[5]);
      }

      n_new = n_new * inarr_ROHR[5] * 180.0 / 3.1415926535897931;
      if (n_new <= 20.0) {
      } else {
        n_new = 20.0;
      }

      n_new += inarr_ROHR[1];
      fiig_new = n_new - floor(n_new / 720.0) * 720.0;
      n_new = 1.0;
      dmfdt = 0.0;
      dqfdt = 0.0;
	  for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}
    }

    /* % No ignition during the ignition delay */
  } else if ((fir >= inarr_ROHR[1]) && (inarr_ROHR[10] == 1.0) && fir < (inarr_ROHR[11])) {
    dmfdt = 0.0;
    dqfdt = 0.0;
    fiig_new = inarr_ROHR[11];
    for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}
    n_new = 1.0;

    /* % First ignition   */
  } else if ((fir >= inarr_ROHR[11]) && (inarr_ROHR[10] == 1.0)) {
    Get3WiebePara(inarr_ROHR[9], inarr_ROHR[8], WiebePara_new);
    Get3Wiebe(WiebePara_new, inarr_ROHR[11], fir, &n_new, &dmfdt);
    dmfdt = dmfdt * inarr_ROHR[6] * (inarr_ROHR[5] * 180.0 / 3.1415926535897931);
    dqfdt = inarr_ROHR[7] * dmfdt;
    n_new = 2.0;
    fiig_new = inarr_ROHR[11];

    /* % Combustion after ignition     */
  } else if ((fir >= inarr_ROHR[11]) && (fir <= (inarr_ROHR[11] + WiebePara[2])
              + WiebePara[5]) && (inarr_ROHR[10] == 2.0)) {
    Get3Wiebe(WiebePara, inarr_ROHR[11], fir, &n_new, &dmfdt);
    dmfdt = dmfdt * inarr_ROHR[6] * (inarr_ROHR[5] * 180.0 / 3.1415926535897931);
    dqfdt = inarr_ROHR[7] * dmfdt;
    n_new = 2.0;
    fiig_new = inarr_ROHR[11];
    for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}

    /* %      */
  } else {
    n_new = inarr_ROHR[10];
    dmfdt = 0.0;
    dqfdt = 0.0;
    fiig_new = inarr_ROHR[11];
    for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}

  }

  /* % Reset the cycle before the new cycle */
  if (fir > 710.0) {
    dmfdt = 0.0;
    dqfdt = 0.0;
    n_new = 5.0;
    fiig_new = inarr_ROHR[11];
	for (i = 0; i < 9; i++) {
		WiebePara_new[i] = WiebePara[i];
		}
  }

  /* % Output */
  for (i = 0; i < 4; i++) {
    outarr_ROHR[i] = 0.0;
  }

  outarr_ROHR[0] = dmfdt;
  outarr_ROHR[1] = dqfdt;
  outarr_ROHR[2] = n_new;
  outarr_ROHR[3] = fiig_new;
}

/* End of code generation (GetROHRDyn.c) */
