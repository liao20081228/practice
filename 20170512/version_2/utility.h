/*************************************************************************
    > File Name: utility.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月18日 星期日 14时25分51秒
 ************************************************************************/
#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include"inetAddress.h"
namespace MyNamespace
{
	using ::socklen_t;
	int
	gGetLocalAddress(IN int nSocketFd,IN CSocketAddress& cSocketAddress)
	{
		std::memset(&cSocketAddress, 0, sizeof(cSocketAddress));
		sockaddr_in sLocalAddress;
		::bzero(&sLocalAddress, sizeof(sLocalAddress));
		socklen_t nLen = sizeof(sockaddr_in);
		if (::getsockname(nSocketFd, reinterpret_cast<sockaddr*>(&sLocalAddress), &nLen) == -1)
		{
			::perror("getsockname failed");
			return -1;
		}
		cSocketAddress.SetFamily(sLocalAddress.sin_family);
		cSocketAddress.SetPort(::ntohs(sLocalAddress.sin_port));
		cSocketAddress.SetIP(::inet_ntoa(sLocalAddress.sin_addr));
		return 0;
	}

	int
	gGetPeerAddress(IN int nSocketFd,IN CSocketAddress& cSocketAddress)
	{
		std::memset(&cSocketAddress, 0, sizeof(cSocketAddress));
		sockaddr_in sLocalAddress;
		::bzero(&sLocalAddress, sizeof(sLocalAddress));
		socklen_t nLen = sizeof(sockaddr_in);
		if (::getpeername(nSocketFd, reinterpret_cast<sockaddr*>(&sLocalAddress), &nLen) == -1)
		{
			::perror("getsockname failed");
			return -1;
		}
		cSocketAddress.SetFamily(sLocalAddress.sin_family);
		cSocketAddress.SetPort(::ntohs(sLocalAddress.sin_port));
		cSocketAddress.SetIP(::inet_ntoa(sLocalAddress.sin_addr));
		return 0;
	}

	
	int
	SetNonBlock(IN int nSocketFd)
	{
		int nflags;
		if((nflags = ::fcntl(nSocketFd, F_GETFL)) == -1)
		{
			::perror("fcntl get file open mode failed");
			return -1;
		}
		if(-1 == ::fcntl(nSocketFd, F_SETFL, nflags | O_NONBLOCK))
		{
			::perror("fcntl set file open mode failed");
			return -1;
		}
		return 0;
	}

	int 
	SetReuseAddress(IN int nSocketFd, IN int nflags = 1)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			perror("setsockopt reuseaddr failed");
			return -1;
		}
		return 0;
	}
	
	int  
	SetReusePort(IN int nSocketFd, IN int nflags = 1)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEPORT, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			perror("setsockopt reuseport failed");
			return -1;
		}
		return 0;
	}
}
#endif /* end of include guard: MY_UTILITY_H */
