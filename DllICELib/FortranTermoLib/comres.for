      SUBROUTINE comres(pu,pd,fu,fd,tu,td,omegat,
     +                  medium,fs,
     +                  momc,dmc,dmco,dmfc,dmfco,deu,ded,vr)
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
C -------------------------------------------------------------------
C                 END OF DOCUMENTATION. 
C -------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      real*8 n288,momc,medium
      real*8 speed(69),prrat(483),volflo(69,483)
      real*8 speed2(69),prrat2(483),volflo2(69,483)
      real*8 rio
      logical first,tut
C
      common /turdat/nsp,npr,speed,prrat,volflo,p0,t0,pi
      common /turdat2/nsp2,npr2,speed2,prrat2,volflo2
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
         nsp = 69
         npr = 483
         nsp2 = 69
         npr2 = 483
         acc = 0.002
         rinit=-1.0
         rlimit=0.0
         iopt = 0
         t0 = 300.0
         p0 = 1.013e5
         pi = 4.0*atan(1.0)
C --> Reading datafiles into tables
         call intab(nsp,npr,speed,prrat,volflo,
     +        'komdat.dat',acc,rinit,rlimit,iopt)
         call intab(nsp2,npr2,speed2,prrat2,volflo2,
     +        'etadat.dat',acc,rinit,rlimit,iopt)
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
      xarg = n288
      yarg = pic 
      ixd  = 69
      iyd  = 483
C --> Interpolate in the 2D speed table to find the corresponding 
C     volume flow (v288)
      call tasear(nsp,npr,speed,prrat,volflo,xarg,yarg,
     +            rlim,v288r,ixd,iyd)

      v288r = v288r
C --> Surging considerations and displayed warnings
C --> (v288 set to 0.1 if pressure ration exceeds the maximum
C -->  possible ratio for the current turbocharger speed)
C  
      if(xarg .gt. n288) then
        v288r=1.0e-1
        rio=rio+1
        if(rio.eq.1.0) then
c         write(6,'(1x,2E12.3,A)') pic,rio,'START SURGING !!!'
        endif
      else
        if(rio .gt. 0.0) then
c         write(6,'(1x,2E12.3,A)') pic,rio,' END SURGING !!!'
        endif
        rio=0
      endif
C
C --> Finding efficiency
C
      call tasear(nsp2,npr2,speed2,prrat2,volflo2,xarg,yarg,
     +            rlim,etaic,ixd,iyd)
      etaic=etaic
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
      tc=t0*pic**((rk0-1.0D0)/rk0)
C
C --> Enthalpy at pd, tc (isentropic compression)
C
      idco=0
      call thdynp(pd,tc,fd,idco,rc,cpc,cvc,uc,hc,sc,rkc,
     +     upc,utc,ufc,rpc,rtc,rfc,ifault)
C
C --> Enthalpy increase
C
      delhc=(hc-h0)/etaic

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
      dmc=v288r*(pu/r0)/DSQRT(298.15*tu)
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
      SUBROUTINE INTAB(NX,NY,XAR,YAR,MATR,FILEN,ACC,RINIT,RLIMIT
     &     ,OPT)
