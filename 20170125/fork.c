#include<stdio.h>
#include<unistd.h>
int main()
{
	printf("源进程的pid=%d\n",getpid());
	pid_t ret=fork();
	if(ret<0)
	{
		printf("进程创建失败\n");
	}
	else if(ret==0)
	{
		printf("我是子进程，id=%d,我的父进程id=%d\n",getpid(),getppid());
	}
	else
	{
		printf("我是父进程，我的iD=%d,我的子进程id是%d\n",getpid(),ret);
		sleep(10);
	}
	return 1;

}
