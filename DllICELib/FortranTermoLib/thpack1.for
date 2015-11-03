      SUBROUTINE THDYNP(PP,TT,FF,ITSW,R,CP,CV,U,H,S,RK,UP,UT,UF,RP,
     &     RT,RF,FAULT)
C
      PARAMETER (NTPACK=2)
C
      IMPLICIT REAL*8 (A-H,O-Z)
      INTEGER*4 JDR,ITSW,FAULT,IDCO
C
      P=PP
      T=TT
      F=FF

      IF(ITSW.LT.0 .OR. ITSW.GT.NTPACK-1) ITSW=0
C     =================================================================
C --- Select thermodynamic package
C     =================================================================
C
C --- 1) Zacharias formulas
C
      IF(ITSW.eq.0) THEN
        IDCO=0
        call THERMO(P,T,F,IDCO,R,CP,CV,U,H,S,RK,
     &              UP,UT,UF,
     &              RP,RT,RF,FAULT)
C
C --- 2) Complete comubstion
C
      ELSEIF(ITSW.eq.1) THEN
C
        CALL PROPM(P,T,F,R,H,U,S,RK,RT,RP,RF,
     &             UT,UP,UF,JDR)
C
        CP=UT+R
        CV=UT
C
C --- 3) Olikara / Borman package
C
C     ELSEIF(ITSW.eq.2) THEN
C       CALL PROPE(P,T,F,R,H,U,S,RK,RT,RP,RF,
C    &             UT,UP,UF,JDR)
C
      ENDIF
    
C
      return
      end
      REAL*8 FUNCTION FSGET(FSINN,RITSW)
C ---------------------------------------------------------------------
C
C     ROUTINE FOR FETCHING ADDITIONAL PARAMETERS
C
C************************************************************************
C   
      IMPLICIT REAL*8 (A-H,O-Z)
C
      COMMON /SIBLOC/ FC(4),AC(6),PHI,T,P,KLO,IERR,
     +                FSS,FA,FB,FMAX,AA(8,3),BB(8,3),TPR,FPR,PPR
C 
C --- NB! Kaller PROPM for aa sikre at FS er beregnet
C
      ITSW=IDINT(RITSW)
      IF(ITSW.eq.0) THEN
C
      FSGET=FSINN
C
      ELSEIF(ITSW.eq.1) THEN
        P=1.0e+5
        T=300.0
        F=0.0
        CALL PROPM(P,T,F,R,H,U,S,GAM,DRT,DRP,DRF,DUT,DUP,DUF,JDR)
        FSGET=FSS
      ELSE
C
C ---   Dummy variable
C
	FSGET=14.3
      ENDIF
      RETURN
      END   
      SUBROUTINE PROPM(P,T,F,R,H,U,S,GAM,DRT,DRP,DRF,DUT,DUP,DUF,JDR)
C
      IMPLICIT REAL*8 (A-H,O-Z)
      INTEGER*4 JDR,KLO,IERR
C
      COMMON /SIBLOC/ FC(4),AC(6),FF,TT,PP,KLO,IERR,
     +                FS,FA,FB,FMAX,AA(8,3),BB(8,3),TPR,FPR,PPR
      COMMON /SIPROP/RR,HH,UU,SS,G,A,DRDT,DHDT,DUDT,DSDT,DGDT,DADT,
     +        DRDP,DHDP,DUDP,DSDP,DGDP,DADP,DRDF,DHDF,DUDF,DSDF,DGDF,
     +              DADF,GAMA,MF,HTF,UTF,STF,GTF,ATF,DMFDT,DHTDT,DUTDT,
     +              DSTDT,DGTDT,DATDT,DMFDP,DHTDP,DUTDP,
     +              DSTDP,DGTDP,DATDP,DMFDF,DHTDF,DUTDF,
     +              DSTDF,DGTDF,DATDF
C
      LOGICAL IFIRST
C
      DATA IFIRST /.true./
C
      SAVE
C
      IF(IFIRST) THEN
C
      	OPEN(UNIT=91,FILE='fuelairc.dat',STATUS='OLD',FORM='FORMATTED')

	  READ(91,*) (FC(i),i=1,4)
	  READ(91,*) (AC(i),i=1,6)
C
	CALL SETFAM(FC,AC)
C
        IFIRST=.FALSE.

      ENDIF
C
      PP=P
      TT=T
      FF=F
C
      CALL PMR(JDR)     
C
      R=RR
      H=HH
      U=UU
      S=SS
      DRT=DRDT
      DRP=DRDP
      DRF=DRDF
      DUT=DUDT
      DUP=DUDP
      DUF=DUDF
      GAM=DHDT/(DHDT-RR)
C
      RETURN
      END
      SUBROUTINE PMR(KLO)
