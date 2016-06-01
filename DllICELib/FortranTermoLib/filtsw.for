      real*8 function filtsw(t,tmstart,sin,ic0)
C
      implicit real*8 (a-h,o-z)
C  
      real*8 ic0
C
      filtsw=ic0
      if(t-tmstart .ge. 0.0) filtsw=sin
C
      return
      end