******************************************************************
*
*     Routine that reads 2-D data from a formatted file, sorts the 
*     values, does a linear interpolation to find unknown values
*     and returns the resulting matrix along with the dimentions
*     and the one dimentional arrays containing the table x and
*     y values.
*     
*     Works on positive rumbers only!
*     
*     Programmed by Hallvard Paulsen Dec 11. 1989
*     last revition Dec 17. 1989 by Hallvard Paulsen
*
*     Variable contents
*
*     input:
*     acc = the best intended accuracy in input data (absolute)
*     file = the filename in which to read the input values
*     rinit = value for initalizing the matrix, must bee smaller
*             than rlimit.
*     rlimit = value for recognizing remaining initial values
*     opt = an integer used to decide whether more data should be 
*           created by interpolation. 1=yes,0=no.
*     in and output:
*     nx = returns the number of datavalues in xar and 1-D matr
*     ny = returns the number of datavalues in yar and 1-D matr
*
*     output only:
*     matr = returns the function values from x and y i.e.
*            matr=f(xar,yar)
*     xar = returns the values along the x-aksis
*     yar = returns the values along the y-aksis
*
****************************************************************
      IMPLICIT REAL*8(A-H,O-Z)
      INTEGER NX,NY,I,J,NDATA,NSET,LAST,OPT
      INTEGER JSTART,JEND,JJ,K,NNY
      INTEGER L,Z
      INTEGER SPDLO,SPDUP,SPD1,SPD2,SPD3
      INTEGER PILO,PIUP,PI1,PI2,PI3
      REAL*8 ACC,RINIT,RLIMIT
      REAL*8 XAR(*),YAR(*),MATR(NX,*)
      REAL*8 TEMP
      REAL*8 DY,DZ
      LOGICAL CHANGE,INTPOL
      CHARACTER*(*) FILEN
C
C     Initializing the matrix and arrays
C
      DO 200 J=1,483
         YAR(J) = RINIT
         DO 201 I=1,69
            MATR(I,J) = RINIT
 201     CONTINUE
 200  CONTINUE
      DO 210 I=1,69
         XAR(I) = RINIT
 210  CONTINUE

C
C     Reading the file input data
C
      IF(OPT.EQ.0)THEN
         OPEN (10,FILE=FILEN,FORM='FORMATTED',STATUS='OLD')
         READ (10,*) NDATA
         LAST = 1
         DO 10 I=1,NDATA
            READ (10,*) XAR(I),NSET
            DO 20 J=LAST,NSET + LAST - 1
               READ (10,*) YAR(J),MATR(I,J)
 20         CONTINUE
            LAST = LAST + NSET
 10      CONTINUE
         CLOSE (10)
         NX = NDATA
         NY = LAST
      ELSE
         OPEN(10,FILE=FILEN,FORM='FORMATTED',STATUS='OLD')
         READ(10,*)NDATA
         READ(10,*)NSET
         LAST=1
         L=0
         DO 88 Z=1,NDATA
            I=4*Z-3
            READ(10,*)XAR(I)
            DO 89 N=LAST,NSET+LAST-1
               J=N+NSET*3*L
               READ(10,*)YAR(J),MATR(I,J)
 89         CONTINUE
            LAST=LAST+NSET
            L=L+1
 88      CONTINUE
         CLOSE(10)
         LAST=1

C:    3 extra speeds with corresponding pressure ratios and 
C:    volume flows between 2 consecutive speeds shall now be
C:    found by lineair interpolation.

         DO 91 M=1,NDATA-1

            SPDLO=4*M-3
            SPDUP=4*M+1
            SPD1=4*M-2
            SPD2=4*M-1
            SPD3=4*M

            TEMP=XAR(SPDUP)-XAR(SPDLO)
            XAR(SPD1)=XAR(SPDLO)+TEMP/4
            XAR(SPD2)=XAR(SPDLO)+TEMP/2
            XAR(SPD3)=XAR(SPDLO)+3*TEMP/4

            DO 92 N=LAST,NSET+LAST-1
               PILO=N
               PIUP=N+NSET*4
               PI1=N+NSET
               PI2=N+NSET*2
               PI3=N+NSET*3

               TEMP=YAR(PIUP)-YAR(PILO)
               YAR(PI1)=YAR(PILO)+TEMP/4
               YAR(PI2)=YAR(PILO)+TEMP/2
               YAR(PI3)=YAR(PILO)+3*TEMP/4

               TEMP=MATR(SPDUP,PIUP)-MATR(SPDLO,PILO)
               MATR(SPD1,PI1)=MATR(SPDLO,PILO)+TEMP/4
               MATR(SPD2,PI2)=MATR(SPDLO,PILO)+TEMP/2
               MATR(SPD3,PI3)=MATR(SPDLO,PILO)+3*TEMP/4
               
 92         CONTINUE
  
            LAST=LAST+NSET*4
 91      CONTINUE
         NX=4*(NDATA-1)+1
         NY=LAST+NSET-1
         LAST=NY
         NDATA=NX
      ENDIF