C   
C:***************************************************************   
C   
C  LAST CORRECTED BY:  H. VALLAND   
C  DATE:  1988-03-10
C   
C  PURPOSE: 
C     COMPUTES THE THERMODYNAMIC PROPERTIES OF THE COMBUSTION   
C     PRODUCTS FROM A C-H-O-N FUEL AND DRY AIR.  DISSOCIATION   
C     IS NEGLECTED, I.E. THE COMPOSITION OF THE PRODUCTS IS 
C     CORRECT ONLY AT TEMPERATURES BELOW APPROXIMATELY 1800 K.  
C   
C  INPUT:   
C     PARAMETERS:
C       P     PRESSURE (PA)   
C       T     TEMPERATURE (K)   
C       F     FUEL-AIR-EQUIVALENCE RATIO
C     COMMON /PROPT/:   
C        FS    FUEL AIR MASS RATIO AT STOECHIOMETRIC COMBUSTION 
C        FA    VALUE OF F AT WHICH ALL CARBON PRODUCE CO ONLY   
C        FB    VALUE OF F AT WHICH ALL HYDROGEN PRODUCE H2 ONLY 
C        FMAX  MAX VALUE OF F, ABOVE THIS VALUE NO MORE FUEL
C              CAN BE BURNED INTO CO2, H2O, CO, AND H2. 
C        AA    MATRIX CONTAINING THE COEFFICIENTS FOR COMPUTATION   
C              OF PRODUCTS COMPOSITION: 
C              AA(I,J) CONTAIN COEFFICIENT A FOR SPECIE NUMBER I 
C                     IN F-REGION NUMBER J: 
C                     J = 1  FOR  0.0 .LE. F .AND. F .LE. 1.0   
C                       = 2  FOR  1.0 .LT. F .AND. F .LE. FA
C                       = 3  FOR   FA .LT. F .AND. F .LE. FB
C        BB    BB(I,J) CONTAINS COEFFICIENT B FOR SPECIE NUMBER I
C                     IN F-REGION NUMBER J. 
C       ** NB!**  THE FUEL COMPOSITION DATA 
C       ** NB!**  CAN BE ENTERED INTO /PROPT/ BY MEANS  
C       ** NB!**  OF SUBROUTINE  SETFD. 
C   
C  OUTPUT:  
C     PARAMETERS:   
C       R     GAS CONSTANT (J/KG*K) 
C       DRF   PARTIAL DERIVATIVE OF R  W.R.T. F
C       GAM   ADIABATIC EXPONENT  GAM=CP/CV
C       H     SPECIFIC ENTHALPY (J/KG)  
C       U     SPECIFIC INTERNAL ENERGY (J/KG)
C       S     SPECIFIC ENTROPY (J/KG K)
C       G     GIBBS FREE ENERGY (J/KG)
C       A     hELMHOLZ FUNCTION (J/KG)   
C       DHT   PARTIAL DERIVATIVE OF H W.R.T. T
C       DHF   ..      ..      ..    H   ..   F  
C       DUT   ..      ..      ..    U   ..   T
C       DUF   ..      ..      ..    U   ..   F
C       DST   ..      ..      ..    S   ..   T
C       DSF   ..      ..      ..    S   ..   F
C       DSP   ..      ..      ..    S   ..   P
C       DGT   ..      ..      ..    G   ..   T
C       DGF   ..      ..      ..    G   ..   F
C       DGP   ..      ..      ..    G   ..   P
C       DAT   ..      ..      ..    A   ..   T
C       DAF   ..      ..      ..    A   ..   F
C       DAP   ..      ..      ..    A   ..   P
C
C       IWAR  WARNING FLAG
C             =-1  FUEL COMPOSITION NOT ACCEPTED
C             = 1  F<0     -> F=0
C             = 2  F>FMAX  -> F=FMAX
C             =+10 T<0     -> T=0
C             =+20 T>4000  -> T=4000 K
C  
C     COMMON /PROPTY/   
C       X     MOLE FRACTIONS OF THE PRODUCT SPECIES 
C              NUMBERING OF SPECIES, AS FOR SM BELOW.   
C       DXF   DERIVATIVE OF X  W.R.T.  F
C       MF    AVERAGE MOLE MASS OF THE PRODUCTS 
C       SH    SPECIFIC ENTHALPY OF THE PRODUCT SPECIES (J/MOL) AT T 
C       SCP   SPECIFIC HEAT CAPACITY OF THE PRODUCT SPECIES 
C        ** NB! **  THE VALUE OF FS CAN BE RETRIEVED
C        ** NB! **  FROM /PROPT/ BY MEANS OF SUBROUTINE  GETFS. 
C   
C  PROGRAMMED BY:  H. VALLAND   
C  DATE:  1983-03-10
C   
C:**************************************************************
C************************************************************************
C   
      IMPLICIT REAL*8 (A-H,O-Z)
C
      REAL*8 MF   
C
      INTEGER*4 KLOO,IERR
C
      COMMON /SIBLOC/ FC(4),AC(6),PHI,T,P,KLOO,IERR,
     +              FS,FA,FB,FMAX,AA(8,3),BB(8,3),TPR,FPR,PPR
      COMMON /SITAB / X(13),DXT(12),DXP(12),DXF(12)
C
      COMMON /SIPROP/R,H,U,S,G,A,DRDT,DHDT,DUDT,DSDT,DGDT,DADT,
     +        DRDP,DHDP,DUDP,DSDP,DGDP,DADP,DRDF,DHDF,DUDF,DSDF,DGDF,
     +              DADF,GAM,MF,HTF,UTF,STF,GTF,ATF,DMFDT,DHTDT,DUTDT,
     +              DSTDT,DGTDT,DATDT,DMFDP,DHTDP,DUTDP,
     +              DSTDP,DGTDP,DATDP,DMFDF,DHTDF,DUTDF,
     +              DSTDF,DGTDF,DATDF
C
C ***************************************************************   
C   
C  THIS BLOCK CONTAINS THERMO-CHEMICAL DATA FOR COMBUSTION  
C  PRODUCTS SPECIES.
C   
C  THE SPECIES NUMBERING IS AS FOLLOWS: 
C      I = 1 - O2   OXYGEN  
C        = 2 - H2O  WATER VAPOR 
C        = 3 - CO2  CARBON DIOXYDE  
C        = 4 - N2   NITROGEN
C        = 5 - CO   CARBON MONOXYDE 
C        = 6 - H2   HYDROGEN
C        = 7 - AR   ARGON   
C  
C      AN      NUMBER OF CARBON ATOMS IN THE FUEL MOLECULE
C      AM        ..      HYDROGEN     ..      ..     ..
C      AL        ..      OXYGEN       ..      ..     ..
C      AK        ..      NITROGEN     ..      ..     ..
C
C      HTF     ENTHALPY ON MOLAR BASIS
C      UTF     INTERNAL ENERGY    ..
C      STF     ENTROPY     ..     ..
C      GTF     GIBBS FREE ENERGY  ..
C      ATF     HELMHOLZ FUNCTION  ..
C
C      DMFDT   DERIVATIVE OF MF  W.R.T. TEMPERATURE (MOLAR BASIS)
C      DRDT       ..     .. R    ..         ..         ..
C      DHTDT      ..     .. HTF  ..         ..         ..
C      DUTDT      ..     .. UTF  ..         ..         ..
C      DSTDT      ..     .. STF  ..         ..         ..
C      DGTDT      ..     .. GTF  ..         ..         ..
C      DATDT      ..     .. ATF  ..         ..         ..
C      DMFDP       ..     .. MF   ..         ..         ..
C      DRDP       ..     .. R    ..         ..         ..
C      DHTDP      ..     .. HTF  ..         ..         ..
C      DUTDP      ..     .. UTF  ..         ..         ..
C      DSTDP      ..     .. STF  ..         ..         ..
C      DGTDP      ..     .. GTF  ..         ..         ..
C      DATDP      ..     .. ATF  ..         ..         ..
C      DMFDF       ..     .. MF   ..         ..         ..
C      DRDF       ..     .. R    ..         ..         ..
C      DHTDF      ..     .. HTF  ..         ..         ..
C      DUTDF      ..     .. UTF  ..         ..         ..
C      DSTDF      ..     .. STF  ..         ..         ..
C      DGTDF      ..     .. GTF  ..         ..         ..
C      DATDF      ..     .. ATF  ..         ..         ..
C 
C      R0      UNIVERSAL GAS CONSTANT (J/MOL.K) 
C      SM      MOLECULAR MASS OF THE SPECIE NO I IS STORED IN SM(I) 
C
C      X(I)    MOLE FRACTION OF SPECIE NO. I
C      DXF(I)  DERIVATIVE OF X(I) W.R.T. FUEL AIR EQUIVALENCE RATIO
C      SH(I)   ABSOLUTE ENTHALPY OF SPECIE NO I
C      SC(I)   SPECIFIC HEAT AT CONSTANT PRESSURE OF SPECIE NO. I
C      SS(I)   THE TEMPERATURE TERM OF ENTROPY, SPECIE NO. I
C      SST(I)  ENTROPY OF SPECIE NO. I
C
C      HT      ABSOLUTE MOLAR ENTHALPY OF THE SPECIES IS
C              GIVEN AT 100 K INTERVALS IN THE REGION 0 - 4000 K
C              UNITS:  KCAL/MOL 
C   
C      CT      MOLAR SPECIFIC HEAT CAPACITY OF THE SPECIES  
C              AT 100 K INTERVALS IN THE REGION  0 - 4000 K 
C              UNITS:  CAL/MOL.K
C
C      ST      ABSOLUTE ENTROPY OF THE SPECIES GIVEN AT 100 K
C              INTERVALS IN THE REGION 0-4000 K.
C              UNITS:  KCAL/MOL.K   
C **************************************************************
C
      REAL*8 SH(7),SC(7),SST(7),SS(7)
      REAL*8 SM(7),HT(246),CT(246),ST(246)   
