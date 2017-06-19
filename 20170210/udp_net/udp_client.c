/*************************************************************************
  > File Name: tcp_client.c
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年02月11日 星期六 19时41分36秒
 ************************************************************************/
#include"udp_net_socket.h"
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong!\n");
		exit(-1);
	}
	int sfd=socket(AF_INET,SOCK_DGRAM,0);//产生自己的套接字
	if(sfd==-1)
	{
		perror("socket");
		exit(-1);
	}
	char buf[100];
	bzero(buf,sizeof(buf));
	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	while(1)
	{  
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf)-1,stdin);
		if(strcmp(buf,"quit\n")==0)
		{
			close(sfd);
			exit(0);
		}
		if(sendto(sfd,buf,strlen(buf)+1,0,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr_in))==-1)//向服务器发送数据，没有握手，所以每个包都要有服务器的ip和port
		{
			perror("sendto");
			close(sfd);
			exit(-1);
		}
		socklen_t addlen=0;
		struct sockaddr_in infofrom;
		bzero(&infofrom,sizeof(struct sockaddr_in));
		if(recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&infofrom,&addlen)==-1)//从服务器，没有握手，所以每个包都要有服务器的ip和port
		{
			perror("recvfrom");
			close(sfd);
			exit(-1);
		}
		printf("server:%s\n",buf);
		printf("recvfrom from%s,%d\n",inet_ntoa(infofrom.sin_addr),ntohs(infofrom.sin_port));
	}
	close(sfd);
	return  0;
}
