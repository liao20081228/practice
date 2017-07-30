#include"acceptor.h"
namespace MyNamespace
{
	inline
	CAcceptor::CAcceptor(IN int nListenSocketFd, IN const CSocketAddress& cAddress)
		: __cm_cListenSocketFd(nListenSocketFd)
		, __cm_cAddress(cAddress)
	{
		if (__cm_cListenSocketFd.GetSocketFd() == -1)
		{
			cout << "传入的原始套接字错误" << endl;
			std::exit(-1);
		}
	}

	void
	CAcceptor::Ready(void) const
	{
		gSetReusePort(__cm_cListenSocketFd.GetSocketFd());
		gSetReuseAddress(__cm_cListenSocketFd.GetSocketFd());
		__BindSocketAddress();
		__ListenSocket();
	}

	int
	CAcceptor::AcceptConnect(void) const
	{
		int nRet = ::accept(__cm_cListenSocketFd.GetSocketFd(), nullptr, nullptr);
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
		if(-1 == ::bind(__cm_cListenSocketFd.GetSocketFd(), __cm_cAddress.GetSockaddr(), static_cast<socklen_t>(sizeof(sockaddr))))
		{
			std::perror("bind failed");
			std::exit(-1);
		}
	}

	void
	CAcceptor::__ListenSocket(void) const
	{
		if(-1 == ::listen(__cm_cListenSocketFd.GetSocketFd(), 10))
		{
			std::perror("listen failed");
			std::exit(-1);
		}
	}

	inline int
	CAcceptor::GetSocketFd(void) const
	{
		return __cm_cListenSocketFd.GetSocketFd();
	}
}
