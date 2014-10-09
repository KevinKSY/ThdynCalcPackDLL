      SUBROUTINE turbin(pu,pd,fu,fd,tu,td,omegat,
     &                  aturb,rturb,medium,fs,
     &                  momt,dmtu,dmtd,dmftu,dmftd,deu,ded)
C -------------------------------------------------------------------
C 
C                  TURBIN DOCUMENTATION: 
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
C  This subroutine calculates the mass and energy flow through
C  the turbine and the shaft torque based on the input variables.
C     
C  Based on work by H.S.Landas, Elif Pedersen etc. 
C
C
C  Required routines: (Included in this file at the end)
C  =================
C  Name:                Function:
C  =====                =========
C  Turbdys.f            - Calculate nozzle flow
C  Turdata.f            - Includes the turbine data
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  PU           R*8     - Upstream pressure
C  PD           R*8     - Downstream pressure
C  FU           R*8     - Upstream fuelfactor
C  FD           R*8     - Downstream fuelfactor
C  TU           R*8     - Upstream temperature 
C  TD           R*8     - Downstream temperature 
C  Aturb        R*8     - Effective turbine flow area 
C  Rturb        R*8     - Mean radius for the vanes
C  medium       R*8     - Medium parameter according to thdynp
C  FS           R*8     - Stoichiometric fuelfactor
C  omegat       R*8     - Turbine speed (rad/s)
C
C  Variances of this routeine:
C  vanes        LOG     - True if vanes are adjustable
C                         then adjust.f are called (available here)
C
C  Output: (upsteam and downstream values (u/d))
C  =============
C  dmtu         R*8     - Rate of mass flow
C  dmtd         R*8     - Rate of mass flow
C  dmftu        R*8     - Rate of combusted mass flow 
C  dmftd        R*8     - Rate of combusted mass flow
C  deu          R*8     - Rate of energy flow in to the turbine
C  ded          R*8     - Rate of energy flow out of the turbine
C  momt	        R*8     - Turbine torque 
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : E.Pedersen
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595786          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      IMPLICIT REAL*8 (a-h,o-z)
      REAL*8 momt, medium
      LOGICAL vanes
C -------------------------------------------------------------------
C --> In the case of adjustable vanes, vanes=.TRUE.
C -------------------------------------------------------------------
      vanes = .FALSE.
      angle = 13.0
C -------------------------------------------------------------------
C --> Find upstream enthalpy and kappa
C -------------------------------------------------------------------
      idco  = idint(medium)
      CALL thdynp(pu,tu,fu,idco,rt,cpt,cvt,ut,htu,st,rkt,
     +     upt,utt,uft,rpt,rtt,rft,ifault)
C -------------------------------------------------------------------
C --> Estimate Tis and find the isentropic entalphy downstream 
C -------------------------------------------------------------------
      tis    = tu*(pu/pd)**((1.0-rkt)/rkt)
      idco   = idint(medium)
      CALL thdynp(pd,tis,fu,idco,rt,cpt,cvt,ut,htisd,st,rkt,
     +     upt,utt,uft,rpt,rtt,rft,ifault)
      delhti = htu-htisd
C -------------------------------------------------------------------
C --> Finding flow coefficient and efficiency 
C -------------------------------------------------------------------
      omegat = max(omegat,1.0d-6)
      uc     = omegat*rturb/dsqrt(2.0d0*max(delhti,1.0e-10))
      pit    = pu/pd
      CALL turdata(pit,efft,alfat,uc)
      area  = aturb*alfat
C -------------------------------------------------------------------
C --> In the case of adjustable guide vanes 
C -------------------------------------------------------------------
      IF (vanes) THEN
         CALL adjust(angle,cda,cde)
         efft = efft*cde
         area = area*cda
      ENDIF
C -------------------------------------------------------------------
C --> Calculate turbine flow
C -------------------------------------------------------------------
      CALL turbdys(pu,pd,fu,fd,tu,td,area,idco,fs,dmt,dmft,dummy)
C -------------------------------------------------------------------
C --> Finding downstream enthalpy
C -------------------------------------------------------------------
      delht  = delhti*efft
      htd    = htu-delht
