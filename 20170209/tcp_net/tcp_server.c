/*************************************************************************
    > File Name: tcp_server.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月11日 星期六 09时47分44秒
 ************************************************************************/
#include"tcp_net_socket.h"
int main(int argc ,char*argv[])
{
	if(argc!=4)
	{
		printf("argc is wrong !\n");
		exit(-2);
	}
	char buf[100];
	int sfd=tcp_server_init(argv[1],atoi(argv[2]),atoi(argv[3]));
	while(1)
	{
		int new_sfd=tcp_server_accept(sfd);
		bzero(buf,sizeof(buf));
		if(recv(new_sfd,buf,sizeof(buf),0)==-1)
		{
			perror("recv");
			close(sfd);
			close(new_sfd);
			exit(-1);
		}
		printf("client:%s\n",buf);
		scanf("%s",buf);
		if(send(new_sfd,buf,sizeof(buf),0)==-1)
		{
			perror("send");
			close(sfd);
			close(new_sfd);
			exit(-1);
		}
		close(new_sfd);
	}
	close(sfd);
	return 0;
}
