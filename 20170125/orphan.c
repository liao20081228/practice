#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	printf("start process pid=%d\n ",getpid());
	pid_t pid=fork();
	if(pid==0)
	{
		sleep(5);
		printf("i is child,mypid=%d,my father pid=%d\n",getpid(),getppid());
	}
	else
	{
		printf("i is parent process ,my child pid=%d,my pid=%d\n",pid,getpid());
		exit(0);
	}
}
