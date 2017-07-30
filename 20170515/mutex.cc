#include"mutex.h"
/*MutexLock*/
namespace MyNamespace
{
	/* 初始一个互互斥锁*/
	inline
	CMutexLock::CMutexLock(void)
		:__cm_sMutex(PTHREAD_MUTEX_INITIALIZER)
	{
		/*int nRet = ::pthread_mutex_init(&__cm_sMutex, nullptr);
		if (nRet != 0)
		{
			perror("Creat MutexLock faild");
			exit(-1);
		}*/
	}

	/* 销毁一个互斥锁*/
	CMutexLock::~CMutexLock(void)
	{
		if (0 != ::pthread_mutex_destroy(&__cm_sMutex))
		{
			perror("destroy MutexLock failed");
			exit(-2);
		}
	}

	/* 加锁，失败返回-3*/
	void
	CMutexLock::Lock(void)
	{
		if (0 != ::pthread_mutex_lock(&__cm_sMutex))
		{
			::perror("lock MutexLock failed");
			exit(-3);
		}
	}

	/* 解锁*/
	void
	CMutexLock::Unlock(void)
	{
		if (0 != ::pthread_mutex_unlock(&__cm_sMutex))
		{
			::perror("Unlock MutexLock faild");
			exit(-3);
		}
	}

	/* 获取一个互斥锁*/
	pthread_mutex_t*
	CMutexLock::GetMutex(void)
	{
		return &__cm_sMutex;
	}


	/* 加锁*/
	inline
	CMutexLockGuard::CMutexLockGuard(IN CMutexLock& cMutexLock)
		:__cm_cMutexLock(cMutexLock)
	{
		__cm_cMutexLock.Lock();
	}

	/* 解锁*/
	inline
	CMutexLockGuard::~CMutexLockGuard(void)
	{
		__cm_cMutexLock.Unlock();
	}
}

