/*************************************************************************
    > File Name: udp_client.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月08日 星期六 23时26分22秒
 ************************************************************************/

#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int  main(int argc, char *argv[])
{
	if(argc !=3)
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
	unsigned int len=sizeof(struct sockaddr );
	char buf[1000];
	while(1)
	{
		bzero(buf,sizeof(buf));
		read(STDIN_FILENO,buf,sizeof(buf));
		sendto(sfd,buf,strlen(buf),0,(struct sockaddr*)&server,len);
		bzero(buf,sizeof(buf));
		recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&server,&len);
		write(STDOUT_FILENO,buf,strlen(buf));
	}
	close(sfd);
	return 0;
}
