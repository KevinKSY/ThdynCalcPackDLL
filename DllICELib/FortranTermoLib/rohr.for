      
      subroutine dmf(rcylno,dficyl,nstrok,fiinj,fiep,p,t,f,vol,
     +               medium,fs,omega,mqf,hn,cssw,bmepnom,omeganom,dmfdt,
     +               dqfdt,cond,fiig)
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
C  Updated 08/12/2011 (by Kevin Koosup Yum)
C  Updated to adapt the variation of Wiebe parameters fitted 
C  to the experimental result from K3 engine
C
C  Updated 22/02/2011 (by Kevin Koosup Yum)
C  Updated to apply three Wiebe functions 
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  Wiebe4.f             - ROHR modelled by two Wiebe funstions
C  Wiebe3.f             - ROHR modelled by three Wiebe funstions
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
C  bmepnom      R*8     - Engine Load (0~1)
C  omeganom     R*8     - Normalized speed (0~1)
C
C  Output:
C  =============
C
C  dmfdt          R*8     - Rate of fuel conversion (kg/s)
C
C 
C  Date created : 210198            UPDATED      :  08122011
C  Programmer   : O.Bunes           By           :  Kevin Koosup Yum
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
      parameter (
     +    a11=	-2.743	,a12=	-0.9602	,a13=	0.4507	,a14=	-0.06202	,
     +    a15=	0.0225	,a16=	1.136	,a17=	0.2	,   a18=	1.996,
     +    a21=	3.537	,a22=	1.073	,a23=	-1.056	,a24=	-0.01238	,
     +    a25=	-0.2475	,a26=	-1.265	,a27=	-0.1	,   a28=	-1.06,
     +    a31=	-574.5	,a32=	-123.5	,a33=	72.78	,a34=	-142.5	,
     +    a35=	-10.24	,a36=	183.4	,a37=	18.5	,a38=	578.6,
     +    a41=	-459.2	,a42=	-212.7	,a43=	66.87	,a44=	-99.87	,
     +    a45=	-25.31	,a46=	154	    ,a47=	67.5	,a48=	518.8,
     +    a51=	70.66	,a52=	376.8	,a53=	56.21	,a54=	-51.08	,
     +    a55=	60.75	,a56=	-75.23	,a57=	-170	,   a58=	-200.4,
     +    a61=	-1325	,a62=	2541	,a63=	111.5	,a64=	-248.8	,
     +    a65=	438.7	,a66=	555.3	,a67=	-1150	,a68=	-794.5,
     +    a71=	-105.7	,a72=	17.51	,a73=	-4.458	,a74=	-25.19	,
     +    a75=	4.275	,a76=	42.41	,a77=	-5	    ,a78=	77.15,
     +    a81=	108.9	,a82=	10.02	,a83=	-8.517	,a84=	27.77	,
     +    a85=	0.2353	,a86=	-36.92	,a87=	-0.5305	,a88=	-99.93,
     +    a91=	447.6	,a92=	118.2	,a93=	-2.617	,a94=	93.74	,
     +    a95=	15.97	,a96=	-181	,a97=	-55	,a98=	-435.4 )

      real*8 mqf, medium
      real*8 fies,dfie,mm,ml,mp
      real*8 rcylno,nstrok
      integer*4 cylno
      integer*4 cf
      real*8 ffmax,qmed,rivar
      real*8 dur
      real*8 mlc,mmc,mpc
      COMMON /INJFL/cf(mncyl),fies(mncyl),m(mncyl),dfie(mncyl),
     +              corrm(mncyl),pw(mncyl),qw(mncyl),rwm1(mncyl),
     +              rwm2(mncyl),q1(mncyl),q2(mncyl),
     +              dCA(mncyl),CDp(mncyl),CDm(mncyl),CDl(mncyl),
     +              mp(mncyl),mm(mncyl),ml(mncyl)
