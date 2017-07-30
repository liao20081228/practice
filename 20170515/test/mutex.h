/*************************************************************************
    > File Name: mutex.h
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 22时34分05秒
 ************************************************************************/
#ifndef MY_MUTEX_H
#define MY_MUTEX_H
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	
	using ::pthread_t;
	using ::pthread_mutex_t;
	using ::pthread_cond_t;
	
	/*互斥锁*/
	class CMutexLock
	{
		public:
			CMutexLock(void); /* 构造一个互斥锁类，并初始化*/
			~CMutexLock(void); /* 销毁一个互斥锁*/

			void Lock(void); /* 加锁*/
			void Unlock(void); /*  解锁*/

			pthread_mutex_t* GetMutex(void); /* 获取互斥锁*/
		private:
			pthread_mutex_t __cm_sMutex;
	};

	/* 互斥锁的保护类，相当于pthread_cleanup_push/pop，利用栈对象建立时的构造函数加锁，销毁时的析构函数来解锁*/
	class CMutexLockGuard
	{
		public:
			CMutexLockGuard(IN CMutexLock& cMutexLock);
			~CMutexLockGuard(void);
		private:
			CMutexLock& __cm_cMutexLock;
	};


}

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

#endif /* end of include guard: MY_MUTEX_H */
