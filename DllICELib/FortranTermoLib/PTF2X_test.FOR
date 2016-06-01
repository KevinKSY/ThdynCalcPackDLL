      
      subroutine ptf2x(P,T,F,C,H,O,N
     +                 ,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,IERR)  
c ----------------------------------------------------------------------
c ... Computation of mole fractions of combustion products at chemical
c ..  equilibrium of a fuel consisting of C-H-O-N atoms and an oxidant
c .   consisting of oxygen and some additional gas species.
c
c .   Based on programs developed by Cheridan Olikara and Gary L. Borman  
c ..  University of Wisconsin, Madison    Version  April 1974.
c ......................................................................   
c
c ... Modified by E. Pedersen and H. Valland to allow oxidants including
c     gas species CO, CO2, H2O and H2 found in recirculated exhaust gas
c
c ... Modified by Kevin Koosup Yum to consider only standard air
c
c ... Last modification: 2002-09-24/hv::
c ----------------------------------------------------------------------
      IMPLICIT REAL*8 (A-H,O-Z)
      integer I,J,K,KP1,IBIG,NCK,MAX,IND,NCALL,JF,KLO
c
      real BIG,ZZ,PP2,D5AN,AC3P4,AMAX,
     +  DC1T,DC2T,DC3T,DC5T,DC7T,DC9T,DC10T,
     +  DC1P,DC2P,DC3P,DC9P,DC10P
      real T14,T28,T311,T54,T58,T78,T711,T94,T98,T106,T108
      real PHIPR,TPR,PPR,PAR,FUN1,FUN2,FUN3,FUN4,OX,SQOX,FOX,DOX,RAT,
     +     SQX4,SQX8,SQX11
      real R3,R4,PREC
      real R,R1,R2,D1,D2,D3,D4,SQP,TA,ALTA,TAIN,TASQ,C1,C2,C3,C5,
     +     C7,C9,C10
      real X4PR,X6PR,X8PR,X11PR,R0,PHI
c
      real DX1T, DX2T, DX3T, DX4T, DX5T, DX6T, DX7T, DX8T, DX9T,
     +  DX10T, DX11T, DX12T, DX1P, DX2P, DX3P, DX4P, DX5P, DX6P, DX7P,  
     +  DX8P, DX9P, DX10P, DX11P, DX12P, DX1F, DX2F, DX3F, DX4F, DX5F,   
     +  DX6F, DX7F, DX8F, DX9F, DX10F, DX11F, DX12F  
c
      double precision  A(4,4),B(4),TERM  
c
c      include '..\cbl\reacts.cbl' 
      COMMON /OVAL/X4PR,X6PR,X8PR,X11PR
      
      X1 = 1e-20
      X2 = 1e-20
      X3 = 1e-20
      X4 = 1e-20
      X5 = 1e-20
      X6 = 1e-20
      X7 = 1e-20
      X8 = 1e-20
      X9 = 1e-20
      X10 = 1e-20
      X11 = 1e-20
      X12 = 1e-20
      X13 = 1e-20
      
      IERR=0
      ERR=0
      KLO=0
c      PHI=F
      if((T-600.)*(4000.-T) .le. 0.0)then
         IERR =1
         go to 9900
      endif
c
c ... Make sure that all elements are present in the equilibrium mixture
      PHI=AMAX1(F,0.0005)
c   
c ... Calculate the constants used in the subroutine.
c ... No EGR but standard air
      R0=(H+0.25*C-0.5*N)/PHI
      R =R0+0.5*N
      R1=R0*3.7274+0.5*O
      R2=R0*0.0444         
c ... When EGR considered following equation to be used
c      R0=(FC(1)+0.25*FC(2)-0.5*FC(3))   
c     *   /((1.0-0.5*AC(3)-AC(6))*PHI)   
c      R =R0*(1.0+0.5*AC(3)+AC(4)+0.5*AC(5))+0.5*FC(3)   
c      R1=R0*AC(1)+0.5*FC(4) 
c      R2=R0*AC(2)   
c      R3=FC(1)+R0*(AC(3)+AC(4)) 
c      R4=FC(2)+R0*(AC(5)+AC(6))*2.0 
c ... End of the constants calculation
c      if(R .le. 0.5*R3)then
c         IERR=2
c         go to 9900
c      endif
      
