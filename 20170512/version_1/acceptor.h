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
namespace MyNamespace
{
	class CAcceptor
	{
		public:
			CAcceptor(IN CSocketFd cListenSocketFd, IN CSocketAddress cAddress); /* 接受一个CSocketFd对象*/
			CAcceptor(IN int nListenSocketFd, IN CSocketAddress cAddress);/*  接收一个原始套接字*/
			
			CSocketFd AcceptConnect(void); /* 接收连接*/ 
		
		private:
			void __BindSocketAddress(void); /* 绑定*/
			void __ListenSocket(void); /*监听*/
		private:
			CSocketFd __cm_cListenSocketFd;
			CSocketAddress __cm_cAddress;
	};

	inline
	CAcceptor::CAcceptor(IN CSocketFd cListenSocketFd, IN CSocketAddress cAddress)
		: __cm_cListenSocketFd(cListenSocketFd)
		, __cm_cAddress(cAddress)

	{
		cout << __cm_cListenSocketFd.GetSocketFd() << endl;
		cout <<__cm_cAddress.GetIp()<<endl;
		cout << __cm_cAddress.GetPort() << endl;
		
	}

	inline
	CAcceptor::CAcceptor(IN int nListenSocketFd, IN CSocketAddress cAddress)
		: __cm_cListenSocketFd(nListenSocketFd)
		, __cm_cAddress(cAddress)
	{
	}

	inline CSocketFd
	CAcceptor::AcceptConnect(void)
	{
		/*__cm_cListenSocketFd.SetReuseAddress();*/
		/*__cm_cListenSocketFd.SetReusePort();*/
		__BindSocketAddress();
		__ListenSocket();
		int nRet = ::accept(__cm_cListenSocketFd.GetSocketFd(),nullptr,nullptr);
		if (nRet == -1)
		{
			::perror("accept failed");
			__cm_cListenSocketFd.~CSocketFd();
			::exit(-1);
		}
		return CSocketFd(nRet);
	}

	void 
	CAcceptor::__BindSocketAddress(void)
	{
		cout << __cm_cListenSocketFd.GetSocketFd() << endl;
		
		if(-1 == ::bind(__cm_cListenSocketFd.GetSocketFd(), __cm_cAddress.GetSockaddr(), static_cast<socklen_t>(sizeof(sockaddr))))
		{
			::perror("bind failed");
			__cm_cListenSocketFd.~CSocketFd();
			::exit(-1);
		}
	}

	void
	CAcceptor::__ListenSocket(void)
	{
		if(-1 == ::listen(__cm_cListenSocketFd.GetSocketFd(), 10))
		{
			::perror("listen failed");
			__cm_cListenSocketFd.~CSocketFd();
			::exit(-1);
		}
	}
}
#endif /* end of include guard: MY_ACCEPTOR_H */
