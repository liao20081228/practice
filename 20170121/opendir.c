#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
int main(int argc,char *argv[])
{
	DIR *dp=NULL;
	char *name_d=getcwd(NULL,0);
	printf("now work directory=%s\n",name_d);
	chdir(argv[1]);
	printf("now work directory after change=%s\n",getcwd(NULL,0));
	if(argc!=2)
	{
		printf("argc error\n");
		return -1;
	}
	if((dp=opendir(argv[1]))==NULL)
	{
		perror("opendir");
		return -2;
	}
	struct dirent *p=NULL;
	off_t pos=0;
	while((p=readdir(dp))!=NULL)
	{
		printf("inode=%ld,d_off=%ld,d_reclen=%d,type=%d,name=%s\n",p->d_ino,p->d_off,p->d_reclen,p->d_type,p->d_name);
		pos=p->d_off;
	}
	rewinddir(dp);
	p=readdir(dp);
	printf("after rewinddir:inode=%ld,d_off=%ld,d_reclen=%d,type=%d,name=%s\n",p->d_ino,p->d_off,p->d_reclen,p->d_type,p->d_name);
	seekdir(dp,pos);
	printf("after seekdir off_t =%ld\n",telldir(dp));
	closedir(dp);
	mkdir("~/Documents/testdir",0777);
	printf("directory has created\n");
	sleep(20);
	rmdir("~/Documents/testdir");
	printf("directory has delete\n");
	return 0;

}
