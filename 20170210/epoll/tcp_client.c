/*************************************************************************
    > File Name: tcp_client1.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月15日 星期三 23时52分11秒
 ************************************************************************/
#include<myhead.h>
int  main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong\n");
		exit(-1);
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(struct sockaddr_in));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	short int ret=0;
	if(connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr_in))==-1)
	{
		perror("connect");
		close(sfd);
		exit(-1);
	}
	char buf[100];
	fd_set readset;
	while(1)//服务器用eppol事件触发，客户机用select轮询
	{
		FD_ZERO(&readset);
		FD_SET(STDIN_FILENO,&readset);
		FD_SET(sfd,&readset);//sfd和标准输入加入监听
		ret=select(sfd+1,&readset,NULL,NULL,NULL);//返回状态已经发生了改变的描述符的个数,标准输入可读，或者套接字可读
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&readset))//如果标准输入可读
			{
				bzero(buf,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))<=0)//读取标准输入
				{
					printf("byebye,see you later server\n");
					break;
				}
				if(send(sfd,buf,sizeof(buf)-1,0)==-1)//发送标准输入的消息
				{
					perror("send");
					close(sfd);
					exit(-1);
				}
			}
			if(FD_ISSET(sfd,&readset))//如果套接字有消息可读
			{
				bzero(buf,sizeof(buf));
				if((ret=recv(sfd,buf,sizeof(buf),0))==-1)//读取对端发送的消息
				{
					perror("recv");
					close(sfd);
					exit(-1);
				}
				else if(ret==0)//对端关闭
				{
					printf("byebye,see you later server\n");
					break;
				}
				else
				{
					printf("message from server:%s\n",buf);
				}
			}
		}
	}
	close(sfd);
	return 0;
}