C     UNIVERSAL GAS CONSTANT AND REFERENCE PRESSURE (PA)
      DATA R0,P0/8314.4,1.0E+05/   
C
      DATA SH /7*0.0/
      DATA SC /7*0.0/
      DATA SST/7*0.0/
      DATA SS /7*0.0/
C
C --- MOLECULAR MASS OF THE SPECIES
      DATA SM/31.999, 18.016, 44.010, 28.013, 28.011, 2.016, 39.944/
C
C --- ABSOLUTE ENTHALPY
      DATA (HT(I),I=1,123)/                     0.000,  0.713,  1.393,  
     9  2.088,  2.799,  3.530,  4.285,  5.063,  5.861,  6.675,  7.502,  
     *  8.341,  9.189, 10.046, 10.910, 11.781, 12.658, 13.540, 14.429,  
     1 15.324, 16.224, 17.129, 18.041, 18.957, 19.879, 20.807, 21.739,  
     2 22.677, 23.620, 24.568, 25.521, 26.478, 27.440, 28.406, 29.377,  
     3 30.351, 31.329, 32.311, 33.296, 34.284, 35.276,  
     3-57.103,-56.317,-55.520,-54.721,-53.911,-53.082,-52.227,-51.346,  
     4-50.436,-49.496,-48.527,-47.526,-46.496,-45.438,-44.352,-43.241,  
     5-42.106,-40.949,-39.772,-38.576,-37.363,-36.134,-34.890,-33.633,  
     6-32.364,-31.083,-29.791,-28.490,-27.180,-25.861,-24.535,-23.201,  
     7-21.860,-20.513,-19.159,-17.800,-16.436,-15.067,-13.693,-12.314,  
     *-10.931,                -93.965,-93.198,-92.534,-91.711,-90.769,  
     8-89.740,-88.640,-87.482,-86.274,-85.025,-83.743,-82.431,-81.095,  
     9-79.739,-78.365,-76.977,-75.575,-74.162,-72.740,-71.309,-69.870,  
     *-68.424,-66.972,-65.515,-64.053,-62.586,-61.114,-59.639,-58.160,  
     1-56.678,-55.192,-53.703,-52.212,-50.717,-49.220,-47.721,-46.219,  
     2-44.715,-43.209,-41.700,-40.189/  
      DATA (HT(I),I=124,246)/                           0.000,  0.685,  
     2  1.388,  2.085,  2.782,  3.485,  4.197,  4.925,  5.668,  6.427,  
     3  7.201,  7.989,  8.790,  9.601, 10.422, 11.251, 12.087, 12.930,  
     4 13.779, 14.632, 15.490, 16.352, 17.218, 18.087, 18.958, 19.833,  
     5 20.710, 21.589, 22.470, 23.352, 24.237, 25.123, 26.011, 26.901,  
     6 27.791, 28.683, 29.577, 30.471, 31.367, 32.263, 33.161,-27.201,  
     *-26.521,-25.813,-25.115,-24.417,-23.711,-22.991,-22.255,-21.501,  
     1-20.731,-19.945,-19.145,-18.334,-17.512,-16.682,-15.843,-14.998,  
     2-14.148,-13.292,-12.431,-11.567,-10.698, -9.827, -8.953, -8.076,  
     3 -7.197, -6.315, -5.432, -4.546, -3.659, -2.771, -1.880,  -.989,  
     4  -.096,   .799,  1.694,  2.591,  3.489,  4.388,  5.288,  6.188,  
     8           .000,   .759,  1.362,  2.037,  2.731,  3.430,  4.130,  
     9  4.832,  5.538,  6.250,  6.968,  7.694,  8.428,  9.172,  9.926,  
     * 10.692, 11.470, 12.257, 13.054, 13.860, 14.675, 15.499, 16.331,  
     1 17.170, 18.017, 18.872, 19.732, 20.599, 21.472, 22.350, 23.234,  
     2 24.122, 25.016, 25.915, 26.818, 27.727, 28.640, 29.559, 30.481,  
     3 31.409, 32.341/  
