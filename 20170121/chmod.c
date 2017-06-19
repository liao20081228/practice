/*************************************************************************
    > File Name: chmod.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月05日 星期日 20时54分29秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/time.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		perror("argc is wrong");
		return 1;
	}
	DIR *dp=NULL;
	if((dp=opendir(argv[1]))==NULL)
	{
		perror("opendir");
		return 1;
	}
	struct dirent *p=NULL;
	while((p=readdir(dp))!=NULL)
	{
		if(strcmp(p->d_name,"..")==0)
		{
			struct stat s;
			stat(p->d_name,&s);
			printf("dname=%s,mode=%d",p->d_name,s.st_mode);
			chmod(p->d_name,0700);
			stat(p->d_name,&s);
			printf("dname=%s,mode=%d",p->d_name,s.st_mode);
		}
	}
	return 0;
}
