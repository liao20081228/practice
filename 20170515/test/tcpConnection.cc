#include"tcpConnection.h"
#include"epoll.h"
namespace MyNamespace
{
	CTcpConnection::CTcpConnection(IN int nNewSocketFd, IN CEpoll& cEpoll)
		: __cm_cNewSocketFd(nNewSocketFd) 
		, __cm_cSocketIO(__cm_cNewSocketFd.GetSocketFd())
		, __cm_cLocalSocketAddress(gGetLocalAddress(__cm_cNewSocketFd.GetSocketFd()))
		, __cm_cPeerSocketAddress(gGetPeerAddress(__cm_cNewSocketFd.GetSocketFd()))
		, __cm_cEpoll(cEpoll)
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
	CTcpConnection::SendAndClose(IN const string& cstrResult) //真正发送计算结果的方法
	{
		SendMessege(cstrResult);
		ShutDown();
	}

	void
	CTcpConnection::SendInEpollLoop(IN const string& cstrResult)
	{
		__cm_cEpoll.RunInLoop(std::bind(&CTcpConnection::SendAndClose, this, cstrResult));
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
