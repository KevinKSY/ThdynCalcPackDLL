/*
 * Get3Wiebe.c
 *
 * Code generation for function 'Get3Wiebe'
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
#include "GetCompCombGas_rtwutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void Get3Wiebe(const real_T WiebePara[9], real_T ficst, real_T fir, real_T *f,
               real_T *dfdphi)
{
  real_T q1c;
  real_T q2c;
  real_T dCAc;
  real_T CDpc;
  real_T CDmc;
  real_T CDlc;
  real_T mpc;
  real_T mmc;
  real_T mlc;
  real_T yp;
  real_T yptomp;
  real_T eex;
  real_T f1;
  real_T df1dy;
  real_T f2;

  /* The function calculates the rate of heat release and accumulated heat */
  /* release as a function of crank angle. ROHR is modeled by the use of  */
  /* three Wiebe functions. */
  /*    Input: */
  /*       WiebePara(1) : Energy fraction of the premixed combustion (q1c) */
  /*       WiebePara(2): Energy fraction of the mixing controlled */
  /*                    combustion (q2c) */
  /*       WiebePara(3): duration in CA from the ficst til the start of the  */
  /*                    mixing controlled and late combustion (dCAc) */
  /*       WiebePara(4): Combustion duration for premixed combustion(CDpc) */
  /*       WiebePara(5): Combustion duration for mixing-controlled */
  /*                    combustion(CDmc) */
  /*       WiebePara(6): Combustion duration for late combustion(CDlc) */
  /*       WiebePara(7): Shape parameter for Wiebe function for premixed */
  /*                    combustion(mpc) */
  /*       WiebePara(8): Shape parameter for Wiebe function for mixing */
  /*                    controlled combustion(mmc) */
  /*       WiebePara(9): Shape parameter for Wiebe function for late */
  /*                    combustion(mlc) */
  /*       ficst : CA at start of premixed combustion */
  /*       fir  : Crank angle */
  /*    Output: */
  /*       dfdphi : Rate of heat release (dQnom/dphi) */
  /*       f : Accumulated heat release (Qnom) */
  /*  */
  /*  Created by Kevin Koosup Yum on 28 June 2012  */
  q1c = WiebePara[0];
  if ((0.0 >= q1c) || rtIsNaN(q1c)) {
    q1c = 0.0;
  }

  q2c = WiebePara[1];
  if ((0.0 >= q2c) || rtIsNaN(q2c)) {
    q2c = 0.0;
  }

  dCAc = WiebePara[2];
  if ((0.0 >= dCAc) || rtIsNaN(dCAc)) {
    dCAc = 0.0;
  }

  CDpc = WiebePara[3];
  if ((0.0 >= CDpc) || rtIsNaN(CDpc)) {
    CDpc = 0.0;
  }

  CDmc = WiebePara[4];
  if ((0.0 >= CDmc) || rtIsNaN(CDmc)) {
    CDmc = 0.0;
  }

  CDlc = WiebePara[5];
  if ((0.0 >= CDlc) || rtIsNaN(CDlc)) {
    CDlc = 0.0;
  }

  mpc = WiebePara[6];
  if ((0.0 >= mpc) || rtIsNaN(mpc)) {
    mpc = 0.0;
  }

  mmc = WiebePara[7];
  if ((0.0 >= mmc) || rtIsNaN(mmc)) {
    mmc = 0.0;
  }

  mlc = WiebePara[8];
  if ((0.0 >= mlc) || rtIsNaN(mlc)) {
    mlc = 0.0;
  }

  if (fir < ficst) {
    *f = 0.0;
    *dfdphi = 0.0;
  } else if (fir > 1.36 * ((ficst + dCAc) + CDlc)) {
    *f = 1.0;
    *dfdphi = 0.0;
  } else {
    yp = (fir - ficst) / CDpc;
    yptomp = rt_powd_snf(yp, mpc);
    eex = exp(-6.9 * yp * yptomp);
    f1 = 1.0 - eex;
    df1dy = 6.9 * (mpc + 1.0) * yptomp * eex / CDpc;
    if (yp > 1.36) {
      f1 = 1.0;
      df1dy = 0.0;
    }

    CDpc = (fir - (ficst + dCAc)) / CDmc;
    yp = (fir - (ficst + dCAc)) / CDlc;
    if (CDpc < 0.0) {
      yptomp = 0.0;
      CDpc = 0.0;
      f2 = 0.0;
      mpc = 0.0;
    } else {
      mpc = rt_powd_snf(CDpc, mmc);
      dCAc = rt_powd_snf(yp, mlc);
      eex = exp(-6.9 * CDpc * mpc);
      f2 = 1.0 - eex;
      yptomp = 6.9 * (mmc + 1.0) * mpc * eex / CDmc;
      eex = exp(-6.9 * yp * dCAc);
      mpc = 1.0 - eex;
      CDpc = 6.9 * (mlc + 1.0) * dCAc * eex / CDlc;
    }

    *f = (q1c * f1 + q2c * f2) + ((1.0 - q1c) - q2c) * mpc;
    *dfdphi = (q1c * df1dy + q2c * yptomp) + ((1.0 - q1c) - q2c) * CDpc;
  }
}

/* End of code generation (Get3Wiebe.c) */