C -------------------------------------------------------------------
C --> Turbine torque and energy flow
C -------------------------------------------------------------------
      dmtu  = dmt
      dmtd  = dmt
      dmftu = dmft
      dmftd = dmft
      deu   = dmt*htu
      ded   = dmt*htd
      momt  = delht*dmt/omegat
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------
      SUBROUTINE TURBDYS(PU,PD,FU,FD,TU,TD,A,MEDIUM,FS,DM,DF,DE)
C -------------------------------------------------------------------
C 
C                 TURBDYS DOCUMENTATION: 
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
C  MEDIUM       I*4     - Thermodyn medium [0,1,2,3] se thdynp.f
C
C
C  Output:
C  =============
C
C  DM           R*8     - Rate of mass flow
C  DF           R*8     - Rate of combusted mass flow
C  DE           R*8     - Rate of energy flow
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
      INTEGER*4 MEDIUM
C -------------------------------------------------------------------
C --> Finding flow direction and thermodynamic properties
C -------------------------------------------------------------------
      AA   = PU/PD
      IDCO = MEDIUM
C --> Case of correct flow
      IF (AA.GT.1D0) THEN
         P = PU
         T = TU
         F = FU
	 CALL THDYNP(P,T,F,IDCO,
     &               RU,CPU,CVU,UU,HU,SU,KU,
     &               UPU,UTU,UFU,RPU,RTU,RFU,IFAULT)
         PCU = (2D0/(KU+1D0))**(KU/(KU-1D0))
         R   = RU
         K   = KU
         H   = HU
         C   = 1D0/PCU
         DIR = 1D0
C --> Case of reverse flow
      ELSE
         AA = 1D0/AA
         P  = PD
         F  = FD
         T  = TD
	 CALL THDYNP(P,T,F,ICDO,
     &               RD,CPD,CVD,UD,HD,SD,KD,
     &               UPD,UTD,UFD,RPD,RTD,RFD,IFAULT)
         PCD = (2D0/(KD+1D0))**(KD/(KD-1D0))
         R   = RD
         K   = KD
         H   = HD
         C   = 1D0/PCD
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
 721  DM = A*P/DSQRT(R*T)*KSI*DIR
      DF = F*FS/(1.0+F*FS)*DM
      DE = DM*H
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------
*
      SUBROUTINE TURDATA(PIT,EFFT,ALFAT,UC)
C -------------------------------------------------------------------
C 
C                 TURDATA DOCUMENTATION: 
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
C  This subroutine calculates the efficiency and 
C  flow coefficient for a turbine using the implemented
C  turbine performance chart.
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  PIT          R*8     - Pressure ratio
C  UC           R*8     - Velocity ratio
C
C
C  Output:
C  =============
C
C  EFFT         R*8     - Turbine efficiency (-)
C  ALFAT        R*8     - Flow coefficient
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
      IMPLICIT NONE
      REAL*8 PHIT(11),ETMX(11),ALFT(11),DALFT(11),DALFT65(11)
      REAL*8 PIT,UCOPT,XBAR,ETAM,ALTO,DALTO,DALTO65,EFFT,ALFAT,UC
      INTEGER NDAT,IX,I
C -------------------------------------------------------------------
C --> Implementation of performance chart
C -------------------------------------------------------------------
C --> Pressure ratios
      DATA(PHIT(I),I=1,8)/1.25,1.5,1.75,2.0,2.25,2.5,2.75,3/

C --> Maximum efficiency for the given pressure ratios
      DATA(ETMX(I),I=1,8)/0.805,0.812,0.82,0.827,0.825,0.817,
     &     0.806,0.805/

C --> Area coeffcient at zero relative blade speed
      DATA(ALFT(I),I=1,8)/0.715,0.775,0.83,0.877,0.907,0.917,0.921,
     &     0.921/

C --> Slope of the area coefficient line 
      DATA(DALFT(I),I=1,8)/-0.018,-0.018,-0.018,-0.018,-0.018,-0.018,
     &     -0.018,-0.018/
C --> Slope of the area coefficient line
C --> when relative blade speed > 0.65
      DATA(DALFT65(I),I=1,8)/-0.353,-0.353,-0.353,-0.353,-0.353,-0.353,
     &     -0.353,-0.353/

      save
