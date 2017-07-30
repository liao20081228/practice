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
			/*由用户调用set**callback方法设置tcpserver的三个函数*/
			void SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnnectCallBack);
			void SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack);
		private:
			std::function<void(const CTcpConnection&)> __cm_cOnConnnectCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnClosedCallBack;
	};

	
} /* MyNamespace */ 
#endif /* end of include guard: MY_TCPSERVER_H */
