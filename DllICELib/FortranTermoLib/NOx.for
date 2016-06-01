      real*8 function CNOPC(FI,Y)

C----------------------------------------------------------------------
C     PROGRAMMED BY : Kevin Koosup Yum
C     DEPARTMENT    : IMM-MTS-NTH-UNIT, TRONDHEIM, NORWAY
C     TELEPHONE     : (07) 595605
C     DATE          : 04.11.2011
C----------------------------------------------------------------------
C
C
C     FUNCTION:
C     --------
C     This subroutine calculate the NO amount per cycle for NOx calculation
C    
C     INPUT:
C     ------
C     FI         crank angle in [rad]      
C     Y          integrated indicated work so far (p*dV/dt)
C     FIM	 crank angle to measure at [grader] (CONSTANT)
C
C----------------------------------------------------------------------
      IMPLICIT none
      REAL*8 FI,Y,FIM,PHICLC,PI,OLDNOPC,OLDNO
      LOGICAL FIRST
C

      DATA OLDNOPC/0.0D0/,OLDNO/0.0D0/
      DATA PI/3.14159/
      DATA FIRST/.true./

      SAVE
C
      
      FIM = 180
      IF(FIRST) THEN
        PHICLC=FIM*pi/180.0
        OLDNO=0
        FIRST=.false.
      ENDIF

C
      IF ( FI .GT. PHICLC) THEN
         PHICLC = FI+4.0D0*PI
         CNOPC   = Y - OLDNO
         OLDNOPC = Y - OLDNO
         OLDNO = Y
      ELSE 
         CNOPC = OLDNOPC
      ENDIF

      RETURN
      END

