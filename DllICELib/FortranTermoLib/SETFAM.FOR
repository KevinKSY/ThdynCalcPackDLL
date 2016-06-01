      subroutine SETFAM(FFC,AAC,FFS)  
c:**********************************************************************
c   
c  Purpose: 
c     The routine enters the fuel composition parameters and oxidant
c     composition into common block /SIBLOC/ and computes stochiometric
c     fuel-air mass ratio fs
c   
c  Input:   
c     Fuel composition:   
c     FFC(1)    relative number of carbon   atoms in fuel molecule   
c     FFC(2)      ..     ..     .. hydrogen  ..      ..       ..   
c     FFC(3)      ..     ..     .. oxygen    ..      ..       ..   
c     FFC(4)      ..     ..     .. nitrogen  ..      ..       ..   
c   
c     Oxidant composition:
c     AAC(1)    Number of N2  moles per mole O2   
c     AAC(2)    ..     .. AR  ..    ..  ..   ..   
c     AAC(3)    ..     .. CO  ..    ..  ..   ..   
c     AAC(4)    ..     .. CO2 ..    ..  ..   ..   
c     AAC(5)    ..     .. H2O ..    ..  ..   ..   
c     AAC(6)    ..     .. H2  ..    ..  ..   ..   
c   
c ... Output:
c     FFS   Stochiometris fuel-air mass ratio
c ......................................................................
c ... Programmed by:  H. Valland   
c     DATE:  2002-10-13
c:**********************************************************************
      implicit none
      real FFC(4),AAC(6),FFS
      real AN,AM,AL,AK,B1,B2,B3,B4,B5,B6
      real D,EE,G,WF,WA,SM(7)
c ......................................................................
      real  FC(4),AC(6),fs
      real htotF,LHV,HHV
      common /reacts/FC,AC,fs,htotF,LHV,HHV
c ......................................................................
      EQUIVALENCE (FC(1),AN),(FC(2),AM),(FC(3),AL),(FC(4),AK)
      EQUIVALENCE (AC(1),B1),(AC(2),B2),(AC(3),B3),(AC(4),B4),
     +            (AC(5),B5),(AC(6),B6)
c ......................................................................
      DATA SM/31.999, 18.016, 44.010, 28.013, 28.011, 2.016, 39.944/
c *********************************************************************   
c
      AN=FFC(1)
      AM=FFC(2)  
      AL=FFC(3)  
      AK=FFC(4)  
      B1=AAC(1)  
      B2=AAC(2)  
      B3=AAC(3)  
      B4=AAC(4)  
      B5=AAC(5)  
      B6=AAC(6)  
c   
c ... Compute stoechiometric fuel-air ratio
c
      D=AN+0.25*AM-0.5*AL   
      EE=1.0-0.5*(B3+B6)
c   
c ... Check if fuel can be burned in the specified oxidant
      if(D*EE .le. 0.0)then
c ...    Fuel cannot be burned by oxidizer
         write(*,*)' Illegal composition:'
         write(*,*)'    *** Fuel cannot be burned by oxidizer ***'   
         fs=0.0
      else
c ...    Composition accepted
         G=D/EE
         WF=12.011*AN+1.008*AM+16.000*AL+14.0065*AK
         WA=G*(SM(1)+B1*SM(4)+B2*SM(7)+B3*SM(5)+B4*SM(3)
     &         +B5*SM(2)+B6*SM(6))
         fs=WF/WA  
      endif
      FFS=FS
c   
      RETURN
      END
