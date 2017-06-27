/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 19时49分31秒
 ************************************************************************/
#include"tcpserver.h"
void OnConnect(const MyNamespace::CTcpConnection& crcTcpConnection)
{
	cout << crcTcpConnection.ToString() << endl;
	crcTcpConnection.SendMessege("welcom to server!");
}
void OnMessage(const MyNamespace::CTcpConnection& crcTcpConnection)
{
	string str;
	crcTcpConnection.RecvMessege(str);
	cout << str << endl;
}
void OnClose(const MyNamespace::CTcpConnection& crcTcpConnection)
{
	cout << "close " << crcTcpConnection.ToString() << endl;
}
int main(void)
{
	MyNamespace::CTcpServer server("127.0.0.123",8888);
	server.SetConnectCallBack(OnConnect);
	server.SetMessageCallBack(OnMessage);
	server.SetCloseCallBack(OnClose);
	server.Start();
}
