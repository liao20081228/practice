/*************************************************************************
    > File Name: popen.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年03月30日 星期四 15时09分12秒
 ************************************************************************/

#include<myhead.h>
int main()
{
	FILE *fp=popen("ls -l","r");
	char buf[1000]={'\0'};
	int n=0;
	if(fp!=NULL)
	{
		n=fread(buf,sizeof(char),1000,fp);
		while(n>0)
		{
			buf[n-1]='\0'; 
			printf("Reading:-\n%s\n",buf);
			n=fread(buf,sizeof(char),1000,fp);
		}
		pclose(fp);
		return 0;
	}
	else
	{
		return -1;
	}
}
