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
	//接收客户端数据
	crcTcpConnection.RecvMessege(str);
	//根据数据抽象出以个CTask 对象
	//CTask task(str);
	//theadpool.addtask(CTask); 将收到的数据交给线程池处理，完成之后处理结果交给IO线程，发给客户端
	//在task中有一个方法execute，方execute执行完任务后，获取了要返回给客户端的数据，在发送时需要知道是
	//哪一个连接来发送数据。但是不能直接调用连接的sendMessage进行发送，如果这样做就相当于在计算线程中
	//把数据发送出去，因此Tcpconnection（本身在计算线程之中） 需要通知IO线程去发送数据，
	//CEpoll需要增加一个eventfd，当计算线程处理完比时，通过eventfd发送信息，告知io线程可以传送了
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
