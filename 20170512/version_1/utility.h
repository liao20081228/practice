/*************************************************************************
    > File Name: utility.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 14时25分51秒
 ************************************************************************/
#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include"inetAddress.h"
#include"socketFd.h"
#include"acceptor.h"
namespace MyNamespace
{
	using ::socklen_t;
	CSocketAddress gGetLocalAddress(IN int nSocketFd)
	{
		sockaddr sLocalAddress;
		socklen_t nLen = sizeof(sockaddr);
		std::memset(&sLocalAddress,0, sizeof(sockaddr));
		if (::getsockname(nSocketFd, &sLocalAddress, &nLen) == -1)
		{
			::perror("getsockname failed");
			::close(nSocketFd);
			::exit(-1);
		}
		return CSocketAddress(sLocalAddress);
	}

	CSocketAddress gGetLocalAddress(IN CSocketFd cSocketFd)
	{
		sockaddr sLocalAddress;
		socklen_t nLen = sizeof(sockaddr);
		std::memset(&sLocalAddress,0, sizeof(sockaddr));
		if (::getsockname(cSocketFd.GetSocketFd(), &sLocalAddress, &nLen) == -1)
		{
			::perror("getsockname failed");
			cSocketFd.~CSocketFd();
			::exit(-1);
		}
		return CSocketAddress(sLocalAddress);
	}
	
	CSocketAddress gGetPeerAddress(IN int nSocketFd)
	{
		sockaddr sPeerAddress;
		socklen_t nLen = sizeof(sockaddr);
		std::memset(&sPeerAddress,0, sizeof(sockaddr));
		if (::getpeername(nSocketFd, &sPeerAddress, &nLen) == -1)
		{
			::perror("getpeername failed");
			::close(nSocketFd);
			::exit(-1);
		}
		return CSocketAddress(sPeerAddress);
	}

	CSocketAddress gGetPeerAddress(IN CSocketFd cSocketFd)
	{
		sockaddr sPeerAddress;
		socklen_t nLen = sizeof(sockaddr);
		std::memset(&sPeerAddress,0, sizeof(sockaddr));
		if (::getpeername(cSocketFd.GetSocketFd(), &sPeerAddress, &nLen) == -1)
		{
			::perror("getpeername failed");
			cSocketFd.~CSocketFd();
			::exit(-1);
		}
		return CSocketAddress(sPeerAddress);
	}


}
#endif /* end of include guard: MY_UTILITY_H */
