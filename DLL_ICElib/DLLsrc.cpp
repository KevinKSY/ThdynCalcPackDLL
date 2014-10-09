#include <windows.h>

#include <math.h>

#include <stdio.h>

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
void GetThermoDynProp(double p, double T, double x[12], double *R, double *Cp, double *Cv, double *u, double *ht, double *s, double *rho);
void GetROHRDyn(double inarr_ROHR[12], double WiebePara[9], double outarr_ROHR[4], double WiebePara_new[9]);
void GetPTx(double m, double mb[12], double E, double V, double T_prev, double *P,double *T, double x[12]);
void GetTxV(double m, double p, double mb[12], double E, double T_prev, double *T, double *V, double x[12]);
void GetCompCombGas(double inarr_CompCG[5], double FC[4], double x_air[12], double x_CG[12]);
double GetAirDensity(double p, double T);
double GetViscosityHCVapor(double p, double T, double p_CR, double T_CR, double
  V_CR, double Z_CR, double rho_R, double MW);
void GetThermalPropertyHCVaporReal(double p, double T, double MW, double T_CR,
  double p_CR, double W, double *rho_v, double *Cp_v, double *Cv_v, double
  *lambda);
void GetThdynCombGasZach(double P, double T, double F, double *R, double *h,
  double *s, double *u, double *RF, double *RP, double *RT, double *uF, double
  *uP, double *uT, double *Cp, double *Cv, double *K);
double GetT_atm_p(double h, double F, double T_prev);
void GetPTF(double m, double m_b, double E, double V, double T_prev, double fs, double *p, double *T, double *F);
void GetIdealNozzleFlow(double Cd, double A, double p_in, double p_out, double
  T_in, double F_in, double fs, double *m_dot, double *h_dot, double *m_b_dot);
double GetAirViscosity(double rho, double T);
double GetAirThermalConduct(double rho, double T);
double GetHTCoeffHTX(double p, double m_dot, double T, double D, double A);
void GetFuelPropertyN_Dodecane(double p, double T, double *p_v, double *rho_l, 
	double *h_l, double *Cp_l, double *h_fg, double *mu_l, double *lambda_l, double *sigma_l);
void GetThdynCombGasZachV1(double P, double T, double F, double fs, double *R, double *h,
  double *s, double *u, double *RF, double *RP, double *RT, double *uF, double
  *uP, double *uT, double *sF, double *sP, double *sT, double *Cp, double *Cv, double *K);
void GetPTFV1(double m, double m_b, double E, double V, double T_prev, 
        double R_prev, double u_prev, double Cv_prev, double fs,
        double *p, double *T, double *F);

DllExport int thdyn_AirDensity(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T;
	p = inarr[0];	T = inarr[1];
	outarr[0] = GetAirDensity(p, T);
	return 0;
}
DllExport int thdyn_ViscHCVapor(double *inarr, int inputs, double *outarr, int outputs, int major)
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
DllExport int thdyn_PropHCVapor(double *inarr, int inputs, double *outarr, int outputs, int major)
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
DllExport int thdyn_CombGasZach(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, F;
	double R, h, s, u, RF, Rp, RT, uF, up, uT, Cp, Cv, K;

	p = inarr[0];		T = inarr[1];
	F = inarr[2];

	GetThdynCombGasZach(p, T, F, &R, &h, &s, &u, &RF, &Rp, &RT, &uF, &up, &uT, &Cp, &Cv, &K);

	outarr[0] = R;		outarr[1] = u;
	outarr[2] = s;		outarr[3] = h;
	outarr[4] = RF;		outarr[5] = Rp;
	outarr[6] = RT;		outarr[7] = uF;
	outarr[8] = up;		outarr[9] = uT;
	outarr[10] = Cp;	outarr[11] = Cv;
	outarr[12] = K;		
	
	return 0;
}

DllExport int thdyn_CombGasZachV1(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double p, T, F, fs;
	double R, h, s, u, RF, Rp, RT, uF, up, uT, sF, sp, sT, Cp, Cv, K;

	p = inarr[0];		T = inarr[1];
	F = inarr[2];		fs = inarr[3];

	GetThdynCombGasZachV1(p, T, F, fs, &R, &h, &s, &u, &RF, &Rp, &RT, &uF, &up, &uT, &sF, &sp, &sT, &Cp, &Cv, &K);

	outarr[0] = R;		outarr[1] = u;
	outarr[2] = s;		outarr[3] = h;
	outarr[4] = RF;		outarr[5] = Rp;
	outarr[6] = RT;		outarr[7] = uF;
	outarr[8] = up;		outarr[9] = uT;
	outarr[10] = sF;	outarr[11] = sp;
	outarr[12] = sT;
	outarr[13] = Cp;	outarr[14] = Cv;
	outarr[15] = K;		
	
	return 0;
}

DllExport int thdyn_T_atm_p(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double h, F, T_prev;
	double T;
	h = inarr[0];		F = inarr[1];
	T_prev = inarr[2];

	T = GetT_atm_p(h, F, T_prev);

	outarr[0] = T;

	return 0;
}
DllExport int thdyn_PTF(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double m, m_b, E, V, T_prev, fs;		
	double P, T, F;
	
	m		= inarr[0];		E		= inarr[1];
	m_b		= inarr[2];		V		= inarr[3];
	fs		= inarr[4];		T_prev	= inarr[5];		

	GetPTF(m, m_b, E, V, T_prev, fs, &P, &T, &F);

	outarr[0] = P;		outarr[1] = T;
	outarr[2] = F;	
	
	return 0;
}
DllExport int thdyn_PTFV1(double *inarr, int inputs, double *outarr, int outputs, int major)
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

