      SUBROUTINE FFMAX(fi,FF,Fmax)
C -------------------------------------------------------------------
C 
C                  PFIMAX DOCUMENTATION: 
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
C  This routine returns maximum fuel/air ratio for a cycle
C
C  Input/Output:
C  =============
C
C  Input:
C
C  fi           R*8     - Crank angle
C  FF           R*8     - Fuel/air ratio
C
C  Output:
C  =============
C
C  Fmax         R*8     - Maximum cylinder pressure     
C 
C  Date created : 091098            UPDATED      :  
C  Programmer   : O.Bunes           By           :  
C  Department   : MT                Type         :  SUBROUTINE
C  Telephone    : 73595779          Language     :  F77
C  Computer     : HPUX/SUN/IBM      Maintenance  :  O.Bunes 
C  Hardware dep.: None              Software dep.:  None
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
C
      IMPLICIT NONE
      REAL*8 fi,FF,Fmax,fistart,fistop

C -------------------------------------------------------------------
      fistart = 500.0
      fistop  = 505.0
      IF (fi.GT.fistart.AND.fi.LT.fistop) THEN
         Fmax = FF
      ENDIF
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------