C     Bouble sorting the yar and matr data (xar data is assumed
C     to be sorted in the input file)
C
      CHANGE = .TRUE.
      DO WHILE (CHANGE)
         CHANGE = .FALSE.
         DO 30 J=1,LAST - 1
            IF (YAR(J) .GT. YAR (J+1)) THEN
               CHANGE = .TRUE.
               TEMP = YAR(J)
               YAR(J) = YAR(J+1)
               YAR(J+1) = TEMP
               DO 40 I=1,NDATA
                  TEMP = MATR(I,J)
                  MATR(I,J) = MATR(I,J+1)
                  MATR(I,J+1) = TEMP
 40            CONTINUE
            ENDIF
 30      CONTINUE
      ENDDO

C     Interpolating interior points
C
      DO 50 I=1,NX
         INTPOL = .FALSE.
         DO 60 J=1,NY
            IF ((MATR(I,J) .GT. RLIMIT) 
     &          .AND. (MATR(I,J+1) .LT. RLIMIT)) THEN
C
C     An endpoint is found
               JSTART = J
               DO 70 K=J+1,NY
                  IF ((MATR(I,K) .GT. RLIMIT) 
     &               .AND. (MATR(I,K-1) .LT. RLIMIT)) THEN
C
C     The other endpoint
                     INTPOL = .TRUE.
                     JEND = K
                     GOTO 145
                  ENDIF
 70            CONTINUE
            ENDIF
 145     IF (INTPOL) THEN
            
C
C     Interpolating the points between jstart and jend
C
            DZ = MATR(I,JEND) - MATR(I,JSTART)
            DY = YAR(JEND) - YAR(JSTART)
            INTPOL = .FALSE.
            DO 80 JJ=JSTART+1,JEND-1
c               PRINT *,i,jj,'INTERPOLATING'
                MATR(I,JJ) = MATR(I,JSTART) + (DZ/DY) *
     &                       (YAR(JJ) - YAR(JSTART))
 80         CONTINUE
         ENDIF
 60      CONTINUE
 50   CONTINUE
   
C     Removing double points

      NNY = NY
      LAST = 0
C:    DO 90 J=1,NY 
C:       IF ((DABS(YAR(J)-YAR(J+1)) .LT. ACC 
C:   &          .AND. (YAR(J) .GT. RLIMIT))) THEN
C           
C     The difference between two y-values is very small.
C     Compress the table so that these lines are removed
C 
C:          DO 100 JJ=J+1,NNY
C:             YAR(JJ) = YAR(JJ+1)
C:             DO 110 I=1,NX
C:                MATR(I,JJ) = MATR(I,JJ+1)
C: 110         CONTINUE
C: 100       CONTINUE
C:           LAST = LAST + 1
C:        ENDIF
C: 90     CONTINUE

C      Removing remaining initializing lines
C 
      NNY = NY - LAST
      DO 120 J=1,NNY
         IF ((YAR(J) .LT. RLIMIT) .AND. (J .LT. (NNY -LAST))) THEN
            DO 130 JJ = J,NNY
               YAR(JJ) = YAR(JJ+1)
               DO 130 I=1,NX
                  MATR(I,JJ) = MATR(I,JJ+1)
 130           CONTINUE
c               PRINT *,'LINE # ',J,' REMOVED'
            LAST = LAST + 1
         ENDIF
 120  CONTINUE
      NY = NY - LAST

      RETURN
      END
