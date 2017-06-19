/*************************************************************************
    > File Name: shm_unrelation.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月03日 星期一 22时47分13秒
 ************************************************************************/
#include<myhead.h>
#define MAXSIZE 1024
typedef struct text 
{
	int usable;
	char buf[MAXSIZE];
}text;
int  main()
{
	int key=ftok("a.txt",1);
	if(key==-1)
	{
		perror("ftok");
		return -1;
	}
	int shmid=shmget(key,sizeof(text),S_IWUSR|S_IRUSR|IPC_CREAT);
	if(shmid==-1)
	{
		printf("shmget is wrong\n");
		return -1;
	}
	text *pw=(text*)shmat(shmid,NULL,0);
	memset(pw,'\0',sizeof(text));
	while(1)
	{
		if(pw->usable==0)
		{
			memset(pw,'\0',sizeof(text));
			read(STDIN_FILENO,pw->buf,MAXSIZE);
			pw->usable=1;
			if(strncmp(pw->buf,"end",3)==0)
			{
				break;
			}
		}
		sleep(1);
	}
	shmdt(pw);
	return 0;
}
