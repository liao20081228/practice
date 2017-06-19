/*************************************************************************
    > File Name: client.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月19日 星期一 14时29分29秒
 ************************************************************************/
#include"socketFd.h"
#include"inetAddress.h"
#include"socketIO.h"
using namespace MyNamespace;
int main(void)
{
	CSocketFd cSocketFd;
	CSocketAddress cSocketAddress(8888, "192.168.220.123");

	::connect(cSocketFd.GetSocketFd(), cSocketAddress.GetSockaddr(), sizeof(sockaddr));
	CSocketIO cSocketIO(cSocketFd);
	char buf[1024];
	cSocketIO.Recv(buf,1024);
	std::strcpy(buf,"i am client!");
	cSocketIO.Send(buf,strlen(buf));
	return 0;
}
