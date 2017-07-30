/*************************************************************************
    > File Name: Utility.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月30日 星期五 19时07分43秒
 ************************************************************************/
#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include"InetAddress.h"
namespace NetworkLibrary
{
	int 
	gCreatedSocketFd(void)
	{
		int nRet = ::socket(AF_INET, SOCK_STREAM, 0);
		if (nRet == -1)
		{
			std::perror("socket() failed");
			std::exit(-1);
		}
		return nRet;
	}

	void
	gSetNonblock(IN int nSocketFd)
	{
		int nFlag = 0;
		nFlag = ::fcntl(nSocketFd, F_GETFL);
		if (nFlag == -1)
		{
			std::perror("fcntl() failed or occur error");
			std::exit(-1);
		}
		if (::fcntl(nSocketFd, F_SETFL, nFlag | O_NONBLOCK) == -1)
		{
			std::perror("fcntl() failed or occur error");
			std::exit(-1);
		}
	}

	CSocketAddress
	gGetLocalSockaddress(IN int nSocketFd)
	{
		sockaddr sSocketaddr;
		std::memset(&sSocketaddr, 0, sizeof(sSocketaddr));
		socklen_t nLen = sizeof(sockaddr);
		if (::getsockname(nSocketFd, &sSocketaddr, &nLen) == -1)
		{
			std::perror("getsockname() failed or occur error");
			std::exit(-1);
		}
		return CSocketAddress(sSocketaddr);
	}
	
	CSocketAddress
	gGetPeerSockaddress(IN int nSocketFd)
	{
		sockaddr sSocketaddr;
		std::memset(&sSocketaddr, 0, sizeof(sSocketaddr));
		socklen_t nLen = sizeof(sockaddr);
		if (::getpeername(nSocketFd, &sSocketaddr, &nLen) == -1)
		{
			std::perror("getpeername() failed or occur error");
			std::exit(-1);
		}
		return CSocketAddress(sSocketaddr);
	}

	void
	gSetReuseAddress(IN int  nSocketFd, int nFlag = 1)
	{
		int nSymbol = nFlag ? 1 : 0;
		if (-1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEADDR, &nSymbol, sizeof(nSymbol)))
		{
			std::perror("setsockopt() failed or occur error");
			std::exit(-1);
		}
	}

	void
	gSetReusePort(IN int  nSocketFd, int nFlag = 1)
	{
		int nSymbol = nFlag ? 1 : 0;
		if (-1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEPORT, &nSymbol, sizeof(nSymbol)))
		{
			std::perror("setsockopt() failed or occur error");
			std::exit(-1);
		}
	}

}
#endif /* end of include guard: MY_UTILITY_H */
