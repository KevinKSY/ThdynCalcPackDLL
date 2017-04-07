/* Example C++ DLL for 20-sim */
//#include <windows.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "subroutines\rt_nonfinite.h"
#include "subroutines\GetAirDensity.h"
#include "subroutines\GetAirThermalConduct.h"
#include "subroutines\GetAirViscosity.h"
#include "subroutines\GetCompCombGas.h"
#include "subroutines\GetCorrAirComp.h"
#include "subroutines\GetDensityHCVapor.h"
#include "subroutines\GetDiffusivityHCVaporToAir.h"
#include "subroutines\GetEquilGrill.h"
#include "subroutines\GetEquilOlikara.h"
#include "subroutines\GetFuelPropertyN_Dodecane.h"
#include "subroutines\GetHTCoeffHTX.h"
#include "subroutines\GetIdealNozzleFlow.h"
#include "subroutines\GetIdealNozzleFlowPTF.h"
#include "subroutines\GetMEMbZach.h"
#include "subroutines\GetPTF.h"
#include "subroutines\GetPTFV1.h"
#include "subroutines\GetPTx.h"
#include "subroutines\GetPTFSimple.h"
#include "subroutines\GetTFromPhF.h"
#include "subroutines\GetT_atm_p.h"
#include "subroutines\GetThdynCombGasZach.h"
#include "subroutines\GetThdynCombGasZachV1.h"
#include "subroutines\GetThermalPropertyHCVaporReal.h"
#include "subroutines\GetThermoDynProp.h"
#include "subroutines\GetThermoDynPropPartial.h"
#include "subroutines\GetTotalStaticPT.h"
#include "subroutines\GetViscosityHCVapor.h"
#include "subroutines\compressor_calc_PTF.h"
#include "subroutines\ThdynPack_terminate.h"
#include "subroutines\ThdynPack_initialize.h"

#define DLLEXPORT __declspec( dllexport )

using namespace std;

ofstream outputStream;

#ifdef _MSC_VER
#define snprintf _snprintf_s
#endif

extern "C"

