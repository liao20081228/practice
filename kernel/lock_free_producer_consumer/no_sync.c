/*****************************************************************************80
    > File Name: queue.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年10月27日 星期五 18时28分56秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include"myhead_c.h"
static long sum = 0;
void* thread_func(void* arg)
{
	for (int i = 1; i <= 1000000; ++i)
	{
		sum = sum +i;
	}
	pthread_exit(NULL);
}


int main(void)
{
	pthread_t thread_id[2];
	for (int i = 0 ;i < 2; ++i)
	{
		pthread_create(&thread_id[i],NULL,thread_func,NULL);
	}
	for (int i = 0 ;i < 2; ++i)
	{
		pthread_join(thread_id[i],NULL);
	}
	printf("sum = %ld", sum);
	return 0;
}
