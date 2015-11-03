/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetIdealNozzleFlowPTF.cpp
 *
 * Code generation for function 'GetIdealNozzleFlowPTF'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetIdealNozzleFlowPTF.h"
#include "GetThdynCombGasZachV1.h"
#include "power.h"
#include "sqrt.h"
#include "rdivide.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
void GetIdealNozzleFlowPTF(double Cd, double A, double p_in, double p_out,
  double T_in, double F_in, double fs, double *m_dot, double *H_dot, double
  *m_b_dot)
{
  double K;
  double unusedUc;
  double unusedUb;
  double unusedUa;
  double unusedU9;
  double unusedU8;
  double unusedU7;
  double unusedU6;
  double unusedU5;
  double unusedU4;
  double unusedU3;
  double unusedU2;
  double unusedU1;
  double unusedU0;
  double ht;
  double R;
  double pr;
  double gamma1;
  int trueCount;
  int b_trueCount;
  int c_trueCount;
  int d_trueCount;
  int i;
  double K_data[1];
  int K_size[2];
  double b_K_data[1];
  int tmp_size[2];
  double tmp_data[1];
  double b_tmp_data[1];
  int b_tmp_size[2];
  int a_size[2];
  int pr_size[2];
  int gamma1_size[2];

  /* Calculate the mass flow through ideal nozzle(valve) */
  /*    Input */
  /*        Cd, A, p_in, p_out, T_in, F_in */
  /*    Output */
  /*        m_dot h_dot m_b */
  GetThdynCombGasZachV1(p_in, T_in, F_in, fs, &R, &ht, &unusedU0, &unusedU1,
                        &unusedU2, &unusedU3, &unusedU4, &unusedU5, &unusedU6,
                        &unusedU7, &unusedU8, &unusedU9, &unusedUa, &unusedUb,
                        &unusedUc, &K);
  pr = p_out / p_in;
  gamma1 = (K - 1.0) / K;
  if (!(pr < rt_powd_snf(2.0 / (K + 1.0), 1.0 / gamma1))) {
    *m_dot = Cd * A * p_in / sqrt(R * T_in) * rt_powd_snf(pr, 1.0 / K) * sqrt
      (2.0 / gamma1 * (1.0 - rt_powd_snf(pr, gamma1)));
  } else {
    trueCount = 0;
    b_trueCount = 0;
    c_trueCount = 0;
    d_trueCount = 0;
    for (i = 0; i < 1; i++) {
      trueCount++;
      b_trueCount++;
      c_trueCount++;
      d_trueCount++;
    }

    K_size[0] = 1;
    K_size[1] = d_trueCount;
    for (i = 0; i < d_trueCount; i++) {
      K_data[i] = K + 1.0;
    }

    for (i = 0; i < d_trueCount; i++) {
      b_K_data[i] = K - 1.0;
    }

    b_rdivide(K_data, K_size, b_K_data, tmp_data, tmp_size);
    b_tmp_size[0] = 1;
    b_tmp_size[1] = d_trueCount;
    for (i = 0; i < d_trueCount; i++) {
      b_tmp_data[i] = 2.0 / (K + 1.0);
    }

    power(b_tmp_data, b_tmp_size, tmp_data, tmp_size, K_data, K_size);
    d_trueCount = 0;
    for (i = 0; i < 1; i++) {
      d_trueCount++;
    }

    unusedU0 = Cd * A;
    tmp_size[0] = 1;
    tmp_size[1] = trueCount;
    for (i = 0; i < b_trueCount; i++) {
      tmp_data[i] = R * T_in;
    }

    b_sqrt(tmp_data, tmp_size);
    a_size[0] = 1;
    a_size[1] = d_trueCount;
    for (i = 0; i < d_trueCount; i++) {
      b_K_data[i] = unusedU0 * p_in;
    }

    b_rdivide(b_K_data, a_size, tmp_data, b_tmp_data, b_tmp_size);
    K_size[0] = 1;
    K_size[1] = c_trueCount;
    for (i = 0; i < c_trueCount; i++) {
      K_data[i] *= K;
    }

    b_sqrt(K_data, K_size);
    trueCount = b_tmp_size[1];
    for (i = 0; i < trueCount; i++) {
      b_tmp_data[i] *= K_data[i];
    }

    unusedU0 = 0.0;
    trueCount = 0;
    for (i = 0; i < 1; i++) {
      unusedU0 = b_tmp_data[trueCount];
      trueCount++;
    }

    tmp_size[0] = 1;
    tmp_size[1] = 0;
    b_sqrt(tmp_data, tmp_size);
    pr_size[0] = 1;
    pr_size[1] = 0;
    gamma1_size[0] = 1;
    gamma1_size[1] = 0;
    power(K_data, pr_size, K_data, gamma1_size, b_tmp_data, b_tmp_size);
    b_tmp_size[0] = 1;
    b_tmp_size[1] = 0;
    b_sqrt(b_tmp_data, b_tmp_size);
    *m_dot = unusedU0;
  }

  *H_dot = *m_dot * ht;
  *m_b_dot = *m_dot * (F_in * fs) / (1.0 + F_in * fs);
}

/* End of code generation (GetIdealNozzleFlowPTF.cpp) */
