#include"get_clock.h"

int main()
{
	double  mhz,arg1{0},arg2{0};
	cycles_t s,e;
	int rear = 9, maxsize = 10;

	for(int i = 1; i< 1000; i++)
	{
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		rear= (rear+1)% maxsize;
		e=get_cycles();
		arg1+=(e-s)/mhz;

	}
}
