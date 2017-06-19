/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月16日 星期四 20时01分39秒
 ************************************************************************/
#include"myhead.h"
void Sighandler(int sig_num)
{
	printf("!!!!after 3 seconds,stop all process\n");
	sleep(3);
	kill(0,sig_num);
	exit(-1);
}
int Send_n(int sfd,char *databag,int databag_len)    
{
	int total=0;
	int pos=0;
	while(total<databag_len)
	{
		pos=send(sfd,databag+total,databag_len-total,0);
		if(pos==-1)
		{
			perror("send");
			return -1;
		}
		total+=pos;
	}
	return 0;
}
int Send_sfd(int sfdwrite,int sfd)
{ 
	struct msghdr msg;
	bzero(&msg,sizeof(struct msghdr));
	struct iovec iov[2];
	bzero(iov,sizeof(struct iovec)*2);
	char buf0[20]="hello";
	char buf1[20]="nice to meet you";
	iov[0].iov_base=buf0;
	iov[0].iov_len=strlen(buf0);
	iov[1].iov_base=buf1;
	iov[1].iov_len=strlen(buf1);
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	size_t len=CMSG_LEN(sizeof(int));
	struct cmsghdr *pcmsg=(struct cmsghdr*)calloc(1,len);
	pcmsg->cmsg_len=len;
	pcmsg->cmsg_level=SOL_SOCKET;
	pcmsg->cmsg_type=SCM_RIGHTS;
	*(int *)CMSG_DATA(pcmsg)=sfd;
	msg.msg_control=pcmsg;
	msg.msg_controllen=len;
	if(sendmsg(sfdwrite,&msg,0)==-1)
	{
		perror("sendmsg");
		return -1; 
	}
	return 0;
} 
int Recv_sfd(int sfdread,int *sfd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(struct msghdr));
	struct iovec iov[2];
	bzero(iov,sizeof(struct iovec)*2);
	char buf0[20]="hello";
	char buf1[20]="nice to meet you";
	iov[0].iov_base=buf0;
	iov[0].iov_len=strlen(buf0);
	iov[1].iov_base=buf1;
	iov[1].iov_len=strlen(buf1);
	msg.msg_iov=iov;
	msg.msg_iovlen=2;
	int  len=CMSG_LEN(sizeof(int));//计算出要传递的负数附属控制信息包的大小
	struct cmsghdr *pcmsg=(struct cmsghdr*)calloc(1,len);//申请控制信息cmsg的空间，并初始化
	pcmsg->cmsg_len=len;
	pcmsg->cmsg_level=SOL_SOCKET;
	pcmsg->cmsg_type=SCM_RIGHTS;
	msg.msg_control=pcmsg;
	msg.msg_controllen=len;
	msg.msg_control=pcmsg;
	msg.msg_controllen=len;
	if(recvmsg(sfdread,&msg,0)==-1)//接收文件描述符
	{
		perror("recvmsg");
		return -1;
	}
	*sfd=*(int *)CMSG_DATA(pcmsg);
	return 0; 
}
int Send_file(int sfd)//sfd 为与客户端连接的套接字描述 符
{
	data databag;
	bzero(&databag,sizeof(data));
	databag.len=strlen(FILENAME); //把文件名发送给客户
	strcpy(databag.buf,FILENAME);
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+databag.len);
	int fd=open(FILENAME,O_RDONLY);//打开文件，文件描述符
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	while(bzero(&databag,sizeof(data)),(databag.len=read(fd,databag.buf,sizeof(databag.buf)))>0)//循环读取文件并发送每一个数据包给客户
	{
		Send_n(sfd,(char*)&databag,sizeof(databag.len)+databag.len); 
	}
	databag.len=0;
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+databag.len); //给客户端发送结束信息
	close(fd);//关闭文件描述符
	return 0;
}
int Handle_connect_need(int sfdread)
{
	int sfd;
	short int flag=1;
	while(1)
	{
		Recv_sfd(sfdread,&sfd);
		Send_file(sfd);
		write(sfdread,&flag,sizeof(short int));//向父进程传递消息，告诉其发送该文件已经完成，父进程收到后，触发epoll就会把子进程的状态改为非忙碌
	}//在父进程看来，套接字对的sfds[0]在子进程是读端fdread，但是在子进程看却时写端
	return 0;
}
int Create_child(pcdata p,int count)
{ 
	int sfds[2];//定义套接字对
	pid_t pid;
	for(int i=0;i<count;i++)
	{
		if(socketpair(AF_LOCAL,SOCK_STREAM,0,sfds)==-1)//循环创建套接字对，给每一个进程
		{
			perror("socketpair");
			free(p);
			exit(-1);
		}
		pid=fork();//创建子进程
		if(pid==0)//是子进程
		{
			close(sfds[1]);//子进程关闭写端
			Handle_connect_need(sfds[0]);
		}
		else//是父进程
		{
			p[i].fdwrite=sfds[1];//记录连接每个子进程的套接字的写端，用于向子进程传递描述符
			p[i].pid=pid;//记录子进程的pid
			p[i].busy=0;//初始状态均为，非忙碌
			close(sfds[0]);//关闭每个子进套接字的读端，
		}
	}
	return 0;
}
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
	short flag=0;
	int ret=0;
	int new_sfd;//接收连接后生成的新的套接字
	struct sockaddr_in clientaddr;//存放客户端的信息
	bzero(&clientaddr,sizeof(struct sockaddr_in));
	evs=(struct epoll_event*)calloc(count,sizeof(struct epoll_event));
	socklen_t clientaddrlen=0;
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
					for(int j=0;i<count;i++)//遍历子进程，将任务发送给非忙碌的进程
					{
						if(p[j].busy==0)
						{
							Send_sfd(p[j].fdwrite,new_sfd);
							p[j].busy=1;
							break;
						}
					}
					close(new_sfd);
				}
				for(int j=0;j<count;j++)//子进程收到任务完成的消息
				{
					if(evs[j].data.fd==p[j].fdwrite)
					{
						read(p[j].fdwrite,&flag,sizeof(int));//人物完成，改为非忙碌状态
						p[j].busy=0;
						printf("transmit file finish!\n");
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