c ... When EGR considered
c      D1=R4/R3  
c      D2=2.0*R/R3   
c      D3=2.0*R1/R3  
c      D4=R2/R3 

c ... When EGR not considered
      D1=C/H  
      D2=2.0*r/H
      D3=2.0*R1/H  
      D4=R2/H  
c   
c      nL=(FC(1)+0.25*FC(2)-0.5*FC(3))/(1.0-0.5*(AC(3)+AC(6)))
c      wf=12.011*FC(1)+SM(1)*FC(2)+SM(2)*FC(3)+SM(3)*FC(4)
c      wa=NL*(SM(8)+SM(11)*AC(1)+SM(12)*AC(2)+SM(6)*AC(3)+SM(10)*AC(4)
c     &       +SM(9)*AC(5)+SM(4)*AC(6))
c      fs=wf/wa
c
c ... The equilibrium constants were curve fitted (least squares) in the
c ..  range 600 to 4000 deg K  (1080 to 7200 deg R) from data in JANAF  
c .   Thermochemical Tables, Second Edition (1971). 
c   
      SQP=SQRT(P/101325.)
      TA=0.001*T
      ALTA=ALOG(TA) 
      TAIN=1.0/TA   
      TASQ=TA*TA
      C1=(10.0**(0.432168*ALTA-11.2464*TAIN+2.67269-0.745744E-01*TA 
     +    +0.242484E-02*TASQ))/SQP  
      C2=(10.0**(0.310805*ALTA-12.9540*TAIN+3.21779-0.738336E-01*TA 
     +    +0.344645E-02*TASQ))/SQP  
      C3=(10.0**(0.389716*ALTA-24.5828*TAIN+3.14505-0.963730E-01*TA 
     +    +0.585643E-02*TASQ))/SQP  
      C5=10.0**(-0.141784*ALTA-2.13308*TAIN+0.853461+0.355015E-01*TA
     +    -0.310227E-02*TASQ)   
      C7=10.0**(0.150879E-01*ALTA-4.70959*TAIN+0.646096+0.272805E-02*TA 
     +    -0.154444E-02*TASQ)   
      C9=(10.0**(-0.752364*ALTA+12.4210*TAIN-2.60286+0.259556*TA
     +    -0.162687E-01*TASQ))*SQP  
      C10=(10.0**(-0.415302E-02*ALTA+14.8627*TAIN-4.75746+0.124699*TA   
     +    -0.900227E-02*TASQ))*SQP  

c   
c ... Decide whether or not to make a new estimate of X4,X6,X8 and X11.
c   
      if(KLO .eq. 0) go to 305
      if(JF .eq. 0) go to 305 
      if(ABS(PHI-PHIPR) .gt. 1.0E-6) go to 305
      if(ABS(T/TPR-1.0) .gt. 0.02) go to 305  
      if(ABS(P/PPR-1.0) .gt. 0.05) go to 305  
c ... Use previous value of X2,X6,X8 and X11
      X4=X4PR   
      X6=X6PR   
      X8=X8PR   
      X11=X11PR 
      go to 410 
c   
c ... Can make an initial estimate of X4,X6,X8 and X11.  
c   
  305 continue
      if(PHI .le. 1.0)then
c         PAR=1.0/(R+R1+R2+0.25*R4)    EGR considered
         PAR=1.0/(0.25*C+R+R1+R2)      
      else
c         PAR=1.0/(R1+R2+R3+0.5*R4)    EGR considered
         PAR=1.0/(H+0.5*C+R1+R2)
      endif
c ... EGR considered
c      FUN1=2.0*R3*C10   
c      FUN2=0.5*R4*C9
c      FUN3=2.0/PAR  
c      FUN4=2.0*R
      FUN1=2.0*H*C10   
      FUN2=0.5*C*C9
      FUN3=2.0/PAR  
      FUN4=2.0*R
      OX=1.0
  320 continue
      SQOX=SQRT(OX) 
      FOX=(FUN1*SQOX+H)/(1.0+C10*SQOX)+FUN2*SQOX/(1.0+C9*SQOX) 
     +    +FUN3*OX-FUN4 
      if(FOX .lt. 0.0)then
         go to 325
      elseif(FOX .eq. 0.0)then
         go to 330
      endif
      OX=0.1*OX 
      if(OX .lt. 1.0E-30)then
         IERR=3
         GO TO 9900 
      endif
      go to 320