C --> cf(mncyl) : Combustion condition : 0(fuel injection not started), 1(fuel injection started but no ignition), 2(ignition started)
C --> fies(mncyl) : Ignition start CA
C --> m(mncyl) : not used
C --> dfie(mncyl) : duration of combustion in CA
C --> corrm(mncyl) : Ratio of maximum fuel injection to actual
      DATA CF/mncyl*0/
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
C --> Energy fraction (pw) and duration (qw) of first Wiebe
C --> Shaping parameter (rwm1, rwm2) for the first and the second Wiebe
C --> The parameters are function of nominal values of engine speed and break mean effective pressure.
C --> Coefficient found by linear regression from the test data of K3 engine(1993).
C   
C --------------------------------------------------------------------
C --> Start ROHR calculations
C --------------------------------------------------------------------
C
C --> Reset and start new cycle
C
      if((fie.lt.fiinj.and. fie.gt.10.0) .and. cf(cylno).eq.5) then
          cf(cylno)=0
          dmfdt=0.0
          dqfdt=0.0
          cond = cf(cylno)
          fiig = fies(cylno)
          return
C --------------------------------------------------------------------
C --> The fuel injection has started (Performed once pr combustion)
C --------------------------------------------------------------------
      elseif(fie.ge. fiinj .and. cf(cylno).eq.0) then
	    corrm(cylno)=1.0
C --> No ignition at low pressure or low temperature 
          if(p.lt. 10.0e+5 .or. t.lt.600.0) then
              cf(cylno)=5
              dmfdt=0.0
              dqfdt=0.0
              cond = cf(cylno)
              fiig = fies(cylno)
          else
C --> Calculating ignition delay 
              call igndel(p,t,omega,dfied)
C --> Max igndelay=20 degrees
              fiesl=fiinj+min(20.0,dfied)
              fies(cylno)=mod(fiesl,fiet)
              
              cf(cylno)=1
C --> Estimate maximum fuel mass to be injected 
C             ffmax=0.8
C             qmed=0.0
C             rivar=20
C             rmcyl=vol*th1gas(p,f,t,qmed,fs,rivar)
C             dmbm=(ffmax-f)*fs/(1.0+fs*f)*rmcyl
C             corrm(cylno)=min(1.0,max(0.0,dmbm/mqf))
              dmfdt=0.0
              dqfdt=0.0
              cond = cf(cylno)
              fiig = fies(cylno)
          endif
          return
C -------------------------------------------------------------------- 
C --> No ignition during ignition delay
C -------------------------------------------------------------------- 
      elseif((fie.ge.fiinj .and. fie .lt. fies(cylno)) .and. 
     +    cf(cylno).eq.1) then
          dmfdt=0.0
          dqfdt=0.0
          cond = cf(cylno)
          fiig = fies(cylno)
          return
C -------------------------------------------------------------------- 
C --> First ignition (Performed once pr combustion)
C -------------------------------------------------------------------- 
      elseif(fie.ge.fies(cylno) .and. cf(cylno).eq.1) then
         dfiign=fies(cylno)-fiinj
C --> Combustion duration
C	   dfie(cylno)=65.0
C	   dfie(cylno)=dur
         fir=fie
C --> Start of the ignition in CA
         ficst=fies(cylno)
C        dfic =dfie(cylno)
C --> Combustion duration in seconds
         dfidt = omega*180.0/pi
