/*************************************************************************
    > File Name: sleep.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 22时09分34秒
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
void sighandler(int signum)
{
	printf("the sigalarm %d is coming\n",signum);
}
int main()
{
	signal(SIGALRM,sighandler);
	alarm(20);
	printf("before pause\n");
	pause();
	printf("after pause\n");
	return 0;
}
