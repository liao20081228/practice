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
			CAcceptor(IN const CSocketFd& cListenSocketFd, IN const CSocketAddress& cAddress); /* 接受一个CSocketFd对象*/
			CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress);/*  接收一个原始套接字*/
			
			int  AcceptConnect(void); /* 接收连接*/ 
			int  GetSocketFd(void) const;
		private:
			int __BindSocketAddress(void) const; /* 绑定*/
			int __ListenSocket(void) const; /*监听*/
		private:
			int __cm_nListenSocketFd;
			CSocketAddress __cm_cAddress;
	};

	inline
	CAcceptor::CAcceptor(IN const CSocketFd& cListenSocketFd, IN const CSocketAddress& cAddress)
		: __cm_nListenSocketFd(cListenSocketFd.GetSocketFd())
		, __cm_cAddress(cAddress)
	{
		
	}

	inline
	CAcceptor::CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress)
		: __cm_nListenSocketFd(nListenSocketFd)
		, __cm_cAddress(cAddress)
	{
	}

	int
	CAcceptor::AcceptConnect(void)
	{
		if (gSetReusePort(__cm_nListenSocketFd) == -1)
		{
			return -1;
		}
		if (gSetReuseAddress(__cm_nListenSocketFd) == -1)
		{
			return -1;
		}
		if (__BindSocketAddress() == -1)
		{
			return -1;
		}
		if (__ListenSocket() == -1)
		{
			return -1;
		}
		int nRet = ::accept(__cm_nListenSocketFd,nullptr,nullptr);
		if (nRet == -1)
		{
			::perror("accept failed");
			return -1;
		}
		return nRet;
	}

	int 
	CAcceptor::__BindSocketAddress(void) const
	{
		if(-1 == ::bind(__cm_nListenSocketFd, __cm_cAddress.GetSockaddr(), static_cast<socklen_t>(sizeof(sockaddr))))
		{
			::perror("bind failed");
			return -1;
		}
		return 0;
	}

	int
	CAcceptor::__ListenSocket(void) const
	{
		if(-1 == ::listen(__cm_nListenSocketFd, 10))
		{
			::perror("listen failed");
			return -1;
		}
		return 0;
	}

	inline int
	CAcceptor::GetSocketFd(void) const
	{
		return __cm_nListenSocketFd;
	}
}
#endif /* end of include guard: MY_ACCEPTOR_H */