C --> Current fraction of combustion period
C --> Total mass to be injected
C -->    tmi=mqf*corrm(cylno)         : Not in use in the routine
C --> Selecting correct shape for ROHR
         if(cssw.eq.2) then
              pwc = -0.473882*bmepnom - 0.362175*omeganom + 
     +                  0.37719*bmepnom*omeganom + 0.55697
              qwc = -3.972727273*bmepnom + 5.43*omeganom	 -
     +                  0.09*bmepnom*omeganom - 1.027272727
              rwm1c = -1.43206*bmepnom - 0.8745*omeganom	- 
     +                  0.011486805*bmepnom*omeganom + 3.2691
              rwm2c = 0.7906*bmepnom + 1.09725*omeganom -
     +                  0.008699295*bmepnom*omeganom + 0.163269
              durc = 51.37784*bmepnom + 27.554175*omeganom + 
     +                  3.3495*bmepnom*omeganom-12.4072 
              pw(cylno) = pwc
              qw(cylno) = qwc
              rwm1(cylno) = rwm1c
              rwm2(cylno) = rwm2c
              dfie(cylno) = durc
              tdfic=durc/dfidt
              y=(fir-ficst)/durc
              call wiebe4(pwc,qwc,rwm1c,rwm2c,y,fw,dfdy)
              dmfdt=dfdy*mqf/tdfic
C         elseif(cssw.eq.5 .or. cssw .eq. 6) then
C            call rohrtab(omega,fiep,cssw,dfic,tdfic,fies(cylno),fw,dfdy)
C            dmfdt=dfdy*mqf
          elseif(cssw.eq.3) then
              q1c = a11*omeganom  + a12*bmepnom + a13*bmepnom*omeganom 
     +                + a14/omeganom  + a15/bmepnom + a16*omeganom**2.0
     +                + a17*bmepnom**2.0 + a18
              q2c = a21*omeganom  + a22*bmepnom + a23*bmepnom*omeganom 
     +                + a24/omeganom  + a25/bmepnom + a26*omeganom**2.0
     +                + a27*bmepnom**2.0 + a28
              dCAc = a31*omeganom  + a32*bmepnom + a33*bmepnom*omeganom 
     +                + a34/omeganom  + a35/bmepnom + a36*omeganom**2.0
     +                + a37*bmepnom**2.0 + a38
              CDpc = a41*omeganom  + a42*bmepnom + a43*bmepnom*omeganom 
     +                + a44/omeganom  + a45/bmepnom + a46*omeganom**2.0
     +                + a47*bmepnom**2.0 + a48
              CDmc = a51*omeganom  + a52*bmepnom + a53*bmepnom*omeganom 
     +                + a54/omeganom  + a55/bmepnom + a56*omeganom**2.0
     +                + a57*bmepnom**2.0 + a58
              CDlc = a61*omeganom  + a62*bmepnom + a63*bmepnom*omeganom 
     +                + a64/omeganom  + a65/bmepnom + a66*omeganom**2.0
     +                + a67*bmepnom**2.0 + a68
              mpc = a71*omeganom  + a72*bmepnom + a73*bmepnom*omeganom 
     +                + a74/omeganom  + a75/bmepnom + a76*omeganom**2.0
     +                + a77*bmepnom**2.0 + a78
              mmc = a81*omeganom  + a82*bmepnom + a83*bmepnom*omeganom 
     +                + a84/omeganom  + a85/bmepnom + a86*omeganom**2.0
     +                + a87*bmepnom**2.0 + a88
              mlc = a91*omeganom  + a92*bmepnom + a93*bmepnom*omeganom 
     +                + a94/omeganom  + a95/bmepnom + a96*omeganom**2.0
     +                + a97*bmepnom**2.0 + a98
              q1(cylno) = q1c
              q2(cylno) = q2c
              dCA(cylno) = dCAc
              CDp(cylno) = CDpc
              CDm(cylno) = CDmc
              CDl(cylno) = CDlc
              mp(cylno) = mpc
              mm(cylno) = mmc
              ml(cylno) = mlc
              dfie(cylno) = dCAc+CDlc
              call wiebe3(q1c,q2c,ficst,dCAc,CDpc,CDmc,CDlc,mpc,mmc,mlc
     +                      ,fir,fw,dfdfi)
              dmfdt=dfdfi*mqf*dfidt
          endif
	    dqfdt=dmfdt*hn
          cf(cylno)=2
          cond = cf(cylno)
          fiig = fies(cylno)
          return
