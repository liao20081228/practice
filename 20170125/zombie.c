#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("i am child process \n");
		exit(0);
	}
	else
	{
		while(1);
	}
}
