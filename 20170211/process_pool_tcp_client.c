/*************************************************************************
    > File Name: process_pool_tcp_client.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月17日 星期五 11时44分51秒
 ************************************************************************/
#include"myhead.h"
int recv_n(int sfd,char *databag,int databag_len)
{
	int total=0;
	int pos=0;
	while(total<databag_len)
	{
		pos=recv(sfd,databag+total,databag_len-total,0);
		total+=pos;
	}
	return 0;
}
int  main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong\n");
		exit(-1);
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);//创建客户机的套接字
	if(sfd==-1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in serveraddr;//存放服务器的信息
	bzero(&serveraddr,sizeof(struct sockaddr_in));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	if(connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))==-1)//连接服务器
	{
		printf("errno is %d\n",errno);
		perror("connect");
		close(sfd);
		exit(-1);
	}
	data databag;
	bzero(&databag,sizeof(databag));
	recv_n(sfd,(char*)&databag.len,sizeof(databag.len));//每次接收都先接收数据包的长度后才开始接收真正的数据
	recv_n(sfd,databag.buf,databag.len);
	int fd=open(databag.buf,O_WRONLY|O_CREAT|O_TRUNC,0755);//打开发送来的文件名，不存在则创建
	if(fd==-1)
	{
		perror("open");
		close(sfd);
		exit(-1);
	}
	while(1)//循环接收
	{
		bzero(&databag,sizeof(data));
		recv_n(sfd,(char*)&databag.len,sizeof(databag.len));//每次接收都先接收数据包的长度后才开始接收真正的数据
		if(databag.len>0)
		{
			recv_n(sfd,databag.buf,databag.len);
			write(fd,databag.buf,databag.len);
		}
		else
		{
			break;
		}
	}
	close(fd);
	close(sfd);
	return 0;
}
