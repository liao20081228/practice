/*************************************************************************
    > File Name: delfifo.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月02日 星期日 23时48分02秒
 ************************************************************************/

#include<myhead.h>
int  main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong\n");
		return -1;
	}
	if(unlink(argv[1])!=0)
	{
		perror("unlink");
		return -1;
	}
	return 0;
}
