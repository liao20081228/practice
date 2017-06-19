#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int  main()
{
	printf("pid%d,ppid=%d\n",getpid(),getppid());
	system("cat system.c");
	printf("pid%d,ppid=%d\n",getpid(),getppid());
	return 0;
}
