#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>
int  main()
{
	if(fork()==0)
	{
		
		printf("i am child,my pid =%d\n",getpid());
		int *p=NULL;
		*p=10;
		return 10;
	}
	else
	{
		int status;
		pid_t childpid;
		childpid=wait(&status);/* status为传输参数*/
		printf("kill the child process's pid =%d\n",childpid);
		if(WIFEXITED(status))/* 正常结束返回非0，异常结束返回0*/
		{
			printf("child process's exit value=%d\n",WEXITSTATUS(status));/*WIFEXITED返回非0值，则返回返回码，否则无意义*/
		}
		else
		{
			printf("procesee crashed\n");
		}
	}
	return 10;
}
