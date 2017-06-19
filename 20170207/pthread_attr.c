/*************************************************************************
    > File Name: pthread.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月06日 星期四 10时37分19秒
 ************************************************************************/

#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
void cleanup(void *arg)
{
	printf("this is cleanup function,arg is %lu\n",(unsigned long)arg);
}
void *threadfunction(void*arg)
{
	printf("i am child thread,my id is %lu \n",pthread_self());
	pthread_cleanup_push(cleanup,(void*)1);
	printf("this is threadfunction,parameter is %lu\n",(unsigned long)arg );
	pthread_testcancel();
	sleep(5);
	pthread_testcancel();
	pthread_exit((void*)100);
	pthread_cleanup_pop(0);
}
int  main()
{
	pthread_t thid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setschedpolicy(&attr,SCHED_OTHER);
	struct sched_param priority;
	priority.sched_priority=0;
	pthread_attr_setschedparam(&attr,&priority);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
	/*pthread_attr_setstack;*/
	/*pthread_attr_setstacksize;*/
	/*pthread_attr_setguardsize;*/
	pthread_create(&thid,&attr,threadfunction,(void*)1);/* attr可为NULL，表示使用默认值*/
	pthread_attr_destroy(&attr);
	sleep(2);
	pthread_cancel(thid);
	int ret;
	pthread_join(thid,(void**)&ret);
	return 0;
}