********************************************************************
*
*     End of routine intab.
*
*******************************************************************

      SUBROUTINE TASEAR(NX,NY,XAR,YAR,MATR,ARGX,ARGY,RLIM,ANS,XD,YD)
******************************************************************
*
*     This routine does a linear interpolating within a 2-D table
*     (i.e. matrix) and returns the value refered to by the two 
*     arguments. If no value is avaiable for the arguments, the 
*     value of the x-argument is changed to get inside the definition
*     boundaries.
*
*     Programmed by Hallvard Paulsen Dec 14. 1989
*     Last revition Dec 17. 1989 by Hallvard Paulsen
*
*     Variable contents:
*
*     Input variables:
*        nx = the number of values avaiable in the x-direction in
*             matr and the lenght of xar.
*        ny = the numbar of values in the y-direction in matr and
*             the length of yar.
*        xar = an array of avaiable arguments in the x-direction
*        yar =  ---------------  "  ---------------- y-direction
*        matr = the 2-D table in which to look up values
*        argx = the x-value for which to get table value
*        argy = the y-value  ----------- " -----------
*        rlim = a parameter from which we are able to find out what
*               matr values that are within the region of definition
*        xd = the x dimention for the deffiniton of the matrix/xar
*        yd = the y  --------------------  "  -------------- / yar
*             (i.e in the call to "intab")
*
*     Output variable:
*        ans = the result of the table lookup
*
***********************************************************************
      INTEGER NX,NY,XD,YD
      REAL*8 XAR(*),YAR(*),MATR(XD,*)
      REAL*8 ARGX,ARGY,RLIM,ANS
C
C     Internal variables
C
      INTEGER I,J,ISTART,JSTART,IEND,JEND
      REAL*8 DX,DY,DZ1,DZ2,DZ,Z1,Z2,DR,R

      SAVE

C
C     Searching  along the akses to find the 
C     four datapoints closest to the arguments
C
      I = 1
      DO WHILE ((XAR(I) .LT. ARGX) .AND. (I .LE. (NX + 1)))
         I = I + 1
      ENDDO
C
C     Checks for argx to large
C
c     IF (I .GT. NX) THEN
c        PRINT *,'XVALUE TOO LARGE',ARGX,' > ', XAR(NX)
c     ENDIF
      ISTART = I - 1
      IEND = I
      J = 1
      DO WHILE ((YAR(J) .LT. ARGY) .AND. (J .LE. (NY + 1)))
         J = J + 1
      ENDDO
C
C     Checks for argy too large
C
      IF (J .GT. NY) THEN
c        PRINT *,'YVALUE TOO LARGE',ARGY,' > ', YAR(NY)
C         ans = matr(nx,ny)
C         return
         STOP
      ENDIF

      JSTART = J - 1
      JEND = J
C
C
C     If there is not any avaiable data for this point,
C     we'll have to change the x-argument to get within
C     the region of definition.
C
      IF (MATR(ISTART,JSTART) .LT. RLIM) THEN
         DO 10 I=ISTART,NX
            IF (MATR(I,JSTART) .GT. RLIM) THEN
c              PRINT *,' INCREASED X ', XAR(I),' <= ',ARGX
               ARGX = XAR(I)
               IF (MATR(I,JEND) .GT. RLIM) THEN
                  DY = YAR(JEND) - YAR(JSTART)
                  DZ = MATR(I,JEND) - MATR(I,JSTART)
                  ANS = MATR(I,JSTART) + (DZ/DY)*(ARGY-YAR(JSTART))
                  RETURN
               ELSE
                  ANS = MATR(I,JSTART)
                  RETURN
               ENDIF
            ENDIF
 10      CONTINUE
         DO 20 I=ISTART,1,-1
            IF (MATR(I,JSTART) .GT. RLIM) THEN
