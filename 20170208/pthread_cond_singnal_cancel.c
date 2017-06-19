/*************************************************************************
    > File Name: pthread_cond_singnal.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月08日 星期三 19时55分05秒
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
#include<time.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void threadcleanup(void *p)
{
	printf("i am the %ld thread's cleaner,i unlock  mutex\n",(long int)p);//用于清理堆内存和释放锁资源
	pthread_mutex_unlock(&mutex);
}
void * threadfunc(void *p)
{
	pthread_cleanup_push(threadcleanup,p);
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_cleanup_pop(0);//只有非正常结束的时候才执行清理函数
	return p;
}
int main()
{
	pthread_t thid[5];
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
	pthread_mutex_init(&mutex,&mutexattr);
	pthread_cond_init(&cond,NULL);
	printf("creat 5 child thread\n");
	for(long int i=0;i<5;i++)
	{
		if(pthread_create(&thid[i],NULL,threadfunc,(void*)i)!=0)
			printf("cread thread %ld falied\n",i);
		else
			printf("creat the chid thread id is%ld\n",thid[i]);
	}
	printf("creat child thread finish\n");
	sleep(3);
	pthread_cancel(thid[3]);
	pthread_cond_broadcast(&cond);
	printf("signal have been sending\n");
	long int ret;
	for(int i=0;i<5;i++)
	{
		pthread_join(thid[i],(void**)&ret);
		printf("the %d child thread %ld  return value is %ld\n",i,thid[i],ret);
	}
	return 0;
}
