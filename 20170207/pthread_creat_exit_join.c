/*************************************************************************
    > File Name: pthread_creat.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月07日 星期二 13时03分46秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/time.h>
#include<dirent.h>
#include<signal.h>
#include<sys/time.h>
#include<pthread.h>
void *threadfun(void *p)
{
	for(int i=0;i<5;i++)
	{
		printf("hi!,i am child thread,my arg is %ld\n",(long int)p);
		//sleep(1);
	}
	pthread_exit(p);
}
int main()
{
	pthread_t thid1,thid2;
	//创建第一个进程
	if(pthread_create(&thid1,NULL,threadfun,(void*)1)!=0)
	{
		printf("pthread_creat error\n");
		return 1;
	}
	int ret;
	printf("i am main thread, my first child thid is %lu\n",thid1);
		//sleep(1);
	if(pthread_create(&thid2,NULL,threadfun,(void*)4)!=0)
	{
		printf("pthread_creat error\n");
		return 1;
	}
	printf("i am main thread, my second child thid is %lu\n",thid2);
	if(pthread_join(thid1,(void**)&ret)!=0)//捕捉第一进程的返回值
		printf("pthread_join error\n");
	printf("the first child ret is %d\n",ret);
	if(pthread_join(thid2,(void**)&ret)!=0)
		printf("pthread_join error\n");
	printf("the second child ret is %d\n",ret);
	return 0;
}
