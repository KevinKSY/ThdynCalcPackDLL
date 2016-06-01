#include "rt_nonfinite.h"
#include "GetCompCombGas.h"
#include "GetPTx.h"
#include "GetROHRDyn.h"
#include "GetThermoDynProp.h"
#include "GetTxV.h"
#include "Get3Wiebe.h"
#include "Get3WiebePara.h"
#include "GetCompCombGas_rtwutil.h"

void Get3WiebePara(real_T omeganom, real_T bmepnom, real_T WiebePara[9])
{
	int test_case;
	test_case = floor(omeganom);
	switch (test_case) 
	{
		case 1:
			WiebePara[0] = 		0.21;
			WiebePara[1] = 		0.34;
			WiebePara[2] = 		3.32;
			WiebePara[3] = 		5.1;
			WiebePara[4] = 		19.6;
			WiebePara[5] = 		60;
			WiebePara[6] = 		1.7;
			WiebePara[7] = 		0.41;
			WiebePara[8] =		0.49;
			break;
		case 2:
			WiebePara[0] = 		0.13;
			WiebePara[1] = 		0.47;
			WiebePara[2] = 		3.4;
			WiebePara[3] = 		6;
			WiebePara[4] = 		30.4;
			WiebePara[5] = 		80;
			WiebePara[6] = 		1.3;
			WiebePara[7] = 		0.5;
			WiebePara[8] =		0.41;
			break;
		case 11:
			WiebePara[0] = 		0.13;
			WiebePara[1] = 		0.5;
			WiebePara[2] = 		2.4;
			WiebePara[3] = 		5.4;
			WiebePara[4] = 		24;
			WiebePara[5] = 		65;
			WiebePara[6] = 		1.77;
			WiebePara[7] = 		0.9;
			WiebePara[8] =		0.9;
			break;
		case 8:
			WiebePara[0] = 		0.09;
			WiebePara[1] = 		0.42;
			WiebePara[2] = 		2.9;
			WiebePara[3] = 		5.5;
			WiebePara[4] = 		26.5;
			WiebePara[5] = 		59.5;
			WiebePara[6] = 		1.4;
			WiebePara[7] = 		0.84;
			WiebePara[8] =		0.68;
			break;
		case 20:
			WiebePara[0] = 		0.075;
			WiebePara[1] = 		0.42;
			WiebePara[2] = 		2.9;
			WiebePara[3] = 		5.4;
			WiebePara[4] = 		27.9;
			WiebePara[5] = 		61;
			WiebePara[6] = 		1.4;
			WiebePara[7] = 		0.91;
			WiebePara[8] =		0.68;
			break;
		case 12:
			WiebePara[0] = 		0.12;
			WiebePara[1] = 		0.5;
			WiebePara[2] = 		2.2;
			WiebePara[3] = 		5;
			WiebePara[4] = 		27;
			WiebePara[5] = 		70;
			WiebePara[6] = 		1.77;
			WiebePara[7] = 		0.8;
			WiebePara[8] =		0.7;
			break;
		case 7:
			WiebePara[0] = 		0.1;
			WiebePara[1] = 		0.43;
			WiebePara[2] = 		3.1;
			WiebePara[3] = 		5.6;
			WiebePara[4] = 		25.4;
			WiebePara[5] = 		58;
			WiebePara[6] = 		1.6;
			WiebePara[7] = 		0.92;
			WiebePara[8] =		0.64;
			break;
		case 15:
			WiebePara[0] = 		0.03;
			WiebePara[1] = 		0.78;
			WiebePara[2] = 		0.7;
			WiebePara[3] = 		10;
			WiebePara[4] = 		36.2;
			WiebePara[5] = 		54;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.7;
			WiebePara[8] =		2.8;
			break;
		case 19:
			WiebePara[0] = 		0.01;
			WiebePara[1] = 		0.78;
			WiebePara[2] = 		0.5;
			WiebePara[3] = 		10;
			WiebePara[4] = 		39.5;
			WiebePara[5] = 		57;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.6;
			WiebePara[8] =		2.6;
			break;
		case 3:
			WiebePara[0] = 		0.12;
			WiebePara[1] = 		0.41;
			WiebePara[2] = 		3.6;
			WiebePara[3] = 		5.3;
			WiebePara[4] = 		29.5;
			WiebePara[5] = 		80;
			WiebePara[6] = 		2.1;
			WiebePara[7] = 		0.6;
			WiebePara[8] =		0.29;
			break;
		case 6:
			WiebePara[0] = 		0.1;
			WiebePara[1] = 		0.43;
			WiebePara[2] = 		3;
			WiebePara[3] = 		5.7;
			WiebePara[4] = 		25.4;
			WiebePara[5] = 		58;
			WiebePara[6] = 		1.7;
			WiebePara[7] = 		0.92;
			WiebePara[8] =		0.64;
			break;
		case 18:
			WiebePara[0] = 		0.025;
			WiebePara[1] = 		0.75;
			WiebePara[2] = 		0.3;
			WiebePara[3] = 		10;
			WiebePara[4] = 		39;
			WiebePara[5] = 		57;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.8;
			WiebePara[8] =		2.6;
			break;
		case 14:
			WiebePara[0] = 		0.03;
			WiebePara[1] = 		0.8;
			WiebePara[2] = 		2.2;
			WiebePara[3] = 		10;
			WiebePara[4] = 		35.4;
			WiebePara[5] = 		54;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.7;
			WiebePara[8] =		2.8;
			break;
		case 13:
			WiebePara[0] = 		0.16;
			WiebePara[1] = 		0.5;
			WiebePara[2] = 		4.7;
			WiebePara[3] = 		7.5;
			WiebePara[4] = 		32.7;
			WiebePara[5] = 		63;
			WiebePara[6] = 		1.77;
			WiebePara[7] = 		0.58;
			WiebePara[8] =		0.8;
			break;
		case 5:
			WiebePara[0] = 		0.09;
			WiebePara[1] = 		0.65;
			WiebePara[2] = 		4.36;
			WiebePara[3] = 		7.9;
			WiebePara[4] = 		35;
			WiebePara[5] = 		60;
			WiebePara[6] = 		1.8;
			WiebePara[7] = 		0.9;
			WiebePara[8] =		0.74;
			break;
		case 10:
			WiebePara[0] = 		0.03;
			WiebePara[1] = 		0.76;
			WiebePara[2] = 		1.7;
			WiebePara[3] = 		10;
			WiebePara[4] = 		38.5;
			WiebePara[5] = 		56;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.7;
			WiebePara[8] =		2;
			break;
		case 17:
			WiebePara[0] = 		0.01;
			WiebePara[1] = 		0.8;
			WiebePara[2] = 		0.7;
			WiebePara[3] = 		9;
			WiebePara[4] = 		46.2;
			WiebePara[5] = 		53;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.6;
			WiebePara[8] =		3.2;
			break;
		case 4:
			WiebePara[0] = 		0.12;
			WiebePara[1] = 		0.65;
			WiebePara[2] = 		4.7;
			WiebePara[3] = 		7;
			WiebePara[4] = 		39.8;
			WiebePara[5] = 		75;
			WiebePara[6] = 		1.9;
			WiebePara[7] = 		0.55;
			WiebePara[8] =		0.45;
			break;
		case 9:
			WiebePara[0] = 		0.03;
			WiebePara[1] = 		0.78;
			WiebePara[2] = 		1.8;
			WiebePara[3] = 		10;
			WiebePara[4] = 		40.9;
			WiebePara[5] = 		70;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.6;
			WiebePara[8] =		1.5;
			break;
		case 16:
			WiebePara[0] = 		0.02;
			WiebePara[1] = 		0.8;
			WiebePara[2] = 		0.5;
			WiebePara[3] = 		12;
			WiebePara[4] = 		52;
			WiebePara[5] = 		60;
			WiebePara[6] = 		2.2;
			WiebePara[7] = 		1.8;
			WiebePara[8] =		2.7;
			break;
	}
}
