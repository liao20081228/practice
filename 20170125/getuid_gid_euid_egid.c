#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <stdlib.h> 
#include <errno.h> 
int main()
{

	printf("uid : %d gid : %d\n", getuid(), getgid()); 
	printf("eudi: %d egid: %d\n", geteuid(), getegid());
	FILE* fp = fopen("a.txt", "a");//注意这里是以追加形式打开，说明 a.txt 要具有可写权限
	if(fp == NULL) 
	{
		 
		perror("fopen error"); 
		exit(-1); 

	} 
	fputs("world", fp); 
	fclose(fp); 
	return 0; 

}
