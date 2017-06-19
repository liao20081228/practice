/*************************************************************************
    > File Name: sleep_alarm.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 22时18分31秒
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
int main()
{
	alarm(5);
	sleep(20);
	return 0;
}
