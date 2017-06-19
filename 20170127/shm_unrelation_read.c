/*************************************************************************
    > File Name: shm_unrelation_read.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月03日 星期一 23时42分16秒
 ************************************************************************/
#include<myhead.h>
#define MAXSIZE 1024
typedef struct text 
{
	int useful;
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
	text *pr=(text*)shmat(shmid,NULL,0);
	memset(pr,'\0',sizeof(text));
	while(1)
	{
		if(pr->useful==1)
		{
			write(STDOUT_FILENO,pr->buf,MAXSIZE);
			pr->useful=0;
			if(strncmp("end",pr->buf,3)==0) 
			{ 
				break; 
			} 
		}
		sleep(1);
	}
	shmdt(pr);
	struct shmid_ds shminfo;
	bzero(&shminfo,sizeof(struct shmid_ds));
	shmctl(shmid,IPC_STAT,&shminfo);
	printf("key:%d uid:%d gid %d cuid %d cgid %d\n",shminfo.shm_perm.__key,shminfo.shm_perm.uid,shminfo.shm_perm.gid,shminfo.shm_perm.cuid,shminfo.shm_perm.cgid);
	printf("size %lu atime %s dtime %s ctime %s cpid %d lpid %d nattach %lu\n",shminfo.shm_segsz,ctime(&shminfo.shm_atime),ctime(&shminfo.shm_dtime),ctime(&shminfo.shm_ctime),shminfo.shm_cpid,shminfo.shm_lpid,shminfo.shm_nattch);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
