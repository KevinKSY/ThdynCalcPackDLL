      subroutine th1tpf(qp,qf,qt,vol,qmed,fs,T,P,F)
C  ------------------------------------------------------------------
C 
C                  TH1TPF DOCUMENTATION: 
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
C  This routine returns the pressure, temperature and
C  fuel factor, given the state varialbes mass, mass burnt and energy
C  and volume.
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  thermo.f             - Calculation of thermodynamic properies
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  qp           R*8     - Mass of gas in the cylinder
C  qf           R*8     - Mass of combusted gas in the cylinder
C  qt           R*8     - Total energy (U) in the volume
C  vol          R*8     - Volume of tank
C  qmed	        R*8     - Medium, i.e selection of thermodynamic package
C                         Default value = 0
C  fs           R*8     - Stochiometric fuel/air ratio
C
C  Output:
C  =============
C  P            R*8     - Pressure in volume
C  T            R*8     - Temperature in volume
C  F            R*8     - Fuel factor in volume
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : E.Pedersen        By           :  O.Bunes  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  OBU/EPE 
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C  ------------------------------------------------------------------
C
      implicit real*8 (a-h,o-z)
C
      parameter (ntemp=41,nfact=10)
C
      real*8 qp,qf,qt,vol,qmed
      real*8 ht
      logical ifirst
c
      common /media/deltaT,deltaF,htab(ntemp,nfact),rtab(nfact)
      common /res/ht(ntemp),ifirst
C
      data ifirst /.false./
C
      idco=IDINT(qmed)
C
      if(.not. ifirst) then
C
C --- Lag temporear tabell
C
      deltaF=1.0/float(nfact-1)
      deltaT=100.0
      do j=1,nfact
       do i=1,ntemp
        T=deltaT*(i-1)
        F=(j-1)*deltaF
        P=1.0e+5
        CALL THDYNP(P,T,F,IDCO,R,CP,CV,U,H,S,RK,
     +              UP,UT,UF,RP,RT,RF,IFAULT)
C --- NB! Ved IFAULT .ne. 0 resettes p,t og f
        if(ifault.eq.1) U=0.0
        if(ifault.eq.1) R=0.0
        htab(i,j)=U
        rtab(j)=R
       enddo
       do k=1,3
       htab(k,j)=htab(3,j)*(k-1)/2.0
       enddo
      enddo
C
      ifirst=.true.
C
      endif
C
C --- Beregn F
C
      if(qf.ge.qp) qf=qp+1.0e-10
      fc=dmax1(0.0d0,dmin1(1.0d0,(qf/(qp-qf))/fs))
      F=fc
C
C --- Beregn T
C
C 1)  Gitt F setter en opp en 2D tabell med index i T (eq. spaced)
C     og fordi dataene (U) er monotone kan en benytte en ensrettet 
C     soekemetode.  
C
C     Alternativt kan en implementere en mer avansert soekemekanisme, 
C     men jeg tror at denne vil bli like kjapp eller kjappere (EPE).
C
      qtl=qt/qp
      iFl=int(F/deltaF)+1
      iFh=iFl+1
      df=F-(iFl-1)*deltaF
      do i=1,ntemp
      ht(i)=htab(i,iFl)+ (htab(i,iFh)-htab(i,iFl))*df/deltaF
      enddo
      rgas=rtab(iFl) + (rtab(iFh)-rtab(iFl))*df
C
C 2)  Finn tabell index 
C
      do i=1,ntemp
      if(qtl.lt.ht(i)) goto 10
      enddo
10    continue
C
C 3)  Done : high and low index er :
      iTh=i
      iTl=i-1
C
C 4)  Beregn T ved interpolasjon
C
      T=(qtl-ht(iTl))/(ht(iTh)-ht(iTl))*deltaT + deltaT*(iTl-1)
C
C --- Beregn P 
C
      P  = qp*rgas*T/vol

C
      return
      end
C  ------------------------------------------------------------------
C --> End of routine
C  ------------------------------------------------------------------

      subroutine th1tpfm(qp,qf,qt,qv,qmed,fs,T,P,F,Pmech)
