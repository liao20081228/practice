/*************************************************************************
    > File Name: pthread_cleanup.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月08日 星期三 14时24分21秒
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
void cleanup(void *parg)
{
	printf("i am clean fucntion: %s \n",(char *)parg);
	free(parg);
}
void *threadfunction(void *p)
{
	char  *str=(char *)malloc(sizeof(char )*100);
	pthread_cleanup_push(cleanup,str);
	strcpy(str,"before cancelpoint");
	sleep(3);
	pthread_exit(p);
	printf("after cancel point\n");
	pthread_cleanup_pop(1);
}
int main()
{
	pthread_t thid;
	pthread_create(&thid,NULL,threadfunction,(void*)10);
	int ret;
	pthread_cancel(thid);
	pthread_join(thid,(void**)&ret);
	printf("chlid thread return value is %d\n",ret);
	return 0;
}
