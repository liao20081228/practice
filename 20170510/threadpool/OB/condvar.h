/*************************************************************************
    > File Name: mutexcondvar.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 20时22分53秒
 ************************************************************************/
#ifndef MY_CONDITION_VARIABLE_H
#define MY_CONDITION_VARIABLE_H
#include"mutex.h"
namespace MyNamespace
{
	//条件变量
	class CConditionVariable : public CForbidCopyAndAssign
	{
		public:
			CConditionVariable(IN CMutexLock& cMutexLock);
			~CConditionVariable(void);

			void Wait(void); //等待激活
			void ActivateOne(void); //激活一个
			void ActivateAll(void); //激活所有
		private:
			CMutexLock& __cm_cMutexLock;
			pthread_cond_t __cm_sCondVar;
	};
}

//========================================================================


/* 条件变量的实现*/
namespace MyNamespace
{
	/* 构造一个条件变量类，并初始化条件变量*/
	inline
	CConditionVariable::CConditionVariable(IN CMutexLock& cMutexLock)
		:__cm_cMutexLock(cMutexLock)
		,__cm_sCondVar(PTHREAD_COND_INITIALIZER)
	{
		/*::pthread_cond_init(&__cm_sCondVar,nullptr);*/
	}
	
	/* 销毁条件变量*/
	inline
	CConditionVariable::~CConditionVariable(void)
	{
		if (0 != ::pthread_cond_destroy(&__cm_sCondVar))
		{
			perror("destroy condition variable failed");
			exit(-6);
		}
	}

	/* 等待激活*/
	void
	CConditionVariable::Wait(void)
	{
		if (0 != ::pthread_cond_wait(&__cm_sCondVar, __cm_cMutexLock.GetMutex()))
		{
			perror("wait thread faild");
			exit(-4);
		}
	}

	/*激活一个*/
	void
	CConditionVariable::ActivateOne(void)
	{
		if (0 != ::pthread_cond_signal(&__cm_sCondVar))
		{
			perror("Activate a  Condition Variable  failed");
			exit(-5);
		}
	}

	/*激活所有 */
	void
	CConditionVariable::ActivateAll(void)
	{
		if (0 != ::pthread_cond_broadcast(&__cm_sCondVar))
		{
			perror("Activate all condition variable failed ");
			exit(-5);
		}
	}

}

#endif /* end of include guard: MY_MUTEX_CONDVER_H */
