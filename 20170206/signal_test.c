/*************************************************************************
    > File Name: signal_test.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月06日 星期一 17时15分50秒
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
#include<signal.h>
#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<signal.h> 
int g_iSeq =0;
void SignHandler(int iSignNo) 
{
	int iSeq =g_iSeq++; 
	printf("%d Enter SignHandler,signo:%d\n",iSeq,iSignNo); 
	sleep(5); 
	printf("%d Leave SignHandler,signo:%d\n",iSeq,iSignNo); 
}
int main() 
{
	char szBuf[8]; 
	int iRet; 
	signal(SIGINT,SignHandler); //不同的信号调用同一个处理函数
	signal(SIGQUIT,SignHandler);
	do
	{
		iRet =read(STDIN_FILENO,szBuf,sizeof(szBuf)-1); 
		if(iRet<0)
		{
			perror("readfail."); 
			break;
		} 
		szBuf[iRet]='\0'; 
		printf("Get:%s",szBuf); 
	}while(strcmp(szBuf,"quit\n")!=0); 
	return 0;
}
