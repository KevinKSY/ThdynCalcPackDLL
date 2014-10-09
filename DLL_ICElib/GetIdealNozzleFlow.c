/*
 * GetIdealNozzleFlow.c
 *
 * Code generation for function 'GetIdealNozzleFlow'
 *
 * C source code generated on: Tue Mar 25 11:39:08 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetThdynCombGasZach.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetViscosityHCVapor.h"
#include "GetCompCombGas_rtwutil.h"

/* Function Definitions */
void GetIdealNozzleFlow(real_T Cd, real_T A, real_T p_in, real_T p_out, real_T
  T_in, real_T F_in, real_T fs, real_T *m_dot, real_T *h_dot, real_T *m_b_dot)
{
  real_T pr;
  real_T gamma1;
  real_T h;
  real_T K;
  real_T R;
  real_T MW;
  real_T unused1,unused2,unused3,unused4,unused5,unused6,unused7,unused8,unused9,unused10;

  /* Calculate the mass flow through ideal nozzle(valve) */
  /*    Input */
  /*        Cd, A, p_in, p_out, T_in, X_in */
  /*    Output */
  /*        m_dot */
  GetThdynCombGasZach(p_in, T_in, F_in, &R, &h, &unused1, &unused2, &unused3, &unused4, &unused5, &unused6, &unused7, &unused8, &unused9, &unused10, &K);
  
  MW = 8314.4621 / R;
  pr = p_out / p_in;
  gamma1 = (K - 1.0) / K;
  if (pr < rt_powd_snf(2.0 / (K + 1.0), 1.0 / gamma1)) {
    *m_dot = Cd * A* p_in / sqrt(R * T_in) *
            sqrt(K * rt_powd_snf(2.0 / (K + 1.0), (K + 1.0) /
                   (K - 1.0)));
  } else {
    *m_dot = Cd * A * p_in / sqrt(R * T_in) * rt_powd_snf(pr, 1.0 / K) *
      sqrt(2.0 / gamma1 * (1.0 - rt_powd_snf(pr, gamma1)));
  }

  *h_dot = *m_dot * h;
  *m_b_dot = *m_dot*(F_in*fs / (1+F_in*fs));
	
}

/* End of code generation (GetIdealNozzleFlow.c) */
