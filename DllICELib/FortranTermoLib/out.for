      REAL*8 FUNCTION OUT(w,f1,f2,f3,t1,t2,p1,d1,t3,d2,
     &     effm,effi,efft,p2,p3,f4,effmt,f5,t4,f6,t5,effv,f7,
     &     f8,f9,mep,mip,kw,cla)
      IMPLICIT NONE
      REAL*8 w,f1,f2,f3,t1,t2,p1,d1,t3,d2,f7,f8,f9,
     &     effm,effi,efft,p2,p3,f4,effmt,f5,t4,f6,t5,effv,
     &     mep,mip,kw,cla
      REAL*8 f1a,f1b,f2a,f2b,f3a,f3b,p1a,p2a,p3a,k1,k2,
     &     effma,effia,effta,f4a,effmta,effva,f8a,f9a,
     &     mepa,mipa
      INTEGER ifile
      ifile = 15
      OPEN(ifile,FILE='output.txt',STATUS='UNKNOWN')      
      WRITE(ifile,6100)
      WRITE(ifile,*)
      
      out=1.0
      k1 = w/6.2831853*0.5*3600.0
      k2 = 1200.0
C kg/s --> g/inj
C      k3 = 4188.79020/w 
C
C --> Flow rates
C
      WRITE(ifile,6200)
      WRITE(ifile,*)
      f1a = f1*k1
      f1b = f1*1000.0
      WRITE(ifile,6210)f1b,f1a
      f2a = f2*k1
      f2b = f2*1000.0
      WRITE(ifile,6220)f2b,f2a
      f3a = f3*1000.0
      f3b = f3*k1
      WRITE(ifile,6230)f3a,f3b
      WRITE(ifile,*)
      WRITE(ifile,*)
C
C --> Temperatures and pressures
C
      WRITE(ifile,6300)
      WRITE(ifile,*)
      p2a = p2/1.0e5
      WRITE(ifile,6310)t1,p2a
      p3a = p3/1.0e5
      WRITE(ifile,6320)t2,p3a
      p1a = p1/1.0e5
      WRITE(ifile,6330)t3,p1a
      WRITE(ifile,*)
      WRITE(ifile,6340)d2
      WRITE(ifile,6350)d1
      WRITE(ifile,*)
      WRITE(ifile,*)
C
C --> Efficiencies
C
      WRITE(ifile,6400)
      WRITE(ifile,*)
      effma = effm*100.0
      WRITE(ifile,6410)effma
      effia = effi*100.0
      WRITE(ifile,6420)effia
      effta = efft*100.0
      WRITE(ifile,6430)effta
      WRITE(ifile,*)
      mepa = mep/1.0e5
      WRITE(ifile,6440)mepa
      mipa = mip/1.0e5
      WRITE(ifile,6450)mipa
      WRITE(ifile,6460)kw
      WRITE(ifile,*)
      WRITE(ifile,*)
C
C --> Turbocharger 
C
      WRITE(ifile,6500)
      WRITE(ifile,*)
      f4a = f4/(6.2832)
      WRITE(ifile,6510)f4a
      effmta = effmt*100.0
      WRITE(ifile,6520)effmta
      WRITE(ifile,*)
C --> Turbine
      WRITE(ifile,6600)
      WRITE(ifile,6610)f5
      WRITE(ifile,6620)t4
      WRITE(ifile,*)
C --> Compressor
      WRITE(ifile,6700)
      WRITE(ifile,6710)f6
      WRITE(ifile,6720)t5
      WRITE(ifile,*)
      WRITE(ifile,*)

C --> Scavenging and charging
      WRITE(ifile,6800)
      WRITE(ifile,*)
      effva = effv*100

      WRITE(ifile,6810)effva

      f8a = 1.0/f8
      WRITE(ifile,6830)f8a

      WRITE(ifile,6835)cla

      WRITE(ifile,*)
      WRITE(ifile,*)


      CLOSE(ifile)

 6100 FORMAT('Cylinder unit performance')

 6200 FORMAT('Flow rates         Gram/cycle       Kg/hour')
 6210 FORMAT('Intake              ',F8.3,'         ',F8.3)
 6220 FORMAT('Exhaust             ',F8.3,'         ',F8.3)
 6230 FORMAT('Fuel                ',F8.3,'         ',F8.3)

 6300 FORMAT('Parameter          Temperature(K)   Pressure (bar)')
 6310 FORMAT('Charge air          ',F6.1,'           ',F6.2) 
 6320 FORMAT('Exhaust (Averaged)  ',F6.1,'           ',F6.2) 
 6330 FORMAT('Cylinder maximum    ',F6.1,'           ',F6.2) 
 6340 FORMAT('Maximum temperature at               ', F6.2' degrees') 
 6350 FORMAT('Maximum pressure at                  ', F6.2' degrees') 

 6400 FORMAT('Efficiencies and developed power')
 6410 FORMAT('Mechanical             ',F6.2' %')
 6420 FORMAT('Indicated thermal      ',F6.2' %')
 6430 FORMAT('Effective thermal      ',F6.2' %') 
 6440 FORMAT('Mean effective pressure               ',F5.2' bar') 
 6450 FORMAT('Mean indicated pressure               ',F5.2' bar') 
 6460 FORMAT('Shaft power                         ',F7.2' kW') 


 6500 FORMAT('Turbocharger system performance')
 6510 FORMAT('Rotating speed       ',F7.2' rps')
 6520 FORMAT('Mechanical efficiency  ',F5.2' %')

 6600 FORMAT('Turbine')
 6610 FORMAT('Mass flow              ',F5.2' kg/s')
 6620 FORMAT('Inlet temperature    ',F7.2' K')

 6700 FORMAT('Compressor')
 6710 FORMAT('Mass flow              ',F5.2' kg/s')
 6720 FORMAT('Outlet temperature   ',F7.2' K')

 6800 FORMAT('Scavenging and charging characteristics')
 6810 FORMAT('Volumetric efficiency ',F6.2' %') 
 6820 FORMAT('Resulting fuel factor   ',F6.4) 
 6830 FORMAT('Lambda in exh receiver  ',F4.2) 
 6835 FORMAT('Min. Lambda in cylinder ',F4.2) 
 6840 FORMAT('Remaining exhaust     ',F6.2' %') 

      END 


