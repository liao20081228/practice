/*************************************************************************
    > File Name: shm.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月03日 星期一 14时53分53秒
 ************************************************************************/

#include<myhead.h>
#define PERM S_IRUSR|S_IWUSR
#define MAXSIZE 1024
int  main(int argc, char *argv[])
{
	int shmid=shmget(IPC_PRIVATE,MAXSIZE,PERM|IPC_CREAT);/* 在亲属进程间可以使用IPC_PRIVATE,而不需ftok函数*/
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	if(fork()>0)
	{
		char *p_wshm=(char *)shmat(shmid,NULL,0);
		memset(p_wshm,'\0',MAXSIZE);
		strncpy(p_wshm,"i am shared memory",MAXSIZE);
		printf("parent %d write buffer %s\n",getpid(),p_wshm);
		sleep(2);
		int status;
		wait(&status);
		if(WIFEXITED(status)!=0)
		{
			printf("child process return value is %d\n",WEXITSTATUS(status));
		}
		return 0;
	}
	else 
	{
		sleep(5);
		char *p_rshm=(char *)shmat(shmid,NULL,0);
		printf("child process %d,shmid is %d,buffer is %s\n",getpid(),shmid,p_rshm);
		return 1;
	}
	return 0;
}
