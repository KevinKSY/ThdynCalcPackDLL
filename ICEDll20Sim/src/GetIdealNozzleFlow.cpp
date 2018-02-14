/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetIdealNozzleFlow.cpp
 *
 * Code generation for function 'GetIdealNozzleFlow'
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
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
void GetIdealNozzleFlow(double Cd, double A, double p_in, double p_out, double
  T_in, const double X_in[12], double *m_dot, double *h_dot, double N_dot[12])
{
  double unusedU2;
  double unusedU1;
  double ht;
  double unusedU0;
  double Cv;
  double Cp;
  double R;
  double MW;
  double pr;
  double b_gamma;
  double gamma1;
  int i;

  /* Calculate the mass flow through ideal nozzle(valve) */
  /*    Input */
  /*        Cd, A, p_in, p_out, T_in, X_in */
  /*    Output */
  /*        m_dot */
  GetThermoDynProp(p_in, T_in, X_in, &R, &Cp, &Cv, &unusedU0, &ht, &unusedU1,
                   &unusedU2);
  MW = 8314.4621 / R;
  pr = p_out / p_in;
  b_gamma = Cp / Cv;
  gamma1 = (b_gamma - 1.0) / b_gamma;
  if (pr < rt_powd_snf(2.0 / (b_gamma + 1.0), 1.0 / gamma1)) {
    *m_dot = Cd * A * p_in / sqrt(R * T_in) * sqrt(b_gamma * rt_powd_snf(2.0 /
      (b_gamma + 1.0), (b_gamma + 1.0) / (b_gamma - 1.0)));
  } else {
    *m_dot = Cd * A * p_in / sqrt(R * T_in) * rt_powd_snf(pr, 1.0 / b_gamma) *
      sqrt(2.0 / gamma1 * (1.0 - rt_powd_snf(pr, gamma1)));
  }

  *h_dot = *m_dot * ht;
  for (i = 0; i < 12; i++) {
    N_dot[i] = X_in[i] * *m_dot / MW;
  }
}

/* End of code generation (GetIdealNozzleFlow.cpp) */
