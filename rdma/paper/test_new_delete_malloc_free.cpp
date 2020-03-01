#include"get_clock.h"
#include<iostream>
int main()
{
	double n = 0 , m = 0, f =0;
	double d = 0, mhz;
	cycles_t s,e;
	char* addr;
	for(int i = 0; i< 100;i++)
	{
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		addr=new char[16];
		e=get_cycles();
		n+=(e-s)/mhz*1000;
		
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		delete[] addr;
		e=get_cycles();
		d+=(e-s)/mhz*1000;
		
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		addr=(char*)malloc(16);
		e=get_cycles();
		m+=(e-s)/mhz*1000;
		
		mhz = get_cpu_mhz(0);
		s=get_cycles();
		free(addr);
		e=get_cycles();
		f+=(e-s)/mhz*1000;
	}
	std::cout << "new" << n/100 << ",delete" << d/100 << ",malloc" << m/100 << ",free" << f/100 <<std::endl;
}
