/************************************************************************
> File Name: tcp_server.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月11日 星期六 09时47分44秒
 ************************************************************************/
#include"udp_net_socket.h"
int main(int argc ,char*argv[])
{	if(argc!=3)
	{
		printf("argc is wrong !\n");
		exit(-2);
	}
	char buf[100];
	int sfd=udp_server_init(argv[1],atoi(argv[2]));//创建套接字并绑定端口
	int ret=0;
	while(1)
	{
		bzero(buf,sizeof(buf));
		struct sockaddr_in clientaddr;
		bzero(&clientaddr,sizeof(struct sockaddr_in));
		socklen_t len=sizeof(struct sockaddr_in);
		ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&clientaddr,&len);//接收每个有客户端发送的包，由于没有握手，所以每个包都有客户端的ip和port信息
		{
			if(ret==-1)
			{
				perror("recvfrom");
				close(sfd);
				exit(-1);
			}
		}
		printf("client %s\n",buf);
		printf("receive measage from %s,%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
		fgets(buf,sizeof(buf)-1,stdin);
		if(strcmp(buf,"quit\n")==0)
		{
			close(sfd);
			exit(0);
		}
		ret=sendto(sfd,buf,strlen(buf)+1,0,(struct sockaddr*)&clientaddr,sizeof(struct sockaddr_in));//向客户端发送数据，由于没有握手，因此每个包都要有客户端的ip和port
	}
	close(sfd);
	return 0; 
}
