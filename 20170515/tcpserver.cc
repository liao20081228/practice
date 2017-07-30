#include"tcpserver.h"
namespace MyNamespace
{
	inline
	CTcpServer::CTcpServer(IN const string& strIP, IN unsigned short usnPort)
		:__cm_cAccptor(gCreateSocketFd(), CSocketAddress(usnPort, strIP))
		,__cm_cEpoll(__cm_cAccptor)
	{
	}

	inline void
	CTcpServer::Start(void)
	{
		/*套接字设置属性，绑定监听，调用epoll的set**callback（）将三个回调函数对象传给epoll，
		 * epoll在有新连接时，生成CTcpConnection对象，调用tcpconnection的set**callback（）将三
		 * 个回调函数传给tcpconnection，
		 */
		__cm_cAccptor.Ready();
		__cm_cEpoll.SetConnectCallBack(__cm_cOnConnnectCallBack);
		__cm_cEpoll.SetMessageCallBack(__cm_cOnMessageCallBack);
		__cm_cEpoll.SetCloseCallBack(__cm_cOnClosedCallBack);
		__cm_cEpoll.Loop();
	}

	inline void
	CTcpServer::Stop(void)
	{
		__cm_cEpoll.UnLoop();
	}
	inline void 
	CTcpServer::SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnnectCallBack)
	{
		__cm_cOnConnnectCallBack = cOnConnnectCallBack;
	}
	inline void 
	CTcpServer::SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack)
	{
		__cm_cOnMessageCallBack = cOnMessageCallBack;
	}
	inline void 
	CTcpServer::SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack)
	{
		__cm_cOnClosedCallBack = cOnCloseCallBack;
	}

}
