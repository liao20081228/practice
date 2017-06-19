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
int i=0;
time_t time1=0,time2=0;
void sighandler(int signum)
{
	i++;
	time_t t;
	t=time(NULL);
	if(i<=1)
		time1=t;
	else
		time2=t;
}
int main()
{
	if(signal(SIGALRM,sighandler)==SIG_ERR)//设置捕捉到信号时要做什么
	{
		perror("signal");
		return 1;
	}
	kill(0,SIGALRM);//设置把信号发给谁
	struct itimerval timer;
	memset(&timer,0,sizeof(timer));
	timer.it_value.tv_sec=1;
	timer.it_interval.tv_sec=1;
	if(setitimer(ITIMER_REAL,&timer,NULL)==-1)//设置多久发一次信号
	{
		perror("setitimer");
		return 2;
	}
	sleep(5);//睡眠时遇到第一个时钟信号就醒来
	char str[100];
	do
	{
		memset(str,0,sizeof(str));
		if(read(STDIN_FILENO,str,sizeof(str))==-1)
		{
			break;
		}
		printf("%s\n",str);
	}while(strcmp("quit\n",str)!=0);
	printf("process run %ld seconds\n",time2-time1);
	return 0;
}
