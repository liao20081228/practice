/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月09日 星期日 21时33分19秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int  main()
{
	int fd1=open("./a.txt",O_RDONLY);
	int fd2=open("./b.txt",O_WRONLY|O_CREAT);
	struct iovec iov[3];
	char str1[200]={'\0'},str2[200]={'\0'},str3[200]={'\0'};
	iov[0].iov_base=str1;
	iov[0].iov_len=sizeof(str1);
	iov[1].iov_base=str2;
	iov[1].iov_len=sizeof(str2);
	iov[2].iov_base=str3;
	iov[2].iov_len=sizeof(str3);
	readv(fd1,iov,3);
	printf("%s%s%s\n",str1,str2,str3 );
	writev(fd2,iov,3);
	close(fd1);
	close(fd2);
	return 0;
}
