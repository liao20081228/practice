#include"semaphore.hpp"
#include<thread>
#include<iostream>
int fun(semaphore& sem)
{
	while(1)
	{
		sem.wait();
		std::cout<<sem.getvalue()<<std::endl;
	}
}


int main()
{
	semaphore sem;
	std::thread a(fun, std::ref(sem));
	std::thread b(fun, std::ref(sem));
	std::thread c(fun, std::ref(sem));
	std::thread d(fun, std::ref(sem));
	for(int i = 0;i < 100;++i)
		sem.post();
	a.join();
	b.join();
	c.join();
	d.join();
}



