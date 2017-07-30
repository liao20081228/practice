/*************************************************************************
    > File Name: timerfd.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 09时47分38秒
 ************************************************************************/
#ifndef MY_TIMER_FD_H
#define MY_TIMER_FD_H
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	class CEvent
	{
		typedef std::function<void()> TEventCallBack;
		public:
			CEvent(IN TEventCallBack tEventCallBack);
			~CEvent(void);
			void Start(void);
			void Stop(void);
			void HandRead(void);
			void WakeUp(void);
		private:
			int CreateEventFd(void);

		private:
			int __cm_nEventFd;
			std::function<void()> __cm_cEventCallBack;
			bool __cm_nIsStarted;

	};
	
	inline
	CEvent::CEvent(IN TEventCallBack tEventCallBack)
		: __cm_nEventFd(CreateEventFd())
		, __cm_cEventCallBack(tEventCallBack)
		,__cm_nIsStarted(false)
	{
	}

	CEvent::~CEvent(void)
	{
		if (__cm_nIsStarted)
		{
			Stop();
		}
		::close(__cm_nEventFd);
	}

	int
	CEvent::CreateEventFd(void)
	{
		int nRet = ::eventfd(10, 0);
		if (nRet == -1)
		{
			std::perror("eventfd() failed or occur error");
			std::exit(-1);
		}
		return nRet;
	}

	void
	CEvent::Start(void)
	{
		__cm_nIsStarted = true;

		struct pollfd sEfd;
		sEfd.fd = __cm_nEventFd;
		sEfd.events = POLLIN;

		while (__cm_nIsStarted)
		{
			int nReady = ::poll(&sEfd, 1 , 5000);
			if (nReady == -1)
			{
				if (errno == EINTR)
				{
					continue;
				}
				std::perror("poll() failed or occur error");
				std::exit(-1);
			}
			else if (nReady == 0) 
			{
				cout << "> poll time out" << endl;
			}
			else 
			{
				if (sEfd.fd == __cm_nEventFd && (sEfd.revents & POLLIN))
				{
					//先对定时器的读事件做处理
					HandRead();
					//再去做任务
					if (__cm_cEventCallBack)
					{
						__cm_cEventCallBack();
					}
				}
			}
		}
	}
	
	void 
	CEvent::HandRead(void)
	{
		uint64_t ulnHowMany;
		if (::read(__cm_nEventFd, &ulnHowMany, sizeof(ulnHowMany)) != sizeof(ulnHowMany))
		{
			std::perror("read() failed or occur error");
			std::exit(-1);
		}
	}

	void
	CEvent::Stop(void)
	{
		if (__cm_nIsStarted)
		{
			__cm_nIsStarted = false;
			cout << "timerfd stop" << endl;
		}
	}

	void 
	CEvent::WakeUp(void)
	{
		uint64_t one = 10;
		int ret = write(__cm_nEventFd, &one, sizeof(one));
		if (ret != sizeof(uint64_t))
		{
			std::perror("write() failed or occur error");
			std::exit(-1);
		}
	}
}
#endif /* end of include guard: MY_TIMER_FD_H */
