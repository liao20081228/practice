/*************************************************************************
    > File Name: taskpool.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 21时57分00秒
 ************************************************************************/
#ifndef MY_TASKPOOL_H
#define MY_TASKPOOL_H
#include"task.h"
#include"condvar.h"
namespace MyNamespace
{
//任务池
	class CTaskPool : public CForbidCopyAndAssign
	{
		public:
			CTaskPool(IN size_t ulnSize = 10);
			~CTaskPool(void);

			void Push(IN const CTask* nValue); /*加入一个任务 */
			const CTask* Pop(void); /* 提取一个任务*/
			bool IsFull(void) const; /* 任务池是否满了*/
			bool IsEmpty(void) const; /* 任务池是否空*/
			void WakeUp(void);
		private:
			CMutexLock __cm_cMutexLock;
			CConditionVariable __cm_cNotFull;
			CConditionVariable __cm_cNotEmpty;
			size_t __cm_ulnSize;
			queue<const CTask*> __cm_quQueue;
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
		,__cm_bIsExit(false) //任务池销毁标志位，建立任务池时为false,要销毁任务池时设为true
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
	
	/*要销毁任务池，则必须将所有阻塞在pop()的线程全部唤醒*/
	inline void 
	CTaskPool::WakeUp(void)
	{
		cout << "唤醒所有" << endl;
		__cm_bIsExit = true;
		__cm_cNotEmpty.ActivateAll();
	}

	//向任务池中添加任务
	void 
	CTaskPool::Push(IN const CTask* nValue)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock); /* 加锁*/
		while (!__cm_bIsExit && IsFull()) /* 如果任务池没销毁且满了则阻塞*/
		{
			__cm_cNotFull.Wait();
			std::cout << "写阻塞" << std::endl;
		}
		__cm_quQueue.push(nValue); //否则添加
		__cm_cNotEmpty.ActivateOne();//并通知一个读线程
	}
	
	//从任务池中取任务
	const CTask*
	CTaskPool::Pop(void)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock);
		while (!__cm_bIsExit && IsEmpty()) //如果任务池未销毁且为空，则等待添加任务,当任务池要销毁或者任务池有任务
		{
			__cm_cNotEmpty.Wait();
			std::cout << "读阻塞" << std::endl;
		}
		if (!__cm_bIsExit) /*如果任务池未销毁，说明由于添加了任务才解除上面的阻塞。则取任务*/
		{
			const CTask* nTemp = __cm_quQueue.front();
			__cm_quQueue.pop();
			__cm_cNotFull.ActivateOne();// 通知写线程可写
			return nTemp;
		}
		else /* 否则,任务池将要销毁，则需要解除阻塞*/
		{
			return nullptr;
		}
	}
}

#endif /* end of include guard: MY_TASKPOOL_H */
