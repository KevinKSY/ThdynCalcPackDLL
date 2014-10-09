      real*8 function rr(t,ts,dt)
C
      implicit real*8 (a-h,o-z)
C
      rr=(t-ts)/dt
      if(t.lt. ts) rr=0.0
      if(t.ge. ts+dt) rr=1.0
C
      return
      end
