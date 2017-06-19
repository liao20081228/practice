#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	printf("my sid is=%d\n",getsid(getpid()));
	setsid();
	printf("my sid is=%d\n",getsid(getpid()));
	return 1;
}
