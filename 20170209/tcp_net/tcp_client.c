/*************************************************************************
    > File Name: tcp_client.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月11日 星期六 19时41分36秒
 ************************************************************************/
#include"tcp_net_socket.h"
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong!\n");
		exit(-1);
	}
	int sfd=tcp_client_connect(argv[1],atoi(argv[2]));
	char buf[100];
	bzero(buf,sizeof(buf));
	scanf("%s",buf);
	if(send(sfd,buf,strlen(buf),0)==-1)
	{
		perror("send");
		close(sfd);
		exit(-1);
	}
	if(recv(sfd,buf,sizeof(buf),0)==-1)
	{
		perror("recv");
		close(sfd);
		exit(-1);
	}
	printf("server:%s\n",buf);
	close(sfd);
	return  0;
}
