/*************************************************************************
    > File Name: singal.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月05日 星期三 11时11分41秒
 ************************************************************************/

#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
void singal_handler(int signum);
int  main()
{
	signal(SIGINT,singal_handler);
	while(1);
	return 0;
}
void singal_handler(int signum)
{
	printf("capture the signal%d\n", signum);
}
