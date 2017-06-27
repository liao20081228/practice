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
			/*void DoPendingFunctor(void);*/
		public:
			//用于设置三个私有成员
			void SetConnectCallBack(IN std::function<void(const CTcpConnection&)> cOnConnectCallback);
			void SetMessageCallBack(IN std::function<void(const CTcpConnection&)> cOnMessageCallBack);
			void SetCloseCallBack(IN  std::function<void(const CTcpConnection&)> cOnCloseCallBack);
		private:
			//传递给Tcpconnection类,那个类中也有三个相应的方法来设置三个私有成员，以达到定制化的操作
			std::function<void(const CTcpConnection&)> __cm_cOnConnectCallback;/* 连接建时的处理*/
			std::function<void(const CTcpConnection&)> __cm_cOnMessageCallBack;/* 收到消息时的处理*/
			std::function<void(const CTcpConnection&)> __cm_cOnCloseCallBack;/* 连接关闭时的处理*/
		private:
			void WaitEpoll(void);
			void HandleConnection(void);
			void HandleMessage(IN int nNewSocketFd);
			void ControlEpoll( IN int nOperation, IN int nFd, IN unsigned int events);
		private:
			CAcceptor& __cm_rcAcceptor;
			int __cm_nEpollFd; /*  epoll fd */
			int __cm_nListenFd; /*原始sfd*/
			bool __cm_bIsLooping; /* 循环标志位*/
			map<int,const CTcpConnection&> __cm_maConnectMap;
			vector<epoll_event> __cm_veEventList;
	};


	CEpoll::CEpoll(CAcceptor& crAcceptor)
		: __cm_rcAcceptor(crAcceptor)
		, __cm_nEpollFd(::epoll_create1(0))
		, __cm_nListenFd(__cm_rcAcceptor.GetSocketFd())
		, __cm_bIsLooping(false)
		, __cm_veEventList(1024)
	{
		if (__cm_nEpollFd == -1)
		{
			cout << "epoll_create1 failed" << endl;
			std::exit(-1);
		}
		ControlEpoll(EPOLL_CTL_ADD, __cm_nListenFd, EPOLLIN);
	}
	
	inline
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

	inline void
	CEpoll::SetConnectCallBack(std::function<void(const CTcpConnection&)> cOnConnectCallback)
	{
		__cm_cOnConnectCallback = cOnConnectCallback;
	}
	
	inline void
	CEpoll::SetMessageCallBack(std::function<void(const CTcpConnection&)> cOnMessageCallBack)
	{
		__cm_cOnMessageCallBack = cOnMessageCallBack;
	}
	
	inline void
	CEpoll::SetCloseCallBack(std::function<void(const CTcpConnection&)> cOnCloseCallBack)
	{
		__cm_cOnCloseCallBack = cOnCloseCallBack;
	}

	void
	CEpoll::ControlEpoll( IN int nOperation, IN int nFd, IN unsigned int events)
	{
		epoll_event event;
		::bzero(&event, sizeof(event));
		event.events = events;
		event.data.fd = nFd;
		if (::epoll_ctl(__cm_nEpollFd, nOperation, nFd, &event) == -1)
		{
			std::perror("epoll_ctl");
			std::exit(-1);
		}
	}
	
	void
	CEpoll::WaitEpoll(void)
	{
		int nReady = 0;
		do
		{
			nReady = ::epoll_wait(__cm_nEpollFd, &(*__cm_veEventList.begin()), __cm_veEventList.size(), 5000);
			
		}while (nReady == -1 && errno == EINTR);

		if (nReady == -1)
		{
			std::perror("epoll_wait failed");
			std::exit(-1);
		}
		else if (nReady == 0)
		{
			cout << "eppol_wait time out" << endl;
		}
		else 
		{
			if (nReady == static_cast<int>(__cm_veEventList.size()))
			{
				__cm_veEventList.resize(__cm_veEventList.size()*2);
			}
			for (int i = 0; i < nReady; ++i) 
			{
				if (__cm_veEventList[i].data.fd == __cm_nListenFd)
				{
					HandleConnection();
				}
				else if (__cm_veEventList[i].events & EPOLLIN) 
				{
					HandleMessage(__cm_veEventList[i].data.fd);
				}
			}
			
		}
	}
	
	void
	CEpoll::HandleConnection(void)
	{
		int nNewSocketFd = __cm_rcAcceptor.AcceptConnect();
		if (nNewSocketFd < 0)
		{
			cout << "建立连接出错" << endl;
			std::exit(-1);
		}
		ControlEpoll(EPOLL_CTL_ADD, nNewSocketFd, EPOLLIN);
		CTcpConnection* pcConnet = new CTcpConnection(nNewSocketFd);
		pcConnet->SetConnectCallBack(__cm_cOnConnectCallback);
		pcConnet->SetMessageCallBack(__cm_cOnMessageCallBack);
		pcConnet->SetCloseCallBack(__cm_cOnCloseCallBack);
		//assert(__cm_maConnectMap.insert(std::pair<int, const CTcpConnection&>(nNewSocketFd, *pcConnet)).second == true);
		assert(__cm_maConnectMap.emplace(nNewSocketFd, *pcConnet).second == true);
		pcConnet->HandleConnectCallBack();
	}

	void
	CEpoll::HandleMessage(IN int nNewSocketFd)
	{
		bool bIsClosed = gIsConnectionClosed(nNewSocketFd);
		map<int, const CTcpConnection&>::iterator it = __cm_maConnectMap.find(nNewSocketFd);
		assert(it != __cm_maConnectMap.end());
		if (bIsClosed)
		{
			(it->second).HandleCloseCallBack();
			ControlEpoll(EPOLL_CTL_DEL, nNewSocketFd, EPOLLIN);
			__cm_maConnectMap.erase(it);
		}
		else
		{
			(it->second).HandleMessageCallBack();
		}
	}

} /* MyNamespace */ 
#endif /* end of include guard: MY_EPPLL_H */
