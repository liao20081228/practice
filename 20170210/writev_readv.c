/*************************************************************************
    > File Name: writev_readv.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月13日 星期一 21时09分20秒
 ************************************************************************/
#include<myhead.h>
int main(int argc,char *argv[])
{
	if(argc!=3)
	 {
		 printf("argc is wrong \n");
		 return -1;
	 }
	int fd1=open("./a.txt",O_RDONLY);
	int fd2=open("./b.txt",O_WRONLY);
	char buf1[20],buf2[20],buf3[20];
	bzero(buf1,sizeof(buf1));
	bzero(buf2,sizeof(buf2));
	bzero(buf3,sizeof(buf3));
	struct iovec iov[3];
	iov[0].iov_base=buf1;
	iov[0].iov_len=sizeof(buf1);
	iov[1].iov_base=buf2;
	iov[1].iov_len=sizeof(buf2);
	iov[2].iov_base=buf3;
	iov[2].iov_len=sizeof(buf3);
	readv(fd1,iov,3);
	printf("%s%s%s\n",buf1,buf2,buf3);
	writev(fd2,iov,3);
	close(fd1);
	close(fd2);
	return 0;
}