C --> Number of pressure ratios
      NDAT    = 8
C --> Blade speed ratio at max efficiency
      UCOPT   = 0.65
C -------------------------------------------------------------------
C --> Interpolating to get flow coefficient and efficiency
C -------------------------------------------------------------------
C --> In the case of too high/low pressure ratio
      IF(PIT.LT.PHIT(1))PIT    = PHIT(1)
      IF(PIT.GT.PHIT(NDAT))PIT = PHIT(NDAT)

      XBAR    = (DBLE(NDAT-1)*PIT-DBLE(NDAT)*PHIT(1)+PHIT(NDAT))/
     &         (PHIT(NDAT)-PHIT(1))         
      IX      = IDINT(XBAR)
      ETAM    = ETMX(IX)+(ETMX(IX+1)-ETMX(IX))*(XBAR-DBLE(IX))
      ALTO    = ALFT(IX)+(ALFT(IX+1)-ALFT(IX))*(XBAR-DBLE(IX))
      DALTO   = DALFT(IX)+(DALFT(IX+1)-DALFT(IX))*(XBAR-DBLE(IX))
      DALTO65 = DALFT65(IX)+(DALFT65(IX+1)-DALFT65(IX))*(XBAR-DBLE(IX))
      EFFT    = ETAM*(2.0*UC/UCOPT-(UC/UCOPT)**2)
      EFFT    = MAX(0.0,MIN(EFFT,1.0))
      IF (UC .LT. UCOPT) THEN
         ALFAT = ALTO+UC*DALTO
      ELSE
         ALFAT = (ALTO+UCOPT*DALTO)+DALTO65*(UC-UCOPT)
      ENDIF
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------
      SUBROUTINE ADJUST(ang,cdarea,cdeff)
C -------------------------------------------------------------------
C 
C                 ADJUST DOCUMENTATION: 
C                ======================== 
C 
C 
C  FILING NO: MS1 FUNCTION
C 
C 
C  FOUR KEY WORDS:  MS1,BONDGRAPH,MODELLING, TURBINE
C 
C 
C  Abstract/Short Summary:
C  =======================
C
C  This routine returns the influence of adjusting the guide vanes
C  in a turbine
C
C
C  Input/Output:
C  =============
C
C  Input:
C
C  ang          R*8     - Angle of handle
C
C  Output:
C  =============
C
C  cdarea       R*8     - Influence on effective flow area
C  cdeff        R*8     - Influence on effectivity
C 
C  Date created : 110298            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      IMPLICIT REAL*8 (a-h,o-z)
      LOGICAL first
      COMMON /adj/first,angle(100),area(100),eff(100),ndata
      DATA first/.TRUE./
C -------------------------------------------------------------------
C --> Start of calculations done at first entry
C -------------------------------------------------------------------
C --> Reading influence data from file
      IF(first) THEN
         ifile = 12
         OPEN(ifile,FILE='adjust.dat',STATUS='UNKNOWN')
         READ(ifile,*) ndata
         DO I=1, ndata
            READ(ifile,*) angle(I), area(I), eff(I)
         END DO
         CLOSE (ifile)
         first = .FALSE.
      ENDIF
C -------------------------------------------------------------------
C --> End of calculations done at first entry
C -------------------------------------------------------------------
C --> Finding values for interpolating tables 
      IF(ang.LT.angle(1)) THEN
         nlo = 1
         nhi = 2
         GOTO 100
      ENDIF
      IF(ang.GT.angle(ndata)) THEN
         nlo = ndata - 1
         nhi = ndata
         GOTO 100
      ENDIF
      DO I=1, (ndata-1)
         IF (ang.GE.angle(I)) THEN
            nlo = I
            nhi = I+1
         ENDIF
      END DO
 100  CONTINUE
C --> Interpolating
      cdarea  = area(nlo)+(area(nhi)-area(nlo))*
     &     (ang-angle(nlo))/(angle(nhi)-angle(nlo))
      cdeff  = eff(nlo)+(eff(nhi)-eff(nlo))*
     &     (ang-angle(nlo))/(angle(nhi)-angle(nlo))
      RETURN
      END
C -------------------------------------------------------------------
C --> End of subroutine 
C -------------------------------------------------------------------
