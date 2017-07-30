/*************************************************************************
    > File Name: Thread.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 21时47分40秒
 ************************************************************************/
#ifndef MY_THREAD_H
#define MY_THREAD_H

#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	class CThread
	{
		public:
			CThread(std::function<void()> cRun);
			~CThread(void);

			void Start(void); //创建一个线程
			void Join(void) const;//回收一个线程
			pthread_t GetThreadID(void) const;//返回线程ID
		private:
			static void* ThreadFunciton(IN void* arg);//线程函数
		private:
			bool __cm_bIsRuning; //标志位，标记一个线程是否在运行
			pthread_t __cm_ulnThreadID; //线程ID
			std::function<void()> __cm_cRun; //真的线程函数对象，创建线程时需要指定对象
	};

}
namespace MyNamespace
{
	//IThread的构造函数
	inline
	CThread::CThread(std::function<void()> cRun)
		:__cm_bIsRuning(false)
		 ,__cm_ulnThreadID(0)
		 ,__cm_cRun(cRun)
	{

	}

	//IThread的析构函数，如果线程在运行，就托管给系统
	CThread::~CThread(void)
	{
		if (__cm_bIsRuning) 
		{
			::pthread_detach(__cm_ulnThreadID); //将线程托管给系统
			__cm_bIsRuning = false;
		}
	}
	
	//创建一个线程，失败返回-1
	void
	CThread::Start(void)
	{
		if (0 != ::pthread_create(&__cm_ulnThreadID, nullptr, ThreadFunciton, static_cast<void*>(this)))
		{
			::perror("Created Thread faild");
			exit(-1);
		}
	}

	//等待回收一个线程，失败返回-1
	void
	CThread::Join(void) const
	{
		if (0 != ::pthread_join(__cm_ulnThreadID, nullptr))
		{
			perror("Join Thread failed");
			exit(-2);
		}
	}

	//获取一个线程的ID
	inline pthread_t
	CThread::GetThreadID(void) const
	{
		return __cm_ulnThreadID;
	}

	//线程函数，但不是真正的线程任务
	inline /* static */ void*
	CThread::ThreadFunciton(IN void* arg)
	{
		static_cast<CThread*>(arg)->__cm_cRun(); //表现多态
		return nullptr;
	}
}

#endif /* end of include guard: MY_THREAD_H */
