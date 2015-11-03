      SUBROUTINE TFIMAX(t,fi,te,temax,fitemax)
C -------------------------------------------------------------------
C 
C                  TFIMAX DOCUMENTATION: 
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
C  This routine returns maximum cylinder temperature for a cycle,
C  and the crank angle this pressure occurs.
C
C  Input/Output:
C  =============
C
C  Input:
C
C  fi           R*8     - Crank angle
C  p            R*8     - Pressure
C
C  Output:
C  =============
C
C  temax         R*8     - Maximum cylinder pressure     
C  fitemax       R*8     - Crank angle of maximum pressure
C 
C  Date created : 190298            UPDATED      :  
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
      REAL*8 fi,te,temax,newtemax,temptemax,fistart,fistop
      REAL*8 lastime,t,fitemax,tempfitemax,newfitemax
      LOGICAL new
      COMMON /tmaxpress/temptemax,newtemax,new,lastime,
     &     tempfitemax,newfitemax
      DATA temptemax/1500.0/
      DATA new/.TRUE./
      DATA newtemax/1500.0/
      DATA lastime/-1.0/

C -------------------------------------------------------------------
      fistart = 350.0
      fistop  = 420.0

      IF (t.GT.lastime) THEN
         IF (fi.GT.fistart.AND.fi.LT.fistop.AND.te.GT.700.0) THEN
            IF (new) THEN
               newtemax   = temptemax
               newfitemax = tempfitemax               
               temptemax  = 0.0
               new = .FALSE.
            ENDIF
            IF (te .GT. temptemax) THEN
               temptemax   = te
               tempfitemax = fi
            ENDIF
         ELSE
            new = .TRUE.
         ENDIF      
         lastime = t
      ENDIF
      temax   = newtemax
      fitemax = newfitemax
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------

