/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GetDiffusivityHCVaporToAir.cpp
 *
 * Code generation for function 'GetDiffusivityHCVaporToAir'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "ThdynPack_rtwutil.h"

/* Function Definitions */
double GetDiffusivityHCVaporToAir(double p, double T, double MW, double C,
  double H, double O, double N, boolean_T Aromatic)
{
  double D_v;
  double a;

  /* The function calculates the diffusivity of the binary gas system (HC vapor */
  /* to air) in the low pressure according to procedure 13B1.2 in API Technical  */
  /* Book : Petroleum Refining . (<3.45 MPa)  */
  /*  Input */
  /*    p : pressure in Pa */
  /*    T : Temperature in K */
  /*    MW : Molecular weight of fuel in kg/kmol */
  /*    C : Number of carbon in the fuel chemical formula */
  /*    H : Number of hydrogen in the fuel chemical formula */
  /*    O : Number of oxygen in the fuel chemical formula */
  /*    N : Number of nitrogen in the fuel chemical formula */
  /*    Aromatic : 1 if aromatic, 0 otherwise */
  /*  Output */
  /*    D_v : Diffusivity in m2/sec */
  /*  Ref */
  /*    Technical Data Book - Petroleum Refining(1985) Americal Petroleum Institute. */
  /*  Created by Kevin Koosup Yum, 18 September 2013 */
  /* % Diffusivity at low pressure  */
  a = rt_powd_snf((((C * 16.5 + H * 1.98) + O * 5.48) + N * 5.69) - (double)
                  Aromatic * 20.2, 0.3333) + 2.7186621817323884;
  D_v = 0.01015 * (rt_powd_snf(T, 1.75) * sqrt(0.034650034650034647 + 1.0 / MW))
    / (p * (a * a));

  /* T_R = T*1.8; */
  /* p_lb = 1.450377e-4*p; */
  /* Sigma = 1.864 - 0.1662e-2*T_R + 0.1036e-5*T_R^2 - 0.2390e-9*T_R^3; */
  /* D_v_1 = 0.00064516*11.339e-6*T^1.5/(p_lb*Sigma); */
  /* %  */
  return D_v;
}

/* End of code generation (GetDiffusivityHCVaporToAir.cpp) */