C
C --- SPECIFIC HEAT CAPACITY AT CONSTANT PRESSURE 
C
      DATA (CT(I),I=1,123)/                     7.050,  6.880,  6.875,  
     6  7.030,  7.210,  7.430,  7.670,  7.883,  8.063,  8.212,  8.336,  
     7  8.439,  8.527,  8.604,  8.674,  8.738,  8.800,  8.858,  8.916,  
     8  8.973,  9.029,  9.084,  9.139,  9.194,  9.248,  9.301,  9.354,  
     9  9.405,  9.455,  9.503,  9.551,  9.596,  9.640,  9.682,  9.723,  
     *  9.762,  9.799,  9.835,  9.869,  9.901,  9.932,  
     *  7.885,  7.945,  7.980,  8.045,  8.195,  8.420,  8.676,  8.954,  
     1  9.246,  9.547,  9.851, 10.152, 10.444, 10.723, 10.987, 11.233,  
     2 11.462, 11.674, 11.869, 12.048, 12.214, 12.366, 12.505, 12.634,  
     3 12.753, 12.863, 12.965, 13.059, 13.146, 13.228, 13.304, 13.374,  
     4 13.441, 13.503, 13.562, 13.617, 13.669, 13.718, 13.764, 13.808,  
     5 13.850,                  7.405,  7.420,  7.435,  8.825,  9.895,  
     * 10.669, 11.310, 11.846, 12.293, 12.667, 12.980, 13.243, 13.466,  
     6 13.656, 13.815, 13.953, 14.074, 14.177, 14.269, 14.352, 14.424,  
     7 14.489, 14.547, 14.600, 14.648, 14.692, 14.734, 14.771, 14.807,  
     8 14.841, 14.873, 14.902, 14.930, 14.956, 14.982, 15.006, 15.030,  
     9 15.053, 15.075, 15.097, 15.119/  
      DATA (CT(I),I=124,246)/                           6.850,  6.940,  
     *  6.950,  6.960,  6.993,  7.067,  7.196,  7.350,  7.512,  7.670,  
     *  7.815,  7.945,  8.061,  8.162,  8.252,  8.330,  8.398,  8.458,  
     1  8.512,  8.559,  8.601,  8.638,  8.672,  8.703,  8.731,  8.756,  
     2  8.779,  8.800,  8.820,  8.838,  8.855,  8.871,  8.886,  8.900,  
     3  8.914,  8.927,  8.939,  8.950,  8.962,  8.972,  8.983,  6.800,  
     7  6.940,  6.956,  6.965,  7.013,  7.120,  7.276,  7.450,  7.624,  
     8  7.786,  7.931,  8.057,  8.168,  8.263,  8.346,  8.417,  8.480,  
     9  8.535,  8.583,  8.626,  8.664,  8.698,  8.728,  8.756,  8.781,  
     *  8.804,  8.825,  8.844,  8.863,  8.879,  8.895,  8.910,  8.924,  
     1  8.937,  8.949,  8.961,  8.973,  8.984,  8.994,  9.004,  9.014,  
     8          7.590,  6.810,  6.390,  6.895,  6.974,  6.993,  7.009,  
     9  7.036,  7.087,  7.148,  7.219,  7.300,  7.390,  7.490,  7.600,  
     *  7.720,  7.823,  7.921,  8.016,  8.108,  8.195,  8.279,  8.358,  
     1  8.434,  8.506,  8.575,  8.639,  8.700,  8.757,  8.810,  8.859,  
     2  8.911,  8.962,  9.012,  9.061,  9.110,  9.158,  9.205,  9.252,  
     3  9.297,  9.342/  
C
C---  ABSOLUTE ENTROPY
C
      DATA (ST(I),I=1,123)/                             0.000, 41.421,
     2 46.244, 49.073, 51.117, 52.748, 54.124, 55.275, 56.387, 57.346,
     3 58.218, 59.017, 59.755, 60.441, 61.081, 61.682, 62.248, 62.783,
     4 63.291, 63.775, 64.236, 64.678, 65.102, 65.509, 65.902, 66.280,
     5 66.646, 67.000, 67.343, 67.676, 67.999, 68.309, 68.618, 68.911,
     6 69.205, 69.564, 69.763, 70.029, 70.295, 70.548, 70.805,
     1  0.000, 36.422, 41.942, 45.181, 47.510, 49.360, 50.917, 52.275,
     2 53.490, 54.596, 55.618, 56.571, 57.467, 58.314, 59.118, 59.885,
     3 60.602, 61.304, 61.976, 62.623, 63.245, 63.845, 64.442, 64.981,
     4 65.521, 66.044, 66.551, 67.042, 67.518, 67.980, 68.447, 68.879,
     5 69.310, 69.719, 70.128, 70.517, 70.907, 71.278, 71.648, 71.817,
     6 72.357,
     1  0.000, 42.798, 47.784, 51.141, 53.843, 56.135, 58.138, 59.922,
     2 61.533, 63.003, 64.355, 65.605, 66.766, 67.851, 68.869, 69.827,
     3 70.731, 71.587, 72.400, 73.173, 73.911, 74.616, 75.292, 75.939,
     4 76.562, 77.161, 77.738, 78.293, 78.831, 79.351, 79.855, 80.336,
     5 80.817, 81.270, 81.724, 81.991, 82.258, 82.894, 83.394, 83.781,
     6 84.168/
      DATA (ST(I),I=124,246)/
     1  0.000, 38.187, 43.007, 45.828, 47.832, 49.400, 50.699, 51.820,
     2 52.811, 53.705, 54.520, 55.271, 55.968, 56.617, 57.224, 57.796,
     3 58.336, 58.847, 59.332, 59.794, 60.233, 60.654, 61.057, 61.443,
     4 61.813, 62.170, 62.514, 62.846, 63.166, 63.476, 63.776, 64.064,
     5 64.348, 64.618, 64.888, 65.143, 65.398, 65.639, 65.881, 66.111,
     6 66.341,
     1  0.000, 39.620, 44.450, 47.272, 49.279, 50.855, 52.166, 53.300,
     2 54.306, 55.213, 56.041, 56.803, 57.508, 58.781, 59.360, 59.905,
     3 60.421, 60.910, 61.374, 61.375, 61.818, 62.241, 62.646, 63.035,
     4 63.408, 63.767, 64.113, 64.445, 64.768, 65.080, 65.381, 65.668,
     5 65.995, 66.226, 66.497, 66.753, 67.009, 67.252, 67.495, 67.726,
     6 67.956,
     1  0.000, 24.407, 28.539, 31.227, 33.265, 34.823, 36.099, 37.182,
     2 38.124, 38.963, 39.719, 40.411, 41.049, 41.644, 42.203, 42.732,
     3 43.233, 43.711, 44.166, 44.601, 45.019, 45.421, 45.808, 46.181,
     4 46.542, 46.890, 47.228, 47.555, 47.872, 48.181, 48.479, 48.768,
     5 49.054, 49.570, 49.600, 49.861, 50.121, 50.370, 50.619, 50.858,
     6 51.096/
