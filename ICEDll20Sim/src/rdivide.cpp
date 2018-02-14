/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rdivide.cpp
 *
 * Code generation for function 'rdivide'
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
#include "rdivide.h"

/* Function Definitions */
void b_rdivide(const double x_data[], const int x_size[2], const double y_data[],
               double z_data[], int z_size[2])
{
  int loop_ub;
  int i10;
  z_size[0] = 1;
  z_size[1] = x_size[1];
  loop_ub = x_size[0] * x_size[1];
  for (i10 = 0; i10 < loop_ub; i10++) {
    z_data[i10] = x_data[i10] / y_data[i10];
  }
}

double rdivide(double x, double y)
{
  return x / y;
}

/* End of code generation (rdivide.cpp) */
