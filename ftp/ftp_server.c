/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月16日 星期四 20时01分39秒
 ************************************************************************/
#include"myhead.h"
int  main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("argc is wrong\n");
		exit(-1);
	}
	int count=atoi(argv[3]);
	pcdata p=(pcdata)calloc(count,sizeof(cdata)*count);
	if(!p)
	{
		printf("calloc failed\n");
		exit(-1);
	}
	Create_child(p,count);//创建count个子进程
	signal(SIGINT,Sighandler);//创建程序退出机制,必须在子进程创建后，否则子进程同样会响应这个信号
	int sfd=socket(AF_INET,SOCK_STREAM,0);//创建服务器的套接字
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
	if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		close(sfd);
		exit(-1);
	} 
	if(listen(sfd,count)==-1)
	{
		perror("listen");
		close(sfd);
		exit(-1);
	}
	int epollfd=epoll_create(1);//创建epoll侦听
	if(epollfd==-1)
	{
		perror("epoll_create");
		close(sfd);
		exit(-1);
	}
	struct epoll_event event,*evs;//evs指向同时触发事件发生的集合,event为注册侦听事件
	bzero(&event,sizeof(struct epoll_event));//初始化event,之后把sfd加入监听事件
	event.events=EPOLLIN;
	event.data.fd=sfd;
	if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sfd,&event)==-1)
	{
		perror("epoll_ctl");
		close(sfd);
		close(epollfd);
		exit(-1);
	}
	for(int i=0;i<count;i++)//将通向每个子进程的套接字加入监听
	{
		bzero(&event,sizeof(struct epoll_event));
		event.events=EPOLLIN;
		event.data.fd=p[i].fdwrite;
		if(epoll_ctl(epollfd,EPOLL_CTL_ADD,p[i].fdwrite,&event)==-1)
		{
			perror("epoll_ctl");
			close(sfd);
			close(epollfd);
			exit(-1);
		}
	}
	int flag=0;
	int ret=0;
	int new_sfd;//接收连接后生成的新的套接字
	struct sockaddr_in clientaddr;//存放客户端的信息
	bzero(&clientaddr,sizeof(struct sockaddr_in));
	evs=(struct epoll_event*)calloc(count,sizeof(struct epoll_event));
	socklen_t clientaddrlen=0;
	signal(SIGINT,Sighandler);
	while(1)//循环监听
	{
		bzero(evs,sizeof(struct epoll_event)*count);
		ret=epoll_wait(epollfd,evs,count,-1);
		if(ret>0)//说明有时间发生，sfd收到链接请求或者子进程的任务发送完成后发送的完成消息
		{
			for(int i=0;i<count;i++)
			{
				if(evs[i].data.fd==sfd)//有链接请求
				{
					new_sfd=accept(sfd,(struct sockaddr*)&clientaddr,&clientaddrlen);//接收连接，产生新的套接字，然后发给空闲的子进程
					if(new_sfd==-1)
					{
						perror("accept");
						close(sfd);
						close(epollfd);
						exit(-1);
					}
					for(int j=0;j<count;j++)//遍历子进程，将任务发送给非忙碌的进程
					{
						if(p[j].busy==0)
						{
							Send_sfd(p[j].fdwrite,new_sfd);
							p[j].busy=1;
							char buf[20]="connnect success\n";
							Send_order_or_information(new_sfd,2,buf);
							break;
						}
					}
					int reuse=0;                                                           
					setsockopt(new_sfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(int));
					close(new_sfd);
				}
				for(int j=0;j<count;j++)//子进程套接字的写端收到子进程发出的任务完成的消息
				{
					if(evs[i].data.fd==p[j].fdwrite)
					{
						read(p[j].fdwrite,&flag,sizeof(int));//人物完成，改为非忙碌状态
						p[j].busy=0;
					}
				}
			}
		}
	}
close(epollfd);
close(sfd);
wait(NULL);
return 0;
}
