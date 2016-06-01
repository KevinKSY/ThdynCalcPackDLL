      real*8 function dmf(rcylno,dficyl,nstrok,fiinj,fiep,p,t,f,vol,
     +                    medium,fs,omega,mqf,hn,cssw,dur)
C  ------------------------------------------------------------------
C 
C                   DMF DOCUMENTATION: 
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
C  This routine returns the ratio of converted fuel.
C  The rate of heat release is calculated using Wiebe
C  functions or measured data. The parameter cssw
C  determines the shape of the rate of heat release.
C  By setting cssw=2.0, the heat release approximated
C  using a double Wiebe function.
C  By setting cssw=5, every rate of heat release will
C  be identical with the one in the data file. 
C  The combustion is then said to be static.
C  By setting cssw=6, the duration and start of the combustion
C  calculated in inject.f will be used (not fixed).
C
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  Wiebe4.f             - ROHR modelled by two Wiebe funstions
C  Rohrtab.f            - ROHR modelled by measured data
C  Igndel.f             - Calculate ignition delay
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  fiin         R*8     - Crank angle
C  cylno        R*8     - Cylinder number
C  dficyl       R*8     - Angle betwwen cylinders
C  nstrok       R*8     - Stroke
C  fiinj        R*8     - Angle when start of diesel injection
C  fiep         R*8     - Crank angle (0 - infinity)
C  p            R*8     - Cylinder pressure
C  t            R*8     - Cylinder temperature
C  f            R*8     - Cylinder fuel factor
C  medium       R*8     - Thermodynamic sw according to thdynp
C  fs           R*8     - Stochiometric fuel/air ratio
C  omega        R*8     - Engine speed (rad/s)
C  mqf          R*8     - Mass of diesel pr injection
C  hn           R*8     - Lower heating value of diesel
C  cssw         R*8     - Combustion shape parameter
C  dur          R*8     - Duration of combustion in crank angles
C
C  Output:
C  =============
C
C  dmf          R*8     - Rate of fuel conversion (kg/s)
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C  ------------------------------------------------------------------
C
      implicit real*8 (a-h,o-z)
      parameter (mncyl=4)
      real*8 mqf, medium
      real*8 fies,dfie,m
      real*8 rcylno,nstrok
      integer*4 cylno
      real*8 cf
      real*8 ffmax,qmed,rivar
      COMMON /INJFL/cf(mncyl),fies(mncyl),m(mncyl),dfie(mncyl),
     +              corrm(mncyl)
C --> cf(mncyl) : Combustion condition : 0(fuel injection not started), 1(fuel injection started but no ignition), 2(ignition started)
C --> fies(mncyl) : Ignition start CA
C --> m(mncyl) : not used
C --> dfie(mncyl) : duration of combustion in CA
C --> corrm(mncyl) : Ratio of maximum fuel injection to actual
      DATA CF/mncyl*0.0/
      DATA corrm/mncyl*1.0/
      DATA fiet/720.0/
C --------------------------------------------------------------------
C --------------------------------------------------------------------
      pi=4.0*datan(1.0d0)
      fie=fiep
      cylno=idint(rcylno)
C --> Transfer crank angle to (0-720 degrees)
      fie=mod(fie,fiet)
C
C --> Input data for ROHR using wiebe4 with a1=a2=6.9
C --> Energy fraction and duration of first Wiebe
C
      pw=0.01d0
      qw=0.1d0
      rwm1=0.5d0
      rwm2=1.0d0
C --------------------------------------------------------------------
C --> Start ROHR calculations
C --------------------------------------------------------------------
C
C --> Reset and start new cycle
C
      if((fie.lt.fiinj.and. fie.gt.10.0)
     +     .and. cf(cylno).eq.5) cf(cylno)=0
C --------------------------------------------------------------------
C --> The fuel injection has started (Performed once pr combustion)
C --------------------------------------------------------------------
      if(fie.ge. fiinj .and. cf(cylno).eq.0) then
	 corrm(cylno)=1.0
C --> No ignition at low pressure or low temperature 
         if(p.lt. 10.0e+5 .or. t.lt.600.0) cf(cylno)=5
