/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 19时49分31秒
 ************************************************************************/
#include<myhead>
int main(void)
{
	struct sockaddr_in server;
	::bzero(&server, sizeof(server));
	server.sin_port=htons(10000);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("192.168.0.123");

	int a=socket(AF_INET,SOCK_STREAM,0);
	int ret = bind(a,(struct sockaddr*)&server,sizeof(struct sockaddr));
	perror("bind");
	cout <<ret<<endl;
	while(1);
	return 0;
}
