/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetHTCoeffHTX.cpp
 *
 * Code generation for function 'GetHTCoeffHTX'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetThdynCombGasZachV1.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
double GetHTCoeffHTX(double p, double m_dot, double T, double D, double A)
{
  double rho_a;
  double mu_a;
  double lambda;
  double unusedUe;
  double unusedUd;
  double d6;
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
  double Re_D;
  double Pr;

  /*  Calculate the heat transfer coeff of convectivity for charge air cooler  */
  /*  exchanger (Cross-flow type) */
  /*  Input */
  /*    p : pressure (Pa) */
  /*    m_dot : mass flow (kg/s) */
  /*    T : temperature (K), should be mean value of the air and coolant */
  /*    D : Diameter of tube (coolant side) */
  /*    A : Effective sectional area of air path */
  /*  Output */
  /*    alpha : Heat transfer coefficient of convectivity (W/m2K) */
  /*  */
  /*  Created by Kevin Koosup Yum (25 March 2014) */
  /*  */
  rho_a = GetAirDensity(p, T);
  mu_a = GetAirViscosity(rho_a, T);
  lambda = GetAirThermalConduct(rho_a, T);
  GetThdynCombGasZachV1(p, T, 0.0, 0.0683, &unusedU0, &unusedU1, &unusedU2,
                        &unusedU3, &unusedU4, &unusedU5, &unusedU6, &unusedU7,
                        &unusedU8, &unusedU9, &unusedUa, &unusedUb, &unusedUc,
                        &d6, &unusedUd, &unusedUe);

  /* % */
  Re_D = m_dot / rho_a / A * D * rho_a / mu_a;
  Pr = mu_a * d6 / lambda;

  /* { */
  /* Nu_D1 = zeros(m,1); */
  /* idx = find(Re_D <= 4); */
  /* Nu_D1(idx) = 0.989*Re_D(idx).^0.330.*Pr(idx); */
  /* idx = find(Re_D <= 40 & Re_D > 4); */
  /* Nu_D1(idx) = 0.911*Re_D(idx).^0.385.*Pr(idx); */
  /* idx = find(Re_D <= 4000 & Re_D > 40); */
  /* Nu_D1(idx) = 0.683*Re_D(idx).^0.466.*Pr(idx); */
  /* idx = find(Re_D <= 40000 & Re_D > 4000); */
  /* Nu_D1(idx) = 0.193*Re_D(idx).^0.618.*Pr(idx); */
  /* idx = find(Re_D <= 400000 & Re_D > 40000); */
  /* Nu_D1(idx) = 0.027*Re_D(idx).^0.805.*Pr(idx); */
  /* alpha1 = Nu_D1.*lambda/D; */
  /* } */
  return (0.3 + 0.62 * sqrt(Re_D) * rt_powd_snf(Pr, 0.333) / rt_powd_snf(1.0 +
           rt_powd_snf(0.4 / Pr, 0.666), 0.25) * rt_powd_snf(1.0 + rt_powd_snf
           (Re_D / 282000.0, 0.625), 0.8)) * lambda / D;
}

/* End of code generation (GetHTCoeffHTX.cpp) */
