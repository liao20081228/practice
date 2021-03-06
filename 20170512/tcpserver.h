/*************************************************************************
    > File Name: tcpserver.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月27日 星期二 17时07分41秒
 ************************************************************************/
#ifndef MY_TCPSERVER_H
#define MY_TCPSERVER_H
#include"epoll.h"
namespace MyNamespace
{
	class CTcpServer
	{
		public:
			CTcpServer(IN const string& strIP,  IN unsigned short usnPort);
			CTcpServer(IN unsigned short usnPort);
			void Start(void);
			void Stop(void);
		private:
			CAcceptor __cm_cAccptor;
			CEpoll __cm_cEpoll;
		public:
			void SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnnectCallBack);
			void SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack);
		private:
			std::function<void(const CTcpConnection&)> __cm_cOnConnnectCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnClosedCallBack;
	};

	inline
	CTcpServer::CTcpServer(IN const string& strIP, IN unsigned short usnPort)
		:__cm_cAccptor(gCreateSocketFd(), CSocketAddress(usnPort, strIP))
		,__cm_cEpoll(__cm_cAccptor)
	{
	}

	inline void
	CTcpServer::Start(void)
	{
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
	
} /* MyNamespace */ 
#endif /* end of include guard: MY_TCPSERVER_H */
