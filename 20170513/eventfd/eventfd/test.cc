/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 12时17分05秒
 ************************************************************************/
#include"eventthread.h"
void make(void)
{
	::srand(::time(nullptr));
	cout << rand()/(double)(RAND_MAX/99) << endl;
}

int main(void)
{
	MyNamespace::CEventThread cEvent(make);
	cEvent.Start();/* */ 
	int n = 20;
	while (n--)
	{
		cEvent.WakeUp();
		sleep(1);
	}
	sleep(5); /* 如果补睡眠则主线程会执行的很快，导致立即退出，子线程被回收*/
	cEvent.Stop();
	return 0;
}