C --> Calculating ignition delay 
         call igndel(p,t,omega,dfied)
C --> Max igndelay=20 degrees
         fiesl=fiinj+min(20.0,dfied)
         fies(cylno)=mod(fiesl,fiet)
         cf(cylno)=1
C --> Estimate maximum fuel mass to be injected 
         ffmax=0.8
         qmed=0.0
         rivar=20
	 rmcyl=vol*th1gas(p,f,t,qmed,fs,rivar)
         dmbm=(ffmax-f)*fs/(1.0+fs*f)*rmcyl
         corrm(cylno)=min(1.0,max(0.0,dmbm/mqf))
         dmf=0.0
         dqf=0.0
         return
C -------------------------------------------------------------------- 
C --> No ignition during ignition delay
C -------------------------------------------------------------------- 
      elseif((fie.ge.fiinj .and. fie .lt. fies(cylno)) .and. 
     +   cf(cylno).eq.1) then
         dmf=0.0
         dqf=0.0
C -------------------------------------------------------------------- 
C --> First ignition (Performed once pr combustion)
C -------------------------------------------------------------------- 
      elseif(fie.ge.fies(cylno) .and. cf(cylno).eq.1) then
         dfiign=fies(cylno)-fiinj
C --> Combustion duration
C	 dfie(cylno)=65.0
	 dfie(cylno)=dur
         fir=fie
         ficst=fies(cylno)
C --> Start of the ignition in CA
         dfic =dfie(cylno)
C --> Combustion duration in seconds
         tdfic=dfic/omega*pi/180.0
C --> Current fraction of combustion period
         y=(fir-ficst)/dfic
C --> Total mass to be injected
         tmi=mqf*corrm(cylno)
C --> Selecting correct shape for ROHR
         if(cssw.eq.2) then
            call wiebe4(pw,qw,rwm1,rwm2,y,fw,dfdy)
            dmf=dfdy*mqf/tdfic
         elseif(cssw.eq.5 .or. cssw .eq. 6) then
            call rohrtab(omega,fiep,cssw,dfic,tdfic,fies(cylno),fw,dfdy)
            dmf=dfdy*mqf
         endif
	 dqf=dmf*hn
         cf(cylno)=2
         return
C -------------------------------------------------------------------- 
C --> Combustion after first ignition
C -------------------------------------------------------------------- 
      elseif((fie.ge.fies(cylno) .and. fie .le. 
     +        (fies(cylno)+dfie(cylno))) .and. cf(cylno).eq.2) then
         fir=fie
         ficst=fies(cylno)
         dfic =dfie(cylno)
         tdfic=dfic/omega*pi/180.0
         y=(fir-ficst)/dfic
         tmi=mqf*corrm(cylno)
         if(cssw.eq.2) then
            call wiebe4(pw,qw,rwm1,rwm2,y,fw,dfdy)
            dmf=dfdy*mqf/tdfic
         elseif(cssw.eq.5 .or. cssw .eq. 6) then
            call rohrtab(omega,fiep,cssw,dfic,tdfic,fies(cylno),fw,dfdy)
            dmf=dfdy*mqf
         endif
	 dqf=dmf*hn
      else
C -------------------------------------------------------------------- 
C --> No combustion
C -------------------------------------------------------------------- 
            dmf=0.0
            dqf=0.0
      endif
C -------------------------------------------------------------------- 
C --> An Eilif stunt????
C -------------------------------------------------------------------- 
      if(fie.gt.fiet-10.0) cf(cylno)=5
      return
      end
C --------------------------------------------------------------------
C --> End of routine
C --------------------------------------------------------------------


      subroutine igndel(p,t,omega,del)
C  ------------------------------------------------------------------
C 
C                 IGNDEL DOCUMENTATION: 
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
C  This routine returns the ignition delay calculated
C  using measured data.
C
C
C  Input/Output:
C  =============
C
C  Input:
C  ======
C  p            R*8     - Cylinder pressure
C  t            R*8     - Cylinder temperature
C  omega        R*8     - Engine speed (rad/s)
C
C  Output:
C  =============
C  DEL          R*8     - Ignition delay
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : E.Pedersen        By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595786          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  E.Pedersen 
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C  ------------------------------------------------------------------
C  ------------------------------------------------------------------
      IMPLICIT real*8 (A-H,o-z)
      REAL*8 P,T,DEL,A,B,C,PI,OMEGA