c               PRINT *,' DECREASED X ', XAR(I), ' <= ',ARGX
               ARGX = XAR(I)
               IF (MATR(I,JEND) .GT. RLIM) THEN
                  DY = YAR(JEND) - YAR(JSTART)
                  DZ = MATR(I,JEND) - MATR(I,JSTART)
                  ANS = MATR(I,JSTART) + (DZ/DY)*(ARGY-YAR(JSTART))
                  RETURN
               ELSE
                  ANS = MATR(I,JSTART)
                  RETURN
               ENDIF
            ENDIF
 20      CONTINUE
      ENDIF
C
C     Assuming everything has worked so far we interpolate the 
C     requested value.
C
C     ALL four datapoints should be at this point
C
      IF ((MATR(ISTART,JSTART) .GT. RLIM) .AND.
     &    (MATR(ISTART,JEND) .GT. RLIM) .AND.
     &    (MATR(IEND,JSTART) .GT. RLIM) .AND.
     &    (MATR(IEND,JEND) .GT. RLIM)) THEN
c         PRINT *,'FOUR POINT INTERPOL'
c         PRINT *,MATR(ISTART,JSTART),MATR(IEND,JSTART)
c         PRINT *,MATR(ISTART,JEND),MATR(IEND,JEND)
         DX = XAR(IEND) - XAR(ISTART)
         DY = YAR(JEND) - YAR(JSTART)
         DZ1 = MATR(ISTART,JEND) - MATR(ISTART,JSTART)
         DZ2 = MATR(IEND,JEND) - MATR(IEND,JSTART)
         Z1 = MATR(ISTART,JSTART) + (DZ1/DY)*(ARGY-YAR(JSTART))
         Z2 = MATR(IEND,JSTART) + (DZ2/DY)*(ARGY-YAR(JSTART))
         DZ = Z2 - Z1
         ANS = Z1 + (DZ/DX)*(ARGX-XAR(ISTART))
      ELSE IF ((MATR(IEND,JEND) .LT. RLIM) .OR.
     &         (MATR(IEND,JSTART) .LT. RLIM) .OR.
     &         (MATR(ISTART,JEND) .LT. RLIM)) THEN
         IF (MATR(IEND,JEND) .LT. RLIM) THEN
c           PRINT *,'CLOSEST AVAILABLE POINT VALUE'
            ANS = MATR(ISTART,ISTART)
         ELSE 
c            PRINT *,'Diagonal interpolation '
            DX = XAR(IEND) - XAR(ISTART)
            DY = YAR(JEND) - YAR(JSTART)
            DR = DSQRT(DX**2.0 + DY **2.0)
            R = DSQRT((ARGX - XAR(ISTART))**2.0 +
     &               (ARGY - YAR(JSTART))**2.0)
            DZ = MATR(IEND,JEND) - MATR(ISTART,JSTART)
            ANS = MATR(ISTART,JSTART) + (DZ/DR) * R
         ENDIF
      ELSE IF ((MATR(IEND,JEND) .LT. RLIM) .AND.
     &         (MATR(IEND,JSTART) .LT. RLIM)) THEN
c        PRINT *,'ONLY ONE X-VALUE'
         DY = YAR(JEND) - YAR(JSTART)
         DZ = MATR(ISTART,JEND) - MATR(ISTART,JSTART)
         ANS = MATR(ISTART,JSTART) + (DZ/DY) * (ARGY - YAR(JSTART))
      ELSE IF ((MATR(ISTART,JEND) .LT. RLIM) .AND.
     &         (MATR(IEND,JEND) .LT. RLIM)) THEN
c        PRINT *,'ONLY ONE Y-VALUE'
         DZ = MATR(ISTART,JEND) - MATR(ISTART,JSTART)
         ANS = MATR(ISTART,JSTART) + (DZ/DX) * (ARGX - XAR(ISTART))
      ELSE
         ANS = MATR(ISTART,JSTART)
c        Print *,'Closest point value taken'
      ENDIF
      RETURN
      END

*******************************************************************
*
*     End of routine tasear !!
*
*******************************************************************













