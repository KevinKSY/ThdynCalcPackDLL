      SUBROUTINE VALVE(PU,PD,FU,FD,TU,TD,A,RMED,FS,
     +     DM,DMO,DF,DFO,DE,DEO)
C -------------------------------------------------------------------
C 
C                  VALVE DOCUMENTATION: 
C                ======================== 
C 
C 
C  FILING NO: MS1 FUNCTION
C 
C 
C  FOUR KEY WORDS:  MS1,BONDGRAPH,MODELLING, COMBUSTION
C 
C 
C  Abstract/Short Summary:
C  =======================
C     This subroutine calculates the rate of mass flow
C     through an idealized conv./div.-nozzle. 
C     The upstream state and properties have "subscript" U,
C     and downstream D. Reversed flow are handled,
C     but the flow direction definition are unchanged.
C     Based upon the work of Kurt Strand 15.09.85.
C     Changed for media with a given F-factor according
C     to the modelling of the cylinder process for a diesel engine
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  fid          R*8     - Crank angle
C  PU           R*8     - Upstream pressure
C  PD           R*8     - Downstream pressure
C  FU           R*8     - Upstream fuelfactor
C  FD           R*8     - Downstream fuelfactor
C  TU           R*8     - Upstream temperature 
C  TD           R*8     - Downstream temperature 
C  A            R*8     - Effective flow area 
C  FS           R*8     - Stoichiometric fuelfactor
C  RMED         R*8     - Thermodyn medium [0,1,2,3] se thermo.f
C
C  Output:
C  =============
C
C  DM           R*8     - Rate of mass flow
C  DMO          R*8     - Rate of mass flow
C  DF           R*8     - Rate of combusted mass flow
C  DFO          R*8     - Rate of combusted mass flow
C  DE           R*8     - Rate of energy flow
C  DEO          R*8     - Rate of energy flow
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      IMPLICIT REAL*8 (A-H,O-Z)
      REAL*8 PU,PD,FU,FD,TU,TD,KU,KD,RU,RD,A,DM,DF,DE
      REAL*8 AA,PCU,PCD,P,T,R,C,DIR,K,KSI
C -------------------------------------------------------------------
C --> Finding flow direction and thermodynamic properties
C -------------------------------------------------------------------
      IF(A .LT. 1.0E-10) THEN
        DM  =0.0
        DMO =0.0
        DF  =0.0
        DFO =0.0
        DE  =0.0
        DEO =0.0
        RETURN
      ENDIF

      AA = PU/PD
      IDCO=IDINT(RMED)
C --> Case of correct flow
      IF (AA.GT.1D0) THEN
         P = PU
         T = TU
         F = FU
	 CALL THDYNP(P,T,F,IDCO,
     &               RU,CPU,CVU,UU,HU,SU,KU,
     &               UPU,UTU,UFU,RPU,RTU,RFU,IFAULT)
         PCU = (2D0/(KU+1D0))**(KU/(KU-1D0))
         R = RU
         K = KU
         H = HU
         C = 1D0/PCU
         DIR = 1D0
C --> Case of reversed flow
      ELSE
         AA = 1D0/AA
         P = PD
         F = FD
         T = TD
	 CALL THDYNP(P,T,F,IDCO,
     &               RD,CPD,CVD,UD,HD,SD,KD,
     &               UPD,UTD,UFD,RPD,RTD,RFD,IFAULT)
         PCD = (2D0/(KD+1D0))**(KD/(KD-1D0))
         R = RD
         K = KD
         H = HD
         C = 1D0/PCD
         DIR = -1D0
      END IF