C     PARAMETER(A=0.00044D0,B=4650.0D0,C=1.19D0)
C     PARAMETER(A=0.00100D0,B=4650.0D0,C=1.19D0)
      PARAMETER(A=0.00020D0,B=4650.0D0,C=1.19D0)
      PARAMETER(PI=3.1415)
C --------------------------------------------------------------------
C --> Calculate ignition delay
C --------------------------------------------------------------------
      DEL=A*EXP(B/T)*(P*1.0D-5)**(-C)
      IF(DEL*OMEGA.GT.PI/3.0D0) DEL=PI/(3.0D0*OMEGA)
      DEL=DEL*OMEGA*180.0/PI
      RETURN
      END
C --------------------------------------------------------------------
C --> End of routine
C --------------------------------------------------------------------
      subroutine wiebe4(p,q,m1,m2,y,f,dfdy)
C -------------------------------------------------------------------
C 
C                  WIEBE4 DOCUMENTATION: 
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
C
C  This routine returns the rate of heat release and 
C  accumulated heat release as a function of crank angle. 
C  ROHR is modeled by the use of two Wiebe functions.
C
C
C  Input/Output:
C  =============
C
C  Input:
C
C  p            R*8     - Energy fraction for first Wiebe
C  q            R*8     - Energy fraction for second Wiebe
C  m1           R*8     - Duration of firste Wiebe
C  m2           R*8     - Duration of seciond Wiebe
C  y            R*8     - Fraction of total duration
C
C  Output:
C  =============
C
C  dfdy         R*8     - Rate of heat release
C  f            R*8     - Accumulated heat release
C 
C  Date created : 091297            UPDATED      :  
C  Programmer   : E.Pedersen        By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595786          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  E.Pedersen
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      real*8 m1,m2
      data a,corr/6.9,1.0010088/
      y=max(0.0,y)
      p=max(0.0,p)
      q=max(0.0,q)
      if(y.gt.1.36) then
         f=1.0d0
         dfdy=0.0d0
         return
      endif
      y1=y/max(q,1.0e-10)
      ytom=y1**m1
      eex=exp(-a*y1*ytom)
      f1=1.0-eex
      df1dy=a*(m1+1.0)*ytom*eex/max(q,1.0e-10)
      if(y1.gt.1.36) then
	f1=1.0
	df1dy=0.0
      endif
      ytom=y**m2
      eex=exp(-a*y*ytom)
      f2=1.0-eex
      df2dy=a*(m2+1.0)*ytom*eex
      sumf=p*(1.0-exp(-a/q))+(1.0-p)*(1.0-exp(-a))
      corr=1.0/sumf
C -------------------------------------------------------------------
C --> Caclulating ROHR and accumulated heat release
C -------------------------------------------------------------------
      f=corr*(p*f1+(1.0-p)*f2)
      dfdy=corr*(p*df1dy+(1.0-p)*df2dy)
      return
      end
C ------------------------------------------------------------------
C --> End of routine
C ------------------------------------------------------------------

      SUBROUTINE rohrtab(omega,fiin,cssw,firange,trange,
     &     fiign,f,dfdy)
