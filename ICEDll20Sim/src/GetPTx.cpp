/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetPTx.cpp
 *
 * Code generation for function 'GetPTx'
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
void GetPTx(double m, const double N[12], double E, double V, double T_prev,
            double *P, double *T, double x[12])
{
  double y;
  int k;
  double d10;
  double b_x;
  static const double b[12] = { 1.00794, 15.9994, 14.0067, 2.01588, 17.00734,
    28.0101, 30.0061, 31.9988, 18.01528, 44.0095, 28.0134, 39.948 };

  double R;
  double dT;
  double T_err;
  double T_sq;
  double T_cb;
  double T_qt;
  double a_CO2[7];
  double a_CO[7];
  double a_O2[7];
  double a_H2[7];
  double a_H2O[7];
  double a_OH[7];
  double a_O[7];
  double a_N2[7];
  double a_N[7];
  double a_NO[7];
  static const double dv36[7] = { 4.6365111, 0.0027414569, -9.9589759E-7,
    1.6038666E-10, -9.1619857E-15, -49024.904, -1.9348955 };

  static const double dv37[7] = { 3.0484859, 0.0013517281, -4.8579405E-7,
    7.8853644E-11, -4.6980746E-15, -14266.117, 6.0170977 };

  static const double dv38[7] = { 3.66096083, 0.000656365523, -1.41149485E-7,
    2.05797658E-11, -1.29913248E-15, -1215.97725, 3.41536184 };

  static const double dv39[7] = { 2.9328305, 0.00082659802, -1.4640057E-7,
    1.5409851E-11, -6.8879615E-16, -813.05582, -1.0243164 };

  static const double dv40[7] = { 2.6770389, 0.0029731816, -7.7376889E-7,
    9.4433514E-11, -4.2689991E-15, -29885.894, 6.88255 };

  static const double dv41[7] = { 2.83853033, 0.00110741289, -2.94000209E-7,
    4.20698729E-11, -2.4228989E-15, 3697.80808, 5.84494652 };

  static const double dv42[7] = { 2.54363697, -2.73162486E-5, -4.1902952E-9,
    4.95481845E-12, -4.79553694E-16, 29226.012, 4.92229457 };

  static const double dv43[7] = { 2.95257637, 0.0013969004, -4.92631603E-7,
    7.86010195E-11, -4.60755204E-15, -923.948688, 5.87188762 };

  static const double dv44[7] = { 2.4159429, 0.00017489065, -1.1902369E-7,
    3.0226244E-11, -2.0360983E-15, 56133.775, 4.6496095 };

  static const double dv45[7] = { 3.26071234, 0.00119101135, -4.29122646E-7,
    6.94481463E-11, -4.03295681E-15, 9921.43132, 6.36900518 };

  static const double dv46[7] = { 2.356813, 0.0089841299, -7.1220632E-6,
    2.4573008E-9, -1.4288548E-13, -48371.971, 9.9009035 };

  static const double dv47[7] = { 3.5795335, -0.00061035369, 1.0168143E-6,
    9.0700586E-10, -9.0442449E-13, -14344.086, 3.5084093 };

  static const double dv48[7] = { 3.78245636, -0.00299673415, 9.847302E-6,
    -9.68129508E-9, 3.24372836E-12, -1063.94356, 3.65767573 };

  static const double dv49[7] = { 2.3443029, 0.0079804248, -1.9477917E-5,
    2.0156967E-8, -7.3760289E-12, -917.92413, 0.68300218 };

  static const double dv50[7] = { 4.1986352, -0.0020364017, 6.5203416E-6,
    -5.4879269E-9, 1.771968E-12, -30293.726, -0.84900901 };

  static const double dv51[7] = { 3.99198424, -0.00240106655, 4.61664033E-6,
    -3.87916306E-9, 1.36319502E-12, 3368.89836, -0.103998477 };

  static const double dv52[7] = { 3.1682671, -0.00327931884, 6.64306396E-6,
    -6.12806624E-9, 2.11265971E-12, 29122.2592, 2.05193346 };

  static const double dv53[7] = { 3.53100528, -0.000123660988, -5.02999433E-7,
    2.43530612E-9, -1.40881235E-12, -1046.97628, 2.96747038 };

  static const double dv54[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, 56104.638, 4.1939088
  };

  static const double dv55[7] = { 4.21859896, -0.00463988124, 1.10443049E-5,
    -9.34055507E-9, 2.80554874E-12, 9845.09964, 2.28061001 };

  double a_H[84];
  double dv56[7];
  double d11;
  static const double b_a_H[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, 25473.66,
    -0.44668285 };

  static const double a_Ar[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, -745.375, 4.3796749 };

  double a_gas[7];
  int i12;
  double d12;
  double d13;
  static const double a[12] = { 26219.035, 29968.7009, 56850.013, 0.0, 4486.1538,
    -13293.628, 10977.0882, 0.0, -29084.817, -47328.105, 0.0, 0.0 };

  static const int b_a[12] = { -6197000, -6725000, -6197000, -8467000, -9172000,
    -8671000, -9192000, -8683000, -9904000, -9364000, -8670000, -6197000 };

  double dv57[7];

  /* Calculate the pressure, temperature and composition of the combustion gas  */
  /* from given internal energy, volume and mass of each gas specie.  */
  /*  */
  /*    The calculation of the internal energy is based on the NASA 7 */
  /*    coefficient polynomial and T is found by using Newton-Raphson method. */
  /*    The gas is assumed to be idea gas. */
  /*  */
  /*    Input */
  /*        N : No. moles of each gas specie (kmol) */
  /*            N(1) = N_H;   N(2) = N_O;   N(3) = N_N;   N(4) = N_H2;   */
  /*            N(5) = N_OH;  N(6) = N_CO;  N(7) = N_NO;  N(8) = N_O2;   */
  /*            N(9) = N_H2O; N(10) = N_CO2;N(11) = N_N2; N(12) = N_Ar */
  /*        E : Internal energy of the gas */
  /*        V : Volume of the gas */
  /*    Output */
  /*        P : Pressure (Pa) */
  /*        T : Temperature (K) */
  /*        rho : Density (kg/m3) */
  /*        x :  Mole fraction of each gas specie */
  /*            x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;  x(5) = x_OH; */
  /*            x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;  x(9) = x_H2O; x(10) = x_CO2; */
  /*            x(11) = x_N2; x(12) = x_Ar */
  /*  */
  /*    Atomic weight calculation from NIST atomic weights */
  /*    Ref : http://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl */
  /*  */
  /*    The NASA 7-coefficients are obtained from the reference: */
  /*    Burcat, A., B. Ruscic, et al. (2005). Third millenium ideal gas and  */
  /*        condensed phase thermochemical database for combustion with updates  */
  /*        from active thermochemical tables, Argonne National Laboratory  */
  /*        Argonne, IL. */
  /*  */
  /*  Created by Kevin Koosup Yum on 29 June */
  /* % */
  /*  in J/kmol/K */
  /* % Calculate the composition in mole fraction and gas constant */
  y = N[0];
  for (k = 0; k < 11; k++) {
    y += N[k + 1];
  }

  d10 = 0.0;
  for (k = 0; k < 12; k++) {
    b_x = N[k] / y;
    d10 += b_x * b[k];
    x[k] = b_x;
  }

  /*  in kg/kmol */
  R = 8314.4621 / d10;

  /*  in J/kg/K */
  /* % Calculate the temperature */
  *T = T_prev;
  dT = 0.0;
  T_err = 1.0;
  while (T_err > 0.001) {
    *T -= dT;
    T_sq = *T * *T;
    T_cb = rt_powd_snf(*T, 3.0);
    T_qt = rt_powd_snf(*T, 4.0);
    if (*T >= 1000.0) {
      /* Valid upto  */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      /* 1000~6000K */
      for (k = 0; k < 7; k++) {
        a_CO2[k] = dv36[k];
        a_CO[k] = dv37[k];
        a_O2[k] = dv38[k];
        a_H2[k] = dv39[k];
        a_H2O[k] = dv40[k];
        a_OH[k] = dv41[k];
        a_O[k] = dv42[k];
        a_N2[k] = dv43[k];
        a_N[k] = dv44[k];
        a_NO[k] = dv45[k];
      }

      /* 1000~6000K     */
    } else {
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K     */
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K */
      /* 300~1000K */
      for (k = 0; k < 7; k++) {
        a_CO2[k] = dv46[k];
        a_CO[k] = dv47[k];
        a_O2[k] = dv48[k];
        a_H2[k] = dv49[k];
        a_H2O[k] = dv50[k];
        a_OH[k] = dv51[k];
        a_O[k] = dv52[k];
        a_N2[k] = dv53[k];
        a_N[k] = dv54[k];
        a_NO[k] = dv55[k];
      }

      /* 300~1000K */
    }

    /*  (J/kmol / J/kmol/K) */
    /* J/kmol */
    y = R * *T;
    dv56[0] = 1.0;
    dv56[1] = *T / 2.0;
    dv56[2] = T_sq / 3.0;
    dv56[3] = T_cb / 4.0;
    dv56[4] = T_qt / 5.0;
    dv56[5] = 1.0 / *T;
    dv56[6] = 0.0;
    d11 = 0.0;
    for (k = 0; k < 7; k++) {
      a_H[12 * k] = b_a_H[k];
      a_H[1 + 12 * k] = a_O[k];
      a_H[2 + 12 * k] = a_N[k];
      a_H[3 + 12 * k] = a_H2[k];
      a_H[4 + 12 * k] = a_OH[k];
      a_H[5 + 12 * k] = a_CO[k];
      a_H[6 + 12 * k] = a_NO[k];
      a_H[7 + 12 * k] = a_O2[k];
      a_H[8 + 12 * k] = a_H2O[k];
      a_H[9 + 12 * k] = a_CO2[k];
      a_H[10 + 12 * k] = a_N2[k];
      a_H[11 + 12 * k] = a_Ar[k];
      a_gas[k] = 0.0;
      for (i12 = 0; i12 < 12; i12++) {
        a_gas[k] += x[i12] * a_H[i12 + 12 * k];
      }

      d11 += y * a_gas[k] * dv56[k];
    }

    d12 = 0.0;
    d13 = 0.0;
    for (k = 0; k < 12; k++) {
      d12 += a[k] * x[k];
      d13 += (double)b_a[k] * x[k];
    }

    dv57[0] = 1.0;
    dv57[1] = *T;
    dv57[2] = T_sq;
    dv57[3] = T_cb;
    dv57[4] = T_qt;
    dv57[5] = 0.0;
    dv57[6] = 0.0;
    y = 0.0;
    for (k = 0; k < 7; k++) {
      y += a_gas[k] * dv57[k];
    }

    dT = (((d11 - (R * d12 + d13 / d10)) - R * *T) - E / m) / (R * (y - 1.0));
    T_err = fabs(dT) / *T;
  }

  /* % Calculate the pressure */
  *P = m / V * R * *T;
}

/* End of code generation (GetPTx.cpp) */
