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
	class CTcpConnection
	{
		public:
			CTcpConnection(IN const CSocketFd& cSocketFd, IN const CSocketAddress& cSocketAddress);
			~CTcpConnection(void);
			
			int SendMessege(IN const string& strBuf) const;
			int RecvMessege(OUT string& strBuf) const ;

			int SendFile(const string& strFileName) const;
			int RecvFile(void) const;

			int ShutDown(void);
		private:
			CAcceptor __cm_cAcceptor;
			CSocketFd __cm_cNewSocketFd;
			CSocketIO __cm_cSocketIO;
			bool __cm_bIsShuntDown;
	};

	CTcpConnection::CTcpConnection(IN const CSocketFd& cSocketFd, IN const CSocketAddress& cSocketAddress)
		: __cm_cAcceptor(cSocketFd, cSocketAddress)
		, __cm_cNewSocketFd(__cm_cAcceptor.AcceptConnect()) 
		, __cm_cSocketIO(__cm_cNewSocketFd)
		, __cm_bIsShuntDown(false)
	{
		if (__cm_cNewSocketFd.GetSocketFd() == -1)
		{
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
	int 
	CTcpConnection::SendMessege(IN const string& strBuf) const
	{
		return __cm_cSocketIO.SendMessage(strBuf);
	}

	int 
	CTcpConnection::RecvMessege(IN string& strBuf) const 
	{
		return __cm_cSocketIO.RecvMessage(strBuf);
	}
	
	int
	CTcpConnection::SendFile(IN const string& strFileName) const 
	{
		return __cm_cSocketIO.SendFile(strFileName);
	}

	int
	CTcpConnection::RecvFile(void) const 
	{
		return __cm_cSocketIO.RecvFile();
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
}

#endif /* end of include guard: MY_TCP_CONNECTION_H */
