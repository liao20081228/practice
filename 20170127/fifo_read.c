/*************************************************************************
    > File Name: fifo_read.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月03日 星期一 00时06分33秒
 ************************************************************************/

#include<myhead.h>
int  main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong\n");
		return -1;
	}
	char buf[100]={'\0'};
	int fd_r=open(argv[1],O_RDONLY);
	int ret=0;
	while(1)
	{
		bzero(buf,sizeof(buf));
		ret=read(fd_r,buf,strlen(buf));
		printf("argc=%d,bud is :%s\n",ret,buf);
	}
	close(fd_r);
	return 0;
}
