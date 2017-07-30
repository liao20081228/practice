/*************************************************************************
    > File Name: timerthread.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 13时02分35秒
 ************************************************************************/
#ifndef MY_TIMER_THREAD_H
#define MY_TIMER_THREAD_H
#include"event.h"
#include"thread.h"
namespace MyNamespace
{
	class CEventThread
	{
		typedef std::function<void()> TEventCallBack;
		public:
			CEventThread(IN TEventCallBack tEventCallBack);

			void Start(void);
			void Stop(void);
			void WakeUp(void); /* wakeup 向eventfd中写入数据来激活fd，poll监听到后就读并且执行一个任务，*/
		private:
			CEvent __cm_cEvent;
			CThread __cm_cThread;
	};

	inline
	CEventThread::CEventThread(IN TEventCallBack tEventCallBack)
		: __cm_cEvent(tEventCallBack)
		, __cm_cThread(std::bind(&CEvent::Start, __cm_cEvent))
	{

	}

	inline void
	CEventThread::Start(void)
	{
		__cm_cThread.Start(); /* 开启子线程，将poll的循环放在子线程中*/
	}

	inline void
	CEventThread::Stop(void)
	{
		__cm_cEvent.Stop();
	}

	inline void
	CEventThread::WakeUp(void)
	{
		__cm_cEvent.WakeUp();
		__cm_cThread.Join();
	}

}

#endif /* end of include guard: MY_TIMER_THREAD_H */
