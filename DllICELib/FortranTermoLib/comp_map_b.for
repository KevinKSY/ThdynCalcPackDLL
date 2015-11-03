      SUBROUTINE comres_mod(pu,pd,fu,fd,tu,td,omegat,
     +                  medium,fs,
     +                  momc,dmc,dmco,dmfc,dmfco,deu,ded,vr,etaic)
C -------------------------------------------------------------------
C 
C                  COMRES DOCUMENTATION: 
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
C  the compressor and the shaft torque based on the input variables.
C     
C  Based on work by E. Pedersen, H.S.Landas, H. Paulsen
C
C
C  Required routines:
C  =================
C  Name:                Function:
C  =====                =========
C  Komdat.dat           - Includes the compressor flow data
C  Komdat.dat           - Includes the compressor efficiency data
C  Intab.f              - Reads datafiles into tables
C  Tasear.f             - Interpolating tables
C  Thdynp.f             - Thermodynamic properies
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
C  MEDIUM       R*8     - Thermodynamic selector according to thdynp.f
C  FS           R*8     - Stoichiometric fuelfactor
C  omegat       R*8     - Turbine speed (rad/s)
C
C
C  Output:
C  =============
C  td           R*8     - Downstream temperature (Optional) 
C  dmc          R*8     - Rate of mass flow
C  dmco         R*8     - Rate of mass flow
C  dmfc         R*8     - Rate of combusted mass flow
C  dmfco        R*8     - Rate of combusted mass flow
C  DF           R*8     - Rate of combusted mass flow
C  deu          R*8     - Rate of energy flow in to the turbine
C  ded          R*8     - Rate of energy flow out of the turbine
C  momc	        R*8     - Compressor torque 
C
C 
C  Date created : 210198            UPDATED      :  
C  Programmer   : E.Pedersen et.al. By           :  E.Pedersen
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  E.Pedersen
C  Hardware dep.: None              Software dep.:  None
C
C Modified by Kevin Koosup Yum. 2D table is given with the index values along x and y.
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      real*8 n288,momc,medium
      real*8 speed(500),prrat(500),flow_comp(500,500)
      real*8 speed2(500),prrat2(500),eff_comp(500,500)
      real*8 rio
      real*8 DX, DY, DZ1, DZ11, DZ2, DZ21, Z1, Z11, Z2, Z21, DZ_v, DZ_e
      logical first,tut
      integer i, jm istart, jstart
C
      common /turdat/nsp,npr,speed,prrat,flow_comp,p0,t0,pi
      common /turdat2/nsp2,npr2,speed2,prrat2,eff_comp
C
      common /comfir/first
C
      data first/.true./
      data tut  /.false./
C
      save
C -------------------------------------------------------------------
C --> Calculations done at first entry
C -------------------------------------------------------------------
      if(first) then
         nsp = 500
         npr = 500
         nsp2 = 500
         npr2 = 500
         acc = 0.002
         rinit=-1.0
         rlimit=0.0
         iopt = 0
         t0 = 300.0
         p0 = 1.013e5
         pi = 4.0*atan(1.0)
C --> Reading datafiles into tables
C         call intab(nsp,npr,speed,prrat,volflo,
C     +        'komdat.dat',acc,rinit,rlimit,iopt)
C         call intab(nsp2,npr2,speed2,prrat2,volflo2,
C     +        'etadat.dat',acc,rinit,rlimit,iopt)
         open(unit=10,file='compFlowMap.dat',form='formatted',
     +         status='old')
         open(unit=11,file='compEffMap.dat',form='formatted',
     +        status='old')
         read(10,*) size
         read(11,*) size
         read(10,*) speed(:)
         read(11,*) speed2(:)
         read(10,*) prrat(:)
         read(11,*) prrat2(:)         
         do i = 1,500
             read(10,*) flow_comp(i,:)        
             read(11,*) eff_comp(i,:)
         end do
         close(10)
         close(11)
         first=.false.

      endif
C -------------------------------------------------------------------
C --> End of calculations done at first entry
C -------------------------------------------------------------------    
C --> Prepare input arg. for the 2D  tables for interpolation
C --> with pu/pd, and n288 as arguments.
C
      omegat=max(0.0d0,omegat)
      n288 = omegat*60/(2.0*pi)*dsqrt(298.0/tu)
