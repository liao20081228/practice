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
	class CTimer
	{
		typedef std::function<void()> TTimeCallBack;
		public:
			CTimer(IN int nInitTime, IN int nIntervalTime, TTimeCallBack tTimeCallBack);
			~CTimer(void);
			void Start(void);
			void Stop(void);

		private:
			int CreateTimerFd(void);
			void SetTimerFd(IN int nInitTime, IN int nIntervalTime);
			void HandRead(void);

		private:
			int __cm_nTimerFd,
				__cm_nInitTime,
				__cm_nIntervalTime;
			std::function<void()> __cm_cTimerCallBack;
			bool __cm_nIsStarted;

	};
	
	inline
	CTimer::CTimer(IN int nInitTime, IN int nIntervalTime, IN TTimeCallBack tTimeCallBack)
		: __cm_nTimerFd(CreateTimerFd())
		, __cm_nInitTime(nInitTime)
		, __cm_nIntervalTime(nIntervalTime)
		, __cm_cTimerCallBack(tTimeCallBack)
		,__cm_nIsStarted(false)
	{
	}

	CTimer::~CTimer(void)
	{
		if (__cm_nIsStarted)
		{
			Stop();
		}
		::close(__cm_nTimerFd);
	}

	int
	CTimer::CreateTimerFd(void)
	{
		int nRet = ::timerfd_create(CLOCK_REALTIME, 0);
		if (nRet == -1)
		{
			std::perror("timerfd_create() failed or occur error");
			std::exit(-1);
		}
		return nRet;
	}

	void
	CTimer::Start(void)
	{
		__cm_nIsStarted = true;
		SetTimerFd(__cm_nInitTime, __cm_nIntervalTime);

		struct pollfd sPfd;
		sPfd.fd = __cm_nTimerFd;
		sPfd.events = POLLIN;

		while (__cm_nIsStarted)
		{
			int nReady = ::poll(&sPfd, 1 , 5000);
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
				if (sPfd.fd == __cm_nTimerFd && (sPfd.revents & POLLIN))
				{
					//先对定时器的读事件做处理
					HandRead();
					//再去做任务
					if (__cm_cTimerCallBack)
					{
						__cm_cTimerCallBack();
					}
				}
			}
		}
	}
	void 
	CTimer::SetTimerFd(IN int nInitTime, IN int nIntervalTime)
	{
		struct itimerspec value;
		value.it_value.tv_sec = nInitTime;
		value.it_value.tv_nsec = 0;
		value.it_interval.tv_sec = nIntervalTime;
		value.it_interval.tv_nsec = 0;
		if (::timerfd_settime(__cm_nTimerFd, 0, &value, NULL) == -1)
		{
			std::perror("timerfd_settime() failed or occur error");
		}
	}
	void 
	CTimer::HandRead(void)
	{
		uint64_t ulnHowMany;
		if (::read(__cm_nTimerFd, &ulnHowMany, sizeof(ulnHowMany)) != sizeof(ulnHowMany))
		{
			std::perror("read() failed or occur error");
			std::exit(-1);
		}
	}

	void
	CTimer::Stop(void)
	{
		if (__cm_nIsStarted)
		{
			SetTimerFd(0,0);
			__cm_nIsStarted = false;
			cout << "timerfd stop" << endl;
		}
		cout << "timerfd stop" << endl;
	}
}
#endif /* end of include guard: MY_TIMER_FD_H */
