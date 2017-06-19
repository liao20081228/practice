/*************************************************************************
    > File Name: pthread_canclepoint.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月08日 星期三 13时09分30秒
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

void * threadfunction(void *p)
{
	printf("before  cancel point\n");
	printf("after cancel point \n");
	return p;
}
int main()
{
	pthread_t thid;
	sleep(2);
	pthread_create(&thid,NULL,threadfunction,(void*)1);
	printf("the cancel return value is %d\n",pthread_cancel(thid));
	sleep(5);
	return 0;
}
