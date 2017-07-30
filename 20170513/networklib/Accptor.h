/*************************************************************************
    > File Name: Accptor.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 17时49分54秒
 ************************************************************************/
#ifndef MY_ACCPTOR_H
#define MY_ACCPTOR_H
#include"SocketFd.h"
#include"InetAddress.h"
#include"Utility.h"
namespace NetworkLibrary
{
	class CAcceptor
	{
		public:
			CAcceptor(IN int nSocketFd, IN const CSocketAddress& ccSocketAddress);
			CAcceptor(IN const CSocketFd& ccSocketFd, IN const CSocketAddress& ccSocketAddress);
			
			void ReadyAcceptConnection(void) const;
			int AcceptConnection(void) const;
			int GetListenSocketFd(void) const;
		private:
			void __Bind(void) const;
			void __Listen(void) const;
		private:
			int __cm_nListenSocketFd;
			CSocketAddress __cm_cSocketAddress;
	};

	inline
	CAcceptor::CAcceptor(IN int nSocketFd, IN const CSocketAddress& ccSocketAddress)
		: __cm_nListenSocketFd(nSocketFd)
		, __cm_cSocketAddress(ccSocketAddress)
	{
		assert(__cm_nListenSocketFd >= 0);
	}

	inline
	CAcceptor::CAcceptor(IN const CSocketFd& ccSocketFd, IN const CSocketAddress& ccSocketAddress)
		: __cm_nListenSocketFd(ccSocketFd.GetSocketFd())
		, __cm_cSocketAddress(ccSocketAddress)
	{
	}

	inline void
	CAcceptor::ReadyAcceptConnection(void) const
	{
		gSetReuseAddress(__cm_nListenSocketFd);
		gSetReusePort(__cm_nListenSocketFd);
		__Bind(void);
		__Listen(void);
	}
	
	void
	CAcceptor::__Bind(void) const
	{
		if (-1 == ::bind(__cm_nListenSocketFd, __cm_cSocketAddress.Getsockaddr(), sizeof(sockaddr)))
		{
			std::perror("bind() failed or occur error");
			std::exit(-1);
		}
	}

	void
	CAcceptor::__Listen(void) const
	{
		if (-1 == ::listen(__cm_nListenSocketFd, 10))
		{
			std::perror("listen() failed or occur error");
			std::exit(-1);
		}
	}

	int 
	CAcceptor::AcceptConnection(void) const
	{
		int nNewSocketFd = ::accept(__cm_nListenSocketFd, nullptr, nullptr);
		if (nNewSocketFd == -1)
		{
			std::perror("accept() failed or occur error");
			std::exit(-1);
		}
		return nNewSocketFd;
	}
	
	int GetListenSocketFd(void)
	{
		return __cm_nListenSocketFd;
	}
}
#endif /* end of include guard: MY_ACCPTOR_H */