C -------------------------------------------------------------------
C --> Calculating nozzle coefficient
C -------------------------------------------------------------------
      IF (AA.LE.1.01D0) THEN
         KSI = DSQRT(2D0*K/(K-1D0)*(1.01D0**(-2D0/K)-
     &        1.01D0**(-(K+1D0)/K)))
         KSI = (AA-1D0)*KSI*100D0
         GO TO 721
      END IF
      IF (AA.GT.C) THEN
  	 KSI = DSQRT(K*((2D0/(K+1D0))**((K+1D0)/(K-1D0))))
      ELSE
	 KSI = DSQRT(2D0*K/(K-1D0)*(AA**(-2D0/K)-AA**(-(K+1D0)/K)))
      END IF
C -------------------------------------------------------------------
C --> Calculating the flow rates to be returned
C -------------------------------------------------------------------
 721  DM  = A*P/DSQRT(R*T)*KSI*DIR
      DMO = DM
      DF  = F*FS/(1.0+F*FS)*DM
      DFO = DF 
      DE  = DM*H
      DEO = DE
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------
      real*8 function VALAI(FID)
C -------------------------------------------------------------------
C 
C                  VALAI DOCUMENTATION: 
C                ======================== 
C 
C 
C  FILING NO: MS1 FUNCTION
C 
C 
C  FOUR KEY WORDS:  MS1,BONDGRAPH,MODELLING, COMBUSTION
C 
C 
C  Abstract/Short Summary:
C  =======================
C  This routine interpolates on inlet valve area data to obtain valve
C  area corresponding to computed crank angle. Flow coefficients and 
C  reference flow area are set manually in the routine.
C
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  Valveiub.dat         - Datafile with camlift versus crank angle
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  fid          R*8     - Crank angle
C
C  Output:
C  =============
C
C  VALAI        R*8     - Effective flow area
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
C
      IMPLICIT REAL*8 (A-H,O-Z)
      REAL*8 FID,AIV,FIDIOP,FIDICL
      REAL*8 AGI(100),LI(100),CAMI(100),CDI(100)
      REAL*8 XBAR
      INTEGER*4 NAI,IDFID
      LOGICAL first
      COMMON/VLVTIMI/NAI,FIDIOP,FIDICL,AGI,first
      DATA first/.TRUE./
C -------------------------------------------------------------------
C --> Start calculations done at first entry
C -------------------------------------------------------------------
      IF(first) THEN
C --> Read lift cam lift from data file
         OPEN(UNIT=20,FILE='ITVSCAN.dat',FORM='FORMATTED',STATUS='OLD')
         READ(20,*) NAI,FIDIOP,FIDICL
         DO I=1,NAI
            READ(20,*)CAMI(I)
C --> Multiply by mododulus and minus slack to find valve lift
            LI(I) = 1.29D0*CAMI(I) - 0.5 
            IF (LI(I) .LT. 0.0D0) THEN
               LI(I) = 0.0D0
            ENDIF
C --> Flow coefficient from measured data
            IF(LI(I).LE.2.0D0)THEN
               CDI(I) = 1.0D0 + 0.0825D0*LI(I)
            ELSEIF(LI(I).GT.2.0D0.AND.LI(I).LE.4.0D0)THEN
               CDI(I) = 1.05D0+0.0575*(LI(I)-2.0D0)
            ELSE
               CDI(I) = 1.165D0-0.020625*(LI(I)-4.0D0)
            ENDIF
C --> Effective flow area = Aref*CD*lift
            AGI(I) = 2.0D0*257.106D0*CDI(I)*LI(I)
         END DO
         first=.FALSE.
         CLOSE(20)
      ENDIF
C -------------------------------------------------------------------
C --> End of calculations done at first entry
C -------------------------------------------------------------------
C -------------------------------------------------------------------
C --> Calculate effective flow area
C -------------------------------------------------------------------
      IF(FID.GT.FIDIOP.AND.FID.LT.FIDICL) THEN
         XBAR  = (DBLE(NAI-1)*FID-DBLE(NAI)*FIDIOP+FIDICL)/
     &        (FIDICL-FIDIOP)
         IDFID = IDINT(XBAR)
         AIV   = AGI(IDFID)+(AGI(IDFID+1)-AGI(IDFID))*(XBAR-DBLE(IDFID))
         VALAI = AIV*1D-6
      ELSE
         VALAI=0.0
      ENDIF
      RETURN
      END  
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------

      REAL*8 FUNCTION VALAE(FID)
