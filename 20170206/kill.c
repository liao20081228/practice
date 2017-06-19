/*************************************************************************
    > File Name: kill.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 21时41分39秒
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
int main(int argc, char*argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong!\n");
		return 1;
	}
	if(kill(atoi(argv[1]),SIGKILL)==-1)
	{
		perror("KILL");
		return 2;
	}
	while(1);
	return 0;
}
