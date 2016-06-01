      subroutine eosx(T,F)
c ... This routine computes the mole fractions in the transition region
c     between complete combustion and chemical equilibrium,
c     i.e. for     TL < T < TH
c
c ... Input:
c     From common block /TAB/:
c     X(i)   mole fraction of specie no i
c     DXP(i) partial derivative of X(i) w.r.t p
c     DXT(i) partial derivative of X(i) w.r.t T
c     DXF(i) partial derivative of X(i) w.r.t F  
c
c ... Output stored common block TAB:
c     X(i)   mole fraction of specie no i
c     DXP(i) partial derivative of X(i) w.r.t p
c     DXT(i) partial derivative of X(i) w.r.t T
c     DXF(i) partial derivative of X(i) w.r.t F  
c
c ......................................................................
      implicit none
      real T,F
      real q,z,dzdT
c
      include '..\cbl\produc.cbl'
c ......................................................................
      if(TL .lt. T .and. T .lt. TH)then
         q=(T-TL)/(TH-TL)
         z=(3.0-2.0*q)*q*q
         call f2x(F)
c
         call blend(DXP,DXPSTO,z)
c
         call blend(DXT,DXTSTO,z)
c
         dzdT=6.0*q*(1.0-q)/(TH-TL)

         DXT(1)=DXT(1)+dzdT*X(1)
         DXT(2)=DXT(2)+dzdT*X(2)
         DXT(3)=DXT(3)+dzdT*X(3)
         DXT(4)=DXT(4)+dzdT*(X(4)-XSTO(6))
         DXT(5)=DXT(5)+dzdT*X(5)
         DXT(6)=DXT(6)+dzdT*(X(6)-XSTO(5))
         DXT(7)=DXT(7)+dzdT*X(7)
         DXT(8)=DXT(8)+dzdT*(X(8)-XSTO(1))
         DXT(9)=DXT(9)+dzdT*(X(9)-XSTO(2))
         DXT(10)=DXT(10)+dzdT*(X(10)-XSTO(3))
         DXT(11)=DXT(11)+dzdT*(X(11)-XSTO(4))
         DXT(12)=DXT(12)+dzdT*(X(12)-XSTO(7))
c
         call blend(DXF,DXFSTO,z)
c
         call blend(X,XSTO,z)
c
      endif
      return
      end
c
      subroutine blend(x,xx,z)
      real x(12),xx(7),z
      x(1)=z*x(1)
      x(2)=z*x(2)
      x(3)=z*x(3)
      x(4)=(1.0-z)*xx(6)+z*x(4)
      x(5)=z*x(5)
      x(6)=(1.0-z)*xx(5)+z*x(6)
      x(7)=z*x(7)
      x(8)=(1.0-z)*xx(1)+z*x(8)
      x(9)=(1.0-z)*xx(2)+z*x(9)
      x(10)=(1.0-z)*xx(3)+z*x(10)
      x(11)=(1.0-z)*xx(4)+z*x(11)
      x(12)=(1.0-z)*xx(7)+z*x(12)
      return
      end
