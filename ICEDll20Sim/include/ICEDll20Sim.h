#pragma once

/* Example C++ DLL for 20-sim */
//#include <windows.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

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
#include "GetPTFSimple.h"
#include "GetTFromPhF.h"
#include "GetT_atm_p.h"
#include "GetThdynCombGasZach.h"
#include "GetThdynCombGasZachV1.h"
#include "GetThermalPropertyHCVaporReal.h"
#include "GetThermoDynProp.h"
#include "GetThermoDynPropPartial.h"
#include "GetTotalStaticPT.h"
#include "GetViscosityHCVapor.h"
#include "compressor_calc_PTF.h"
#include "ThdynPack_terminate.h"
#include "ThdynPack_initialize.h"

#define DLLEXPORT __declspec( dllexport )

using namespace std;

ofstream outputStream;

#ifdef _MSC_VER
#define snprintf _snprintf_s
#endif

extern "C"
{
	DLLEXPORT int getThdynCombGas(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getpTF(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getpTFV1(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getpTFSimple(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getTFromPhF(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getIdealNozzleFlow(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int compressorPTF(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int getHTCoeffHTX(double *inarr, int inputs, double *outarr, int outputs, int major);
	DLLEXPORT int Initialize();
	DLLEXPORT int InitializeRun();
	DLLEXPORT int TerminateRun();
	DLLEXPORT int Terminate();
	DLLEXPORT int RegisterModelPath(const char * modelPath);
	DLLEXPORT char* LastErrorMessage();
}