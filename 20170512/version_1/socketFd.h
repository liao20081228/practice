/*************************************************************************
    > File Name: socket.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月16日 星期五 15时29分35秒
 ************************************************************************/
#ifndef MY_SOCKET_H
#define MY_SOCKET_H
#include<myhead>
namespace MyNamespace
{
	class CSocketFd
	{
		public:
			CSocketFd(void); /* 创建一个socketfd*/
			CSocketFd(IN int nSocketFd);/* 将传入的socketfd封装为对象*/
			~CSocketFd(void);/* 关闭fd*/
			
			int GetSocketFd(void) const;/* 获取fd*/
			
			void ShutDown(IN int nHow = SHUT_WR); /* 以某种方式关闭fd*/
			void SetNonBlock(void); /* 设置为非阻塞*/
			void SetReuseAddress(IN int nflags = 1);/* 设置为地址重用*/
			void SetReusePort(IN int nflags = 1);/* 设置端口重用*/
		private:
			int __cm_nSocketFd;
	};
	
	CSocketFd::CSocketFd(void)
		:__cm_nSocketFd(::socket(AF_INET, SOCK_STREAM, 0))
	{
		if(__cm_nSocketFd == -1)
		{
			perror("SocketFd Created failed");
			exit(-1);
		}
	}

	inline
	CSocketFd::CSocketFd(IN int nSocketFd)
	:__cm_nSocketFd(nSocketFd)
	{
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
	CSocketFd::ShutDown(IN int nHow /* =SHUT_WR */)
	{
		if(-1 == ::shutdown(__cm_nSocketFd,nHow))
		{
			::perror("shutdown SocketFd failed");
			this->~CSocketFd();
			exit(-1); /* 执行exit不会调用析构函数，因此必须手动关闭fd*/
		}
	}

	void
	CSocketFd::SetNonBlock(void)
	{
		int nflags;
		if((nflags = ::fcntl(__cm_nSocketFd, F_GETFL)) == -1)
		{
			::perror("fcntl get file open mode failed");
			this->~CSocketFd();
			exit(-1);
		}
		if(-1 == ::fcntl(__cm_nSocketFd, F_SETFL, nflags | O_NONBLOCK))
		{
			::perror("fcntl set file open mode failed");
			this->~CSocketFd();
			exit(-1);
		}
	}

	void 
	CSocketFd::SetReuseAddress(IN int nflags /*=1*/)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(__cm_nSocketFd, SOL_SOCKET, SO_REUSEADDR, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			perror("setsockopt reuseaddr failed");
			this->~CSocketFd();
			exit(-1);
		}
	}
	
	void 
	CSocketFd::SetReusePort(IN int nflags /*=1*/)
	{
		int flags = (nflags ? 1 : 0);
		if( -1 == ::setsockopt(__cm_nSocketFd, SOL_SOCKET, SO_REUSEPORT, static_cast<void*>(&flags), static_cast<socklen_t>(sizeof(int))))
		{
			perror("setsockopt reuseport failed");
			this->~CSocketFd();
			exit(-1);
		}
	}
}
#endif /* end of include guard: MY_SOCKET_H */
