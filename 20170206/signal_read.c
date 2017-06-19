/*************************************************************************
    > File Name: signal.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 10时55分10秒
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
	printf("capture signal is %d\n",signum);
}
int main()
{
	signal(SIGINT,sighandler);
	char str[100];
	memset(str,'\0',sizeof(str));
	read(STDIN_FILENO,str,sizeof(str));
	printf("str=%s\n",str);
	return 0;
}