C *********************************************************************  
C
      IF(P .LE. 0.) P=1.
      F=PHI   
C   
C --- TEST IF FUEL COMPOSITION IS ACCEPTED  
      IF(IERR .NE. 0) THEN
      IWAR=-1
      GO TO 9999
      ENDIF
C   
C --- COMPUTE FUNCTIONS OF F.   
C   
      IF(ABS(F-FPR) .LT. 0.000001) GO TO 2000   
      IF(F .GE. 0.0) GO TO 1010 
      IWAR=1
      F=0.0 
 1010 CONTINUE  
      IF(F .LE. FMAX) GO TO 1020
      IWAR=2
      F=FMAX
 1020 CONTINUE  
      IF(F .GE. 0.0 .AND. F .LE. 1.0)  J=1  
      IF(F .GT. 1.0 .AND. F.LE. FA)    J=2  
      IF(F .GT. FA  .AND. F .LE. FB)   J=3  
C   
C ---  COMPUTE MOLE FRACTIONS AND DERIVATIVES   
C
      FACT=1.0/(AA(8,J)+BB(8,J)*F)
      DO 1100 I=1,7 
      X(I)=(AA(I,J)+BB(I,J)*F)*FACT   
      DXF(I)=(BB(I,J)-BB(8,J)*X(I))*FACT  
 1100 CONTINUE  
      FPR=F 
 2000 CONTINUE  
C   
C --- COMPUTE FUNCTIONS OF T
      IF(ABS(T-TPR) .LT. 0.02) GO TO 3000   
      IF(T .GE. 0.0) GO TO 2010 
      IWAR=IWAR+10  
      T=0.0 
 2010 CONTINUE  
      IF(T .LE. 4000.) GO TO 2020   
      IWAR=IWAR+20  
      T=4000.   
 2020 CONTINUE  
C
      TK=0.01*T 
      IT=TK 
      FR=TK-FLOAT(IT)   
      DO 2100 I=1,6 
      IN=41*I+IT-40 
      SH(I)=HT(IN)+FR*(HT(IN+1)-HT(IN)) 
      SC(I)=CT(IN)+FR*(CT(IN+1)-CT(IN))
      SS(I)=ST(IN)+FR*(ST(IN+1)-ST(IN))
 2100 CONTINUE  
      SH(7)=0.0049682*T 
      SC(7)=4.9682
      SS(7)=36.9822 
      IF(T .GT. 0.) SS(7)=SS(7)+SC(7)*DLOG(T/293.15)
C   
C --- TRANSFORM TO SI-UNITS 
      DO 2200 I=1,7 
      SH(I)=4184000.*SH(I)  
      SC(I)=4184.*SC(I)   
      SS(I)=4184.*SS(I)
 2200 CONTINUE  
      TPR=T 
      GO TO 3010
C --------------------------------------------------------------
C   
 3000 CONTINUE  
      IF(ABS(P-PPR) .LT. 0.001E5) GO TO 3100
 3010 CONTINUE
C --- ADD PRESSURE DEPENDENCE
      DO 3050 I=1,7
      SST(I)=0.
      IF(X(I) .GT. 0.) SST(I)=SS(I)-R0*(DLOG(P/P0)+DLOG(X(I)))
 3050 CONTINUE
      PPR=P
C --------------------------------------------------------------
 3100 CONTINUE
C --- COMPUTE SPECIFIC MOLAR PROPERTIES (PER MOLE)   
      MF=0.0
      HTF=0.0   
      CPTF=0.0  
      STF=0.0
C   
      DO 3500 I=1,7 
      MF=MF+X(I)*SM(I)  
      HTF=HTF+X(I)*SH(I)
      STF=STF+X(I)*SST(I)
      CPTF=CPTF+X(I)*SC(I) 
 3500 CONTINUE
C
C --- GAS CONSTANT AND DRF
C  
      UTF =HTF-R0*T
      GTF =HTF-STF*T
      ATF =UTF-STF*T
C
C --- DERIVATIVES W.R.T.  T,P,F  (MOLAR BASIS)
C
      DMFDT=0.
      DRDT=0.
      DHTDT=CPTF
      DUTDT=DHTDT-R0
      DSTDT=CPTF
      IF(T .GT. 0.) DSTDT=CPTF/T
      DGTDT=DHTDT-STF-T*DSTDT
      DATDT=DUTDT-STF-T*DSTDT
C
      DMFDP =0.
      DRDP =0.
      DHTDP=0.
      DUTDP=0.
      DSTDP=-R0/P
      DGTDP=R0*T/P
      DATDP=R0*T/P
C
      DMFDF=0.
      DHTDF=0.
      DSTDF=0.
C
      DO 2150 I=1,7
      DMFDF =DMFDF+DXF(I)*SM(I)
      DHTDF=DHTDF+DXF(I)*SH(I)
      DSTDF=DSTDF+DXF(I)*(SS(I) -R0)
 2150 CONTINUE
C
      DUTDF=DHTDF
      DGTDF=DHTDF-DSTDF*T
      DATDF=DUTDF-DSTDF*T
C
C --- SPECIFIC PROPERTIES (PER KG)
C
      R=R0/MF   
      H=HTF/MF  
      U=UTF/MF
      S=STF/MF
      G=GTF/MF
      A=ATF/MF
C   
      DRDT=0.
      DHDT=DHTDT/MF   
      DUDT=DUTDT/MF
      DSDT=DSTDT/MF
      DGDT=DGTDT/MF
      DADT=DATDT/MF
C
      DRDP=0.
      DHDP=0.
      DUDP=0.
      DSDP=-R0/(P*MF)
      DGDP=R0*T/(P*MF)
      DADP=R0*T/(P*MF)
C
      DRDF=-R*DMFDF/MF
      DHDF=(DHTDF-H*DMFDF)/MF
      DUDF=(DUTDF-U*DMFDF)/MF
      DSDF=(DSTDF-S*DMFDF)/MF
      DGDF=(DGTDF-G*DMFDF)/MF
      DADF=(DATDF-A*DMFDF)/MF
C
      GAM=DHDT/(DHDT-R)
