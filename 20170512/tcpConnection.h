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

	class CTcpConnection;
	class CTcpConnection /*: public std::enable_shared_from_this<CTcpConnection>*/
	{
		public:
			CTcpConnection(IN int nNewSocketFd);
			~CTcpConnection(void);
			
			void SendMessege(IN const string& strBuf) const;
			void  RecvMessege(OUT string& strBuf) const;

			void SendFile(const string& strFileName) const;
			void RecvFile(void) const;

			string ToString(void) const;

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
			bool __cm_bIsShuntDown;
	};

	CTcpConnection::CTcpConnection(IN int nNewSocketFd)
		: __cm_cNewSocketFd(nNewSocketFd) 
		, __cm_cSocketIO(__cm_cNewSocketFd.GetSocketFd())
		, __cm_cLocalSocketAddress(gGetLocalAddress(__cm_cNewSocketFd.GetSocketFd()))
		, __cm_cPeerSocketAddress(gGetPeerAddress(__cm_cNewSocketFd.GetSocketFd()))
		, __cm_bIsShuntDown(false)
	{
		if (__cm_cNewSocketFd.GetSocketFd() == -1)
		{
			cout << "传入新建连接的套接字错误" << endl;
			exit(-1);
		}
	}

	CTcpConnection::~CTcpConnection(void)
	{
		if(!__cm_bIsShuntDown)
		{
			__cm_bIsShuntDown = true;
			ShutDown();
		}
	}
	void 
	CTcpConnection::SendMessege(IN const string& strBuf) const
	{
		 __cm_cSocketIO.SendMessage(strBuf);
	}

	void 
	CTcpConnection::RecvMessege(IN string& strBuf) const 
	{
		 __cm_cSocketIO.RecvMessage(strBuf);
	}
	
	void
	CTcpConnection::SendFile(IN const string& strFileName) const 
	{
		__cm_cSocketIO.SendFile(strFileName);
	}

	void
	CTcpConnection::RecvFile(void) const 
	{
		 __cm_cSocketIO.RecvFile();
	}

	string
	CTcpConnection::ToString(void) const
	{
		char buf[200]={'\0'};
		std::sprintf(buf, "server ip:%s,server port%d; client ip:%s,client port:%d" ,
			   	 __cm_cLocalSocketAddress.GetIp_c(), __cm_cLocalSocketAddress.GetPort(),
				 __cm_cPeerSocketAddress.GetIp_c(), __cm_cPeerSocketAddress.GetPort());
		return string(buf);
	}

	int 
	CTcpConnection::ShutDown(void) 
	{
		if(!__cm_bIsShuntDown)
		{
			__cm_cNewSocketFd.ShutDown();
		}
		__cm_bIsShuntDown = true;
		return 0;
	}

	inline void 
	CTcpConnection::SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnectCallBack)
	{
		__cm_cOnConnectCallBack = cOnConnectCallBack;
	}

	inline void 
	CTcpConnection::SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack)
	{
		__cm_cOnMessageCallBack = cOnMessageCallBack;
	}
	
	inline void 
	CTcpConnection::SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack)
	{
		__cm_cOnCloseCallBack = cOnCloseCallBack;
	}

	void
	CTcpConnection::HandleConnectCallBack(void) const
	{
		if (__cm_cOnConnectCallBack)
		{
			__cm_cOnConnectCallBack(*this);
		}
	}

	void
	CTcpConnection::HandleMessageCallBack(void) const
	{
		if (__cm_cOnMessageCallBack)
		{
			__cm_cOnMessageCallBack(*this);
		}
	}

	void
	CTcpConnection::HandleCloseCallBack(void) const
	{
		if (__cm_cOnCloseCallBack)
		{
			__cm_cOnCloseCallBack(*this);
		}
	}
}

#endif /* end of include guard: MY_TCP_CONNECTION_H */
