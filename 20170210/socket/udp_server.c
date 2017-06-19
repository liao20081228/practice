/*************************************************************************
    > File Name: udp_server.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月08日 星期六 22时48分10秒
 ************************************************************************/

#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int  main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong\n");
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	if(bind(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1)
	{
		printf("bind failed\n");
		close(sfd);
		return -1;
	}
	char buf[1000];
	struct sockaddr_in client;
	unsigned int len=sizeof(struct sockaddr);
	bzero(&client,sizeof(struct sockaddr));
	while(1)
	{
		bzero(&client,sizeof(struct sockaddr));
		bzero(buf,sizeof(buf));
		recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
		write(STDOUT_FILENO,buf,strlen(buf));
		bzero(buf,sizeof(buf));
		read(STDIN_FILENO,buf,sizeof(buf));
		sendto(sfd,buf,strlen(buf),0,(struct sockaddr*)&client,sizeof(struct sockaddr));
	}
	close(sfd);
	return 0;
}
