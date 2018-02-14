/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dNOx.cpp
 *
 * Code generation for function 'dNOx'
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

/* Function Definitions */
double dNOx(double p, double T, double F, double V, double NOmol, double T_L,
            double T_H, const double FC[4], const double xAir[12])
{
  double dNOConc;
  double B;
  double C[12];
  int i0;
  double R1;
  double cNO;

  /* Computes the rate of formation of NO in the combustion gas in kmol/m3/s. */
  /*    Detailed explanation goes here */
  B = 8314.5 * T;
  GetCompCombGas(p, T, F, T_L, T_H, FC, xAir, C);
  for (i0 = 0; i0 < 12; i0++) {
    C[i0] = C[i0] * p / B;
  }

  /* molar concentration[kmol/m3] */
  if (C[6] == 0.0) {
    dNOConc = 0.0;
  } else {
    /*         %{ */
    /*         %From Heywoods */
    /*         k1 = 7.6e7*exp(-38000/T); */
    /*         k2 = 6.4e3*T*exp(-3150/T); */
    /*         k3 = 4.1e7; */
    /*         %}  */
    /*  From Hanson and Salimian in kmol/m3 */
    R1 = 1.8E+11 * exp(-38370.0 / T) * C[1] * C[10];
    cNO = NOmol / V;

    /*  in kmol/m3 */
    B = cNO / C[6];
    dNOConc = 2.0 * R1 * (1.0 - B * B) / (1.0 + cNO / C[6] * R1 / ((1.8E+7 * T *
      exp(-4680.0 / T) * C[2] * C[7] + 7.1E+10 * exp(-450.0 / T) * C[2] * C[4])
      + 1.0E-20));
  }

  return dNOConc;
}

/* End of code generation (dNOx.cpp) */