c
  325 continue
      do IND=1,20
         FOX=(FUN1*SQOX+H)/(1.0+C10*SQOX)+FUN2*SQOX/(1.0+C9*SQOX) 
     +       +FUN3*OX-FUN4 
         DOX=0.25*FUN1/(SQOX*(1.0+C10*SQOX)**2)+0.5*FUN2/(SQOX*(1.0+C9 
     +       *SQOX)**2)+FUN3   
         RAT=FOX/DOX   
c
         if(RAT .gt. OX)then
            OX=OX*0.1
         else
            OX=OX-RAT 
         endif
         SQOX=SQRT(OX) 
         if(ABS(RAT/OX) .le. 1.0E-2) go to 330
      enddo
c
  330 continue
c
      X4=0.5*C*PAR/(1.0+C9*SQOX)   
      X6=H*PAR/(1.0+C10*SQOX)  
      X8=OX 
      X11=R1*PAR
      KLO=1
c   
c ... Calculate the elements of the matrix of linearised equations.
c   
  410 continue
      IND=1 
      NCALL=0   
  455 SQX4=SQRT(X4) 
      SQX8=SQRT(X8) 
      SQX11=SQRT(X11)   
      X1=C1*SQX4
      X2=C2*SQX8
      X3=C3*SQX11   
      X5=C5*SQX4*SQX8   
      X7=C7*SQX11*SQX8  
      X9=C9*X4*SQX8 
      X10=C10*X6*SQX8   
  460 T14=0.5*C1/SQX4   
      T28=0.5*C2/SQX8   
      T311=0.5*C3/SQX11 
      T54=0.5*C5*SQX8/SQX4  
      T58=0.5*C5*SQX4/SQX8  
      T78=0.5*C7*SQX11/SQX8 
      T711=0.5*C7*SQX8/SQX11
      T94=C9*SQX8   
      T98=0.5*C9*X4/SQX8
      T106=C10*SQX8 
      T108=0.5*C10*X6/SQX8  
      A(1,1)=T14+2.0+T54+2.0*T94
      A(1,2)=-D1*(1.0+T106) 
      A(1,3)=(T58+2.0*T98)-D1*T108  
      A(1,4)=0.0
      A(2,1)=T54+T94
      A(2,2)=(1.0+2.0*T106)-D2*(1.0+T106)   
      A(2,3)=(T28+T58+T78+2.0+T98+2.0*T108)-D2*T108 
      A(2,4)=T711   
      A(3,1)=0.0
      A(3,2)=-D3*(1.0+T106) 
      A(3,3)=T78-D3*T108
      A(3,4)=T311+T711+2.0  
      A(4,1)=T14+1.0+T54+T94
      A(4,2)=1.0+T106+D4*(1.0+T106) 
      A(4,3)=T28+T58+T78+1.0+T98+T108+D4*T108   
      A(4,4)=T311+T711+1.0  
      if(NCALL .eq. 1) return  
      B(1)  =-(X1+2.0*X4+X5+2.0*X9)+D1*(X6+X10) 
      B(2)  =-(X2+X5+X6+X7+2.0*X8+X9+2.0*X10)+D2*(X6+X10)   
      B(3)  =-(X3+X7+2.0*X11)+D3*(X6+X10)   
      B(4)  =-(X1+X2+X3+X4+X5+X6+X7+X8+X9+X10+X11+D4*(X6+X10))+1.0  

