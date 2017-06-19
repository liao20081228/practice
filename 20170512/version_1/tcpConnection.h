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
namespace MyNamespace
{
	class CTcpConnection
	{
		public:
			CTcpConnection(IN CSocketFd cSocketFd, IN CSocketAddress cSocketAddress);
			int Send(IN const char* buf) const;
			int Recv(OUT char* buf, IN int nLength) const ;

			int SendFile(const char* FileName) const;
			int RecvFile(void) const ;
		private:
			CAcceptor __cm_cAcceptor;
			CSocketFd __cm_cNewSocketFd;
			CSocketIO __cm_cSocketIO;
	};

	inline
	CTcpConnection::CTcpConnection(IN CSocketFd cSocketFd, IN CSocketAddress cSocketAddress)
		: __cm_cAcceptor(cSocketFd, cSocketAddress)
		, __cm_cNewSocketFd(__cm_cAcceptor.AcceptConnect()) 
		, __cm_cSocketIO(__cm_cNewSocketFd)
	{
		cout << cSocketFd.GetSocketFd() << endl;
		cout << __cm_cNewSocketFd.GetSocketFd()<<endl;
	}
	
	int 
	CTcpConnection::Send(IN const char* buf) const
	{
		return __cm_cSocketIO.Send(buf, std::strlen(buf));
	}

	int 
	CTcpConnection::Recv(IN char* buf, IN int nLength) const 
	{
		return __cm_cSocketIO.Recv(buf, nLength);
	}
	
	int
	CTcpConnection::SendFile(IN const char* FileName) const 
	{
		return __cm_cSocketIO.SendFile(FileName);
	}

	int
	CTcpConnection::RecvFile(void) const 
	{
		return __cm_cSocketIO.RecvFile();
	}
}

#endif /* end of include guard: MY_TCP_CONNECTION_H */
