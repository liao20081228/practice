/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月02日 星期日 23时00分48秒
 ************************************************************************/
#include<myhead.h>
int  main()
{
	int pipefd[2]={0};
	if(pipe(pipefd)==-1)
	{
		perror("pipe");
		return -1;
	}
	char buf[100]={'\0'};
	if(fork()==0) /*子进程为读端*/
	{
		close(pipefd[1]);/* 关闭写端*/
		sleep(2);
		if(read(pipefd[0],buf,sizeof(buf)-1)>0)
			printf("%s\n", buf);
		close(pipefd[0]);/* 关闭读端*/
		exit(0);
	}
	else
	{
		close(pipefd[0]);/* 关闭读端*/
		write(pipefd[1],"hello world",strlen("hello world"));
		waitpid(-1,NULL,0);
		close(pipefd[1]);
		exit(0);
	}
	return 0;
}
