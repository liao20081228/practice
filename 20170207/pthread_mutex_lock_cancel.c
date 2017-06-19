/*************************************************************************
    > File Name: pthread_mutex.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月08日 星期三 15时05分45秒
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
void unlock(void *p)
{
	printf(" call the cleanup to unlock\n");
	/*pthread_mutex_unlock(&mutex);//当加锁和解锁之间有cancelpoint时，线程会因cancel而不释放资源，这时就需要调用清理函数释放资源*/
}
void *thread_func1(void *p)
{
	pthread_cleanup_push(unlock,NULL);
	pthread_mutex_lock(&mutex);
	long int i=0;
	sleep(1);
	while(i<1000000)
	{
		i++;
		(*(long int*)p)++;
	}
	pthread_exit((void*)i);
	pthread_mutex_unlock(&mutex);
	pthread_cleanup_pop(0);//正常弹栈不执行函数，遇到取消点时才执行
}
void *thread_func2(void *p)
{
	long int i=0;
	while(i<1000000)
	{
		i++;
	pthread_mutex_lock(&mutex);
		(*(long int*)p)++;
	pthread_mutex_unlock(&mutex);
	}
	pthread_exit((void*)i);
}
int main()
{
	pthread_t thid1,thid2;
	long int ret1=0,ret2=0;
	long int *p=(long int *)malloc(sizeof(long int));
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
	pthread_mutex_init(&mutex,&mutexattr);
	pthread_create(&thid1,NULL,thread_func1,p);
	pthread_create(&thid2,NULL,thread_func2,p);
	pthread_cancel(thid1);
	pthread_join(thid1,(void**)&ret1);
	printf("the first child  thread return value is %ld\n",ret1);
	pthread_join(thid2,(void**)&ret2);
	printf("the second child  thread return value is %ld\n",ret2);
	pthread_mutex_destroy(&mutex);
	printf("the sum=%ld\n",*p);

}
