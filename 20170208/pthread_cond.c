/*************************************************************************
    > File Name: pthread_cond.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月06日 星期四 16时44分26秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
void cleanup(void *p)
{
	printf("this is %lu cleanup\n",(unsigned long int)p );
	pthread_mutex_unlock(&mutex);
}
void *threadfunction(void *p)
{
	pthread_cleanup_push(cleanup,p);/* 释放锁资源和堆空间*/
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond,&mutex);/* 先将锁打开并挂起，等待条件成立，在锁上*/
	/*此函数为取消点，若等待条件的过程中取消，则函数返回，并加锁，后面的解锁函数不能再执行,若不处理则会发生死锁*/
	printf("this is %lu threadfunction\n",(unsigned long int )p );
	pthread_mutex_unlock(&mutex);
	pthread_cleanup_pop(0);
	pthread_exit(p);
}

int main()
{
	pthread_t thid[5];
	/* 设置线程属性*/
	pthread_attr_t pthread_attr;
	pthread_attr_init(&pthread_attr);
	pthread_attr_setdetachstate(&pthread_attr,PTHREAD_CREATE_JOINABLE);/* 设置分离属性*/
	pthread_attr_setscope(&pthread_attr,PTHREAD_SCOPE_SYSTEM);/* 设置作用域*/
	pthread_attr_setschedpolicy(&pthread_attr,SCHED_OTHER);/* 设置调度策略为非实时*/
	struct sched_param param;
	param.sched_priority=0;
	pthread_attr_setschedparam(&pthread_attr,&param);/* 设置优先级为0，只有实时系统才有效*/
	pthread_attr_setinheritsched(&pthread_attr,PTHREAD_EXPLICIT_SCHED);/* 设置继承属性*/
	/*pthread_attr_setstacksize(&pthread_attr,10);*//* 设置栈大小*/
	/*pthread_attr_setstack(&pthread_attr,NULL,10);*//* 设置栈空间和大小*/
	/*pthread_attr_setguardsize(&pthread_attr,10);*//* 设置警戒区大小*/
	/* 设置mutex属性*/
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	int mutexkind;
	pthread_mutexattr_gettype(&mutexattr,&mutexkind);
	printf("mutex初始值为%d\n",mutexkind );
	pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
	pthread_mutexattr_destroy(&mutexattr);
	/* 设置条件变量的属性*/
	pthread_cond_init(&cond,NULL);
	/*创建立线程*/
	for(unsigned long  i=0;i<5;i++)
	{
		if(pthread_create(&thid[i],&pthread_attr,threadfunction,(void*)i)!=0)
		{
			exit(i);
		}
	}
	pthread_cancel(thid[3]);
	unsigned long int ret[5];
	pthread_cond_broadcast(&cond);
	for(int i=0;i<5;i++)
	{
		pthread_join(thid[i],(void**)&ret[i]);
	}
	return 0;
}
