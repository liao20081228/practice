#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	printf("mypid=%d,myppid=%d \n",getpid(),getppid());
    while(1);
}
