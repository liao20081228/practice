#include"utility.h"
namespace MyNamespace
{
	using ::socklen_t;
	CSocketAddress
	gGetLocalAddress(IN int nSocketFd)
	{
		sockaddr_in sLocalAddress;
		::bzero(&sLocalAddress, sizeof(sLocalAddress));
		socklen_t nLen = sizeof(sockaddr_in);
		if (::getsockname(nSocketFd, reinterpret_cast<sockaddr*>(&sLocalAddress), &nLen) == -1)
		{
			std::perror("getsockname failed");
			std::exit(-1);
		}
		return CSocketAddress(sLocalAddress);
	}

	CSocketAddress
	gGetPeerAddress(IN int nSocketFd)
	{
		sockaddr_in sLocalAddress;
		::bzero(&sLocalAddress, sizeof(sLocalAddress));
		socklen_t nLen = sizeof(sockaddr_in);
		if (::getpeername(nSocketFd, reinterpret_cast<sockaddr*>(&sLocalAddress), &nLen) == -1)
		{
			std::perror("getsockname failed");
			return -1;
		}
		return CSocketAddress(sLocalAddress);
	}

	
	void
	gSetNonBlock(IN int nSocketFd)
	{
		int nflags;
		if((nflags = ::fcntl(nSocketFd, F_GETFL)) == -1)
		{
			std::perror("fcntl get file open mode failed");
			std::exit(-1);
		}
		if(-1 == ::fcntl(nSocketFd, F_SETFL, nflags | O_NONBLOCK))
		{
			std::perror("fcntl set file open mode failed");
			std::exit(-1);
		}
	}

	void 
	gSetReuseAddress(IN int nSocketFd, IN int nflags /*= 1*/)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			std::perror("setsockopt reuseaddr failed");
			std::exit(-1);
		}
	}
	
	void 
	gSetReusePort(IN int nSocketFd, IN int nflags /*= 1*/)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(nSocketFd, SOL_SOCKET, SO_REUSEPORT, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			std::perror("setsockopt reuseport failed");
			std::exit(-1);
		}
	}

	bool
	gIsConnectionClosed(IN int nSocketFd)
	{
		char buf[1024];
		int Ret = 0;
		do
		{
			Ret = ::recv(nSocketFd, buf, sizeof(buf), MSG_PEEK);
		}while (Ret == -1 && errno == EINTR);
		if (Ret == -1)
		{
			std::perror("recv failed");
			return true;
		}
		return (0 == Ret);
	}

	int
	gCreateSocketFd(void)
	{
		int nRet = ::socket(AF_INET, SOCK_STREAM, 0);
		if (nRet == -1)
		{
			std::perror("socket");
			std::exit(-1);
		}
		return nRet;
	}
}
