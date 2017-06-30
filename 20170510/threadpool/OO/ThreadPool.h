/*************************************************************************
    > File Name: pthread.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 16时41分17秒
 ************************************************************************/
#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H
#include"TaskPool.h"
#include"Thread.h"
namespace MyNamespace
{
	
	/*线程池*/
	class CThreadPoolThread;
	class CThreadPool : public CForbidCopyAndAssign
	{
		public:
			CThreadPool(IN size_t ulnTaskPoolSize, IN size_t __cm_ulnThreadPoolSize = 10);
			~CThreadPool(void);

			void Start(void); /* 启动线程池*/
			void Stop(void);  /* 停止线程池*/
			
			void AddTask(IN const ITask* pcITask); /* 向任务池中添加任务*/
		public:
			friend class CThreadPoolThread;
		private:
			const ITask* GetTask(void);  /* 从任务池中取得任务*/
		
			void ThreadFunction(void); 
		private:
			size_t __cm_ulnTaskPoolSize; //任务池大小
			size_t __cm_ulnThreadPoolSize; //线程池大小
			CTaskPool __cm_cTaskPool; //任务池
			bool __cm_bIsExit; //线程池可销毁标志位,用于析构函数判断是否可以直接销毁线程池对象
			vector<shared_ptr<IThread>> __cm_veThreadPool;//线程池,容器元素是智能指针
	};
	
	//线程池的实际线程
	class CThreadPoolThread : public IThread
	{
		public:
			CThreadPoolThread(CThreadPool& cThreadPool);
			~CThreadPoolThread(void);
			virtual void Run(void);
		private:
			CThreadPool& __cm_cThreadPool;
	};


}

namespace MyNamespace
{
	inline
	CThreadPool::CThreadPool(IN size_t ulnTaskPoolSize, IN size_t __cm_ulnThreadPoolSize /*=10 */)
		:__cm_ulnTaskPoolSize(ulnTaskPoolSize)
		,__cm_ulnThreadPoolSize(__cm_ulnThreadPoolSize)
		,__cm_cTaskPool(__cm_ulnTaskPoolSize)
		,__cm_bIsExit(false) //线程池是否销毁标志位
	{
	}


	void
	CThreadPool::Start(void)
	{
		for (size_t i = 0; i < __cm_ulnThreadPoolSize; ++i) 
		{
			shared_ptr<IThread> spIThread(new CThreadPoolThread(*this)); //创建线程对象
			__cm_veThreadPool.push_back(spIThread); //放入线程池
			spIThread->Start(); /* 真正创建一个线程*/
		}
	}

	inline
	CThreadPool::~CThreadPool(void)
	{
		while (!__cm_bIsExit) //如果可销毁标志位不为真，则调用stop方法
		{
			Stop();
		}
	}


	void 
	CThreadPool::Stop(void)
	{
		if (!__cm_bIsExit) //如果不能直接退出，任务池还有任务
		{
			while (!__cm_cTaskPool.IsEmpty()) //等待任务池的任务执行完
			{
				::sleep(1);
			}

			__cm_bIsExit = true; /*任务池已经清空， 将可退出标志位设为真*/
			__cm_cTaskPool.WakeUp();//如果没有这一个方法，每个子线程都阻塞在getTask方法上，从而导致主线程阻塞下面的在join()方法之上
			
			for (shared_ptr<IThread>& elem : __cm_veThreadPool) /* 回收所有线程*/
			{
				elem->Join();
			}
		}
	}
	
	inline void
	CThreadPool::AddTask(IN const ITask* pcITask)
	{
		__cm_cTaskPool.Push(pcITask);
	}

	inline const ITask*
	CThreadPool::GetTask(void)
	{
		return __cm_cTaskPool.Pop();
	}
	
//如果缓冲区中没有任务时，所有的子线程都会阻塞在getTask方法之上,
//无法回到while开头,即使将_isExit设置为true之后，每个线程也不会正常退出
	inline void
	CThreadPool::ThreadFunction(void)
	{
		while (!__cm_bIsExit) //当线程池不可销毁时，每个线程都从线程池中取任务
		{
			const ITask* cpcItask = GetTask(); 
			if (cpcItask) //对于取出的任务，并不一定都是可用的
			{
				cpcItask->Execute();
			}
		}
	}

}

namespace MyNamespace
{
	inline
	CThreadPoolThread::CThreadPoolThread(CThreadPool& cThreadPool)
		:__cm_cThreadPool(cThreadPool)
	{
	}

	inline
	CThreadPoolThread::~CThreadPoolThread(void)
	{

	}

	inline /*virtual*/ void
	CThreadPoolThread::Run(void)
	{
		__cm_cThreadPool.ThreadFunction();
	}
}
#endif /* end of include guard: MY_THREAD_POOL_H */
