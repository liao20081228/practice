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
	string strBuf;
	strBuf.assign(10000,'c');
	server.SendMessege(strBuf);
	strBuf.clear();
	server.RecvMessege(strBuf);
	cout << strBuf << endl;
	server.SendFile("./tcpConnection.h");
	server.RecvFile();
	return 0;
}
