
#include "stdafx.h"
#include "GetThermoDynProp.h"
#include "ThdynPack_rtwutil.h"
#include "GetPTx.h"
#include "GetCompCombGas.h"
#include "GetAirDensity.h"
#include "GetAirThermalConduct.h"
#include "GetAirViscosity.h"
#include "GetHTCoeffHTX.h"
#include "GetThdynCombGasZachV1.h"
#include "GetDensityHCVapor.h"
#include "GetDiffusivityHCVaporToAir.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetViscosityHCVapor.h"
#include "GetThdynCombGasZach.h"
#include "GetT_atm_p.h"
#include "GetPTFV1.h"
#include "GetIdealNozzleFlowPTF.h"
#include "GetFuelPropertyN_Dodecane.h"
#include "GetTFromPhF.h"
//#include "compressor_calc_PTF.h"

#define DllExport __declspec( dllexport )


extern "C"
{
// Eksterne FORTRAN-filer som kalles i funksjonene under. Dette er en Prototyping og jeg
// jeg benytter bare *[r]variabel foran alle variablene i FORTRAN kallene. I de virkelige
// kallene benyttes subroutinen med STORE bokstaver og real og integer variable med &-tegn
// 
// Thermodynamiske rutiner:
void TH1TPF(double *rqp, double *rqf,double *rqt, double *rvol, 
			double *rqmed, double *rfs, double *rT, double *rP, double *rF );
void THDYNP(double *rPPIN, double *rTTIN, double *rFFIN, int *iITSW,double *rR,
			double * rCP, double *rCV, double *rU,double *rH, double *rS, double *rK, 
			double *rUP, double *rUT, double *rUF, double *rRP, double *rRT, double *rRF,int *iFAULT);
// ICE - rutiner:
void DMF( double *rcylno,double *rdficyl,double *rnstrok,double *rfiinj,double *rfiep,
		    double *rp,double *rt,double *rf,double *rvol,double *rmedium,double *rfs,double *romega,
		    double *rmqf,double *rhn,double *rcssw,double *rbmepnom,double *romeganom, double *rdmf, double *rdqf,
			int *rcf, double *rfies);
void VALVE( double *rPU, double *rPD, double *rFU, double *rFD, double *rTU, double *rTD, double *rA,
		    double *rRMED, double *rFS, double *rDM, double *rDMO, double *rDF, double *rDFO, double *rDE, double *rDEO);
double VALAI(double *rFID);
double VALAE(double *rFID);
void COMRES_MOD(double *rpu, double *rpd,double *rfu,double *rfd,double *rtu,double *rtd,double *romegat,
			double *rmedium,double *rfs,double *rmomc,double *rdmc,double *rdmco,double *rdmfc,
			double *rdmfco,double *rdeu,double *rded, double *rvr, double *etaic);
void TURBIN(double *rpu,double *rpd,double *rfu,double *rfd,double *rtu,double *rtd,double *romegat,
			double *raturb,double *rrturb,double *rmedium,double *rfs,double *rmomt,double *rdmtu,
			double *rdmtd,double *rdmftu,double *rdmftd,double *rdeu,double *rded);
void FFMAX (double *rfi, double *rFF, double *rFmax);
double RMIP(double *rFI, double *rY);
void PFIMAX(double *rt,double *rfi,double *rp,double *rpmax,double *rfipmax);
void TFIMAX(double *t,double *fi,double *te,double *temax,double *fitemax);
void PTF2X(double *P, double *T, double *F, double *mm, double *nn, double *kk, double *ll, double *X1, double *X2, double *X3, double *X4, double *X5, double *X6, double *X7, double *X8, double *X9, double *X10, double *X11, double *X12, double *X13, int *err);
double CNOPC(double *rFI, double *rY);

DllExport int getThdynCombGas(double *inarr, int inputs, double *outarr, int outputs, int major)
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

DllExport int getAirRho(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T;
	p = inarr[0];	T = inarr[1];
	outarr[0] = GetAirDensity(p, T);
	return 0;
}
DllExport int getViscHCVapor(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, p_CR, T_CR, V_CR, Z_CR, rho_R, MW;
	double mu_v;

	p = inarr[0];		T = inarr[1];
	p_CR = inarr[2];	T_CR = inarr[3];
	V_CR = inarr[4];	Z_CR = inarr[5];
	rho_R = inarr[6];	MW = inarr[7];
	
	mu_v = GetViscosityHCVapor(p, T, p_CR, T_CR, V_CR, Z_CR, rho_R, MW);

	outarr[0] = mu_v;	
	
	return 0;
}
DllExport int getPropHCVapor(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, MW, T_CR, p_CR, W;
	double rho_v, Cp_v, Cv_v, lambda;

	p = inarr[0];		T = inarr[1];
	MW = inarr[2];		T_CR = inarr[3];
	p_CR = inarr[4];	W = inarr[5];
		
	GetThermalPropertyHCVaporReal(p, T, MW, T_CR, p_CR, W, 
		&rho_v, &Cp_v, &Cv_v, &lambda);

	outarr[0] = rho_v;		outarr[1] = Cp_v;
	outarr[2] = Cv_v;		outarr[3] = lambda;
	
	return 0;
}


DllExport int getTatAtmP(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double h, F, T_prev;
	double T;
	h = inarr[0];		F = inarr[1];
	T_prev = inarr[2];

	T = GetT_atm_p(h, F, T_prev);

	outarr[0] = T;

	return 0;
}

DllExport int getPTF(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double m, m_b, E, V, T_prev, R_prev, u_prev, Cv_prev, fs;		
	double P, T, F;
	
	m		= inarr[0];		E		= inarr[1];
	m_b		= inarr[2];		V		= inarr[3];
	T_prev	= inarr[4];		R_prev	= inarr[5];	
	u_prev	= inarr[6];		Cv_prev = inarr[7];		
	fs		= inarr[8];		

	GetPTFV1(m, m_b, E, V, T_prev, R_prev, u_prev, Cv_prev, fs, &P, &T, &F);

	outarr[0] = P;		outarr[1] = T;
	outarr[2] = F;	
	
	return 0;
}

DllExport int getFlowIdealNozzle(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double Cd, A, p_in, p_out, T_in, F_in, fs;		
	double m_dot, h_dot, m_b_dot;
	
	Cd		= inarr[0];		A		= inarr[1];
	p_in	= inarr[2];		p_out	= inarr[3];
	T_in	= inarr[4];		F_in	= inarr[5];		
	fs		= inarr[6];

	GetIdealNozzleFlowPTF( Cd, A, p_in, p_out, T_in, F_in, fs, &m_dot, &h_dot, &m_b_dot);

	outarr[0] = m_dot;		outarr[1] = h_dot;
	outarr[2] = m_b_dot;	
	
	return 0;
}
DllExport int getAirVisc(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double rho, T;
	double mu_a;
	rho = inarr[0];		T = inarr[1];

	mu_a = GetAirViscosity(rho, T);

	outarr[0] = mu_a;

	return 0;
}
DllExport int getAirThConduct(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double rho, T;
	double lambda_a;
	rho = inarr[0];		T = inarr[1];

	lambda_a = GetAirThermalConduct(rho, T);

	outarr[0] = lambda_a;

	return 0;
}
DllExport int getHTCoeffHTX(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, m_dot, T, D, A;
	double alpha;
	
	p = inarr[0];	m_dot = inarr[1];
	T = inarr[2];	D = inarr[3];
	A = inarr[4];	

	alpha = GetHTCoeffHTX(p, m_dot, T, D, A);
	outarr[0] = alpha;

	return 0;
}
DllExport int getFuelPropNDodecane(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T;
	double p_v, rho_l, h_l, Cp_l, h_fg, mu_l, lambda_l, sigma_l;

	p = inarr[0];	T = inarr[1];
	
	GetFuelPropertyN_Dodecane(p, T, &p_v, &rho_l, &h_l, &Cp_l, &h_fg, &mu_l, &lambda_l,
		&sigma_l);

	outarr[0] = p_v;	outarr[1] = rho_l;
	outarr[2] = h_l;	outarr[3] = Cp_l;
	outarr[4] = h_fg;	outarr[5] = mu_l;
	outarr[6] = mu_l;	outarr[7] = lambda_l;

	return 0;
}


/*
DllExport int ice_rohr2(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double inarr_ROHR[12], wiebepara[9];		
	double outarr_ROHR[4], wiebe_para_new[9];
	
	inarr_ROHR[0]	= inarr[0];		inarr_ROHR[1]	= inarr[1];
	inarr_ROHR[2]	= inarr[2];		inarr_ROHR[3]	= inarr[3];
	inarr_ROHR[4]	= inarr[4];		inarr_ROHR[5]	= inarr[5];
	inarr_ROHR[6]	= inarr[6];		inarr_ROHR[7]	= inarr[7];
	inarr_ROHR[8]	= inarr[8];		inarr_ROHR[9]	= inarr[9];
	inarr_ROHR[10]	= inarr[10];	inarr_ROHR[11]	= inarr[11];
	wiebepara[0] = inarr[12];	wiebepara[1] = inarr[13];	
	wiebepara[2] = inarr[14];	wiebepara[3] = inarr[15];	
	wiebepara[4] = inarr[16];	wiebepara[5] = inarr[17];	
	wiebepara[6] = inarr[18];	wiebepara[7] = inarr[19];	
	wiebepara[8] = inarr[20];	

	GetROHRDyn(inarr_ROHR, wiebepara, outarr_ROHR, wiebe_para_new);	
	
	outarr[0] = outarr_ROHR[0];		outarr[1] = outarr_ROHR[1];
	outarr[2] = outarr_ROHR[2];		outarr[3] = outarr_ROHR[3];
	outarr[4] = wiebe_para_new[0];	outarr[5] = wiebe_para_new[1];
	outarr[6] = wiebe_para_new[2];	outarr[7] = wiebe_para_new[3];
	outarr[8] = wiebe_para_new[4];	outarr[9] = wiebe_para_new[5];
	outarr[10] = wiebe_para_new[6];	outarr[11] = wiebe_para_new[7];
	outarr[12] = wiebe_para_new[8];	

	return 0;
}
*/
DllExport int getXCombGas(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, F, T_L, T_H, Fc[4], xAir[12];
	double xCG[12];
	
	p	= inarr[0];		T	= inarr[1];		F	= inarr[2];
	T_L	= inarr[3];		T_H	= inarr[4];		Fc[0] = inarr[5];
	Fc[1] = inarr[6];	Fc[2] = inarr[7];	Fc[3] = inarr[8];
	xAir[0] = inarr[9];				xAir[1] = inarr[10];
	xAir[2] = inarr[11];			xAir[3] = inarr[12];
	xAir[4] = inarr[13];			xAir[5] = inarr[14];
	xAir[6] = inarr[15];			xAir[7] = inarr[16];
	xAir[8] = inarr[17];			xAir[9] = inarr[18];
	xAir[10] = inarr[19];			xAir[11] = inarr[20];

	GetCompCombGas(p, T, F, T_L, T_H, Fc, xAir, xCG);
	
	outarr[0] = xCG[0];	outarr[1] = xCG[1];
	outarr[2] = xCG[2];	outarr[3] = xCG[3];
	outarr[4] = xCG[4];	outarr[5] = xCG[5];
	outarr[6] = xCG[6];	outarr[7] = xCG[7];
	outarr[8] = xCG[8];	outarr[9] = xCG[9];
	outarr[10] = xCG[10];	outarr[11] = xCG[11];

	return 0;
}

DllExport int getThdynPropPTx(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, N[12];		
	double R, Cp, Cv, u, ht, s, rho;
	
	p	= inarr[0];		T	= inarr[1];
	N[0] = inarr[2];	N[1] = inarr[3];
	N[2] = inarr[4];	N[3] = inarr[5];
	N[4] = inarr[6];	N[5] = inarr[7];
	N[6] = inarr[8];	N[7] = inarr[9];
	N[8] = inarr[10];	N[9] = inarr[11];
	N[10] = inarr[12];	N[11] = inarr[13];

	GetThermoDynProp(p, T, N, &R, &Cp, &Cv, &u, &ht, &s, &rho);
	
	outarr[0] = R;		outarr[1] = Cp;
	outarr[2] = Cv;		outarr[3] = u;
	outarr[4] = ht;		outarr[5] = s;
	outarr[6] = rho;

	return 0;
}

DllExport int getPTx(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double m, mb[12], E, V, T_prev;		
	double P, T, x[12];
	
	mb[0]	= inarr[0];		mb[1]	= inarr[1];
	mb[2]	= inarr[2];		mb[3]	= inarr[3];
	mb[4]	= inarr[4];		mb[5]	= inarr[5];
	mb[6]	= inarr[6];		mb[7]	= inarr[7];
	mb[8]	= inarr[8];		mb[9]	= inarr[9];
	mb[10]	= inarr[10];	mb[11]	= inarr[11];

	m		= inarr[12];		E		= inarr[13];
	V		= inarr[14];	T_prev	= inarr[15];

	GetPTx(m, mb, E, V, T_prev, &P, &T, x);

	outarr[0] = P;		outarr[1] = T;
	outarr[2] = x[0];	outarr[3] = x[1];
	outarr[4] = x[2];	outarr[5] = x[3];
	outarr[6] = x[4];	outarr[7] = x[5];
	outarr[8] = x[6];	outarr[9] = x[7];
	outarr[10] = x[8];	outarr[11] = x[9];
	outarr[12] = x[10];	outarr[13] = x[11];
	
	return 0;
}

DllExport int getTFromPhF(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	real_T p, h, F, fs;

	p = inarr[0];		h = inarr[1];		F = inarr[2];		fs = inarr[3];		
	outarr[0] = GetTFromPhF(p, h, F, fs);

	return 0; // Success
}
/*
DllExport int compressorPTF(double *inarr, int inputs, double *outarr, int outputs, int major)
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
// Fortran routines
*/
DllExport int ice_rohr(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double rcylno, dficyl, nstrok, fiinj, fiep, p, t, f, vol, medium, fs, omega, mqf, hn, cssw, bmepnom, omeganom;
	double dmfdt, dqfdt, fies;
	int cf;

	rcylno	= inarr[0];		dficyl	= inarr[1];
	nstrok	= inarr[2];		fiinj	= inarr[3];
	fiep	= inarr[4];		p		= inarr[5];
	t		= inarr[6];		f		= inarr[7];
	vol		= inarr[8];		medium	= inarr[9];
	fs		= inarr[10];	omega	= inarr[11];
	mqf		= inarr[12];	hn		= inarr[13];
	cssw	= inarr[14];	bmepnom	= inarr[15];
	omeganom= inarr[16];	
		
	DMF(&rcylno, &dficyl, &nstrok, &fiinj, &fiep, &p, &t, &f, &vol,&medium, &fs, &omega, &mqf, 
	    &hn, &cssw, &bmepnom, &omeganom, &dmfdt, &dqfdt, &cf, &fies);

	outarr[0] = dmfdt;	outarr[1] = dqfdt;	
	outarr[2] = cf;		outarr[3] = fies;	

	return 0;
}

DllExport int ice_valve(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double pu, pd, fu, fd, tu, td, a, rmed, fs;
	double dm, dmo, df, dfo, de, deo;

	pu		= inarr[0];		pd		= inarr[1];
	fu		= inarr[2];		fd		= inarr[3];
	tu		= inarr[4];		td		= inarr[5];
	a		= inarr[6];		rmed	= inarr[7];
	fs		= inarr[8];		

	VALVE(&pu, &pd, &fu, &fd, &tu, &td, &a, &rmed, &fs, &dm, &dmo, &df, &dfo, &de, &deo);

	return 0;
}
DllExport int ice_valai(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double fi;

	fi		= inarr[0];

	outarr[0]=VALAI(&fi);

	return 0;
}
DllExport int ice_valae(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double fi;

	fi		= inarr[0];

	outarr[0]=VALAE(&fi);

	return 0;
}
DllExport int ice_turbin(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double pu, pd, fu, fd, tu, td, omegat, aturb, rturb, medium, fs;
	double momt, dmtu, dmtd, dmftu, dmftd, deu, ded;

	pu		= inarr[0]; pd		= inarr[1];
	fu		= inarr[2]; fd		= inarr[3];
	tu		= inarr[4]; td		= inarr[5];
	omegat	= inarr[6]; aturb	= inarr[7];
	rturb	= inarr[8];	medium	= inarr[9];
	fs		= inarr[8];

	TURBIN(&pu,&pd,&fu,&fd,&tu,&td,&omegat,&aturb,&rturb,&medium,&fs,
		   &momt,&dmtu,&dmtd,&dmftu,&dmftd,&deu,&ded);

	outarr[0] = momt;
	outarr[1] = dmtu;	outarr[2] = dmtd;
	outarr[3] = dmftu;	outarr[4] = dmftd;
	outarr[5] = deu;	outarr[6] = ded;

	return 0;
}
DllExport int ice_comres(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double pu, pd, fu, fd, tu, td, omegat, medium, fs;
	double momc, dmc, dmco, dmfc, dmfco, deu, ded, vr, etaic;

	pu		= inarr[0]; tu		= inarr[1];
	fu		= inarr[2]; pd		= inarr[3];
	td		= inarr[4]; fd		= inarr[5];
	omegat	= inarr[6]; medium	= 0;
	fs		= inarr[9];

	COMRES_MOD(&pu, &pd, &fu, &fd, &tu, &td, &omegat, &medium, &fs, &momc, &dmc, &dmco, &dmfc, &dmfco, &deu, &ded, &vr, &etaic);

	outarr[6] = momc;
	outarr[0] = dmc;	outarr[3] = dmco;
	outarr[2] = dmfc;	outarr[5] = dmfco;
	outarr[1] = deu;	outarr[4] = ded;
	//outarr[7] = vr;		
	outarr[7] = etaic;

	return 0;
}
DllExport int ice_ffmax(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double fi, FF, Fmax;

	fi		= inarr[0]; FF		= inarr[1];


	FFMAX(&fi, &FF, &Fmax);

	outarr[0] = Fmax;

	return 0;
}
DllExport int ice_mip(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double fi, Y;

	fi		= inarr[0]; Y		= inarr[1];

	outarr[0]=RMIP(&fi, &Y);

	return 0;
}
DllExport int ice_pfimax(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double t, fi, p, pmax, fipmax;

	t		= inarr[0]; fi		= inarr[1];
	p		= inarr[2]; 

	PFIMAX(&t, &fi, &p, &pmax, &fipmax);

	outarr[0] = pmax;	outarr[1] = fipmax;

	return 0;
}
DllExport int ice_tfimax(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double t, fi, te, temax, fitmax;

	t		= inarr[0]; fi		= inarr[1];
	te		= inarr[2]; 

	TFIMAX(&t, &fi, &te, &temax, &fitmax);

	outarr[0] = temax;	outarr[1] = fitmax;

	return 0;
}
DllExport int th_mEV(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double qp, qf, qt, vol, qmed, fs, T, P, F;

	qp		= inarr[0];
	qf		= inarr[1];
	qt		= inarr[2];
	vol		= inarr[3];
	qmed	= inarr[4];
	fs		= inarr[5];


	TH1TPF(&qp, &qf, &qt, &vol, &qmed, &fs, &T, &P, &F);

	outarr[0]=P;
	outarr[1]=T;
	outarr[2]=F;

	return 0;
}
DllExport int th_PT(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double ppin, ttin, ffin, r, cp, cv, u, h, s, k, up, ut, uf, rp, rt, rf;
	int	   itsw, fault;

// Input variables preparation
	ppin	= inarr[0];
	ttin	= inarr[1];
	ffin	= inarr[2];
	itsw	= int(inarr[3]);

// Calling thermopackage (den generelle som kaller THERMO eller PER eller...

	THDYNP(&ppin, &ttin, &ffin, &itsw, &r, &cp, &cv, &u, &h, &s, &k, &up, &ut, &uf, &rp, &rt, &rf, &fault);

// Setting up output variables	
	outarr[0] = ppin/(r*ttin);
	outarr[1] = cp;
	outarr[2] = cv;
	outarr[3] = u;
	outarr[4] =	h;
	outarr[5] = s;
	outarr[6] = r;
	outarr[7] = k;
	outarr[8] = up;
	outarr[9] = ut;
	outarr[10] = uf;
	outarr[11] = rp;
	outarr[12] = rt;
	outarr[13] = rf;

	return 0;
}
DllExport int ice_eq(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double P, T, F, mm, nn, kk, ll;
	double X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13;
	int err;

// Input variables preparation
	P	= inarr[0];
	T	= inarr[1];
	F	= inarr[2];
	mm	= inarr[3];
	nn	= inarr[4];
	kk	= inarr[5];
	ll	= inarr[6];

// Calling ptf2x (calculate the equilibrium mole fraction)

	PTF2X(&P, &T, &F, &mm, &nn, &kk, &ll, &X1, &X2, &X3, &X4, &X5, &X6, &X7, &X8, &X9, &X10, &X11, &X12, &X13, &err);

// Setting up output variables	
	outarr[0] = X1;
	outarr[1] = X2;
	outarr[2] = X3;
	outarr[3] = X4;
	outarr[4] =	X5;
	outarr[5] = X6;
	outarr[6] = X7;
	outarr[7] = X8;
	outarr[8] = X9;
	outarr[9] = X10;
	outarr[10] = X11;
	outarr[11] = X12;
	outarr[12] = X13;
	outarr[13] = err;

	return 0;
}
DllExport int ice_NOPC(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double fi, Y;

	fi		= inarr[0]; Y		= inarr[1];

	outarr[0] = CNOPC(&fi, &Y);

	return 0;
}

DllExport int Initialize()

{

// Indicate that the dll was initialized successfully.
	return 0;

}
DllExport int Terminate()

{

// Indicate that the dll was terminated successfully.
	return 0;

}



}


