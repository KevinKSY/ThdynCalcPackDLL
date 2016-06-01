      SUBROUTINE PFIMAX(t,fi,p,pmax,fipmax)
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
C  This routine returns maximum cylinder pressure for a cycle,
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
C  pmax         R*8     - Maximum cylinder pressure     
C  fipmax       R*8     - Crank angle of maximum pressure
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
      REAL*8 fi,p,pmax,newpmax,temppmax,fistart,fistop
      REAL*8 lastime,t,fipmax,tempfipmax,newfipmax
      LOGICAL new
      COMMON /pmaxpress/temppmax,newpmax,new,lastime,
     &     tempfipmax,newfipmax
      DATA temppmax/150.0e5/
      DATA new/.TRUE./
      DATA newpmax/150.0e5/
      DATA lastime/-1.0/

C -------------------------------------------------------------------
      fistart = -10.0
      fistop  = 40.0

      IF (t.GT.lastime) THEN
         IF (fi.GT.fistart.AND.fi.LT.fistop.AND.p.GT.5.0e5) THEN
            IF (new) THEN
               newpmax   = temppmax
               newfipmax = tempfipmax               
               temppmax  = 0.0
               new = .FALSE.
            ENDIF
            IF (p .GT. temppmax) THEN
               temppmax   = p
               tempfipmax = fi
            ENDIF
         ELSE
            new = .TRUE.
         ENDIF      
         lastime = t
      ENDIF
      pmax   = newpmax
      fipmax = newfipmax
      RETURN
      END
C -------------------------------------------------------------------
C --> End of routine
C -------------------------------------------------------------------

