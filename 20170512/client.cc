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
	CSocketAddress cSocketAddress(8888, "127.0.0.123");
	::connect(cSocketFd.GetSocketFd(), cSocketAddress.GetSockaddr(), sizeof(sockaddr));
	CSocketIO client(cSocketFd);
	string strBuf;
	client.RecvMessage(strBuf);
	cout << strBuf << endl;
	client.SendMessage("i am client");
	client.RecvFile();
	client.SendFile("./acceptor.h");
	return 0;
}