C -------------------------------------------------------------------- 
C --> Combustion after first ignition
C -------------------------------------------------------------------- 
      elseif((fie.ge.fies(cylno) .and. fie .le. 
     +        (fies(cylno)+dfie(cylno))) .and. cf(cylno).eq.2)
     +             then
          fir=fie
          ficst=fies(cylno)
          dfidt = omega*180.0/pi
C         tmi=mqf*corrm(cylno)
          if(cssw.eq.2) then
              dfic =dfie(cylno)
              y=(fir-ficst)/dfic
              tdfic=dfic/dfidt
              pwc = pw(cylno)
              qwc = qw(cylno)
              rwm1c = rwm1(cylno)
              rwm2c = rwm2(cylno)
              call wiebe4(pwc,qwc,rwm1c,rwm2c,y,fw,dfdy)
              dmfdt=dfdy*mqf/tdfic
          elseif(cssw.eq.3) then
              q1c = q1(cylno)  
              q2c = q2(cylno)  
              dCAc = dCA(cylno)  
              CDpc = CDp(cylno)  
              CDmc = CDm(cylno)  
              CDlc = CDl(cylno)  
              mpc = mp(cylno)  
              mmc = mm(cylno)  
              mlc = ml(cylno)
              call wiebe3(q1c,q2c,ficst,dCAc,CDpc,CDmc,CDlc,
     +                 mpc,mmc,mlc,fir,fw,dfdfi)
              dmfdt=dfdfi*mqf*dfidt
C         elseif(cssw.eq.5 .or. cssw .eq. 6) then
C             call rohrtab(omega,fiep,cssw,dfic,tdfic,fies(cylno),fw,dfdy)
C             dmfdt=dfdy*mqf
          endif
	    dqfdt=dmfdt*hn
          cond = cf(cylno)
          fiig = fies(cylno)
          return
      else
C -------------------------------------------------------------------- 
C --> No combustion
C -------------------------------------------------------------------- 
          dmfdt=0.0
          dqfdt=0.0
          cond = cf(cylno)
          fiig = fies(cylno)
      endif
C -------------------------------------------------------------------- 
C --> An Eilif stunt????
C -------------------------------------------------------------------- 
      if(fie.gt.fiet-10.0) cf(cylno)=5
      cond = cf(cylno)
      fiig = fies(cylno)
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
      subroutine wiebe4(pc,qc,m1c,m2c,y,f,dfdy)
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
C  accumulated heat release as a function of fraction of total combustion duration. 
C  ROHR is modeled by the use of two Wiebe functions.
C
C
C  Input/Output:
C  =============
C
C  Input:
C
C  pc            R*8     - Energy fraction for first Wiebe
C  qc            R*8     - Time fraction for first Wiebe
C  m1c           R*8     - Shape parameter of firste Wiebe
C  m2c           R*8     - Shape parameter of seciond Wiebe
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
      real*8 m1c,m2c
      data a,corr/6.9,1.0010088/
      y=max(0.0,y)
      pc=max(0.0,pc)
      qc=max(0.0,qc)
      if(y.gt.1.36) then
         f=1.0d0
         dfdy=0.0d0
         return
      endif
      y1=y/max(qc,1.0e-10)
      ytom=y1**m1c
      eex=exp(-a*y1*ytom)
      f1=1.0-eex
      df1dy=a*(m1c+1.0)*ytom*eex/max(qc,1.0e-10)
      if(y1.gt.1.36) then
	f1=1.0
	df1dy=0.0
      endif
      ytom=y**m2c
      eex=exp(-a*y*ytom)
      f2=1.0-eex
      df2dy=a*(m2c+1.0)*ytom*eex
      sumf=pc*(1.0-exp(-a/qc))+(1.0-pc)*(1.0-exp(-a))
      corr=1.0/sumf