DllExport int thdyn_Flow_Ideal_Nozzle(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double Cd, A, p_in, p_out, T_in, F_in, fs;		
	double m_dot, h_dot, m_b_dot;
	
	p_in	= inarr[0];		p_out	= inarr[1];
	T_in	= inarr[2];		F_in	= inarr[3];
	Cd		= inarr[4];		A		= inarr[5];		
	fs		= inarr[6];

	GetIdealNozzleFlow( Cd, A, p_in, p_out, T_in, F_in, fs, &m_dot, &h_dot, &m_b_dot);

	outarr[0] = m_dot;		outarr[1] = h_dot;
	outarr[2] = m_b_dot;	
	
	return 0;
}
DllExport int thdyn_AirViscosity(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double rho, T;
	double mu_a;
	rho = inarr[0];		T = inarr[1];

	mu_a = GetAirViscosity(rho, T);

	outarr[0] = mu_a;

	return 0;
}
DllExport int thdyn_AirThConduct(double *inarr, int inputs, double *outarr, int outputs, int major)
{
	double rho, T;
	double lambda_a;
	rho = inarr[0];		T = inarr[1];

	lambda_a = GetAirThermalConduct(rho, T);

	outarr[0] = lambda_a;

	return 0;
}
DllExport int thdyn_HTCoeffHTX(double *inarr, int inputs, double *outarr, int outputs, int major)
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
DllExport int thdyn_FuelPropN_Dodecane(double *inarr, int inputs, double *outarr, int outputs, int major)
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
DllExport int ice_N_CG(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double inarr_CompCG[5], Fc[4], x_air[12];		
	double x_CG[12];
	
	inarr_CompCG[0]	= inarr[0];		inarr_CompCG[1]	= inarr[1];
	inarr_CompCG[2]	= inarr[2];		inarr_CompCG[3]	= inarr[3];
	inarr_CompCG[4]	= inarr[4];		
	Fc[0] = inarr[5];				Fc[1] = inarr[6];
	Fc[2] = inarr[7];				Fc[3] = inarr[8];
	x_air[0] = inarr[9];			x_air[1] = inarr[10];
	x_air[2] = inarr[11];			x_air[3] = inarr[12];
	x_air[4] = inarr[13];			x_air[5] = inarr[14];
	x_air[6] = inarr[15];			x_air[7] = inarr[16];
	x_air[8] = inarr[17];			x_air[9] = inarr[18];
	x_air[10] = inarr[19];			x_air[11] = inarr[20];

	GetCompCombGas(inarr_CompCG, Fc, x_air, x_CG);
	
	outarr[0] = x_CG[0];	outarr[1] = x_CG[1];
	outarr[2] = x_CG[2];	outarr[3] = x_CG[3];
	outarr[4] = x_CG[4];	outarr[5] = x_CG[5];
	outarr[6] = x_CG[6];	outarr[7] = x_CG[7];
	outarr[8] = x_CG[8];	outarr[9] = x_CG[9];
	outarr[10] = x_CG[10];	outarr[11] = x_CG[11];

	return 0;
}
DllExport int Thdyp(double *inarr, int inputs, double *outarr, int outputs, int major)

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
DllExport int th_MEV2(double *inarr, int inputs, double *outarr, int outputs, int major)

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
DllExport int th_MEP(double *inarr, int inputs, double *outarr, int outputs, int major)

{
	double m, mb[12], E, P, T_prev;		
	double T, x[12], V;
	
	mb[0]	= inarr[0];		mb[1]	= inarr[1];
	mb[2]	= inarr[2];		mb[3]	= inarr[3];
	mb[4]	= inarr[4];		mb[5]	= inarr[5];
	mb[6]	= inarr[6];		mb[7]	= inarr[7];
	mb[8]	= inarr[8];		mb[9]	= inarr[9];
	mb[10]	= inarr[10];	mb[11]	= inarr[11];
	m		= inarr[12];		E		= inarr[13];	
	P		= inarr[14];	T_prev	= inarr[15];

	GetTxV(m, P, mb, E, T_prev, &T, &V, x);

	outarr[0] = T;		outarr[1] = V;
	outarr[2] = x[0];	outarr[3] = x[1];
	outarr[4] = x[2];	outarr[5] = x[3];
	outarr[6] = x[4];	outarr[7] = x[5];
	outarr[8] = x[6];	outarr[9] = x[7];
	outarr[10] = x[8];	outarr[11] = x[9];
	outarr[12] = x[10];	outarr[13] = x[11];
	
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

	pu		= inarr[0]; pd		= inarr[1];
	fu		= inarr[2]; fd		= inarr[3];
	tu		= inarr[4]; td		= inarr[5];
	omegat	= inarr[6]; medium	=inarr[7];
	fs		= inarr[8];

	COMRES_MOD(&pu, &pd, &fu, &fd, &tu, &td, &omegat, &medium, &fs, &momc, &dmc, &dmco, &dmfc, &dmfco, &deu, &ded, &vr, &etaic);

	outarr[0] = momc;
	outarr[1] = dmc;	outarr[2] = dmco;
	outarr[3] = dmfc;	outarr[4] = dmfco;
	outarr[5] = deu;	outarr[6] = ded;
	outarr[7] = vr;		outarr[8] = etaic;

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


