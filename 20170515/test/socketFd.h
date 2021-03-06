/*************************************************************************
    > File Name: socket.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月16日 星期五 15时29分35秒
 ************************************************************************/
#ifndef MY_SOCKET_H
#define MY_SOCKET_H
#include<myhead_cpp.h>
namespace MyNamespace
{
	class CSocketFd
	{
		public:
			CSocketFd(void); /* 创建一个socketfd*/
			CSocketFd(IN int nSocketFd);/* 将传入的socketfd封装为对象*/
			~CSocketFd(void);/* 关闭fd*/
			
			int GetSocketFd(void) const;/* 获取fd*/
			void ShutDown(IN int nHow = SHUT_WR) const; /* 以某种方式关闭fd*/
			
		private:
			int __cm_nSocketFd;
	};
	

}
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
#endif /* end of include guard: MY_SOCKET_H */
