/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 12时17分05秒
 ************************************************************************/
#include"timerthread.h"
void make(void)
{
	::srand(::time(nullptr));
	cout << rand()/(double)(RAND_MAX/99) << endl;
}

int main(void)
{
	MyNamespace::CTimerThread timer(2, 2 , make);
	timer.Start();
	/*sleep(5);*/ /* 如果补睡眠则主线程会执行的很快，导致立即退出，子线程被回收*/
	timer.Stop();
	return 0;
}
