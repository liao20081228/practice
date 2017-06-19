/*************************************************************************
    > File Name: tcp_client1.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月15日 星期三 23时52分11秒
 ************************************************************************/
#include"myhead.h"
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
	char buf[110];
	char buf_order[10];//输入命令
	char buf_par[100];//输入参数
	data databag;
	bzero(&databag,sizeof(databag)); 
	fd_set readset;
	while(1)//服务器用eppol事件触发，客户机用select轮询
	{
		FD_ZERO(&readset);//每次监听都要从新注册，否则不能监测
		FD_SET(STDIN_FILENO,&readset);
		FD_SET(sfd,&readset);//sfd和标准输入加入监听
		ret=select(sfd+1,&readset,NULL,NULL,NULL);//返回状态已经发生了改变的描述符的个数,标准输入可读，或者套接字可读
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&readset))//如果标准输入可读
			{ 
				bzero(&databag,sizeof(databag));
				bzero(buf_order,sizeof(buf_order));
				bzero(buf_par,sizeof(buf_par));
				bzero(buf,sizeof(buf));
				read(STDIN_FILENO,buf,sizeof(buf));
				sscanf(buf,"%s%s",buf_order,buf_par);
				if(strlen(buf_order)==0)//读取标准输入,没有输入任何指令则退出
				{
				}
				else
				{
					if(strcmp(buf_order,"cd")==0)//判断输入命令种类，采取相应的操作
					{
						if(strlen(buf_par)==0)
							strcpy(buf_par,".");
						Send_order_or_information(sfd,1,buf_par);
					}
					else if(strcmp(buf_order,"ls")==0)
					{
						if(strlen(buf_par)==0)
							strcpy(buf_par,".");
						Send_order_or_information(sfd,2,buf_par);
					}
					else if(strcmp(buf_order,"puts")==0)
					{
						if(strlen(buf_par)>0)
						{
							if(Send_file(sfd,3,buf_par)==0)
								printf("上传%s成功\n",buf_par);
							else
								printf("上传%s失败\n",buf_par);
						}
					}
					else if(strcmp(buf_order,"gets")==0)
					{
						 if(strlen(buf_par)>0)
							Send_order_or_information(sfd,4,buf_par);
					}
					else if(strcmp(buf_order,"remove")==0)
					{
						if(strlen(buf_par)>0)
							Send_order_or_information(sfd,5,buf_par);
					}
					else if(strcmp(buf_order,"pwd")==0)
					{
						bzero(buf_par,sizeof(buf_par));
						strcpy(buf_par,".");
						Send_order_or_information(sfd,6,buf_par);
					}else if(strcmp(buf_order,"quit")==0)
					{
						break;
					}
				}
			}
			if(FD_ISSET(sfd,&readset))//如果套接字有消息可读
			{
				bzero(&databag,sizeof(databag));
				Recv_n(sfd,(char*)&databag.len,sizeof(databag.len));//每次接收都先接收数据包的长度后才开始接收真正的数据 
				if(databag.len>0)
				{
					Recv_n(sfd,(char *)&databag.order,sizeof(databag.order));//接着接收命令种类
					if(databag.order!=4)//如果不是下载命令的数据包，就循环打印
					{
						Recv_n(sfd,databag.buf,databag.len);
						write(STDOUT_FILENO,databag.buf,databag.len);
						while(1)//循环接收                                                                                       
						{  
							bzero(&databag,sizeof(data));
							Recv_n(sfd,(char*)&databag.len,sizeof(databag.len));//每次接收都先接收数据长度
							if(databag.len>0)
							{
								Recv_n(sfd,(char*)&databag.order,databag.len+sizeof(databag.order));
								write(STDOUT_FILENO,databag.buf,databag.len);
							}
							else
							{
								break;
							}
						}
					}
					else//如果是下载命令就要写入文件中
					{
						Recv_n(sfd,databag.buf,databag.len);//接收文件名
						Recv_file(sfd,databag.order,databag.buf);
					}
				}
			}
		}
	}
	printf("发送停止消息\n");
	Send_stop(sfd);
	printf("已经发送\n");
	close(sfd);
	return 0;
}
