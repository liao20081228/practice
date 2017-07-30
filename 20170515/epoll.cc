#include"epoll.h"
namespace MyNamespace
{
	CEpoll::CEpoll(CAcceptor& crAcceptor)
		: __cm_rcAcceptor(crAcceptor)
		, __cm_nEpollFd(::epoll_create1(0))
		, __cm_nEventFd(::eventfd(0,0))
		, __cm_nListenFd(__cm_rcAcceptor.GetSocketFd())
		, __cm_bIsLooping(false)
		, __cm_veEventList(1024)
	{
		if (__cm_nEpollFd == -1)
		{
			cout << "epoll_create1 failed" << endl;
			std::exit(-1);
		}
		if (__cm_nEventFd == -1)
		{
			cout << "eventfd()failed" << endl;
			std::exit(-1);
		}
		ControlEpoll(EPOLL_CTL_ADD, __cm_nListenFd, EPOLLIN);
		ControlEpoll(EPOLL_CTL_ADD, __cm_nEventFd, EPOLLIN);
	}
	
	inline
	CEpoll::~CEpoll(void)
	{
		::close(__cm_nEpollFd);
		::close(__cm_nEventFd);
	}

	void
	CEpoll::RunInLoop(IN const std::function<void()>& cFunctor)
	{
		//处理结果完成后，由TCPconnect的sendinloop 调用该函数，将真的发送数据的函数sendandclose绑定为函数对象 加入待发送数组，
		//同时由WAkeup函数通知epoll可以发结果了。
		{
			CMutexLockGuard cMutexGuard(__cm_cMutexLock);
			__cm_vePendingFunctors.push_back(cFunctor);
		}
		WakeUp();
	}
	
	void 
	CEpoll::DoPendingFunctor(void)
	{
		vector<std::function<void()>> veFunctorTemp;
		{
			CMutexLockGuard cMutexGuard(__cm_cMutexLock);
			veFunctorTemp.swap(__cm_vePendingFunctors);
		}
		for (std::function<void()> elem : veFunctorTemp)
		{
			elem();
		}
	}
	void 
	CEpoll::WakeUp(void) const
	{
		uint16_t ulnTemp = 1;
		if (::write(__cm_nEventFd, &ulnTemp, sizeof(ulnTemp)) != sizeof(uint64_t))
		{
			std::perror("write eventfd() failed or occur error");
			std::exit(-1);
		}
	}

	void
	CEpoll::HandleRead(void) const
	{
		uint64_t ulnTemp = 0;
		if (::read(__cm_nEventFd, &ulnTemp, sizeof(uint64_t)) != sizeof(uint64_t))
		{
			std::perror("read eventfd failed or occur error");
			std::exit(-1);
		}
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
				else if (__cm_veEventList[i].data.fd == __cm_nEventFd && __cm_veEventList[i].events & EPOLLIN) 
				{
					HandleRead();
					DoPendingFunctor();
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
		CTcpConnection* pcConnet = new CTcpConnection(nNewSocketFd, *this);
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

}
