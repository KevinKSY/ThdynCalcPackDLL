      subroutine f2x(F)
c ......................................................................
c ... This routine computes the product composition assuming complete
c     combustion for a specified value of the fuel-air equivalence ratio
c
c     Initialization of constants related to the fuel composition and
c     oxidant composition is performed at the first call of the routine.
c
c ... Input:
c     F    actual value of fuel-air equivalence ratio (F=1/lambda>
c ... Output stored common block PRODUC:
c     XSTO(i)   mole fraction x(i) of specie no i
c     DXPSTO(i) partial derivative of x(i) w.r.t p
c     DXTSTO(i) partial derivative of x(i) w.r.t T
c     DXFSTO(i) partial derivative of x(i) w.r.t F  
c
c     Input through common blocks:   
c     FUEL COMPOSITION:   
c        FC(1)    NUMBER OF CARBON ATOMS IN FUEL MOLECULE   
c        FC(2)    ..     .. HYDROGEN  ..      ..       ..   
c        FC(3)    ..     .. OXYGEN    ..      ..       ..   
c        FC(4)    ..     .. NITROGEN  ..      ..       ..   
c   
c     OXIDANT COMPOSITION:
c        AC(1)    NUMBER OF N2  MOLES PER MOLE O2   
c        AC(2)    ..     .. AR  ..    ..  ..   ..   
c        AC(3)    ..     .. CO  ..    ..  ..   ..   
c        AC(4)    ..     .. CO2 ..    ..  ..   ..   
c        AC(5)    ..     .. H2O ..    ..  ..   ..   
c        AC(6)    ..     .. H2  ..    ..  ..   ..   
c   
c     Product mole mass:   
c        SM    MOLE MASS OF THE PRODUCT SPECIES:
c              SM(1) - O2   OXYGEN  
c              SM(2) - H2O  WATER VAPOR 
c              SM(3) - CO2  CARBON DIOXYDE  
c              SM(4) - N2   NITROGEN
c              SM(5) - CO   CARBON MONOXYDE 
c              SM(6) - H2   HYDROGEN
c              SM(7) - AR   ARGON   
c   
c  OUTPUT:  
c     COMMON PRODUC:   
cc        FS    FUEL AIR MASS RATIO AT STOECHIOMETRIC COMBUSTION 
c        FA    VALUE OF F AT WHICH ALL CARBON PRODUCE CO ONLY   
c        FB    VALUE OF F AT WHICH ALL HYDROGEN PRODUCE H2 ONLY 
c        FMAX  MAX VALUE OF F, ABOVE THIS VALUE NO MORE FUEL
c              CAN BE BURNED INTO CO2, H2O, CO, AND H2. 
c        AA    MATRIX CONTAINING THE COEFFICIENTS FOR COMPUTATION   
c              OF PRODUCTS COMPOSITION: 
c              AA(I,J) CONTAIN COEFFICIENT A FOR SPECIE NUMBER I 
c                     IN F-REGION NUMBER J: 
c                     J = 1  FOR  0.0 .LE. F .AND. F .LE. 1.0   
c                       = 2  FOR  1.0 .LT. F .AND. F .LE. FA
c                       = 3  FOR   FA .LT. F .AND. F .LE. FB
c        BB    BB(I,J) CONTAINS COEFFICIENT B FOR SPECIE NUMBER I
c                     IN F-REGION NUMBER J. 
c ----------------------------------------------------------------------   
c  Programed by:  H. VALLAND   
c  Date:          2003-08-05
c   
c:**********************************************************************  
      implicit none
      integer I,J,IERR,IINIT
      real F
      real AN,AM,AL,AK,B1,B2,B3,B4,B5,B6,D,E,EE,G,Q,Y,W,WF,WA,GG,
     &     B32,B52,B23,B63,FACT
      real SM(7)
c ......................................................................
      real  FC(4),AC(6),fs
      real htotF,LHV,HHV
c
      common /reacts/FC,AC,fs,htotF,LHV,HHV
c ......................................................................
      real X(12),DXP(12),DXT(12),DXF(12)
      real XSTO(7),DXPSTO(7),DXTSTO(7),DXFSTO(7)
      real Tmin,TL,TH,Tmax
      real FA,FB,FMAX,AA(8,3),BB(8,3)
      common /produc/X,DXP,DXT,DXF,XSTO,DXPSTO,DXTSTO,DXFSTO,
     &            Tmin,TL,TH,Tmax,FA,FB,FMAX,AA,BB
c ......................................................................
      EQUIVALENCE (FC(1),AN),(FC(2),AM),(FC(3),AL),(FC(4),AK)
      EQUIVALENCE (AC(1),B1),(AC(2),B2),(AC(3),B3),(AC(4),B4),
     +            (AC(5),B5),(AC(6),B6)
c ......................................................................
      DATA SM/31.999, 18.016, 44.010, 28.013, 28.011, 2.016, 39.944/
      DATA IINIT/0/
c *********************************************************************   
cc      write(*,*)'  Enter f2x with IINIT=',IINIT
      if(IINIT .eq. 0)then
c
c ...    Initialize some constants
c   
         IERR=0
         FA=0.0
         FB=0.0
         FMAX=0.0  
         do I=1,8 
            do J=1,3 
               AA(I,J)=0.0
               BB(I,J)=0.0
            enddo
         enddo
c   
         D=AN+0.25*AM-0.5*AL   
         E=0.25*AM+0.5*AL+0.5*AK   
         EE=1.0-0.5*(B3+B6)
c   
c ...    Check if fuel can be burned in the specified oxidant
         if(D*EE .le. 0.0) go to 1500
c   
         G=D/EE
         Q=B5+B6   
         Y=B3+B4   
         W=B1+B2+B3+B4+B5+B6   
c   
c ...    Stoechiometric fuel-air ratio
         WF=12.011*AN+1.008*AM+16.000*AL+14.0065*AK
         WA=G*(SM(1)+B1*SM(4)+B2*SM(7)+B3*SM(5)+B4*SM(3)
     &         +B5*SM(2)+B6*SM(6))
         fs=WF/WA  
c   
c ---    Generate A and B coefficients in region no. 1
c
         AA(1,1)=D  
         AA(2,1)=Q*G
         AA(3,1)=Y*G
         AA(4,1)=B1*G   
         AA(7,1)=B2*G   
         AA(8,1)=D+W*G  
         BB(1,1)=-D 
         BB(2,1)=0.5*AM 
         BB(3,1)=AN 
         BB(4,1)=0.5*AK 
         BB(8,1)=E  
         FMAX=1.0  
c
         if(AN .lt. 0.0001) go to 1500 
c   
c ...    Test if oxydation of CO to CO2 is possible
c ..     Do region no. 2 exist? 
c
         GG=AN+0.5*AM-AL   
         if(GG .lt. 0.0001) go to 1500 
c
c ...    Region no. 2: CO is partially oxidised to CO2
c
         FA=G*(2.0+B4-B6)/(AN+0.5*AM-AL)   
         B32=(Y*G+AN)/(FA-1.0) 
         B52=(Y*G+AN*FA)/(FA-1.0)  
         AA(2,2)=Q*G
         AA(3,2)=B32*FA 
         AA(4,2)=B1*G   
         AA(5,2)=-B52   
         AA(7,2)=B2*G   
         AA(8,2)=W*G
         BB(2,2)=0.5*AM 
         BB(3,2)=-B32   
         BB(4,2)=0.5*AK 
         BB(5,2)=B52
         BB(8,2)=D+E
         FMAX=FA   
c
         if(AM .ge. 0.0001)then
c ...       Test if hydrogen formation is possible
c
            if(AN-AL .ge. 0.0001)then
c ...          Region no. 3 exists
               FB=G*(2.0+B4+B5)/(AN-AL)  
               B23=(Q*G+0.5*AM*FA)/(FB-FA)   
               B63=(Q*G+0.5*AM*FB)/(FB-FA)   
               AA(2,3)=B23*FB 
               AA(4,3)=B1*G   
               AA(5,3)=Y*G
               AA(6,3)=-B63*FA
               AA(7,3)=B2*G   
               AA(8,3)=W*G
               BB(2,3)=-B23   
               BB(4,3)=0.5*AK 
               BB(5,3)=AN 
               BB(6,3)=B63
               BB(8,3)=D+E
               FMAX=FB   
            endif
         endif
         go to 2000
c   
 1500    continue
         IERR=1
     	endif
c
 2000 continue
      IINIT=1
      if(IERR .gt. 0)then
         do i=1,7
            XSTO(i)=0.0
            DXFSTO(i)=0.0
         enddo
      else
c
c ...    Compute mole fractions and partial derivatives:
c   
         F=AMAX1(0.0,F)
         F=AMIN1(F,FMAX)
         if(F .ge. 0.0 .and. F .le. 1.0)  J=1  
         if(F .gt. 1.0 .and. F .le. FA)   J=2  
         if(F .gt. FA  .and. F .le. FB)   J=3  
c   
         FACT=1.0/(AA(8,J)+BB(8,J)*F)
         do I=1,7
            XSTO(I)=(AA(I,J)+BB(I,J)*F)*FACT   
            DXFSTO(I)=(BB(I,J)-BB(8,J)*XSTO(I))*FACT  
         enddo
      endif
c   
      return
      END
