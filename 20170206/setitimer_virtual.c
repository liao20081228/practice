/*************************************************************************
    > File Name: setitimer_virtual.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月07日 星期二 21时51分27秒
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
void sighandler(int signum)
{
	i++;
	time_t t;
	t=time(NULL);
	printf("%d times capture the signal: %d,now  time is :%s\n",i,signum,ctime(&t));
}
int main()
{
	if(signal(SIGVTALRM,sighandler)!=0)
	{
		perror("signal");
		return 1;
	}
	kill(0,SIGVTALRM);
	struct itimerval timer;
	memset(&timer,0,sizeof(timer));
	timer.it_value.tv_sec=3;
	timer.it_interval.tv_sec=2;
	if(setitimer(ITIMER_VIRTUAL,&timer,NULL)==-1)
	{
		perror("setitimer");
		return 2;
	}
	sleep(5);
	printf(" i first awake\n");
	sleep(10);
	printf("i second awake\n");
	char str[10];
	read(STDIN_FILENO,str,sizeof(str)-1);
	while(1);
	return 0;
}
