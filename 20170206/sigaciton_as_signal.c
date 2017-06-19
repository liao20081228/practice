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
/**
 * @brief 用sigaction，实现signal函数一样的功能
 */
void sighandold(int signum)
{
	printf("capture the signal:%d\n",signum);
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_handler=sighandold;
	act.sa_flags=0;
	if(sigaction(SIGINT,&act,NULL)==-1)
	{
		perror("sigaction");
		return 1;
	}
	while(1);
	return 0;
}
