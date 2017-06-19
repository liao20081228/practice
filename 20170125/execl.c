#include<stdio.h>
#include<unistd.h>
int  main()
{
	printf("下一步执行execl函数\n");
	execl("./system","system",NULL);
	printf("上一步是execl函数\n");
}
