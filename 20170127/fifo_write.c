/*************************************************************************
    > File Name: fifo_write.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月02日 星期日 23时57分44秒
 ************************************************************************/

#include<myhead.h>
int  main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong\n");
		return -1;
	}
	int fd_w=open(argv[1],O_WRONLY);
	char buf[100]={'\0'};
	while((long int)(bzero(buf,sizeof(buf)),fgets(buf,sizeof(buf)-1,stdin))!=EOF)
	{
		write(fd_w,buf,strlen(buf));
	}
	close(fd_w);
	return 0;
}