{
/*
	// Declaration of fortran routines
	void COMRES_MOD(double *rpu, double *rpd, double *rfu, double *rfd, double *rtu, double *rtd, double *romegat,
		double *rmedium, double *rfs, double *rmomc, double *rdmc, double *rdmco, double *rdmfc,
		double *rdmfco, double *rdeu, double *rded, double *rvr, double *etaic);
		*/
	char g_lasterrormessage[255]; /* Used to store a DLL error message
								  for transfer to 20-sim */
	const char* g_modelpath;
	/**
	* @param inarr   This double array contains all inputs that will be
	*                send from 20-sim to the other side
	* @param inputs  20-sim tells the dll how many elements inarr[]
	*                contains.
	* @param outarr  Result from this dll function that will be returned
	*                to 20-sim
	* @param outputs 20-sim tells the dll how many elements it expects
	*                (and allocated) in outarr.
	* @param major   1=major integration step, 0=minor step (e.g. an
	*                intermediate integration method step in Runge Kutta
	*                4)
	**/

	DLLEXPORT int getThdynCombGas(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		real_T p, T, F, fs, T_L, T_H, FC[4], xAir[12];
		int16_T	mode;
		real_T R, h, s, u, RF, RP, RT, uF, uP, uT, sF, sP, sT, Cp, Cv, K, x[12], rho;

		real_T R1, Cp1, Cv1, u1, h1, s1, rho1, deltaF;

		p = inarr[0];
		T = inarr[1];
		F = inarr[2];
		fs = inarr[3];
		mode = (const int) inarr[4];
		if (mode == 2)
		{
			T_L = inarr[5];		T_H = inarr[6];
			for (int i = 0; i < 4; i++) {
				FC[i] = inarr[7 + i];
			}
			for (int i = 0; i < 12; i++) {
				xAir[i] = inarr[11 + i];
			}
		}

		switch (mode)
		{
		case 1:		//using Zacharias methods
			GetThdynCombGasZachV1(p, T, F, fs, &R, &h, &s, &u, &RF, &RP, &RT, &uF, &uP, &uT, &sF, &sP, &sT, &Cp, &Cv, &K);
			break;
		case 2:		//using Chemical Equilibrum (Grill) without partial derivatives
			GetCompCombGas(p, T, F, T_L, T_H, FC, xAir, x);
			GetThermoDynProp(p, T, x, &R, &Cp, &Cv, &u, &h, &s, &rho);
			K = Cp / Cv;
			RF = 0;		RP = 0;		RT = 0;
			uF = 0;		uP = 0;		uT = 0;
			sF = 0;		sP = 0;		sT = 0;
			break;
		case 3:		//using Chemical Equilibrum (Grill) with partial derivatives
			GetCompCombGas(p, T, F, T_L, T_H, FC, xAir, x);
			GetThermoDynProp(p, T, x, &R, &Cp, &Cv, &u, &h, &s, &rho);
			deltaF = min(F*(F/(F+0.002) - 1),-0.001);
			GetCompCombGas(p+5, T+1, F + deltaF, T_L, T_H, FC, xAir, x);
			GetThermoDynProp(p, T, x, &R1, &Cp1, &Cv1, &u1, &h1, &s1, &rho1);
			RF = (R1 - R) / deltaF;		RP = (R1 - R) / 5;		RT = (R1 - R) / 1;
			uF = (u1 - u) / deltaF;		uP = (u1 - u) / 5;		uT = (u1 - u) / 1;
			sF = (s1 - s) / deltaF;		sP = (s1 - s) / 5;		sT = (s1 - s) / 1;
			break;
		default:
			break;
		}

		outarr[0] = R;		outarr[1] = h;		outarr[2] = s;		outarr[3] = u;
		outarr[4] = RF;		outarr[5] = RP;		outarr[6] = RT;		outarr[7] = uF;
		outarr[8] = uP;		outarr[9] = uT;		outarr[10] = sF;	outarr[11] = sP;
		outarr[12] = sT;	outarr[13] = Cp;	outarr[14] = Cv;	outarr[15] = K;

		return 0; // Success
	}

	DLLEXPORT int getpTF(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		real_T m, E, mb, V, TPrev, fs;
		real_T p, T, F;

		m = inarr[0];		E = inarr[1];		mb = inarr[2];
		V = inarr[3];		TPrev = inarr[4];	fs = inarr[5];


		GetPTF(m, E, mb, V, TPrev, fs, &p, &T, &F);

		outarr[0] = p;		outarr[1] = T;		outarr[2] = F;

		return 0; // Success
	}



	DLLEXPORT int getpTFV1(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		real_T m, E, mb, V, TPrev, RPrev, uPrev, CvPrev, fs;
		real_T p, T, F;

		m = inarr[0];		E = inarr[1];		mb = inarr[2];
		V = inarr[3];		TPrev = inarr[4];	RPrev = inarr[5];
		uPrev = inarr[6];	CvPrev = inarr[7];	fs = inarr[8];

		GetPTFV1(m, mb, E, V, TPrev, RPrev, uPrev, CvPrev, fs, &p, &T, &F);

		outarr[0] = p;		outarr[1] = T;		outarr[2] = F;

		return 0; // Success
	}

	DLLEXPORT int getpTFSimple(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		real_T m, E, mb, V, PPrev, TPrev, fs;
		real_T p, T, F;

		m = inarr[0];		E = inarr[1];		mb = inarr[2];
		V = inarr[3];		PPrev = inarr[4];	TPrev = inarr[5];
		fs = inarr[6];

		GetPTFSimple(m, mb, E, V, PPrev, TPrev, fs, &p, &T, &F);

		outarr[0] = p;		outarr[1] = T;		outarr[2] = F;

		return 0; // Success
	}

	DLLEXPORT int getTFromPhF(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		real_T p, h, F, fs;

		p = inarr[0];		h = inarr[1];		F = inarr[2];		fs = inarr[3];
		outarr[0] = GetTFromPhF(p, h, F, fs);

		return 0; // Success
	}

	DLLEXPORT int getIdealNozzleFlow(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		double Cd, A, p_in, p_out, T_in, F_in, fs;
		double m_dot, H_dot, m_b_dot;

		Cd = inarr[0];		A = inarr[1];		p_in = inarr[2];		p_out = inarr[3];
		T_in = inarr[4];	F_in = inarr[5];	fs = inarr[6];

		GetIdealNozzleFlowPTF(Cd, A, p_in, p_out, T_in, F_in, fs, &m_dot, &H_dot, &m_b_dot);

		outarr[0] = m_dot;		outarr[1] = H_dot;		outarr[2] = m_b_dot;

		return 0; // Success
	}


	DLLEXPORT int compressorPTF(double *inarr, int inputs, double *outarr, int outputs, int major)
	{

		double pu, Tu, Fu, pd, Td, Fd, omegat, flow_prev, eta_prev, fs;
		double dmu, deu, dmbu, dmd, ded, dmbd, Tqt, eta_ic;

		pu = inarr[0];		Tu = inarr[1];		Fu = inarr[2];
		pd = inarr[3];		Td = inarr[4];		Fd = inarr[5];
		omegat = inarr[6];	flow_prev = inarr[7];	eta_prev = inarr[8];
		fs = inarr[9];


		compressor_calc_PTF(&pu, &Tu, &Fu, &pd, &Td, &Fd, &omegat, &dmu, &deu,
			&dmbu, &dmd, &ded, &dmbd, &Tqt, &eta_ic, &flow_prev, &eta_prev, &fs, 1);

		outarr[0] = dmu;		outarr[1] = deu;		outarr[2] = dmbu;
		outarr[3] = dmd;		outarr[4] = ded;		outarr[5] = dmbd;
		outarr[6] = Tqt;		outarr[7] = eta_ic;

		return 0; // Success
	}

/*
	DLLEXPORT int ice_comres(double *inarr, int inputs, double *outarr, int outputs, int major)

	{
		double pu, pd, fu, fd, tu, td, omegat, medium, fs;
		double momc, dmc, dmco, dmfc, dmfco, deu, ded, vr, etaic;

		pu = inarr[0]; pd = inarr[1];
		fu = inarr[2]; fd = inarr[3];
		tu = inarr[4]; td = inarr[5];
		omegat = inarr[6]; medium = inarr[7];
		fs = inarr[8];

		COMRES_MOD(&pu, &pd, &fu, &fd, &tu, &td, &omegat, &medium, &fs, &momc, &dmc, &dmco, &dmfc, &dmfco, &deu, &ded, &vr, &etaic);


		outarr[0] = dmc;		outarr[1] = deu;		outarr[2] = dmfc;
		outarr[3] = dmco;		outarr[4] = ded;		outarr[5] = dmfco;
		outarr[6] = momc;		outarr[7] = etaic;

		return 0;
	}
*/
	DLLEXPORT int getHTCoeffHTX(double *inarr, int inputs, double *outarr, int outputs, int major)
	{
		double p_in, dm, T_mean, D, A;
		double alpha;

		p_in = inarr[0];		dm = inarr[1];		T_mean = inarr[2];
		D = inarr[3];			A = inarr[4];

		alpha = GetHTCoeffHTX(p_in,dm,T_mean,D,A);

		outarr[0] = alpha;

		return 0; // Success
	}


	/****** Initialization and cleanup ******/
	/* Note 1:
	*   The Initialize(), InitializeRun(), Terminate() and TerminateRun()
	*   functions are optional.
	*   Implement them when you need to initialize something before the
	*   actual experiment is started and to cleanup/reset your DLL
	*   functionality for a next run.
	* Note 2:
	*   When these functions are implemented, the "continue run"
	*   functionality in 20-sim is disabled.
	*/

	/**
	* Initialize() [optional]
	*
	* This function is called by the 20-sim simulator BEFORE starting the
	* simulation experiment (and only once in a multiple run experiment)
	* to initialize the dll properly.
	*/

	DLLEXPORT int Initialize()
	{
		outputStream.open("c:\\temp\\data.log");
		return 0; // Indicate that the dll was initialized successfully.
	}

	/**
	* InitializeRun() [optional]
	*
	* This function is called by the 20-sim simulator BEFORE starting the
	* simulation experiment (and only once in a multiple run experiment)
	* to initialize the dll properly.
	*/

	DLLEXPORT int InitializeRun()
	{
		/* Clear lasterrormessage before every run. */
		snprintf(g_lasterrormessage, 255, "");
		return 0; /* Indicate that the dll was initialized successfully. */
	}

	/**
	* TerminateRun() [optional]
	*
	* This function is called by 20-sim after each finished run
	*/

	DLLEXPORT int TerminateRun()
	{
		/* Cleanup / reset your DLL here for the next run
		* (e.g. in a multiple run experiment)
		*/
		return 0; // Indicate that the dll was terminated successfully.
	}

	/**
	* Terminate() [optional]
	*
	* This function is called by 20-sim on a DLL unload
	*/

	DLLEXPORT int Terminate()
	{
		outputStream.close();
		return 0; // Indicate that the DLL was terminated successfully.
	}

	/**
	* LastErrorMessage() [optional]
	* Used by 20-sim to fetch a string with the last error that occurred
	* within the DLL
	* @return A char pointer to a string indicating the error message
	*/
	DLLEXPORT char* LastErrorMessage()
	{
		return g_lasterrormessage;
	}

	/**
	* RegisterModelPath() [optional]
	* This function is called by 20-sim before Initialize() to learn the
	* DLL where the model is located. It can be used e.g. to find data
	* files stored in the same folder as the model.
	*
	* @param modelPath char pointer to the model directory
	* @return 0 if parameter is set successfully, 1 if not successful.
	*/

	DLLEXPORT int RegisterModelPath(const char * modelPath)
	{
		g_modelpath = modelPath;
		return 0;
	}
}
