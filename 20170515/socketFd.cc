#include"socketFd.h"
namespace MyNamespace
{
	CSocketFd::CSocketFd(void)
		:__cm_nSocketFd(::socket(AF_INET, SOCK_STREAM, 0))
	{
		if(__cm_nSocketFd == -1)
		{
			std::perror("SocketFd Created failed");
			std::exit(-1);
		}
	}

	inline
	CSocketFd::CSocketFd(IN int nSocketFd)
	:__cm_nSocketFd(nSocketFd)
	{
		if (__cm_nSocketFd == -1)
		{
			exit(-1);
		}
	}

	CSocketFd::~CSocketFd(void)
	{
		if(::close(__cm_nSocketFd) == -1)
		{
			::perror("close SocketFd failed");
		}
	}

	inline int
	CSocketFd::GetSocketFd(void) const
	{
		return __cm_nSocketFd;
	}

	
	void
	CSocketFd::ShutDown(IN int nHow /* =SHUT_WR */) const
	{
		if(-1 == ::shutdown(__cm_nSocketFd,nHow))
		{
			::perror("shutdown SocketFd failed");
			::exit(-1);
		}
	}

}