c   
c ... Solve the matrix equation by Gaussian elimination.
c ..  Rows are interchanged only if the pivot point is smaller than E-05
c   
      do K=1,3  
         KP1=K+1   
         BIG=ABS(A(K,K))   
         if(BIG .lt. 1.0E-05)then
            IBIG=K
            do I=KP1,4
               if (ABS(A(I,K)) .gt. BIG)then
                  BIG=ABS(A(I,K))   
                  IBIG=I
               endif
            enddo
            if(BIG .le. 0.)then
               IERR=4
               GO TO 9900 
            endif
            if(IBIG .ne. K)then
               do J=K,4  
                  TERM=A(K,J)   
                  A(K,J)=A(IBIG,J)  
                  A(IBIG,J)=TERM
               enddo
               TERM=B(K) 
               B(K)=B(IBIG)  
               B(IBIG)=TERM  
            endif
         endif
c
         do I=KP1,4
            TERM=A(I,K)/A(K,K)
            do J=KP1,4
               A(I,J)=A(I,J)-A(K,J)*TERM 
            enddo
            B(I)=B(I)-B(K)*TERM   
         enddo
      enddo
      if(ABS(A(4,4)) .eq. 0.0)then 
         IERR=4
         GO TO 9900 
      endif
      B(4)=B(4)/A(4,4)  
      B(3)=(B(3)-A(3,4)*B(4))/A(3,3)
      B(2)=(B(2)-A(2,3)*B(3)-A(2,4)*B(4))/A(2,2)
      B(1)=(B(1)-A(1,2)*B(2)-A(1,3)*B(3)-A(1,4)*B(4))/A(1,1)
c
c ... Modifythe corrections to avoid negative mole fractions.
c
      if(B(1) .lt. -0.9*X4 ) B(1)=-0.9*X4
      if(B(2) .lt. -0.9*X6 ) B(2)=-0.9*X6
      if(B(3) .lt. -0.9*X8 ) B(3)=-0.9*X8
      if(B(4) .lt. -0.9*X11) B(4)=-0.9*X11
c   
c ... Correct the estimates of the variables and checks precision.
c   
      NCK=0 
      X4=X4+B(1)
      if(ABS(B(1)/X4 ) .gt. PREC) NCK=1   
      X6=X6+B(2)
      if(ABS(B(2)/X6 ) .gt. PREC) NCK=1   
      X8=X8+B(3)
      if(ABS(B(3)/X8 ) .gt. PREC) NCK=1   
      X11=X11+B(4)  
      if(ABS(B(4)/X11) .gt. PREC) NCK=1   
      if((X4 .le. 0.0) .or. (X8 .le. 0.0) .or. (X11 .le. 0.0))then
         IERR=5
         GO TO 9900 
      endif
c
      if(NCK .ne. 0)then
         if(IND .ge. 50)then
            IERR=6
            GO TO 5000 
         endif
         IND=IND+1 
         GO TO 455 
      endif
      if(X6 .lt. 0.0)then
         IERR=5
         GO TO 9900 
      endif
c   
c ... Calculate the remaining molefractions.
c         
c   
c ... Calculate the remaining molefractions.
c   
5000  IERR=0
      JF=1  
      PHIPR=PHI 
      TPR=T 
      PPR=P 
      X4PR=X4   
      X6PR=X6   
      X8PR=X8   
      X11PR=X11 
      SQX4=SQRT(X4) 
      SQX8=SQRT(X8) 
      SQX11=SQRT(X11)   
      X1=C1*SQX4
      X2=C2*SQX8
      X3=C3*SQX11   
      X5=C5*SQX4*SQX8   
      X7=C7*SQX11*SQX8  
      X9=C9*X4*SQX8 
      X10=C10*X6*SQX8   
      X13=(X6+X10)/H 
      X12=R2*X13 
 9900 continue
      if(IERR .gt. 0)then
         JF=0  
c         write(*,*)' Error return from EQMD: IERR =',IERR
      endif
      
c      open(unit=1,file='equil.txt')
c      write(1,*) P,T,F,C,H,O,N,X1,X2,X3,X4,X5,X6,
c     +                 X7,X8,X9,X10,X11,X12,X13,IERR
c      close(1)
c      open(unit=2,file='intermediate.txt')
c      write(2,*) A(1,1),A(1,2),A(1,3),A(1,4),A(2,1),A(2,2),A(2,3),A(2,4)
c     +          ,A(3,1),A(3,2),A(3,3),A(3,4),A(4,1),A(4,2),A(4,3),A(4,4)
c      close(2)
      RETURN
      END

