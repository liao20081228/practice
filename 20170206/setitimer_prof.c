/*************************************************************************
    > File Name: setitimer.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 22时42分06秒
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
#include<time.h>
int i;
void sighandler(int signum)
{
	i++;
	time_t t;
	t=time(NULL);
	printf("this is %d signal ,now time is:%s\n",i,ctime(&t));
}
int main()
{
	if(signal(SIGPROF,sighandler)==SIG_ERR)//设置捕捉到信号时要做什么
	{
		perror("signal");
		return 1;
	}
	kill(0,SIGPROF);//设置把信号发给谁
	struct itimerval timer;
	memset(&timer,0,sizeof(timer));
	timer.it_value.tv_sec=3;
	timer.it_interval.tv_sec=2;
	if(setitimer(ITIMER_PROF,&timer,NULL)==-1)//设置多久发一次信号
	{
		perror("setitimer");
		return 2;
	}
	char str[100];
	sleep(10);
	printf("i am first  wake\n");
	sleep(5);
	printf("i am the second wake\n");
	/*
	do
	{
		memset(str,0,sizeof(str));
		if(read(STDIN_FILENO,str,sizeof(str))==-1)
		{
			break;
		}
		printf("%s\n",str);
	}while(strcmp("quit\n",str)!=0);
	*/
	while(1);
	return 0;
}
