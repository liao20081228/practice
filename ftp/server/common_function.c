/*************************************************************************
    > File Name: common_function.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月17日 星期五 21时15分49秒
 ************************************************************************/
#include"myhead.h"
int Send_stop(int sfd)
{
	int len=-2;
	send(sfd,&len,sizeof(int),0);
	return 0;
}
int Remove_dir(char *pathname)//递归删除文件夹或者文件
{
	struct stat status;
	bzero(&status,sizeof(struct stat));
	stat(pathname,&status);//获取文件状态
	if(S_ISDIR(status.st_mode))//判断文件类型，如果是目录
	{
		DIR *dp=opendir(pathname);
		if(dp==NULL)
		{
			perror("opendir");
			return -1;
		}
		struct dirent *p=NULL;//打开目录读取目录信息
		while((p=readdir(dp))!=NULL)
		{
			if(strcmp(".",p->d_name)!=0 && strcmp("..",p->d_name)!=0)//除.和..之外全部递归删除
			{
				chdir(pathname);//删除时必须进入该目录
				Remove_dir(p->d_name);
				chdir("..");//删除完成后退出该目录
			}
		}
		closedir(dp);//关闭文件目录指针
	}
	remove(pathname);//删除文件或空目录
	return 0;
}
int Judgemode(mode_t st_mode,char mode[])//判断文件的权限，以字符串形式返回
{ 
	if(st_mode&S_IRUSR)//判断所有者组权限
		mode[0]='r';
	else
		mode[0]='-';
	if(st_mode&S_IWUSR)
		mode[1]='w';
	else
		mode[1]='-';
	if(st_mode&S_IXUSR)
		if(st_mode&S_ISUID)//是否有特殊权限
			mode[2]='s';
		else
			mode[2]='x';
	else
		if(st_mode&S_ISUID)
			mode[2]='S';
		else
			mode[2]='-';
	if(st_mode&S_IRGRP)//判断用户组权限
		mode[3]='r';
	else
		mode[3]='-';
	if(st_mode&S_IWGRP)
		mode[4]='w';
	else
		mode[4]='-';
	if(st_mode&S_IXGRP)
		if(st_mode&S_ISGID)//是否有特殊权限
			mode[5]='s';
		else
			mode[5]='x';
	else
		if(st_mode&S_ISGID)
			mode[5]='S';
		else
			mode[5]='-';
	if(st_mode&S_IROTH)
		mode[6]='r';
	else
		mode[6]='-';
	if(st_mode&S_IWOTH)
		mode[7]='w';
	else
		mode[7]='-';
	if(st_mode&S_IXOTH)
		if(st_mode&S_ISVTX)
			mode[8]='t';
		else
			mode[8]='x';
	else
		if(st_mode&S_ISVTX)
			mode[8]='T';
		else
			mode[8]='-';
	return 0;
}
int Judgefiletype(mode_t st_mode,char *ch)//判断文件类型，以字符形式返回
{ 
	if(S_ISLNK(st_mode))
		*ch='d';
	else if(S_ISBLK(st_mode))
		*ch='b';
	else if(S_ISREG(st_mode))
		*ch='-';
	else if(S_ISDIR(st_mode))
		*ch='d';
	else if(S_ISCHR(st_mode))
		*ch='c';
	else if(S_ISFIFO(st_mode))
		*ch='p';
	else if(S_ISSOCK(st_mode))
		*ch='s';
	return 0;
}
void Sighandler(int sig_num)//终止所有进程
{
	printf("!!!!after 3 seconds,stop all process\n");
	sleep(3);
	kill(0,sig_num);
	exit(-1);
}
int Send_dir(int sfd,int order,char *buf)//发送文件目录遍历信息
{
	char *pdir=getcwd(NULL,0);
	char buf_dir[1000];//存放要发送的信息
	bzero(buf_dir,sizeof(buf_dir));
	struct stat status;
	char mode[10];//存放读写权限
	char filetype;//存放文件类型符
	char week[3],month[3],day[2],time[8],year[4];
	bzero(&status,sizeof(struct stat));
	if(stat(buf,&status)==-1)//获取文件状态
	{
		strcpy(buf_dir,"stat pathname is wrong\n");
		Send_order_or_information(sfd,order,buf_dir);
		return -1;
	}
	if(S_ISDIR(status.st_mode))//判断文件类型，如果是目录
	{
		if(chdir(buf)!=0)
		{
			strcpy(buf_dir,"chdir pathname is wrong\n");
			Send_order_or_information(sfd,order,buf_dir);
			return -1;
		}
		DIR *dp=NULL;//目录流指针
		dp=opendir(buf);//打开目录
		if(dp==NULL)
		{
			strcpy(buf_dir,"open pathname is wrong\n");
			Send_order_or_information(sfd,order,buf_dir);
			return -1;
		}
		struct dirent *p;//文件信息简略指针
		bzero(&status,sizeof(struct stat));
		while((p=readdir(dp))!=NULL)
		{
			if(strcmp(".",p->d_name)!=0 && strcmp("..",p->d_name)!=0)
			{
				bzero(&status,sizeof(struct stat));
				if(stat(p->d_name,&status)!=0)
				{
					strcpy(buf_dir,"readdir pathname is wrong\n");
					Send_order_or_information(sfd,order,buf_dir);
					return -1;
				}
				filetype='\0';
				Judgefiletype(status.st_mode,&filetype);//判断文件类型；
				bzero(mode,sizeof(mode));
				Judgemode(status.st_mode,mode);//判断文件权限
				bzero(week,sizeof(week));
				bzero(month,sizeof(month));
				bzero(day,sizeof(day));
				bzero(time,sizeof(time));
				bzero(year,sizeof(year));
				sscanf(ctime(&status.st_mtime),"%s%s%s%s%s",week,month,day,time,year);
				bzero(buf_dir,sizeof(buf_dir));
				sprintf(buf_dir,"%c%-11s%-5lu%-10s%-10s%-10lu%-4s%-4s%-3s%-9s%-5s%-50s",filetype,mode,status.st_nlink,getpwuid(status.st_uid)->pw_name,getgrgid(status.st_gid)->gr_name,status.st_size,week,month,day,time,year,p->d_name);//文件类型权限用户所属组大小最后修改时间文件名
				Send_order_or_information(sfd,order,buf_dir);
			}
		}
		bzero(buf_dir,sizeof(buf_dir));
		strcpy(buf_dir,"\n");
		Send_order_or_information(sfd,order,buf_dir);
		closedir(dp);
		chdir(pdir);
	}
	else
	{	
		filetype='\0';
		Judgefiletype(status.st_mode,&filetype);//判断文件类型；
		bzero(mode,sizeof(mode));
		Judgemode(status.st_mode,mode);//判断文件权限
		bzero(week,sizeof(week));
		bzero(month,sizeof(month));
		bzero(day,sizeof(day));
		bzero(time,sizeof(time));
		bzero(year,sizeof(year));
		sscanf(ctime(&status.st_mtime),"%s%s%s%s%s",week,month,day,time,year);
		bzero(buf_dir,sizeof(buf_dir));
		sprintf(buf_dir,"%c%-11s%-5lu%-10s%-10s%-10lu%-4s%-4s%-3s%-9s%-5s%-50s\n",filetype,mode,status.st_nlink,getpwuid(status.st_uid)->pw_name,getgrgid(status.st_gid)->gr_name,status.st_size,week,month,day,time,year,buf);//文件类型权限用户所属组大小最后修改时间文件名
		Send_order_or_information(sfd,order,buf_dir);
	}
	return 0;
}
int Send_order_or_information(int sfd,int order,char *buf_par)//发送消息
{
	data databag;
	bzero(&databag,sizeof(data));
	databag.order=order;
	strcpy(databag.buf,buf_par);
	databag.len=strlen(databag.buf);
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+sizeof(databag.order)+databag.len);
	databag.len=0;
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+databag.len);
	return 0;
}
int Send_n(int sfd,char *databag,int databag_len) //发送数据
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
int Recv_n(int sfd,char *databag,int databag_len)//接收数据
{
	int total=0;
	int pos=0;
	while(total<databag_len)
	{
		pos=recv(sfd,databag+total,databag_len-total,0);
		if(pos==-1)
		{
			perror("recv");
			return -1;
		}
		total+=pos;
	}
	return 0;
}
int Send_sfd(int sfdwrite,int sfd)//发送描述符
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
int Recv_sfd(int sfdread,int *sfd)//接收描述符
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
int Send_file(int sfd,int order,char *buf)//发送文件
{  
	data databag;
	bzero(&databag,sizeof(data));
	struct stat status;
	bzero(&status,sizeof(struct stat));
	stat(buf,&status);
	if(S_ISDIR(status.st_mode))
	{
		strcpy(databag.buf,"不能上传或者下载目录\n");
		Send_order_or_information(sfd,2,databag.buf);
		return -1;
	}
	int fd=open(buf,O_RDONLY);//打开文件，文件描述符
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	databag.len=strlen(buf); //把文件名发送给客户
	databag.order=order;
	strcpy(databag.buf,buf);
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+sizeof(databag.order)+databag.len);
	while(bzero(&databag,sizeof(data)),databag.order=order,(databag.len=read(fd,databag.buf,sizeof(databag.buf)))>0)//循环读取文件并发送每一个数据包给客户
	{
		Send_n(sfd,(char*)&databag,sizeof(databag.len)+sizeof(databag.order)+databag.len); 
	}
	databag.len=0;
	Send_n(sfd,(char*)&databag,sizeof(databag.len)+databag.len); //给客户端发送结束信息
	close(fd);//关闭文件描述符
	return 0;
}  
int Recv_file(int sfd,int order,char *buf)//接收文件
{
	data databag;
	databag.order=order;
	bzero(&databag,sizeof(data));
	databag.len=strlen(buf); //根据收到的文件名创建文件
	int fd=open(buf,O_WRONLY|O_CREAT|O_TRUNC,0755);//打开文件，文件描述符
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	while(1)//循环接收
	{
		bzero(&databag,sizeof(data));
		Recv_n(sfd,(char*)&databag.len,sizeof(databag.len));
		if(databag.len>0)
		{
			Recv_n(sfd,(char*)&databag.order,databag.len+sizeof(databag.order));
			write(fd,databag.buf,databag.len); 
		}
		else
		{
			 break;
		}
	}
	close(fd);
	return 0;
} 
int Handle_connect_need(int sfdread)//处理连接请求
{ 
	int new_sfd;
	int flag=1;
	data databag;
	bzero(&databag,sizeof(data));
	while(1)
	{
		Recv_sfd(sfdread,&new_sfd);//接收主进程传来的新套接字
		while(1)
		{
			bzero(&databag,sizeof(data));
			Recv_n(new_sfd,(char*)&databag.len,sizeof(databag.len));//每次接收都先接收数据包的长度后,判断客户端的命令类型，再作出相应的处理
			if(databag.len>0)
			{
				Recv_n(new_sfd,(char *)&databag.order,sizeof(databag.order));//接收命令，并判断命令种类；
				switch(databag.order)
				{
					case 1: Recv_n(new_sfd,databag.buf,databag.len);//cd 命令，改变工作目录到目标目录
							if(chdir(databag.buf)==-1)
							{
								bzero(&databag.buf,sizeof(databag.buf));
								strcat(databag.buf,"pathname is wrong!\n");
							}
							else
							{
								bzero(&databag.buf,sizeof(databag.buf));
								strcpy(databag.buf,getcwd(NULL,0));
								strcat(databag.buf,"\n");
							}
							Send_order_or_information(new_sfd,databag.order,databag.buf);
							break;
					case 2: Recv_n(new_sfd,databag.buf,databag.len);//ls 命令，列出当前目录的信息
//							printf("%s,%s\n",databag.buf,getcwd(NULL,0));
	//						pdir=getcwd(NULL,0);
		//					if(chdir(databag.buf)==-1)
			//				{
				//				bzero(&databag.buf,sizeof(databag.buf));
					//			strcat(databag.buf,"pathname is wrong!\n");
						//		Send_order_or_information(new_sfd,databag.order,databag.buf);
						//		break;
					//		}
				//			printf("%s,%s\n",databag.buf,getcwd(NULL,0));
							Send_dir(new_sfd,databag.order,databag.buf);
			//				chdir(pdir);
							break;
					case 3: Recv_n(new_sfd,databag.buf,databag.len);//puts命令，上传文件；
						    Recv_file(new_sfd,databag.order,databag.buf);
							break;
					case 4: Recv_n(new_sfd,databag.buf,databag.len);//gets命令，下载文件
						    if(Send_file(new_sfd,databag.order,databag.buf)!=0)
							{
								bzero(&databag.buf,sizeof(databag.buf));
								strcat(databag.buf,"pathname is wrong!\n");
							}
							Send_order_or_information(new_sfd,databag.order,databag.buf);
							break;
					case 5: Recv_n(new_sfd,databag.buf,databag.len);//remove命令，删除文件
							if(Remove_dir(databag.buf)==0)
							{
								strcat(databag.buf," remove sucsess!\n");
							}
							else
							{
								strcat(databag.buf," remove failed!\n");
							}
							Send_order_or_information(new_sfd,databag.order,databag.buf);
							break;
					case 6: Recv_n(new_sfd,databag.buf,databag.len);//pwd命令，查看当前目录
							bzero(databag.buf,sizeof(databag.buf));
							strcpy(databag.buf,getcwd(NULL,0));
							strcat(databag.buf,"\n");
							Send_order_or_information(new_sfd,databag.order,databag.buf);
							break;
					default:break;
				}
			}
			else if(databag.len==-2)
			{
				write(sfdread,&flag,sizeof(short int));//向父进程传递消息，告诉其客户端已经退出，父进程收到后，触发epoll就会把子进程的状态改为非忙碌
				break;
			}
		}
		int reuse=0; 
		setsockopt(new_sfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(int));
		close(new_sfd);
	}//在父进程看来，套接字对的sfds[0]在子进程是读端fdread，但是在子进程看却时写端
	return 0;
}
int Create_child(pcdata p,int count)//创建子进程
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
