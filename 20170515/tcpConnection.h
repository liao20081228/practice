/*************************************************************************
    > File Name: tcpConnection.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月19日 星期一 12时32分02秒
 ************************************************************************/
#ifndef MY_TCP_CONNECTION_H
#define MY_TCP_CONNECTION_H
#include"acceptor.h"
#include"socketIO.h"
#include"utility.h"
namespace MyNamespace
{

	class CEpoll;
	class CTcpConnection /*: public std::enable_shared_from_this<CTcpConnection>*/
	{
		public:
			CTcpConnection(IN int nNewSocketFd,  IN CEpoll& cEpoll);
			~CTcpConnection(void);
			
			void SendMessege(IN const string& strBuf) const;
			void  RecvMessege(OUT string& strBuf) const;

			void SendFile(const string& strFileName) const;
			void RecvFile(void) const;
			
			void SendInEpollLoop(IN const string& cstrResult);
			string ToString(void) const;
		private:
			void SendAndClose(IN const string& cstrResult);
			int ShutDown(void);
		public:
			/*void SetConnectCallBack(std::function<void(const shared_ptr<CTcpConnection>&)> cOnConnectCallBack);*/
			/*void SetMessageCallBack(std::function<void(const shared_ptr<CTcpConnection>&)> cOnMessageCallBack);*/
			/*void SetCloseCallBack(std::function<void(const shared_ptr<CTcpConnection>&)> cOnCloseCallBack);*/
			void SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnectCallBack);
			void SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack);
			void HandleConnectCallBack(void) const; 
			void HandleMessageCallBack(void) const;
			void HandleCloseCallBack(void) const;

		private:
			//每个连接在连接，收到消息，断开时的处理方法
			/*std::function<void(const shared_ptr<CTcpConnection>&)> __cm_cOnConnectCallBack;*/
			/*std::function<void(const shared_ptr<CTcpConnection>&)> __cm_cOnMessageCallBack;*/
			/*std::function<void(const shared_ptr<CTcpConnection>&)> __cm_cOnCloseCallBack;*/
			
			std::function<void(const CTcpConnection&)> __cm_cOnConnectCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnCloseCallBack;
		private:
			CSocketFd __cm_cNewSocketFd;
			CSocketIO __cm_cSocketIO;
			CSocketAddress __cm_cLocalSocketAddress,
						   __cm_cPeerSocketAddress;
			CEpoll&  __cm_cEpoll;
			bool __cm_bIsShuntDown;
	};
}

#endif /* end of include guard: MY_TCP_CONNECTION_H */