C  ------------------------------------------------------------------
C 
C                 FCYLTPM DOCUMENTATION: 
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
C  This routine returns the pressure, temperature and
C  fuel factor.
C  This routine is a special version for use with moving
C  piston. Therefor Pmech is added as output for conveniency
C  for MS1 inclusion.
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  thdynp               - Calculation of thermodynamic properies
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  qp           R*8     - Mass of gas in the cylinder
C  qf           R*8     - Mass of combusted gas in the cylinder
C  qt           R*8     - Total energy (U) in the volume
C  qv           R*8     - Volume of volume
C  fs           R*8     - Stochiometric fuel/air ratio
C
C  Output:
C  =============
C  P            R*8     - Pressure in volume
C  T            R*8     - Temperature in volume
C  F            R*8     - Fuel factor in volume
C  Pmech        R*8     - Pressure in volume
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : E.Pedersen        By           :  O.Bunes  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  OBU/EPE 
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C  ------------------------------------------------------------------
C
      implicit real*8 (a-h,o-z)
C
      parameter (ntemp=41,nfact=10)
C
      real*8 qp,qf,qt,qv,qmed
C
      call th1tpf(qp,qf,qt,qv,qmed,fs,T,P,F)
C
      Pmech=P
      return
      end

      subroutine th1tpfu(qp,qf,qt,qu,qv,
     +           qmed,fs,pres,ffac,temp,umom,rkap,rgas,hh)
C  ------------------------------------------------------------------
C
C                 TH1PTFU DOCUMENTATION:
C                ========================
C
C
C  FILING NO: PIPE AUXILLARY ROUTINE
C
C
C  FOUR KEY WORDS:  MS1,BONDGRAPH,MODELLING, PIPEFLOW
C
C
C  Abstract/Short Summary:
C  =======================
C  This routine returns the pressure, temperature, fuelfactor and 
C  velocity.
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  thdynp               - Calculation of thermodynamic properies
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  qp           R*8     - Mass of gas in the cylinder
C  qf           R*8     - Mass of combusted gas in the cylinder
C  qt           R*8     - Total energy (U) in the volume
C  qu           R*8     - Momentum ro*u
C  qv           R*8     - Volume of volume
C  qmed         R*8     - Selection of thermodynamic package
C  fs           R*8     - Stochiometric fuel/air ratio
C
C  Output:
C  =============
C  P            R*8     - Pressure in volume
C  T            R*8     - Temperature in volume
C  F            R*8     - Fuel factor in volume
C  UMOM         R*8     - Velocity in volume
C  RKAP         R*8     - Specific heat ration
C  RGAS	        R*8     - Gas constant
C  HH           R*8     - Enthalpy
C
C  Date created : 210198            UPDATED      :  EPE
C  Programmer   : E.Pedersen        By           :  O.Bunes
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  OBU/EPE
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION.
C  ------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
C
      parameter (ntemp=41,nfact=10)
C
      real*8 qp,qf,qt,qv,qmed
      real*8 ht
      logical ifirst
c
      common /media/deltaT,deltaF,htab(ntemp,nfact),rtab(nfact)
      common /res/ht(ntemp),ifirst
C
      data ifirst /.false./
C
      idco=0
C
      if(.not. ifirst) then
C
C --- Lag temporear tabell
C
      deltaF=1.0/float(nfact-1)
      deltaT=100.0
      do j=1,nfact
       do i=1,ntemp
        TT=deltaT*(i-1)
        FF=(j-1)*deltaF
        P=1.0e+5
        CALL THDYNP(P,TT,FF,IDCO,R,CP,CV,U,H,S,RK,
     +              UP,UT,UF,RP,RT,RF,IFAULT)
        if(ifault.eq.1) U=0.0
        if(ifault.eq.1) R=0.0
        htab(i,j)=U
        rtab(j)=R
       enddo
       do k=1,3
       htab(k,j)=htab(3,j)*(k-1)/2.0
       enddo
      enddo
C
      ifirst=.true.
C
      endif
