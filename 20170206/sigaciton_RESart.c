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
void sighandlenew(int signum,siginfo_t *psiginfo,void *preserve)
{
	printf("capture the signal:%d\n",signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sighandlenew;
	//act.sa_flags=SA_SIGINFO;//如果不加SA_RESTART,被阻塞的系统调用会被中断后直接返回
	act.sa_flags=SA_SIGINFO|SA_RESTART;//如果加SA_RESTART,被阻塞的系统调用会中断后继续执行完返回
	if(sigaction(SIGINT,&act,NULL)==-1)
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
