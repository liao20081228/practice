/*************************************************************************
    > File Name: acceptor.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月17日 星期六 15时30分10秒
 ************************************************************************/
#ifndef MY_ACCEPTOR_H
#define MY_ACCEPTOR_H
#include"inetAddress.h"
#include"socketFd.h"
#include"utility.h"
namespace MyNamespace
{
	class CAcceptor
	{
		public:
			CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress);/*  接收一个原始套接字*/
			
			void Ready(void) const;
			int AcceptConnect(void) const; /* 接收连接*/ 
			int GetSocketFd(void) const;
		private:
			void __BindSocketAddress(void) const; /* 绑定*/
			void __ListenSocket(void) const; /*监听*/
		private:
			int __cm_nListenSocketFd;
			CSocketAddress __cm_cAddress;
	};

	inline
	CAcceptor::CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress)
		: __cm_nListenSocketFd(nListenSocketFd)
		, __cm_cAddress(cAddress)
	{
		if (__cm_nListenSocketFd == -1)
		{
			cout << "传入的原始套接字错误" << endl;
			std::exit(-1);
		}
	}

	void
	CAcceptor::Ready(void) const
	{
		gSetReusePort(__cm_nListenSocketFd);
		gSetReuseAddress(__cm_nListenSocketFd);
		__BindSocketAddress();
		__ListenSocket();
	}

	int
	CAcceptor::AcceptConnect(void) const
	{
		int nRet = ::accept(__cm_nListenSocketFd,nullptr,nullptr);
		if (nRet == -1)
		{
			std::perror("accept failed");
			std::exit(-1);
		}
		return nRet;
	}

	void 
	CAcceptor::__BindSocketAddress(void) const
	{
		if(-1 == ::bind(__cm_nListenSocketFd, __cm_cAddress.GetSockaddr(), static_cast<socklen_t>(sizeof(sockaddr))))
		{
			std::perror("bind failed");
			std::exit(-1);
		}
	}

	void
	CAcceptor::__ListenSocket(void) const
	{
		if(-1 == ::listen(__cm_nListenSocketFd, 10))
		{
			std::perror("listen failed");
			std::exit(-1);
		}
	}

	inline int
	CAcceptor::GetSocketFd(void) const
	{
		return __cm_nListenSocketFd;
	}
}
#endif /* end of include guard: MY_ACCEPTOR_H */