C ---------------------------------------------------------------------
 9999 RETURN
      END 

      SUBROUTINE SETFAM(FC,AC)  
C:***************************************************************   
C   
C  LAST CORRECTION BY: H.VALLAND
C  DATE:  1983-03-10
C   
C  PURPOSE: 
C     THE ROUTINE ENTERS THE FUEL COMPOSITION PARAMETERS INTO   
C     COMMON /SIBLOC/ AND PERFORM INITIAL COMPUTATION OF  CONSTANTS. 
C   
C  CALLING SEQUENCE:
C     CALL SETFAM(FC,AC)
C   
C  INPUT:   
C     ARGUMENTS:
C       FUEL COMPOSITION:   
C        FC(1)    NUMBER OF CARBON ATOMS IN FUEL MOLECULE   
C        FC(2)    ..     .. HYDROGEN  ..      ..       ..   
C        FC(3)    ..     .. OXYGEN    ..      ..       ..   
C        FC(4)    ..     .. NITROGEN  ..      ..       ..   
C   
C       OXIDANT COMPOSITION:
C        AC(1)    NUMBER OF N2  MOLES PER MOLE O2   
C        AC(2)    ..     .. AR  ..    ..  ..   ..   
C        AC(3)    ..     .. CO  ..    ..  ..   ..   
C        AC(4)    ..     .. CO2 ..    ..  ..   ..   
C        AC(5)    ..     .. H2O ..    ..  ..   ..   
C        AC(6)    ..     .. H2  ..    ..  ..   ..   
C   
C     COMMON /PROPT/:   
C        SM    MOLE MASS OF THE PRODUCT SPECIES:
C              SM(1) - O2   OXYGEN  
C              SM(2) - H2O  WATER VAPOR 
C              SM(3) - CO2  CARBON DIOXYDE  
C              SM(4) - N2   NITROGEN
C              SM(5) - CO   CARBON MONOXYDE 
C              SM(6) - H2   HYDROGEN
C              SM(7) - AR   ARGON   
C   
C  OUTPUT:  
C     COMMON /SIBLOC/:   
C        FS    FUEL AIR MASS RATIO AT STOECHIOMETRIC COMBUSTION 
C        FA    VALUE OF F AT WHICH ALL CARBON PRODUCE CO ONLY   
C        FB    VALUE OF F AT WHICH ALL HYDROGEN PRODUCE H2 ONLY 
C        FMAX  MAX VALUE OF F, ABOVE THIS VALUE NO MORE FUEL
C              CAN BE BURNED INTO CO2, H2O, CO, AND H2. 
C        A     MATRIX CONTAINING THE COEFFICIENTS FOR COMPUTATION   
C              OF PRODUCTS COMPOSITION: 
C              A(I,J) CONTAIN COEFFICIENT A FOR SPECIE NUMBER I 
C                     IN F-REGION NUMBER J: 
C                     J = 1  FOR  0.0 .LE. F .AND. F .LE. 1.0   
C                       = 2  FOR  1.0 .LT. F .AND. F .LE. FA
C                       = 3  FOR   FA .LT. F .AND. F .LE. FB
C        B     B(I,J) CONTAINS COEFFICIENT B FOR SPECIE NUMBER I
C                     IN F-REGION NUMBER J. 
C   
C  PROGRAMMED BY:  H. VALLAND   
C  DATE:  1983-03-10
C   
C:****************************************************************  
C   
      IMPLICIT REAL*8 (A-H,O-Z)
C

      REAL*8 FC(4),AC(6) 
C
C************************************************************************
C   
c     REAL*8 MF   
      INTEGER*4 KLO,IERR
C
      COMMON /SIBLOC/ FFC(4),AAC(6),PHI,T,P,KLO,IERR,
     +              FS,FA,FB,FMAX,A(8,3),B(8,3),TPR,FPR,PPR
C
      EQUIVALENCE (FFC(1),AN),(FFC(2),AM),(FFC(3),AL),(FFC(4),AK)
      EQUIVALENCE (AAC(1),B1),(AAC(2),B2),(AAC(3),B3),(AAC(4),B4),
     +            (AAC(5),B5),(AAC(6),B6)
C
      REAL*8 SM(7)
      DATA SM/31.999, 18.016, 44.010, 28.013, 28.011, 2.016, 39.944/
C *********************************************************************   
C
C   
C --- INITIALIZE SOME CONSTANTS 
C   
      IERR=0
      TPR=-1.0  
      FPR=-1.0  
      FA=0.0
      FB=0.0
      FMAX=0.0  
      DO 1000 I=1,8 
      DO 1000 J=1,3 
      A(I,J)=0.0
      B(I,J)=0.0
 1000 CONTINUE  
C   
      AN=FC(1)  
      AM=FC(2)  
      AL=FC(3)  
      AK=FC(4)  
      B1=AC(1)  
      B2=AC(2)  
      B3=AC(3)  
      B4=AC(4)  
      B5=AC(5)  
      B6=AC(6)  
      D=AN+0.25*AM-0.5*AL   
      E=0.25*AM+0.5*AL+0.5*AK   
      EE=1.0-0.5*(B3+B6)
C   
C --- CHECK IF FUEL CAN BE BURNED IN OXIDANT
      IF(D*EE .GT. 0.0) GO TO 2000  
      IERR=1
      GO TO 9999
 2000 CONTINUE  
C   
      G=D/EE
      Q=B5+B6   
      Y=B3+B4   
      W=B1+B2+B3+B4+B5+B6   
C   
C --- STOECHIOMETRIC FUEL-AIR-RATIO 
      WF=12.011*AN+1.008*AM+16.000*AL+14.0065*AK
      WA=G*(SM(1)+B1*SM(4)+B2*SM(7)+B3*SM(5)+B4*SM(3)+B5*SM(2)+B6*SM(6))
      FS=WF/WA  
C   
C --- GENERATE A AND B COEFFICIENTS IN REGION NO. 1 
      A(1,1)=D  
      A(2,1)=Q*G
      A(3,1)=Y*G
      A(4,1)=B1*G   
      A(7,1)=B2*G   
      A(8,1)=D+W*G  
      B(1,1)=-D 
      B(2,1)=0.5*AM 
      B(3,1)=AN 
      B(4,1)=0.5*AK 
      B(8,1)=E  
      FMAX=1.0  
      IF(AN .LT. 0.0001) GO TO 9999 
      GG=AN+0.5*AM-AL   
