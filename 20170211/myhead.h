#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<dirent.h> 
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h> 
#include<errno.h>
#include<sys/select.h>
#include<syslog.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<signal.h>
#include<ctype.h>
#include<sys/ipc.h> 
#include<sys/shm.h> 
#include<sys/sem.h>
#include<sys/time.h>
#include<pthread.h>
#include<malloc.h>
#include<semaphore.h>
#include<arpa/inet.h>
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/uio.h>
#include<sys/epoll.h>
#include<poll.h>
#include<strings.h>
#define FILENAME "file"
typedef struct childdata
{
	pid_t pid;//子进程的pid；
	short int busy;//子进程是否忙碌
	int fdwrite;//sockpair 的写端
}cdata,*pcdata;

typedef struct databag
{
	int len;//每次发送数据的真实长度
	char buf[1000];//数据缓冲区
}data,*pdata;