C -------------------------------------------------------------------
C --> Caclulating ROHR and accumulated heat release
C -------------------------------------------------------------------
      f=corr*(pc*f1+(1.0-pc)*f2)
      dfdy=corr*(pc*df1dy+(1.0-pc)*df2dy)
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
      subroutine wiebe3 (q1c,q2c,ficst,dCAc,CDpc,CDmc,CDlc,mpc,
     +                      mmc,mlc,fir,f,dfdfi)
C -------------------------------------------------------------------
C 
C                  WIEBE3 DOCUMENTATION: 
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
C  accumulated heat release as a function of crank angle
C  ROHR is modeled by the use of three Wiebe functions.
C
C
C  Input/Output:
C  =============
C
C  Input:
C  q1c           R*8     - Energy fraction of the premixed combustion
C  q2c           R*8     - Energy fraction of the mixing controlled combustion
C  ficst        R*8     - CA at start of premixed combustion
C  dCAc          R*8     - duration in CA from the ficst til the start of the mixing controlled and late combustion
C  CDpc          R*8     - Combustion duration for premixed combustion
C  CDmc          R*8     - Combustion duration for mixing-controlled combustion
C  CDlc          R*8     - Combustion duration for late combustion
C  mpc           R*8     - Shape parameter for Wiebe function for premixed combustion
C  mmc           R*8     - Shape parameter for Wiebe function for mixing controlled combustion
C  mlc           R*8     - Shape parameter for Wiebe function for late combustion
C  fir          R*8     - CA
C
C  Output:
C  =============
C
C  dfdfi        R*8     - Rate of heat release (dQnom/dphi)
C  f            R*8     - Accumulated heat release (Qnom)
C 
C  Date created : 22.02.2012        UPDATED      :  
C  Programmer   : Kevin Koosup Yum  By           :  
C  Department   : IMT               Type         :  SUBROUTINE
C  Telephone    : 45071422          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  E.Pedersen
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      real*8 mpc,mmc,mlc,fir
      data a,corr/6.9,1.0010088/
C     y=max(0.0,y)
      q1c=max(0.0,q1c)
      q2c=max(0.0,q2c)
      dCAc=max(0.0,dCAc)
      CDpc=max(0.0,CDpc)
      CDmc=max(0.0,CDmc)
      CDlc=max(0.0,CDlc)
      mpc=max(0.0,mpc)
      mmc=max(0.0,mmc)
      mlc=max(0.0,mlc)
      if(fir.gt.1.36*(ficst+dCAc+CDlc)) then
         f=1.0d0
         dfdfi=0.0d0
         return
      endif
      yp=(fir-ficst)/CDpc
      yptomp=yp**mpc
      eex=exp(-a*yp*yptomp)
      f1=1.0-eex
      df1dy=a*(mpc+1.0)*yptomp*eex/CDpc
      if(yp.gt.1.36) then
	f1=1.0d0
	df1dy=0.0d0
      endif
      ym=(fir-(ficst+dCAc))/CDmc
      yl=(fir-(ficst+dCAc))/CDlc
      if(ym.lt.0) then
          df2dy=0.0d0
          df3dy=0.0d0
          f2=0.0d0
          f3=0.0d0
      else
          ymtomm=ym**mmc
          yltoml=yl**mlc
          eex=exp(-a*ym*ymtomm)
          f2=1.0-eex
          df2dy=a*(mmc+1.0)*ymtomm*eex/CDmc
          eex=exp(-a*yl*yltoml)
          f3=1.0-eex
          df3dy=a*(mlc+1.0)*yltoml*eex/CDlc
      endif
C -------------------------------------------------------------------
C --> Caclulating ROHR and accumulated heat release
C -------------------------------------------------------------------
      f=q1c*f1+q2c*f2+(1.0-q1c-q2c)*f3
      dfdfi=q1c*df1dy+q2c*df2dy+(1.0-q1c-q2c)*df3dy
      return
      end
C ------------------------------------------------------------------
C --> End of routine
C ------------------------------------------------------------------
