      real*8 function RMIP(FI,Y)

C----------------------------------------------------------------------
C     PROGRAMMED BY : EPE/POM
C     DEPARTMENT    : IMM-MTS-NTH-UNIT, TRONDHEIM, NORWAY
C     TELEPHONE     : (07) 595605
C     DATE          : 97
C----------------------------------------------------------------------
C
C
C     FUNCTION:
C     --------
C     This subroutine calculate the mean indicated pressure for the 
C     process.
C    
C     INPUT:
C     ------
C     FI         crank angle in [rad]      
C     Y          integrated indicated work so far (p*dV/dt)
C     FIM	 crank angle to measure at [grader] (CONSTANT)
C
C----------------------------------------------------------------------
      IMPLICIT NONE
      REAL*8 FI,Y,FIM,PHICLC,OLDWRK,PI,OLDMIP
      LOGICAL FIRST
C

      DATA OLDWRK/0.0/,OLDMIP/0.0D0/
      DATA PI/3.14159/
      DATA FIRST/.true./

      SAVE
C
      FIM = 180.0 
      IF(FIRST) THEN
        PHICLC=FIM*pi/180.0
        FIRST=.false.
      ENDIF

C
      IF ( FI .GT. PHICLC) THEN
         PHICLC = FI+4.0D0*PI
         RMIP   = Y - OLDWRK
         OLDMIP = Y - OLDWRK
         OLDWRK = Y
      ELSE 
         RMIP = OLDMIP
      ENDIF

      R E T U R N
      E N D