C --> Due to the interpolation routine tasear the pic > 1.0
      pic  = max(1.0d0+1.0d-10,pd/pu)
      rlim = 0.0
C     ixd  = 500
C     iyd  = 500
      
C --> Interpolate in the 2D speed table to find the corresponding 
C     volume flow (v288) and efficiency
      I = 2
      DO WHILE ((prrat(I) .LT. pic) .AND. (I .LT. (npr)))      
         I = I + 1
      ENDDO
      ISTART = I - 1
      IEND = I
      J = 2
      DO WHILE ((speed(J) .LT. n288) .AND. (J .LT. (nsp)))
         J = J + 1
      ENDDO
      JSTART = J - 1
      JEND = J

      DX = speed(JEND) - speed(JSTART)
      DY = prrat(IEND) - prrat(ISTART)
      
      DZ1 = flow_comp(IEND,JSTART) - flow_comp(ISTART,JSTART)
      DZ11 = eff_comp(IEND,JSTART) - eff_comp(ISTART,JSTART)
      DZ2 = flow_comp(IEND,JEND) - flow_comp(ISTART,JEND)
      DZ21 = eff_comp(IEND,JEND) - eff_comp(ISTART,JEND)
      Z1 = flow_comp(ISTART,JSTART) + (DZ1/DY)*(pic-prrat(ISTART))
      Z11 = eff_comp(ISTART,JSTART) + (DZ11/DY)*(pic-prrat(ISTART))
      Z2 = flow_comp(ISTART,JEND) + (DZ2/DY)*(pic-prrat(ISTART))
      Z21 = eff_comp(ISTART,JEND) + (DZ21/DY)*(pic-prrat(ISTART))
      DZ_v = Z2 - Z1
      DZ_e = Z21 - Z11
      v288r = Z1 + (DZ_v/DX)*(n288-speed(JSTART))
      etaic = Z11 + (DZ_e/DX)*(n288-speed(JSTART))

C
C --> Finding the entalphy difference and new temp after comp.
C --> Enthalpy before compressor h0
C
      idco=idint(medium)
      call thdynp(pu,tu,fu,idco,r0,cp0,cv0,u0,h0,
     +            s0,rk0,up0,ut0,uf0,rp0,rt0,rf0,ifault)
C
C --> Estimating compressor outlet temperature and enthalpy:
C
      tc=tu*pic**((rk0-1.0D0)/rk0)
C
C --> Enthalpy at pd, tc (isentropic compression)
C
      idco=0
      call thdynp(pd,tc,fd,idco,rc,cpc,cvc,uc,hc,sc,rkc,
     +     upc,utc,ufc,rpc,rtc,rfc,ifault)
C
C --> Enthalpy increase
C
      if (etaic.eq.0) then
          delhc = 0;
      else
          delhc=(hc-h0)/etaic
      endif    

      hc=h0+delhc
C
C --> Start iterate for Tc if tut is true (optionally)
C
      if(tut) then
         iter=0
         dtc=0.0D0
 723     tc=tc+dtc
         if(iter.gt.10) then
            write(6,*) 'No convergence in search for Tc'
            STOP
         endif 
C     
C --> Find h(tc) =
C
         call thdynp(pd,tc,fd,idco,rc,cpc,cvc,uc,hctemp,sc,rkc,
     +        upc,utc,ufc,rpc,rtc,rfc,ifault)
         dtc=(hc-hctemp)/cpc
C
C --> Temperature out of compressor found by interation
C
         td=tc
      endif
C --> End of iteration
C -------------------------------------------------------------------
C --> Calculating output values
C -------------------------------------------------------------------
C --> Rate of mass flow through the compressor
      vr = v288r
      dmc=v288r*(pu/1e5)*DSQRT(298/tu)
      dmco=dmc
      dmfc=dmc*fu*fs/(1.0+fu*fs)
      dmfco=dmfc
C --> Torque and energy flow in and out of the compressor
      deu=dmc*h0
      ded=dmc*hc
      if (omegat .gt. 100.0) then
         momc=dmc*delhc/(omegat+1.0d-6)
      else
         momc=0.1
      endif
      return
      end
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------
C
