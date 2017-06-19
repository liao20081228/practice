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
	act.sa_flags=SA_SIGINFO;
	if(sigaction(SIGINT,&act,NULL)==-1)
	{
		perror("sigaction");
		return 1;
	}
	while(1);
	return 0;
}
