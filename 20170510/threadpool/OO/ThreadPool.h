/*************************************************************************
    > File Name: pthread.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月08日 星期四 16时41分17秒
 ************************************************************************/
#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H

#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNamespace
{
	using ::pthread_t;
	using ::pthread_mutex_t;
	using ::pthread_cond_t;

	//禁止拷贝
	class CForbidCopyAndAssign
	{
		public:
			CForbidCopyAndAssign(void);
			~CForbidCopyAndAssign(void);
			CForbidCopyAndAssign(const CForbidCopyAndAssign& lref) = delete;
			CForbidCopyAndAssign& operator = (const CForbidCopyAndAssign& lref) = delete;
	};
	

	/*互斥锁*/
	class CMutexLock : public CForbidCopyAndAssign
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


	/* 互斥锁的保护类，相当于pthread_cleanup_push/pop，利用栈对象建立时的构造函数加锁，销毁时的析构函数来解锁*/
	class CMutexLockGuard : public CForbidCopyAndAssign
	{
		public:
			CMutexLockGuard(IN CMutexLock& cMutexLock);
			~CMutexLockGuard(void);
		private:
			CMutexLock& __cm_cMutexLock;
	};


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

	//抽象任务类，由其派生类决定具体任务
	class ITask
	{
		public:
			virtual ~ITask(void);
			virtual void Execute(void) const = 0;
	};



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

//========================================================================

/*CForbidCopyAndAssign的实现*/
namespace MyNamespace
{
	inline
	CForbidCopyAndAssign::CForbidCopyAndAssign(void)
	{
	}

	inline 
	CForbidCopyAndAssign::~CForbidCopyAndAssign(void)
	{
	}
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

namespace MyNamespace
{
	inline /*virtual */
	ITask::~ITask(void)
	{
	}
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