C -------------------------------------------------------------------
C 
C                  VALAE DOCUMENTATION: 
C                ======================== 
C 
C 
C  FILING NO: MS1 FUNCTION
C 
C 
C  FOUR KEY WORDS:  MS1,BONDGRAPH,MODELLING, COMBUSTION
C 
C 
C  Abstract/Short Summary:
C  =======================
C  This routine interpolates on exhaust valve area data
C  to obtain valve area corresponding to computed
C  crank angle.
C  The effective opening cross-sectional areas are calculated
C  by using the method described in: 'Zur Berechnung des 
C  geometrischen Offnungsquerschnitts von Kegelventilen'.
C  Based upon the work of Hallvard Engja
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  Valveub.dat         - Datafile with camlift versus crank angle
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  fid          R*8     - Crank angle
C
C  Output:
C  =============
C
C  VALAE        R*8     - Effective flow area
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      IMPLICIT REAL*8 (A-H,O-Z)
      REAL*8 FID,AEV,FIDEOP,FIDECL
      REAL*8 AGE(100),LE(100),CAME(100),CDE(100)
      REAL*8 XBAR,ld
      INTEGER*4 NAE,IDFID
      LOGICAL first
      COMMON/VLVTIME/NAE,FIDEOP,FIDECL,AGE,first
      DATA first/.TRUE./
C -------------------------------------------------------------------
C --> Start calculations done at first entry
C -------------------------------------------------------------------
      IF(first) THEN
         OPEN(UNIT=20,FILE='EXVSCAN.dat',FORM='FORMATTED',STATUS='OLD')
         READ(20,*) NAE,FIDEOP,FIDECL
         DO I=1,NAE
            READ(20,*)CAME(I)
C --> Multiply by mododulus and minus slack to find valve lift
            LE(I) = 1.29D0*CAME(I) - 0.7 
            IF (LE(I) .LT. 0.0D0) THEN
               LE(I) = 0.0D0
            ENDIF
C --> Flow coefficient from manufacturer
            ld = LE(I)/105.0D0
            IF(ld.LT.0.1D0)THEN
               CDE(I) = 5.1*ld
            ENDIF
            IF(ld.GE.0.1D0.AND.ld.LE.0.125D0)THEN
               CDE(I) = 0.51 + 4.8*(ld - 0.1)
            ENDIF
            IF(ld.GE.0.125D0.AND.ld.LE.0.25D0)THEN
               CDE(I) = 0.63 + 2.8*(ld - 0.125)
            ENDIF
            IF(ld.GE.0.25D0) THEN
               CDE(I) = 0.98 + 1.6*(ld - 0.25)
            ENDIF
C --> Effective flow area = Aref*CD*lift
            AGE(I) = 8659.0D0*CDE(I)
         END DO
         first=.FALSE.
         CLOSE(20)
      ENDIF
C -------------------------------------------------------------------
C --> End of calculations done at first entry
C -------------------------------------------------------------------
C -------------------------------------------------------------------
C --> Calculate effective flow area
C -------------------------------------------------------------------
      IF(FID.GT.FIDEOP.AND.FID.LT.FIDECL) THEN
         XBAR  = (DBLE(NAE-1)*FID-DBLE(NAE)*FIDEOP+FIDECL)
     &        /(FIDECL-FIDEOP)
         IDFID = IDINT(XBAR)
         AEV   = AGE(IDFID)+(AGE(IDFID+1)-AGE(IDFID))*(XBAR-DBLE(IDFID))
         VALAE = AEV*1D-6
      ELSE
         VALAE = 0.0
      ENDIF
      RETURN
      END  
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------



























