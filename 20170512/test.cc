/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月19日 星期一 19时48分44秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int main(void)
{
	int sfd= socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(struct sockaddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(5000);
	serveraddr.sin_addr.s_addr=inet_addr("192.168.220.100");
	cout<<bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr))<<endl;
	
	return 0;
}
