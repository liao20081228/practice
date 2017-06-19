/*************************************************************************
  > File Name: tcp_net_socket.h
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年02月11日 星期六 13时42分04秒
 ************************************************************************/
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
extern int tcp_server_init(const char*ip,int port,int listenport_count); 
extern int tcp_server_accept(int sfd); 
extern int tcp_client_connect(const char*ip,int  port); 
extern void signalhandler(void);