C   
C --- TEST IF OXYDATION OF CO2 TO CO IS POSSIBLE
C     DO REGON NO. 2 EXIST? 
      IF(GG .LT. 0.0001) GO TO 9999 
      FA=G*(2.0+B4-B6)/(AN+0.5*AM-AL)   
      B32=(Y*G+AN)/(FA-1.0) 
      B52=(Y*G+AN*FA)/(FA-1.0)  
      A(2,2)=Q*G
      A(3,2)=B32*FA 
      A(4,2)=B1*G   
      A(5,2)=-B52   
      A(7,2)=B2*G   
      A(8,2)=W*G
      B(2,2)=0.5*AM 
      B(3,2)=-B32   
      B(4,2)=0.5*AK 
      B(5,2)=B52
      B(8,2)=D+E
      FMAX=FA   
      IF(AM .LT. 0.0001) GO TO 9999 
C   
C --- TEST IF HYDROGEN FORMATION IS POSSIBLE
C     DO REGION NO. 3 EXIST?
      IF(AN-AL .LT. 0.0001) GO TO 9999  
      FB=G*(2.0+B4+B5)/(AN-AL)  
      B23=(Q*G+0.5*AM*FA)/(FB-FA)   
      B63=(Q*G+0.5*AM*FB)/(FB-FA)   
      A(2,3)=B23*FB 
      A(4,3)=B1*G   
      A(5,3)=Y*G
      A(6,3)=-B63*FA
      A(7,3)=B2*G   
      A(8,3)=W*G
      B(2,3)=-B23   
      B(4,3)=0.5*AK 
      B(5,3)=AN 
      B(6,3)=B63
      B(8,3)=D+E
      FMAX=FB   
C   
 9999 RETURN
      END   
      SUBROUTINE THERMO(PPIN,TTIN,FFIN,DCO,R,CP,CV,U,H,S,K,UP,UT,UF,RP,
     &     RT,RF,FAULT)
*************************************************************************
C     This subroutine calculates the thermodynamical gas properties
C     from Zacharias formulae. Free state variables are:
C
C     P  pressure
C     T  temperature
C     F  equivalence ratio
C
C     Dependent variables:
C
C     R  gas constant
C     U  internal energy
C     H  enthalpy
C     S  entropi
C     K  ratio of specific heats
C     UP,UT,UF  Partial derivatives of U with respect to P,T,F
C     RP,RT,RF  Partial derivatives of R with respect to P,T,F
C
C     Control variable:
C
C     DCO=0  Ideal gas properties and real-gas correction is employed
C     DCO=1  Correction for lower stage dissociation
C     DCO=2  Correction for upper stage dissociation
C
C     SI units!

      IMPLICIT NONE

      INTEGER*4 DCO,FAULT

      REAL*8 K,LNT2,ZZP,F,ZZT,H,ZZV,HH,P,R,S,ZZ,FC0,EP0,EP1,EP2,
     &     EP3,EP4,EP5,EP6,PA,PAT,PAV,PB,FC1,FC2,FC3,FC4,FC5,FC6,
     &     FC7,FC8,Y,YV,YT,YP,EY,AZ,AZV,AZP,AH,AHV,AHP,CP,CV,T,
     &     U,V,RF,UF,PP,HHP,RP,HHT,UT,UP,SS,HHV,RT,TT,LNPP
      REAL*8 PPIN,TTIN,FFIN

C     Test if input parameters are out of range:
      
      P=PPIN
      T=TTIN
      F=FFIN
C --- EPE's fix
      p=dmax1(100.0d0,dmin1(1.0d8,p))
      t=dmax1(200.0d0,dmin1(6.0d3,t))
      f=dmax1(0.0d0,dmin1(1.0d0,f))
C --- EPS's fix slutt
      GO TO 719
  718  WRITE(*,*)' Subroutine THERMO: Input paras out of range '
       WRITE(*,*)' P = ',P
       WRITE(*,*)' T = ',T
       WRITE(*,*)' F = ',F
      P=1.0D6
      T=200.0D0
      F=0.0D0
      FAULT=1
      GO TO 730

 719  CONTINUE
      FAULT=0
      FC0 = 1.01972D-5
      TT  = 1.0D-3*T
      PP  = FC0*P
      V   = (1.0D0-F)/(1.0D0+6.98D-2*F)

      EP0 = 3.514956     -0.005026*V
      EP1 =  0.131438     -0.383504*V
      EP2 =  0.477182     +0.185214*V
      EP3 = -0.287367     -0.694862E-1*V
      EP4 =  0.742561E-1  +0.164041E-1*V
      EP5 = -0.916344E-2  -0.204537E-2*V
      EP6 =  0.439896E-3  +0.101610E-3*V
      PA  = EP0+TT*(EP1+TT*(EP2+TT*(EP3+TT*(EP4+TT*(EP5+TT*EP6)))))
      PAT = EP1+TT*(2.0D0*EP2+TT*(3.0D0*EP3+TT*(4.0D0*EP4+TT*(5.0D0*EP5+
     &     TT*6.0D0*EP6))))
      PAV = -5.06D-3+TT*(-3.83504D-1+TT*(1.85214D-1+TT*(-6.94862D-2
     &     +TT*(1.64041D-2+TT*(-2.04537D-3+TT*1.01610D-4)))))
      PB  = 2.972979D0+5.5314D-1*V+TT*(5.83837D-2-4.85001D-1*V+TT*(
     &     8.71349D-1+6.98183D-2*V+TT*(-4.51556D-1-2.8772D-3*V+TT*(
     &     1.09164D-1-6.93663D-4*V+TT*(1.29754D-2+9.20231D-5*V+TT*(
     &     6.08234D-4-2.99679D-6*V))))))
      FC1 = -8.05214D-1+V*(-4.00981D-1+V*(5.76989+6.0056D-2*V))
      FC2 = 2.77105D-4-0.900711D-4*V
      FC3 = 6.42217D-4-0.983670D-4*V
      FC4 = 0.88680D-2-0.613100D-2*V
      LNPP= DLOG(PP)
      FC5 = TT*TT
      FC6 = DEXP(FC4/FC5)/TT
      FC7 = PP/TT
      FC8 = 1.0D0+FC4/FC5
      ZZ  = FC7*(FC3-FC2*FC6)+1.0D0
      ZZV = FC7*(9.8367D-5-FC6*(9.00711D-5-6.131D-4*FC2/FC5))
      ZZT = FC7*(FC2*FC6*(FC8+1.0D0)-FC3)/TT
      ZZP = (FC3-FC2*FC6)/TT
      HH  = PA-ZZT*TT
      HHP = -ZZT*TT/PP
      HHT = -FC7/TT*(FC3-4.0D0*FC2*FC6*(FC8*FC8+FC4/FC5))+PAT
      HHV = FC7*(-9.8367D-5-2.0D0*FC6*(FC8*(-9.00711D-5
     &     -6.131D-3*FC2/FC5)-6.131D-3*FC2/FC5))+PAV
      SS  = (3.5566D0-6.59D-2*V)*DLOG(T)+PB-FC1-LNPP
      SS  = SS-FC7*FC2*FC6*FC8
      IF(DCO.EQ.0)GO TO 720

