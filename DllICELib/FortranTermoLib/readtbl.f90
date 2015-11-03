    subroutine readtbl(matr,xar,yar,filename)
    ! The subroutine reads the row reference vector, column
    ! reference vector and the table and return the vector and table
    ! Kevin Koosup Yum, 27/03/2014, Trondheim
    
    implicit none
    integer :: size
    real, allocatable :: matr(:,:)
    real, allocatable :: xar(:)
    real, allocatable :: yar(:)
    character :: filename

    integer :: i
    
    open(unit=10,file='test.dat',form='formatted',status='old')
    read(10,*) size
    allocate(xar(size))
    allocate(yar(size))
    allocate(matr(size,size))
    read(10,*) XAR(:)
    read(10,*) YAR(:)
    do i = 1,size
        read(10,*) MATR(i,:)        
    end do
    close(10)
    
    return
    end