#include"get_clock.h"
#include<iostream>
int main()
{
	double  mhz,arg1{0},arg2{0};
	cycles_t s,e;
	int rear = 9, maxsize = 10;

	mhz = get_cpu_mhz(0);
	for(int i = 1; i< 1000000; i++)
	{
		s=get_cycles();
		rear= (i+1)% maxsize;
		e=get_cycles();
		arg1+=(e-s)/mhz;
		
		s=get_cycles();
		rear=i+1;
		if( rear >=maxsize )
			rear=rear-maxsize;
		e=get_cycles();
		arg2+=(e-s)/mhz;
	}
	std::cout<<"mod : "<<arg1<<",add-sub:"<< arg2 <<std::endl;

}
