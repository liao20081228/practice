/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 19时49分31秒
 ************************************************************************/
#include"tcpConnection.h"
int main(void)
{
	MyNamespace::CSocketFd cSocket;
	MyNamespace::CSocketAddress cSocketAddress(8888, "127.0.0.123");
	MyNamespace::CTcpConnection server(cSocket, cSocketAddress);
	char* pbuf = new char[10000];
	std::memset(pbuf, 'b', 10000);
	server.SendMessege(pbuf);
	::bzero(pbuf, 10000);
	server.RecvMessege(pbuf);
	cout << pbuf << endl;
	server.SendFile("./tcpConnection.h");
	server.RecvFile();
	return 0;
}
