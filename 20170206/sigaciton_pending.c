/*************************************************************************
    > File Name: sigaciton.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 18时37分24秒
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
int i=0;
void sighandlenew(int signum,siginfo_t *psiginfo,void *preserve)
{
	int t=++i;
	printf("this is the %d enter the signal handle:%d\n",t,signum);
	sleep(3);
	sigset_t set;
	sigpending(&set);/* set是传出参数*/
	if(sigismember(&set,SIGQUIT)==1)
		printf("sigquit is block\n");
	else
		printf("sigquit is not block\n");
	printf("this is the %d leave the signal handle:%d\n",t,signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sighandlenew;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);// add a signal number
	//sigaddset(&act.sa_mask,SIGINT);// add a signal number
	if(sigismember(&act.sa_mask,SIGINT)==1)//judge the signal  in the set?
		printf("before del ,igint is in set\n");
	else
		printf("before del, sigint is no set\n");
	if(sigdelset(&act.sa_mask,SIGINT)==0)//del a  signal 
		printf("del sucess\n");
	else
		printf("del fail\n");
	
	if(sigismember(&act.sa_mask,SIGINT)==1)//judge 
		printf("after del ,igint is in set\n");
	else
		printf("after del, sigint is no set\n");
	if(sigdelset(&act.sa_mask,SIGINT)==0)// del a  same signal
		printf("twice del sucess\n");
	else
		printf("twice del fail\n");
	//act.sa_flags=SA_SIGINFO;//如果不加SA_RESTART,被阻塞的系统调用会被中断后直接返回
	act.sa_flags=SA_SIGINFO|SA_RESTART;//如果加SA_RESTART,被阻塞的系统调用会中断后继续执行完返回
	//act.sa_flags=SA_SIGINFO|SA_RESTART|SA_NODEFER;//如果加SA_NODEFER,可以嵌套的递归打断，否则不同信号只能打断一次，相同信号多执行一次
	if(sigaction(SIGINT,&act,NULL)==-1)
	{
		perror("sigaction");
		return 1;
	}
	if(sigaction(SIGQUIT,&act,NULL)==-1)
	{
		perror("sigaction");
		return 1;
	}
	char str[10]={'\0'};
	do
	{
		
		if(read(STDIN_FILENO,str,sizeof(str)-1)<0)
		{
			perror("read");
			break;
		}
		printf("the string is :%s\n",str);
	}while(strcmp(str,"quit\n")!=0);
	return 0;
}
