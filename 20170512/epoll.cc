/*************************************************************************
    > File Name: epoll.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月25日 星期日 16时58分41秒
 ************************************************************************/
#ifndef MY_EPPLL_H
#define MY_EPPLL_H
#include"tcpConnection.h"
namespace MyNamespace
{
	using ::epoll_event;
	class CEpoll
	{
		public:
			CEpoll(IN CAcceptor& rcAcceptor);
			~CEpoll(void);
			
			void Loop(void); /* epoll循环监听*/
			void UnLoop(void); /* 停止epoll循环*/
			void DoPendingFunctor(void);
		public:
			void SetConnectCallBack(IN std::function<void(const CTcpConnection&)> cOnConnectCallback);
			void SetMessageCallBack(IN std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(IN  std::function<void(const CTcpConnection&)> cOnCloseCallBack);
		private:
			std::function<void(const CTcpConnection&)> __cm_cOnConnectCallback;
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;
			std::function<void(const CTcpConnection&)> __cm_cOnCloseCallBack;
			
		private:
			void WaitEpoll(void);
			void HandleConnect(void);
			void HandleMessage(int nSocketFd);
			int ControlEpoll( IN int nOperation, IN int nFd, IN unsigned int events);
		private:
			CAcceptor& __cm_rcAcceptor;
			int __cm_nEpollFd; /*  epoll fd */
			int __cm_nListenFd; /*原始sfd*/
			bool __cm_bIsLooping; /* 循环标志位*/
			map<int,CTcpConnection> __cm_maConnectMap;
			vector<epoll_event> __cm_veEventList;
	};


	CEpoll::CEpoll(CAcceptor& crAcceptor)
		: __cm_rcAcceptor(crAcceptor)
		, __cm_nEpollFd(::epoll_create1(0))
		, __cm_nListenFd(__cm_rcAcceptor.GetSocketFd())
		, __cm_bIsLooping(false)
	{
		if (__cm_nEpollFd == -1)
		{
			::perror("epoll_create1 failed");
			::exit(-1);
		}
		ControlEpoll(EPOLL_CTL_ADD, __cm_nListenFd, EPOLLIN);
	}

	CEpoll::~CEpoll(void)
	{
		::close(__cm_nEpollFd);
	}


	void
	CEpoll::Loop(void)
	{
		__cm_bIsLooping = true;
		while (__cm_bIsLooping)
		{
			WaitEpoll();
		}
	}

	void
	CEpoll::UnLoop(void)
	{
		if (__cm_bIsLooping)
		{
			__cm_bIsLooping = false;
		}
	}

	void
	CEpoll::SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnectCallback)
	{
		__cm_cOnConnectCallback = cOnConnectCallback;
	}
	
	void
	CEpoll::SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack)
	{
		__cm_cOnMessageCallBack = cOnMessageCallBack;
	}
	
	void
	CEpoll::SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack)
	{
		__cm_cOnCloseCallBack = cOnCloseCallBack;
	}

	int
	CEpoll::ControlEpoll( IN int nOperation, IN int nFd, IN unsigned int events)
	{
		epoll_event event;
		::bzero(&event, sizeof(event));
		event.events = events;
		event.data.fd = nFd;
		if (::epoll_ctl(__cm_nEpollFd, nOperation, nFd, &event) == -1)
		{
			std::perror("epoll_ctl");
			return -1;
		}
		return 0;
	}
} /* MyNamespace */ 
#endif /* end of include guard: MY_EPPLL_H */
