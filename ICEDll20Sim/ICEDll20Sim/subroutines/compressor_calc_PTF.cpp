/*
 * Include Files
 *
 */
#include "rt_nonfinite.h"
#include "compressor_calc_PTF.h"
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

using namespace std;

/*
* Output functions
*
*/
void compressor_calc_PTF(const real_T *pu,
	const real_T *Tu,
	const real_T *Fu,
	const real_T *pd,
	const real_T *Td,
	const real_T *Fd,
	const real_T *omegat,
	real_T *dmu,
	real_T *deu,
	real_T *dmbu,
	real_T *dmd,
	real_T *ded,
	real_T *dmbd,
	real_T *Tqt,
	real_T *eta_ic,
	const real_T *flow_prev,
	const real_T *eta_prev,
	const real_T  *fs, const int_T  p_width0)
{
	static bool init;
	static int nGridFlow, nGridEff;
	if (!init) {
		ifstream myfile;
		myfile.open("compFlowMap.dat");
		myfile >> nGridFlow;
		myfile.close();
		myfile.open("compEffMap.dat");
		myfile >> nGridEff;
		myfile.close();
	}
	static vector<vector<double>> effMap(nGridEff, vector<double>(nGridEff));
	static vector<vector<double>> flowMap(nGridFlow, vector<double>(nGridFlow));
	static vector<double> prRep(nGridFlow);
	static vector<double> speedRep(nGridEff);

	if (!init) {
		init = true;
		ifstream myfile;
		myfile.open("compFlowMap.dat");
		myfile >> nGridFlow;
		for (int i = 0; i < nGridFlow; i++) {
			myfile >> speedRep[i];
		}
		for (int i = 0; i < nGridFlow; i++) {
			myfile >> prRep[i];
		}
		for (int i = 0; i < nGridFlow; i++) {
			for (int j = 0; j < nGridFlow; j++) {
				myfile >> flowMap[i][j];
			}
		}
		myfile.close();
		myfile.open("compEffMap.dat");
		myfile >> nGridEff;
		for (int i = 0; i < nGridEff; i++) {
			myfile >> speedRep[i];
		}
		for (int i = 0; i < nGridEff; i++) {
			myfile >> prRep[i];
		}
		for (int i = 0; i < nGridEff; i++) {
			for (int j = 0; j < nGridEff; j++) {
				myfile >> effMap[i][j];
			}
		}
		myfile.close();
	}



	/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
	double n288, dn288_intv, dpr_intv, dz1, dz11, dz2, dz21, z1, z11, z2, z21,
		dz_flow, dz_eff;
	int i, j, istart, iend, jstart, jend;
	double dm_corr;
	double pr, pic, Tdi, delhc;
	double hu, su, uu, Ru, RFu, Rpu, RTu, uFu, upu, uTu, sFu, spu, sTu, Cpu, Cvu, Ku;
	double hdi, sdi, udi, Rdi, RFdi, Rpdi, RTdi, uFdi, updi, uTdi, sFdi, spdi, sTdi,
		Cpdi, Cvdi, Kdi;
	const double pi = 3.14159265358979323846;

	//bool first;


	// Calculating the pressure ratio
	pr = *pd / *pu;
	if (pr < 1.000001) {
		pic = 1.000001;
	}
	else {
		pic = pr;
	}
	//pic = max(1.000001,pr);

	//Find the corrected flow and efficiency from the compressor map table
	n288 = *omegat * 60 / (2.0*pi)*sqrt(298.0 / *Tu);
	if ((pic <= prRep[0]) || (pic >= prRep[nGridEff - 1]) || (n288 <= speedRep[0]) || (n288 >= speedRep[nGridEff - 1]))
	{
		dmu[0] = 0;
		deu[0] = 0;
		dmbu[0] = 0;
		dmd[0] = 0;
		ded[0] = 0;
		dmbd[0] = 0;
		Tqt[0] = 0;
		eta_ic[0] = 0;
	}
	else
	{
		// interpolate in the 2D speed table to find the corresponding 
		// corrected flow (dm_corr) and isentropic efficiency (eta_ic)
		i = 1;
		while ((prRep[i] < pic) && (i < nGridEff))
		{
			i++;
		}
		istart = i - 1;
		iend = i;
		j = 1;
		while ((speedRep[j] < n288) && (j < nGridEff))
		{
			j++;
		}
		jstart = j - 1;
		jend = j;
		dn288_intv = speedRep[jend] - speedRep[jstart];
		dpr_intv = prRep[iend] - prRep[istart];

		dz1 = flowMap[iend][jstart] - flowMap[istart][jstart];
		dz11 = effMap[iend][jstart] - effMap[istart][jstart];
		dz2 = flowMap[iend][jend] - flowMap[istart][jend];
		dz21 = effMap[iend][jend] - effMap[istart][jend];
		z1 = flowMap[istart][jstart] + (dz1 / dpr_intv)*(pic - prRep[istart]);
		z11 = effMap[istart][jstart] + (dz11 / dpr_intv)*(pic - prRep[istart]);
		z2 = flowMap[istart][jend] + (dz2 / dpr_intv)*(pic - prRep[istart]);
		z21 = effMap[istart][jend] + (dz21 / dpr_intv)*(pic - prRep[istart]);
		dz_flow = z2 - z1;
		dz_eff = z21 - z11;
		dm_corr = z1 + (dz_flow / dn288_intv)*(n288 - speedRep[jstart]);
		*eta_ic = z11 + (dz_eff / dn288_intv)*(n288 - speedRep[jstart]);

		//Calculate the thermodynamic property of the upstream gas
		GetThdynCombGasZachV1(*pu, *Tu, *Fu, fs[0], &Ru, &hu, &su, &uu, &RFu, &Rpu, &RTu,
			&uFu, &upu, &uTu, &sFu, &spu, &sTu, &Cpu, &Cvu, &Ku);

		//Calculate the temperature and thermodynamic property of the downstream 
		//gas with isentropic expansion
		Tdi = *Tu*pow(pic, ((Ku - 1) / (Ku)));
		GetThdynCombGasZachV1(*pd, Tdi, *Fu, fs[0], &Rdi, &hdi, &sdi, &udi, &RFdi, &Rpdi,
			&RTdi, &uFdi, &updi, &uTdi, &sFdi, &spdi, &sTdi, &Cpdi, &Cvdi, &Kdi);

		//Calculate the actual increase in enthalpy using isentropic efficiency
		if (*eta_ic < 0.5) {
			delhc = (hdi - hu) / 0.5;
			eta_ic[0] = 0.5;
		}
		else {
			delhc = (hdi - hu) / *eta_ic;
		}

		// Calculating the flows and the mechanical torque
		if (dm_corr == 0) {
			dmu[0] = flow_prev[0];
		}
		else {
			*dmu = dm_corr * (*pu / 1e5) * sqrt(298 / *Tu);
		}
		*deu = *dmu * hu;
		*dmbu = (*dmu) * (*Fu) * (*fs) / (1.0 + (*Fu) * (*fs));
		*dmd = *dmu;
		*ded = *dmu*(hu + delhc);
		*dmbd = *dmbu;
		*Tqt = delhc* *dmu / (*omegat + 1.0e-6);
		/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
	}
}