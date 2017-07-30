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


#endif /* end of include guard: MY_MUTEX_H */
