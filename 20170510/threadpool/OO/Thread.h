/*************************************************************************
    > File Name: Thread.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月28日 星期三 21时26分54秒
 ************************************************************************/
#ifndef MY_THREAD_H
#define MY_THREAD_H
#include"ForbidCopyAndAssign.h"
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	//线程抽象类，由其派生类来决定每个线程具体任务
	class IThread : public CForbidCopyAndAssign
	{
		public:
			IThread(void);
			virtual ~IThread(void);

			void Start(void); //创建一个线程
			void Join(void) const;//回收一个线程
			pthread_t GetThreadID(void) const;//返回线程ID
		protected:
			virtual void Run(void) = 0;//该线程要处理的任务
		private:
			static void* ThreadFunciton(IN void* arg);//线程函数
		private:
			bool __cm_bIsRuning; //标志位，标记一个线程是否在运行
			pthread_t __cm_ulnThreadID; //线程ID
	};
}

namespace MyNamespace
{
	//IThread的构造函数
	inline
	IThread::IThread(void)
		:__cm_bIsRuning(false)
		 ,__cm_ulnThreadID(0)
	{

	}

	//IThread的析构函数，如果线程在运行，就托管给系统
	IThread::~IThread(void)
	{
		if (__cm_bIsRuning) 
		{
			::pthread_detach(__cm_ulnThreadID); //将线程托管给系统
			__cm_bIsRuning = false;
		}
	}
	
	//创建一个线程，失败返回-1
	void
	IThread::Start(void)
	{
		if (0 != ::pthread_create(&__cm_ulnThreadID, nullptr, ThreadFunciton, static_cast<void*>(this)))
		{
			::perror("Created Thread faild");
			exit(-1);
		}
	}

	//等待回收一个线程，失败返回-1
	void
	IThread::Join(void) const
	{
		if (0 != ::pthread_join(__cm_ulnThreadID, nullptr))
		{
			perror("Join Thread failed");
			exit(-2);
		}
	}

	//获取一个线程的ID
	inline pthread_t
	IThread::GetThreadID(void) const
	{
		return __cm_ulnThreadID;
	}

	//线程函数，但不是真正的线程任务
	inline /* static */ void*
	IThread::ThreadFunciton(IN void* arg)
	{
		static_cast<IThread*>(arg)->Run(); //表现多态
		return nullptr;
	}
}

#endif /* end of include guard: MY_THREAD_H */
