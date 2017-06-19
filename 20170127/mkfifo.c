/*************************************************************************
    > File Name: mkfifo.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月02日 星期日 23时42分44秒
 ************************************************************************/

#include<myhead.h>
int  main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong\n");
		return -1;
	}
	if(mkfifo(argv[1],0666)==-1)
	{
		perror("mkfifo");
		return -1;
	}
	return 0;
}
