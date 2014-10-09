/*
 * GetDiffusivityHCVaporToAir.c
 *
 * Code generation for function 'GetDiffusivityHCVaporToAir'
 *
 * C source code generated on: Tue Mar 25 11:39:07 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "GetCompCombGas_rtwutil.h"

/* Function Definitions */
real_T GetDiffusivityHCVaporToAir(real_T p, real_T T, real_T MW, real_T C,
  real_T H, real_T O, real_T N, boolean_T Aromatic)
{
  real_T D_v;
  real_T c;

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
  c = rt_powd_snf((((C * 16.5 + H * 1.98) + O * 5.48) + N * 5.69) - (real_T)
                  Aromatic * 20.2, 0.3333);
  D_v = 0.01015 * (rt_powd_snf(T, 1.75) * sqrt(0.034650034650034647 + 1.0 / MW))
    / (p * ((c + 2.7186621817323884) * (c + 2.7186621817323884)));

  /* T_R = T*1.8; */
  /* p_lb = 1.450377e-4*p; */
  /* Sigma = 1.864 - 0.1662e-2*T_R + 0.1036e-5*T_R^2 - 0.2390e-9*T_R^3; */
  /* D_v_1 = 0.00064516*11.339e-6*T^1.5/(p_lb*Sigma); */
  /* %  */
  return D_v;
}

/* End of code generation (GetDiffusivityHCVaporToAir.c) */
