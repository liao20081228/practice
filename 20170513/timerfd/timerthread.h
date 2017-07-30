/*************************************************************************
    > File Name: timerthread.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 13时02分35秒
 ************************************************************************/
#ifndef MY_TIMER_THREAD_H
#define MY_TIMER_THREAD_H
#include"timerfd.h"
#include"thread.h"
namespace MyNamespace
{
	class CTimerThread
	{
		typedef std::function<void()> TTimerCallBack;
		public:
			CTimerThread(IN int nInitTime, IN int nIntervalTime, IN TTimerCallBack tTimerCallBack);

			void Start(void);
			void Stop(void);
		private:
			CTimer __cm_cTimer;
			CThread __cm_cThread;
	};

	inline
	CTimerThread::CTimerThread(IN int nInitTime, IN int nIntervalTime, IN TTimerCallBack tTimerCallBack)
		: __cm_cTimer(nInitTime, nIntervalTime, tTimerCallBack)
		, __cm_cThread(std::bind(&CTimer::Start, __cm_cTimer))
	{

	}

	inline void
	CTimerThread::Start(void)
	{
		__cm_cThread.Start();
	}

	inline void
	CTimerThread::Stop(void)
	{
		__cm_cTimer.Stop();
		__cm_cThread.Join();
	}
}

#endif /* end of include guard: MY_TIMER_THREAD_H */