C  ------------------------------------------------------------------
C 
C                 ROHRTAB DOCUMENTATION: 
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
C
C  This routine returns the rate of heat release and 
C  accumulated heat release as a function of crank angle. 
C  The heat release reference case is read from a file, 
C  rohr**.dat, containing a measured heat release data. 
C  The file is read into a table.
C  By setting cssw=5, every rate of heat release will
C  be identical with the one in the data file. 
C  The combustion is then said to be static.
C  By setting cssw=6, the duration and start of the combustion
C  calculated in inject.f will be used (not fixed).
C
C
C  Input/Output:
C  =============
C
C  Input:
C
C  fiin         R*8     - Crank angle
C  omega        R*8     - Rotaing speed
C  cssw         R*8     - Combustion shape switch parameter
C                          cssw = 5 ==> Static rate of heat release
C                          cssw = 6 ==> Dynamic rate of heat release
C  firange      R*8     - Combustion duration (crank degrees)
C                          (used if cssw=6)  
C  trange       R*8     - Combustion duration (seconds)
C                          (used if cssw=6)  
C  fiign        R*8     - Crank angle at combustion start
C                          (used if cssw=6)
C
C  Output:
C  =============
C
C  dfdy         R*8     - Rate of heat release
C  f            R*8     - Accumulated heat release
C 
C  Date created : 091297            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C  ------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C  ------------------------------------------------------------------
C
      IMPLICIT REAL*8 (a-h,o-z)
      REAL*8 fi, rohr, area
      LOGICAL first, again

      COMMON /rohr/first,ndata,fi(100),rohr(100),area(100),fistart,
     &     fistop,again

      DATA first/.TRUE./
      DATA again/.TRUE./
C     ---------------------------------------------------------------
C --> Start of calculations done at first entry
C     ---------------------------------------------------------------
C
C --> Reading rate of heat release from from file 
C
      IF(first) THEN
         OPEN(UNIT=20, FILE='rohr20.dat',FORM='FORMATTED',STATUS='OLD')
         READ(20,*) ndata
         READ(20,*) fistart, fistop
         DO I=1, ndata
            READ(20,*) fi(I), rohr(I)
         END DO
         CLOSE (20)
C
C --> Calculate area below rohr curve for cssw=5
C
         IF(cssw.EQ.5) THEN
            fiprsec = omega*180.0D0/(4.0D0*ATAN(1.0D0))
            area(1) = 0.0D0
            DO I=2, ndata
               area(I) = area(I-1)+(rohr(I-1)+(rohr(I)-
     &              rohr(I-1))/2.0D0)*(fi(I)-fi(I-1))/fiprsec
            END DO
         ENDIF
         first = .FALSE.
      ENDIF
C     ---------------------------------------------------------------
C --> End of calculations done at first entry
C     ---------------------------------------------------------------
C
C     ---------------------------------------------------------------
C --> Start of calculations done if cssw=6
C     ---------------------------------------------------------------
      IF(cssw.EQ.6.AND. again) THEN
         fistart = fiign
         fistop  = fiign+firange
C
C --> Arranging the fi table for cssw=6
C     
         dfi     = firange/float(ndata - 1)
         fi(1)   = fistart
         DO I=2, ndata
            fi(I) = fi(I-1)+dfi
         ENDDO
C
C --> Calculating total area below rohr curve for cssw=6
C
         area(1) = 0.0D0
         DO I=2, ndata
            area(I) = area(I-1)+(rohr(I-1)+(rohr(I)-
     &           rohr(I-1))/2.0D0)*trange/float(ndata-1)
         ENDDO
      ENDIF
C     ---------------------------------------------------------------
C --> End of calculations for cssw=6
C     ---------------------------------------------------------------
C
C     ---------------------------------------------------------------
C --> Starting rate of heat release and accumulated heat calculations
C     ---------------------------------------------------------------
C      
C --> Case of combustion
C
      IF (fiin.GE.fistart .AND. fiin.LE.fistop) THEN
C
C --> Finding values for interpolating tables of rohr and acc. heat
C
         DO I=1, (ndata-1)
            IF (fiin.GT.fi(I)) THEN
               nlo = I
               nhi = I+1
            ENDIF
         END DO
C
C --> Calculating rohr and and acc.heat during combustion
C     
         dfdy  = (rohr(nlo)+(rohr(nhi)-rohr(nlo))*
     &        (fiin-fi(nlo))/(fi(nhi)-fi(nlo)))/area(ndata)
         f     = (area(nlo)+(area(nhi)-area(nlo))*
     &        (fiin-fi(nlo))/(fi(nhi)-fi(nlo)))/area(ndata)
         again = .FALSE.
C     
C --> Case of no combustion
C
      ELSE
         dfdy  = 0.0D0
         f     = 0.0D0
         again = .TRUE.
      ENDIF
      RETURN
      END
C  ------------------------------------------------------------------
C --> End of subroutine rohrdat.f
C  ------------------------------------------------------------------
