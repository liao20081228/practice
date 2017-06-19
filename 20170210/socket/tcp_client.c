/*************************************************************************
    > File Name: tcp_client.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月08日 星期六 16时30分31秒
 ************************************************************************/

#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int  main(int argc, char *argv[])
{
	if(argc !=3)
	{
		printf("argc is wrong\n");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	inet_aton(argv[1],&server.sin_addr);
	if(connect(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		return -1;
	}	
	char buf[1000];
	while(1)
	{
		bzero(buf,sizeof(buf));
		read(STDIN_FILENO,buf,sizeof(buf));
		if(send(sfd,buf,strlen(buf),0)==0)
		{
			printf("server closed\n");
			break;
		}
		bzero(buf,sizeof(buf));
		recv(sfd,buf,sizeof(buf),0);
		write(STDOUT_FILENO,buf,strlen(buf));
	}
	close(sfd);
	return 0;
}
