#include<myhead.h>
int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("i am child ,my pid = %d,my pgid=%d,my ppid=%d\n",getpid(),getpgid(getpid()),getppid());
		setpgid(0,0);
		printf("i am child after setpgid ,my pid = %d,my pgid=%d,my ppid=%d\n",getpid(),getpgid(getpid()),getppid());
		return 3;
	}
	else
	{
		printf("i am parent,my pid=%d,my pgid=%d,my ppid=%d\n",getpid(),getpgid(getpid()),getppid());
		int status;
		wait(&status); /*status 传出参数*/
		if(WIFEXITED(status))/* 正常返回非0，异常返回0*/
		{
			printf("the app return value is %d\n",WEXITSTATUS(status));/*WIFEXITED非0则返回退出吗，为0则无意义*/
		}
		else
		{
			printf("app crash\n");
		}
	}
	return 0;
}
