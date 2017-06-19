/*************************************************************************
    > File Name: change_nonblock.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月13日 星期一 20时45分21秒
 ************************************************************************/

#include<myhead.h>
void change_nonbloc(int fd)
{
	int flags=0;
	flags=fcntl(fd,F_GETFL);
	if(-1==fcntl(fd,F_SETFL,flags|O_NONBLOCK))
	{
		perror("fcntl");
		return ;
	}
	return ;
}
int main()
{
	char buf[20];
	change_nonbloc(STDIN_FILENO);
	bzero(buf,sizeof(buf));
	int ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
	printf("%s,%d,%d\n",buf,ret,errno);
	return 0;
}