C     Correction for lower stage dissociation:

      LNT2= DLOG(TT/1.65D0)
      EP0 = EXP(7.0D-3*LNPP)
      EP1 = EXP(1.15D-2*LNPP)
      EP2 = EXP(-3.453D-2*LNPP)
      EP3 = EXP(-1.03D-1*LNPP)
      EP4 = EXP(-1.27D-1*LNPP)
      EP5 = EXP(-2.12D-2*LNPP)
      EP6 = EXP(-3.06D-1*TT)
      FC1 = -5.1D-1*EP3-1.4D-1+(1.2D-1-2.9D-1*EP4)*LNT2
      FC2 = (1.0D0-V)*(1.0D0-(1.0D0-V)*(1.0D0-V)*(1.0D0-V)*
     &     2.772D-1)*9.088D-1*EP5
      FC3 = (5.73D-1+8.3D-2*LNPP)*EP6
      FC4 = 1.5D1*EXP(FC1*LNT2)
      Y   = FC4-6.9078D0-FC2+FC3
      YV  = (1.0D0-(1.0D0-V)*(1.0D0-V)*(1.0D0-V)*1.1088D0)*
     &     9.088*EP5
      YT  = FC4*(FC1+LNT2*(1.2D-1-2.9D-1*EP4))/TT-3.06D-1*FC3
      YP  = (FC4*LNT2*(5.253D-2*EP3+3.683D-2*EP4*LNT2)+FC2*
     &     2.12D-2+8.3D-2*EP6)/PP
      EY  = EXP(Y)/TT
      FC5 = 1.0D0+EY
      FC6 = FC5*FC5
      FC7 = FC5*TT
      FC8 = FC7*FC7
      AZ  = (4.2D-1-1.93D-1*V)*EP0
      AZV = 1.93D-1*EP0
      AZP = AZ*7.0D-3/PP
      ZZ  = AZ/FC5+ZZ
      ZZV = ZZV+(AZV+EY*(AZV-AZ*YV))/FC6
      ZZP = ZZP+(AZP+EY*(AZP-AZ*YP))/FC6
      ZZT = ZZT+(AZ*EY*(1.0D0/TT-YT))/FC6
      AH  = (2.59D1-1.1D1*V)*EP1
      AHV = -1.1D1*EP1
      AHP = AH*1.15D-2/PP
      HH  = AH/FC7+HH
      HHV = HHV+(EY*TT*(AHV-AH*YV)+TT*AHV)/FC8
      HHP = HHP+(EY*TT*(AHP-AH*YP)+TT*AHP)/FC8
      HHT = HHT-AH*(1.0D0+EY*TT*YT)/FC8
      SS  = SS+(8.179D0-3.726D0*V)*EP2/FC5
      IF(DCO.EQ.1)GO TO 720

C     Correction for upper stage dissociation

      EP0 = EXP(-5.648-2*LNPP)
      EP1 = EXP(-4.5D-2*LNPP)
      Y   = 1.80972D1-2.43D0*TT*EP1
      YT  = -2.43D0*EP1
      YP  = -2.43D0*TT*EP1*(-4.5D-2/PP)
      EY  = EXP(Y)/TT
      FC1 = 1.0D0+EY
      FC2 = FC1*FC1
      AZ  = 7.74D-1-1.19D-1*V-(1.28D-2+5.0D-3*V)*LNPP
      AZV = -1.19D-1-5.0D-3*LNPP
      AZP = (-1.28D-2-5.0D-3*V)/PP
      ZZ  = ZZ+AZ/FC1
      ZZV = ZZV+(AZV+EY*AZV)/FC2
      ZZP = ZZP+(AZP+EY*(AZP-AZ*YP))/FC2
      ZZT = ZZT+AZ*EY*(1.0D0/TT-YT)/FC2
      AH  = 8.65D1-3.065D0*LNPP-1.435D1*V
      AHP = -3.065D0/PP
      AHV = -1.435D1
      HH  = HH+AH/(TT*FC1)
      HHV = HHV+(EY*AHV+AHV)/(TT*FC2)
      HHP = HHP+(EY*(AHP-AH*YP)+AHP)/(TT*FC2)
      HHT = HHT-AH*(1.0D0+EY*TT*YT)/(TT*TT*FC2)
      SS  = SS+(1.4512D1*EP0-2.434D0*V)/FC1
 720  CONTINUE

C     Calculation of properties and derivatives:

      FC1 = 8.3147D3*(3.333333D-1*F+4.773384D0)/
     &     (9.344254D0*F+1.382266D2)
      FC2 = -1.471965D0/((3.333333D-1*F+4.773384D0)*
     &     (9.344254D0*F+1.382266D2))
      FC3 = -1.0698D0/((1.0D0+6.98D-2*F)*(1.0D0+6.98D2*F))
      R   = FC1*ZZ
      H   = FC1*T*HH
      S   = FC1*SS
      U   = H-R*T
      RF  = FC1*(ZZV*FC3-ZZ*FC2)
      RP  = FC1*ZZP*FC0
      RT  = FC1*ZZT*1.0D-3
      UF  = FC1*T*((HHV-ZZV)*FC3-(HH-ZZ)*FC2)
      UP  = FC1*T*(HHP-ZZP)*FC0
      UT  = FC1*(HH-ZZ+TT*(HHT-ZZT))
      CP  = FC1*(HH+TT*HHT)
      CV  = UT+UP*(R/T+RT)/(R/P-RP)
      K   = CP/CV

 730  CONTINUE

C     End THERMO/Zacharias

      RETURN
      END
