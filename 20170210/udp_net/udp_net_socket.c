/*************************************************************************
    > File Name: tcp_net_socket.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月11日 星期六 13时51分06秒
 ************************************************************************/
#include"udp_net_socket.h"
//establish server socket,and return the sfd
int udp_server_init(const char *ip,int port)
{
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sfd)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(struct sockaddr_in));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr(ip);
	if(bind(sfd,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr))==-1)
	{
		perror("bind"); 
		close(sfd); 
		exit(-1); 
	}
	return sfd;
}
void signalhandler(void) //用于信号处理，让服务端在按下Ctrl+c或Ctrl+\的时候不会退出 {
{
	sigset_t sigSet; 
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGINT); 
	sigaddset(&sigSet,SIGQUIT); 
	sigprocmask(SIG_BLOCK,&sigSet,NULL);
}

