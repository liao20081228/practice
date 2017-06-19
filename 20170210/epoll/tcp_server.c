/*************************************************************************
    > File Name: tcp_server.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月14日 星期二 22时00分41秒
 ************************************************************************/
#include<myhead.h>
int  chang_nonblock(int fd)//将描述符改为非阻塞
{
	if(fcntl(fd,F_SETFL,fcntl(fd,F_GETFL)|O_NONBLOCK)==-1)
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}
int main(int argc ,char *argv[])
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
	struct sockaddr_in  serveraddr;
	bzero(&serveraddr,sizeof(struct sockaddr_in));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr=inet_addr(argv[1]);
	if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr_in))==-1)
	{
		perror("bind");
		close(sfd);
		exit(-1);
	}
	if(listen(sfd,10)==-1)
	{
		perror("listen");
		close(sfd);
		exit(-1);
	}
	int eplfd=epoll_create(1);
	if(eplfd==-1)
	{
		perror("eplfd");
		close(sfd);
		exit(-1);
	}
	struct epoll_event event,evs[3];//定义监测的事件集合
	bzero(&event,sizeof(struct epoll_event));
	event.data.fd=sfd;
	event.events=EPOLLIN;//将sfd变为可读加入监测
	if(epoll_ctl(eplfd,EPOLL_CTL_ADD,sfd,&event)==-1)
	{
		perror("epoll_ctl");
		close(sfd);
		close(eplfd);
		exit(-1);
	}
	bzero(&event,sizeof(struct epoll_event));
	event.data.fd=STDIN_FILENO;
	event.events=EPOLLIN;//将标准输入变为可读加入监测
	if(epoll_ctl(eplfd,EPOLL_CTL_ADD,STDIN_FILENO,&event)==-1)
	{
		perror("epoll_ctl");
		close(sfd);
		close(eplfd);
		exit(-1);
	}
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(struct sockaddr_in));
	char buf[100];
	bzero(buf,sizeof(buf));
	bzero(evs,sizeof(struct epoll_event)*3);
	int new_sfd;
	int i;//循环计数器;
	short int ret;
	socklen_t addrlen=0;
	while(1)//epoll循环监听
	{
		bzero(evs,sizeof(evs));
		ret=epoll_wait(eplfd,evs,3,-1);//监测标准输入是否可读，sfd是否有链接请求
		if(ret<0)
		{
			perror("epoll_wait");
			close(sfd);
			close(eplfd);
			exit(-1);
		}
		else if(ret>0)
		{
			for(i=0;i<ret;i++)//循环遍历每一个事件
			{
				if(evs[i].data.fd==sfd)//说明sfd状态改变，有链接请求
				{
					addrlen=0;
					new_sfd=accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);//接收客户端的链接请求，客户端信息并放在clientaddr结构体
					if(new_sfd==-1)
					{
						perror("accept");
						close(sfd);
						close(eplfd);
						exit(-1);
					}
					printf("client ip is%s,potr=%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));//打印客户机的ip和端口
					if(chang_nonblock(new_sfd)==-1)//改变描述符为非阻塞状态
					{
						close(sfd);
						close(eplfd);
						close(new_sfd);
						exit(-1);
					}
					bzero(&event,sizeof(struct epoll_event));//将新的new_sfd加入监测
					event.data.fd=new_sfd;
					event.events=EPOLLIN;
					if(epoll_ctl(eplfd,EPOLL_CTL_ADD,new_sfd,&event)==-1)
					{
						perror("epoll_ctl");
						close(sfd);
						close(eplfd);
						close(new_sfd);
						exit(-1);
					}
				}
				if(evs[i].data.fd==new_sfd)
				{
					while(1)//循环读取数据
					{
						bzero(buf,sizeof(buf));
						ret=recv(new_sfd,buf,sizeof(buf),0);
						if(ret==-1)//读取出错
						{
							if(errno==EAGAIN)//缓冲区读空了返回的非阻塞下调用阻塞的错误
							{
								break;
							}
							else//出现的其他错误
							{
								perror("epoll_ctl");
								close(sfd);
								close(eplfd);
								close(new_sfd);
								exit(-1);
							}
						}
						else if(ret==0)//说明客户端已经关闭,这个new_sfd就要从监听集合中删除
						{
							printf("byebye,see you later!\n");
							bzero(&event,sizeof(struct epoll_event));
							event.data.fd=new_sfd;
							event.events=EPOLLIN;
							if(epoll_ctl(eplfd,EPOLL_CTL_DEL,new_sfd,&event)==-1)
							 { 
								perror("epoll_ctl");
								close(sfd);
								close(eplfd); 
								exit(-1); 
							 } 
							 close(new_sfd);
							break;
						}
						else if(ret>0)//说明读取了数据
						{
							printf("message frome client:%s\n", buf);
						}
						printf("\n");
					}
				} 
				if(evs[i].data.fd==STDIN_FILENO && evs[i].events==EPOLLIN)//说明有消息需要发送
				{
					bzero(buf,sizeof(buf));
					ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
					if(ret<=0)//如果没有输入消息，则表示会话完成
					{
						printf("byebye,see you later\n");
						close(new_sfd);
						bzero(&event,sizeof(struct epoll_event));
						event.data.fd=new_sfd;
						event.events=EPOLLIN;
						if(epoll_ctl(eplfd,EPOLL_CTL_DEL,new_sfd,&event)==-1)
						{
							perror("epoll_ctl");
							close(sfd);
							close(eplfd);
							exit(-1);
						}
						continue;
					}
					else//有消息则发送
					{
						if(send(new_sfd,buf,strlen(buf)-1,0)==-1)
						{
							perror("send");
							close(sfd);
							close(eplfd);
							close(new_sfd);
							exit(-1);
						}
					}
				}
			}
		}
	}
	close(sfd);
	return 0;
}
