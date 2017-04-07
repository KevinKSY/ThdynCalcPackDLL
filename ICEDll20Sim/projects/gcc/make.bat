@echo off
gcc -O3 -Wall -c -fmessage-length=0 -o ICEDll20Sim.o "..\\..\\codes\\ICEDll20Sim.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o rt_nonfinite.o "..\\..\\codes\\subroutines\\rt_nonfinite.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetAirDensity.o "..\\..\\codes\\subroutines\\GetAirDensity.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetAirThermalConduct.o "..\\..\\codes\\subroutines\\GetAirThermalConduct.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetAirViscosity.o "..\\..\\codes\\subroutines\\GetAirViscosity.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetCompCombGas.o "..\\..\\codes\\subroutines\\GetCompCombGas.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetCorrAirComp.o "..\\..\\codes\\subroutines\\GetCorrAirComp.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetDensityHCVapor.o "..\\..\\codes\\subroutines\\GetDensityHCVapor.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetDiffusivityHCVaporToAir.o "..\\..\\codes\\subroutines\\GetDiffusivityHCVaporToAir.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetEquilGrill.o "..\\..\\codes\\subroutines\\GetEquilGrill.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetEquilOlikara.o "..\\..\\codes\\subroutines\\GetEquilOlikara.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetFuelPropertyN_Dodecane.o "..\\..\\codes\\subroutines\\GetFuelPropertyN_Dodecane.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetHTCoeffHTX.o "..\\..\\codes\\subroutines\\GetHTCoeffHTX.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetIdealNozzleFlow.o "..\\..\\codes\\subroutines\\GetIdealNozzleFlow.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetIdealNozzleFlowPTF.o "..\\..\\codes\\subroutines\\GetIdealNozzleFlowPTF.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetMEMbZach.o "..\\..\\codes\\subroutines\\GetMEMbZach.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetPTF.o "..\\..\\codes\\subroutines\\GetPTF.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetPTFV1.o "..\\..\\codes\\subroutines\\GetPTFV1.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetPTx.o "..\\..\\codes\\subroutines\\GetPTx.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetPTFSimple.o "..\\..\\codes\\subroutines\\GetPTFSimple.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetTFromPhF.o "..\\..\\codes\\subroutines\\GetTFromPhF.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetT_atm_p.o "..\\..\\codes\\subroutines\\GetT_atm_p.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetThdynCombGasZach.o "..\\..\\codes\\subroutines\\GetThdynCombGasZach.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetThdynCombGasZachV1.o "..\\..\\codes\\subroutines\\GetThdynCombGasZachV1.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetThermalPropertyHCVaporReal.o "..\\..\\codes\\subroutines\\GetThermalPropertyHCVaporReal.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetThermoDynProp.o "..\\..\\codes\\subroutines\\GetThermoDynProp.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetThermoDynPropPartial.o "..\\..\\codes\\subroutines\\GetThermoDynPropPartial.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetTotalStaticPT.o "..\\..\\codes\\subroutines\\GetTotalStaticPT.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetViscosityHCVapor.o "..\\..\\codes\\subroutines\\GetViscosityHCVapor.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o compressor_calc_PTF.o "..\\..\\codes\\subroutines\\compressor_calc_PTF.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o ThdynPack_terminate.o "..\\..\\codes\\subroutines\\ThdynPack_terminate.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o ThdynPack_initialize.o "..\\..\\codes\\subroutines\\ThdynPack_initialize.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o rtGetInf.o "..\\..\\codes\\subroutines\\rtGetInf.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o rtGetNaN.o "..\\..\\codes\\subroutines\\rtGetNaN.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o sqrt.o "..\\..\\codes\\subroutines\\sqrt.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o mldivide.o "..\\..\\codes\\subroutines\\mldivide.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o power.o "..\\..\\codes\\subroutines\\power.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o rdivide.o "..\\..\\codes\\subroutines\\rdivide.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o rt_nonfinite.o "..\\..\\codes\\subroutines\\rt_nonfinite.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o ThdynPack_data.o "..\\..\\codes\\subroutines\\ThdynPack_data.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o ThdynPack_rtwutil.o "..\\..\\codes\\subroutines\\ThdynPack_rtwutil.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetCompCombGas.o "..\\..\\codes\\subroutines\\GetCompCombGas.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o KpNASA7_upper.o "..\\..\\codes\\subroutines\\KpNASA7_upper.cpp"
gcc -O3 -Wall -c -fmessage-length=0 -o GetCompleteComb.o "..\\..\\codes\\subroutines\\GetCompleteComb.cpp"
g++ -shared -static-libgcc -static-libstdc++ -o ICEDll20Sim.dll ICEDll20Sim.o rt_nonfinite.o GetAirDensity.o GetAirThermalConduct.o GetAirViscosity.o GetCompCombGas.o GetCorrAirComp.o GetDensityHCVapor.o GetDiffusivityHCVaporToAir.o GetEquilGrill.o GetEquilOlikara.o GetFuelPropertyN_Dodecane.o GetHTCoeffHTX.o GetIdealNozzleFlow.o GetIdealNozzleFlowPTF.o GetMEMbZach.o GetPTF.o GetPTFV1.o GetPTx.o GetPTFSimple.o GetTFromPhF.o GetT_atm_p.o GetThdynCombGasZach.o GetThdynCombGasZachV1.o GetThermalPropertyHCVaporReal.o GetThermoDynProp.o GetThermoDynPropPartial.o GetTotalStaticPT.o GetViscosityHCVapor.o compressor_calc_PTF.o ThdynPack_terminate.o ThdynPack_initialize.o rtGetInf.o rtGetNan.o sqrt.o mldivide.o power.o rdivide.o ThdynPack_data.o ThdynPack_rtwutil.o KpNASA7_upper.o GetCompleteComb.o -Wl,--out-implib,ICEDll20Sim.lib