C
C --- Beregner F (her konstant)
C
      F=min(1.0,max(0.0,(qf/(max(1.0e-10,(qp-qf))))/fs))
C
C --- Beregner U
C
      U=qu/dmax1(qp,1.0d-10)
C
C --- Beregn T
C
C 1)  Gitt F setter en opp en 2D tabell med index i T (eq. spaced)
C     og fordi dataene (U) er monotone kan en benytte en ensrettet 
C     soekemetode.  
C
C     Alternativt kan en implementere en mer avansert soekemekanisme, 
C     men jeg tror at denne vil bli like kjapp eller kjappere (EPE).
C
      qtl=(qt-qp*0.5*U*U)/qp
C
      iFl=int(F/deltaF)+1
      iFh=iFl+1
      df=F-(iFl-1)*deltaF
      do i=1,ntemp
      ht(i)=htab(i,iFl)+ (htab(i,iFh)-htab(i,iFl))*df/deltaF
      enddo
C
      rgas=rtab(iFl) + (rtab(iFh)-rtab(iFl))*df
C
C 2)  Finn tabell index 
C
      do i=1,ntemp
      if(qtl.lt.ht(i)) goto 10
      enddo
10    continue
C
C 3)  Done : high and low index er :
      iTh=i
      iTl=i-1
C
C 4)  Beregn T og P ved interpolasjon
C
      T=(qtl-ht(iTl))/(ht(iTh)-ht(iTl))*deltaT + deltaT*(iTl-1)
      P=qp*rgas*T/qv
C
      call th1gas2(P,F,T,qmed,fs,rro,rkap,rgas,cpp,hh)
C
C --- Beregn P 
C
      pres=P
      ffac=F
      temp=T
      umom=U
C
      return
      end
C     -----------------------------------------------------------------
C ### Real function TH1GAS() 
C     -----------------------------------------------------------------
      real*8 function th1gas(p,f,t,qmed,fs,rivar)
C
C   Function used to return single thermodynamic variables 
C   depending on the gifen p,f and t, in addition to medium
C   and fs.
C   For specification of rivar see the code sequence below!
C   
C   EPE
C
      implicit real*8 (a-h,o-z)
C
      integer*4 ivar
C
      pres=p
      temp=t
      ffac=f
      idco=IDINT(qmed)
      call thdynp(pres,temp,ffac,IDCO,
     &     R,CP,CV,U,H,S,RK,UP,UT,UF,RP,
     &     RT,RF,IFAULT)
C
      ivar=idint(rivar)
C
      if(ivar.eq.1) th1gas=r
      if(ivar.eq.2) th1gas=cp
      if(ivar.eq.3) th1gas=cv
      if(ivar.eq.4) th1gas=u
      if(ivar.eq.5) th1gas=h
      if(ivar.eq.6) th1gas=s
      if(ivar.eq.7) th1gas=rk
      if(ivar.eq.8) th1gas=up
      if(ivar.eq.9) th1gas=ut
      if(ivar.eq.10) th1gas=uf
      if(ivar.eq.11) th1gas=rp
      if(ivar.eq.12) th1gas=rt
      if(ivar.eq.13) th1gas=rf
C
      cb=ffac*fs/(1.0+ffac*fs)
C
C --- ivar=20 -> rho
C
      if(ivar.eq.20) th1gas=pres/(r*temp)
C
C --- ivar=21 -> rho*u=E
C
      if(ivar.eq.21) th1gas=pres/(r*temp)*u
C
C --- ivar=22 -> rho(sub)b
C
      if(ivar.eq.22) th1gas=cb*pres/(r*temp)
      return
      end
      subroutine th1gas2(p,f,t,qmed,fs,ro,rkap,rgas,cpp,hh)
C
      implicit real*8 (a-h,o-z)
C
C
      pres=p
      temp=t
      ffac=f
      idco=0
      call thdynp(pres,temp,ffac,IDCO,
     &     R,CP,CV,U,H,S,RK,UP,UT,UF,RP,
     &     RT,RF,IFAULT)
C
C
      ro=pres/(r*temp)
      rkap=RK
      rgas=R
      cpp=CP
      hh=H
      return
      end

