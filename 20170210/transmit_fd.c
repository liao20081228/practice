/*************************************************************************
    > File Name: transmit_fd.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月13日 星期一 22时33分27秒
 ************************************************************************/
#include<myhead.h>
void  send_fd(int sfd_write,int fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(struct msghdr));
	char str1[10]="hello",str2[10]=" child!",str3[20]="i am  parent!";
	struct iovec iov[3];
	iov[0].iov_base=str1;
	iov[0].iov_len=strlen(str1);
	iov[1].iov_base=str2;
	iov[1].iov_len=strlen(str2);
	iov[2].iov_base=str3;
	iov[2].iov_len=strlen(str3);
	msg.msg_iov=iov;
	msg.msg_iovlen=3;
	struct cmsghdr *pcmsg;//边长结构体必须先确定结构体大小，不能直接定义结构体变量
	socklen_t len=CMSG_LEN(sizeof(int ));
	pcmsg=(struct cmsghdr *)calloc(1,len);
	pcmsg->cmsg_len=len;
	pcmsg->cmsg_level=SOCK_STREAM;
	pcmsg->cmsg_type=SCM_RIGHTS;
	*(int *)CMSG_DATA(pcmsg)=fd;
	msg.msg_control=pcmsg;
	msg.msg_controllen=len;
	if(sendmsg(sfd_write,&msg,0)==-1)
	{
		perror("sendmsg");
		exit(-1);
	}
	return;
}
void recv_fd(int sfd_read,int *fd)
{
	struct msghdr msg;
	bzero(&msg,sizeof(struct msghdr));
	char str1[10]="hello",str2[10]=" child!",str3[20]="i am  parent!";
	struct iovec iov[3];
	iov[0].iov_base=str1;
	iov[0].iov_len=strlen(str1);
	iov[1].iov_base=str2;
	iov[1].iov_len=strlen(str2);
	iov[2].iov_base=str3;
	iov[2].iov_len=strlen(str3);
	msg.msg_iov=iov;
	msg.msg_iovlen=3;
	struct cmsghdr *pcmsg;//边长结构体必须先确定结构体大小，不能直接定义结构体变量
	socklen_t len=CMSG_LEN(sizeof(int ));
	pcmsg=(struct cmsghdr *)calloc(1,len);
	pcmsg->cmsg_len=len;
	pcmsg->cmsg_level=SOCK_STREAM;
	pcmsg->cmsg_type=SCM_RIGHTS;
	msg.msg_control=pcmsg;
	msg.msg_controllen=len;
	if(recvmsg(sfd_read,&msg,0)==-1)
	{
		perror("sendmsg");
		exit(-1);
	}
	*fd=*(int *)CMSG_DATA(pcmsg);//发送描述符和接收描述符只有这一句的位置和写法不同，其余一样；
	return;
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("argc is wrong\n");
		exit(-1);
	}
	int fds[2];
	if(-1==socketpair(AF_LOCAL,SOCK_STREAM,0,fds))
	{
		perror("socketpair");
		exit(-1);
	}
	printf("这两个套接口是%d,%d\n",fds[0],fds[1]);
	if(fork()==0)
	{
		int fd=0;
		close(fds[1]);//关闭写端
		recv_fd(fds[0],&fd);//子进程从fds[0]读取父进程发来文件描述符
		printf("chlid receive fd is%d\n",fd);
		char buf[100];
		bzero(buf,sizeof(buf));
		if(read(fd,buf,sizeof(buf))==-1)//对文件读操作
		{
			perror("read");
			exit(-2);
		}
		printf("buf=%s\n",buf);
		close(fds[0]);
		exit(0);
	}
	else
	{
		close(fds[0]);//关闭读端
		int fd=open(argv[1],O_RDONLY);
		if(fd==-1)
		{
			perror("open");
			exit(-1);
		}
		printf("in parent process ,the file's fd is %d",fd);
		send_fd(fds[1],fd);
		wait(NULL);
		close(fd);
		return 0;
	}
}
