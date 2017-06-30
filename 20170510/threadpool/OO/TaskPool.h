/*************************************************************************
    > File Name: taskpool.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月28日 星期三 21时02分48秒
 ************************************************************************/
#ifndef MY_TASK_POOL_H
#define MY_TASK_POOL_H
#include"ConditionVariable.h"
#include"Task.h"
namespace MyNamespace
{
	//任务池
	class CTaskPool : public CForbidCopyAndAssign
	{
		public:
			CTaskPool(IN size_t ulnSize);
			~CTaskPool(void);

			void Push(IN const ITask* nValue); /*加入一个任务 */
			const ITask* Pop(void); /* 提取一个任务*/
			bool IsFull(void) const; /* 任务池是否满了*/
			bool IsEmpty(void) const; /* 任务池是否空*/
			void WakeUp(void);
		private:
			CMutexLock __cm_cMutexLock;
			CConditionVariable __cm_cNotFull;
			CConditionVariable __cm_cNotEmpty;
			size_t __cm_ulnSize;
			queue<const ITask*> __cm_quQueue;
			bool __cm_bIsExit; /* 任务池销毁标志位*/
	};
}
namespace MyNamespace
{
	inline
	CTaskPool::CTaskPool(IN size_t ulnSize)
		:__cm_cMutexLock()
		,__cm_cNotFull(__cm_cMutexLock)
		,__cm_cNotEmpty(__cm_cMutexLock)
		,__cm_ulnSize(ulnSize)
		,__cm_bIsExit(false) //任务池销毁标志位，建立任务池时为false
	{
	}

	inline
	CTaskPool::~CTaskPool(void)
	{

	}

	inline bool
	CTaskPool::IsFull(void) const
	{
		return __cm_quQueue.size() == __cm_ulnSize;
	}

	inline bool
	CTaskPool::IsEmpty(void) const
	{
		return __cm_quQueue.empty();
	}
	
	/* 激活所有阻塞的线程,准备销毁任务池*/
	inline void 
	CTaskPool::WakeUp(void)
	{
		__cm_bIsExit = true;
		__cm_cNotEmpty.ActivateAll();
	}

	//向任务池中添加任务
	void 
	CTaskPool::Push(IN const ITask* nValue)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock); /* 加锁*/
		while (!__cm_bIsExit && IsFull()) /* 如果任务池没销毁且满了则阻塞*/
		{
			__cm_cNotFull.Wait();
			std::cout << "写阻塞" << std::endl;
		}
		__cm_quQueue.push(nValue); //否则添加
		__cm_cNotEmpty.ActivateOne();//并通知一个线程
	}
	
	//从任务池中取任务
	const ITask*
	CTaskPool::Pop(void)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock);
		while (!__cm_bIsExit && IsEmpty()) //如果任务池未销毁且为空，则等待添加任务
		{
			__cm_cNotEmpty.Wait();
			std::cout << "读阻塞" << std::endl;
		}
		if (!__cm_bIsExit) /*如果任务池不销毁，，说明由于添加了任务才解除上面的阻塞。则取任务*/
		{
			const ITask* nTemp = __cm_quQueue.front();
			__cm_quQueue.pop();
			__cm_cNotFull.ActivateOne();
			return nTemp;
		}
		else /* 否则说明是广播了激活信号，任务池销毁，需要解除阻塞*/
		{
			return nullptr;
		}
	}
}

#endif /* end of include guard: MY_TASK_POOL_H */
