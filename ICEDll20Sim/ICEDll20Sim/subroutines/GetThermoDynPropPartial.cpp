/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetThermoDynPropPartial.cpp
 *
 * Code generation for function 'GetThermoDynPropPartial'
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
void GetThermoDynPropPartial(double, double T, const double x[12], const double
  dx[36], double *R, double *h, double *s, double *u, double *RP, double *RT,
  double *RF, double *uP, double *uT, double *uF, double *sP, double *sT, double
  *sF, double *Cp, double *Cv)
{
  double T_sq;
  double T_cb;
  double T_qt;
  double d18;
  int i14;
  static const double b[12] = { 1.00794, 15.9994, 14.0067, 2.01588, 17.00734,
    28.0101, 30.0061, 31.9988, 18.01528, 44.0095, 28.0134, 39.948 };

  double dR[3];
  int i;
  double dMW[3];
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
  static const double dv58[7] = { 4.6365111, 0.0027414569, -9.9589759E-7,
    1.6038666E-10, -9.1619857E-15, -49024.904, -1.9348955 };

  static const double dv59[7] = { 3.0484859, 0.0013517281, -4.8579405E-7,
    7.8853644E-11, -4.6980746E-15, -14266.117, 6.0170977 };

  static const double dv60[7] = { 3.66096083, 0.000656365523, -1.41149485E-7,
    2.05797658E-11, -1.29913248E-15, -1215.97725, 3.41536184 };

  static const double dv61[7] = { 2.9328305, 0.00082659802, -1.4640057E-7,
    1.5409851E-11, -6.8879615E-16, -813.05582, -1.0243164 };

  static const double dv62[7] = { 2.6770389, 0.0029731816, -7.7376889E-7,
    9.4433514E-11, -4.2689991E-15, -29885.894, 6.88255 };

  static const double dv63[7] = { 2.83853033, 0.00110741289, -2.94000209E-7,
    4.20698729E-11, -2.4228989E-15, 3697.80808, 5.84494652 };

  static const double dv64[7] = { 2.54363697, -2.73162486E-5, -4.1902952E-9,
    4.95481845E-12, -4.79553694E-16, 29226.012, 4.92229457 };

  static const double dv65[7] = { 2.95257637, 0.0013969004, -4.92631603E-7,
    7.86010195E-11, -4.60755204E-15, -923.948688, 5.87188762 };

  static const double dv66[7] = { 2.4159429, 0.00017489065, -1.1902369E-7,
    3.0226244E-11, -2.0360983E-15, 56133.775, 4.6496095 };

  static const double dv67[7] = { 3.26071234, 0.00119101135, -4.29122646E-7,
    6.94481463E-11, -4.03295681E-15, 9921.43132, 6.36900518 };

  static const double dv68[7] = { 2.356813, 0.0089841299, -7.1220632E-6,
    2.4573008E-9, -1.4288548E-13, -48371.971, 9.9009035 };

  static const double dv69[7] = { 3.5795335, -0.00061035369, 1.0168143E-6,
    9.0700586E-10, -9.0442449E-13, -14344.086, 3.5084093 };

  static const double dv70[7] = { 3.78245636, -0.00299673415, 9.847302E-6,
    -9.68129508E-9, 3.24372836E-12, -1063.94356, 3.65767573 };

  static const double dv71[7] = { 2.3443029, 0.0079804248, -1.9477917E-5,
    2.0156967E-8, -7.3760289E-12, -917.92413, 0.68300218 };

  static const double dv72[7] = { 4.1986352, -0.0020364017, 6.5203416E-6,
    -5.4879269E-9, 1.771968E-12, -30293.726, -0.84900901 };

  static const double dv73[7] = { 3.99198424, -0.00240106655, 4.61664033E-6,
    -3.87916306E-9, 1.36319502E-12, 3368.89836, -0.103998477 };

  static const double dv74[7] = { 3.1682671, -0.00327931884, 6.64306396E-6,
    -6.12806624E-9, 2.11265971E-12, 29122.2592, 2.05193346 };

  static const double dv75[7] = { 3.53100528, -0.000123660988, -5.02999433E-7,
    2.43530612E-9, -1.40881235E-12, -1046.97628, 2.96747038 };

  static const double dv76[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, 56104.638, 4.1939088
  };

  static const double dv77[7] = { 4.21859896, -0.00463988124, 1.10443049E-5,
    -9.34055507E-9, 2.80554874E-12, 9845.09964, 2.28061001 };

  static const double a_H[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, 25473.66, -0.44668285
  };

  double A[84];
  static const double a_Ar[7] = { 2.5, 0.0, 0.0, 0.0, 0.0, -745.375, 4.3796749 };

  double da_gas[21];
  int i15;
  double T_arr_Cp[7];
  double c;
  double T_arr_h[7];
  double y;
  static const double a[12] = { 26219.035, 29968.7009, 56850.013, 0.0, 4486.1538,
    -13293.628, 10977.0882, 0.0, -29084.817, -47328.105, 0.0, 0.0 };

  double b_y;
  static const int b_b[12] = { -6197000, -6725000, -6197000, -8467000, -9172000,
    -8671000, -9192000, -8683000, -9904000, -9364000, -8670000, -6197000 };

  double b_dx[3];
  double c_dx[3];
  double dh_298_0[3];
  static const double c_b[12] = { 26219.035, 29968.7009, 56850.013, 0.0,
    4486.1538, -13293.628, 10977.0882, 0.0, -29084.817, -47328.105, 0.0, 0.0 };

  static const int b_a[12] = { -6197000, -6725000, -6197000, -8467000, -9172000,
    -8671000, -9192000, -8683000, -9904000, -9364000, -8670000, -6197000 };

  double dv78[7];

  /* Calculate the specific thermodynamic properties of the gas and  */
  /* partial derivatives of them based on the pressure, temperature and the  */
  /* composition based on the 7-coefficient NASA polynomials. Valid in the  */
  /* temperature range 300~6000K. */
  /*    Input */
  /*        P : Pressure in Pa */
  /*        T : Temperature in Kelvin */
  /*        x : Composition of the gas */
  /*            x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;   */
  /*            x(5) = x_OH;  x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;   */
  /*            x(9) = x_H2O; x(10) = x_CO2;x(11) = x_N2; x(12) = x_Ar */
  /*    Output */
  /*        R : Gas constant (J/kgK) */
  /*        h : Specific enthalpy (J/kg) */
  /*        s : Specific entropy (J/kg/K) */
  /*        u : Specific internal energy (J/kg) */
  /*        RP : partial derivative(PD) of R w.r.t. pressure  */
  /*        RT : partial derivative(PD) of R w.r.t. temperature  */
  /*        RF : partial derivative(PD) of R w.r.t. F */
  /*        uP : partial derivative(PD) of u w.r.t. pressure  */
  /*        uT : partial derivative(PD) of u w.r.t. temperature  */
  /*        uF : partial derivative(PD) of u w.r.t. F */
  /*        sP : partial derivative(PD) of s w.r.t. pressure  */
  /*        sT : partial derivative(PD) of s w.r.t. temperature  */
  /*        sF : partial derivative(PD) of s w.r.t. F */
  /*        Cp : Specific heat capacity at constant pressure (J/kg/K)  */
  /*        Cv : Specific heat capacity at constant volume (J/kg/K) */
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
  T_sq = T * T;
  T_cb = T_sq * T;
  T_qt = T_cb * T;

  /*  in J/kmol/K */
  /* % Calculate R */
  /*  kg/kmol */
  d18 = 0.0;
  for (i14 = 0; i14 < 12; i14++) {
    d18 += x[i14] * b[i14];
  }

  /*  in kg/kmol */
  /*  Partial derivative of MW in p,T,F */
  *R = 8314.4621 / d18;

  /*  in J/kg/K */
  for (i = 0; i < 3; i++) {
    dMW[i] = 0.0;
    for (i14 = 0; i14 < 12; i14++) {
      dMW[i] += dx[i14 + 12 * i] * b[i14];
    }

    dR[i] = -*R * dMW[i] / d18;
  }

  *RP = dR[0];
  *RT = dR[1];
  *RF = dR[2];

  /* % */
  if (T >= 1000.0) {
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
    for (i14 = 0; i14 < 7; i14++) {
      a_CO2[i14] = dv58[i14];
      a_CO[i14] = dv59[i14];
      a_O2[i14] = dv60[i14];
      a_H2[i14] = dv61[i14];
      a_H2O[i14] = dv62[i14];
      a_OH[i14] = dv63[i14];
      a_O[i14] = dv64[i14];
      a_N2[i14] = dv65[i14];
      a_N[i14] = dv66[i14];
      a_NO[i14] = dv67[i14];
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
    for (i14 = 0; i14 < 7; i14++) {
      a_CO2[i14] = dv68[i14];
      a_CO[i14] = dv69[i14];
      a_O2[i14] = dv70[i14];
      a_H2[i14] = dv71[i14];
      a_H2O[i14] = dv72[i14];
      a_OH[i14] = dv73[i14];
      a_O[i14] = dv74[i14];
      a_N2[i14] = dv75[i14];
      a_N[i14] = dv76[i14];
      a_NO[i14] = dv77[i14];
    }

    /* 300~1000K */
  }

  for (i14 = 0; i14 < 7; i14++) {
    A[12 * i14] = a_H[i14];
    A[1 + 12 * i14] = a_O[i14];
    A[2 + 12 * i14] = a_N[i14];
    A[3 + 12 * i14] = a_H2[i14];
    A[4 + 12 * i14] = a_OH[i14];
    A[5 + 12 * i14] = a_CO[i14];
    A[6 + 12 * i14] = a_NO[i14];
    A[7 + 12 * i14] = a_O2[i14];
    A[8 + 12 * i14] = a_H2O[i14];
    A[9 + 12 * i14] = a_CO2[i14];
    A[10 + 12 * i14] = a_N2[i14];
    A[11 + 12 * i14] = a_Ar[i14];
    a_CO2[i14] = 0.0;
    for (i = 0; i < 12; i++) {
      a_CO2[i14] += x[i] * A[i + 12 * i14];
    }
  }

  for (i14 = 0; i14 < 3; i14++) {
    for (i = 0; i < 7; i++) {
      da_gas[i14 + 3 * i] = 0.0;
      for (i15 = 0; i15 < 12; i15++) {
        da_gas[i14 + 3 * i] += dx[i15 + 12 * i14] * A[i15 + 12 * i];
      }
    }
  }

  /* % Calculate Cp & Cv */
  T_arr_Cp[0] = 1.0;
  T_arr_Cp[1] = T;
  T_arr_Cp[2] = T_sq;
  T_arr_Cp[3] = T_cb;
  T_arr_Cp[4] = T_qt;
  T_arr_Cp[5] = 0.0;
  T_arr_Cp[6] = 0.0;

  /* k = x ./ M_mw'; */
  /* a_gas_Cp = k*A; */
  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    c += *R * a_CO2[i14] * T_arr_Cp[i14];
  }

  *Cp = c;

  /* J/kmol/K */
  *Cv = c - *R;

  /* J/kmol/K */
  /* % Calculate h and u */
  /*  (J/kmol / J/kmol/K) */
  /* J/kmol */
  T_arr_h[0] = T;
  T_arr_h[1] = T_sq / 2.0;
  T_arr_h[2] = T_cb / 3.0;
  T_arr_h[3] = T_qt / 4.0;
  T_arr_h[4] = T_qt * T / 5.0;
  T_arr_h[5] = 1.0;
  T_arr_h[6] = 0.0;

  /*            x(1) = x_H;   x(2) = x_O;   x(3) = x_N;   x(4) = x_H2;   */
  /*            x(5) = x_OH;  x(6) = x_CO;  x(7) = x_NO;  x(8) = x_O2;   */
  /*            x(9) = x_H2O; x(10) = x_CO2;x(11) = x_N2; x(12) = x_Ar */
  y = 0.0;
  for (i14 = 0; i14 < 12; i14++) {
    y += a[i14] * x[i14];
  }

  b_y = 0.0;
  for (i14 = 0; i14 < 12; i14++) {
    b_y += x[i14] * (double)b_b[i14];
  }

  c = d18 * d18;
  for (i14 = 0; i14 < 3; i14++) {
    b_dx[i14] = 0.0;
    c_dx[i14] = 0.0;
    for (i = 0; i < 12; i++) {
      b_dx[i14] += dx[i + 12 * i14] * c_b[i];
      c_dx[i14] += dx[i + 12 * i14] * (double)b_b[i];
    }

    dh_298_0[i14] = (dR[i14] * y + *R * b_dx[i14]) + (c_dx[i14] * d18 - b_y *
      dMW[i14]) / c;
  }

  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    c += a_CO2[i14] * T_arr_h[i14];
  }

  b_y = 0.0;
  y = 0.0;
  for (i14 = 0; i14 < 12; i14++) {
    b_y += a[i14] * x[i14];
    y += (double)b_a[i14] * x[i14];
  }

  *h = *R * c - (*R * b_y + y / d18);
  *u = *h - *R * T;
  d18 = 0.0;
  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += a_CO2[i14] * T_arr_h[i14];
    c += da_gas[3 * i14] * T_arr_h[i14];
  }

  *uP = ((dR[0] * d18 + *R * c) - dh_298_0[0]) - dR[0] * T;
  d18 = 0.0;
  c = 0.0;
  b_y = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += a_CO2[i14] * T_arr_h[i14];
    c += da_gas[1 + 3 * i14] * T_arr_h[i14];
    b_y += *R * a_CO2[i14] * T_arr_Cp[i14];
  }

  *uT = ((((dR[1] * d18 + *R * c) + b_y) - dh_298_0[1]) - *R) - dR[1] * T;
  d18 = 0.0;
  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += a_CO2[i14] * T_arr_h[i14];
    c += da_gas[2 + 3 * i14] * T_arr_h[i14];
  }

  *uF = ((dR[2] * d18 + *R * c) - dh_298_0[2]) - dR[2] * T;

  /* % Calculate s */
  T_arr_Cp[0] = log(T);
  T_arr_Cp[1] = T;
  T_arr_Cp[2] = T_sq / 2.0;
  T_arr_Cp[3] = T_cb / 3.0;
  T_arr_Cp[4] = T_qt / 4.0;
  T_arr_Cp[5] = 0.0;
  T_arr_Cp[6] = 1.0;
  d18 = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += *R * a_CO2[i14] * T_arr_Cp[i14];
  }

  *s = d18;
  d18 = 0.0;
  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += dR[0] * a_CO2[i14] * T_arr_Cp[i14];
    c += *R * da_gas[3 * i14] * T_arr_Cp[i14];
  }

  *sP = d18 + c;
  d18 = 0.0;
  c = 0.0;
  dv78[0] = 1.0 / T;
  dv78[1] = 1.0;
  dv78[2] = T;
  dv78[3] = T_sq;
  dv78[4] = T_cb;
  dv78[5] = 0.0;
  dv78[6] = 0.0;
  b_y = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += dR[1] * a_CO2[i14] * T_arr_Cp[i14];
    c += *R * da_gas[1 + 3 * i14] * T_arr_Cp[i14];
    b_y += *R * a_CO2[i14] * dv78[i14];
  }

  *sT = (d18 + c) + b_y;
  d18 = 0.0;
  c = 0.0;
  for (i14 = 0; i14 < 7; i14++) {
    d18 += dR[2] * a_CO2[i14] * T_arr_Cp[i14];
    c += *R * da_gas[2 + 3 * i14] * T_arr_Cp[i14];
  }

  *sF = d18 + c;

  /* % Calculate rho */
}

/* End of code generation (GetThermoDynPropPartial.cpp) */
