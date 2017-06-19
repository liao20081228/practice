/*************************************************************************
    > File Name: productor_consumer_OO.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年06月01日 星期四 23时44分04秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNameSpace
{
	using ::pthread_t;
	using ::pthread_mutex_t;
	using ::pthread_cond_t;

	class CForbidCopyAndAssign
	{
		public:
			CForbidCopyAndAssign(void);
			~CForbidCopyAndAssign(void);
			CForbidCopyAndAssign(const CForbidCopyAndAssign& lref) = delete;
			CForbidCopyAndAssign& operator = (const CForbidCopyAndAssign& lref) = delete;
		//也可以放入private区域
	};


	inline
	CForbidCopyAndAssign::CForbidCopyAndAssign(void)
	{

	}


	inline
	CForbidCopyAndAssign::~CForbidCopyAndAssign(void)
	{

	}


	//abstract class:IThead,which provide user with interface's regulation 
	class IThread : public CForbidCopyAndAssign 
	{
		public:
			IThread(void);
			virtual ~IThread(void);

			void Start(void);
			void Join(void) const;
			pthread_t GetThreadID(void) const;

		protected:
			virtual void Run(void)  = 0;
		private:
			static void* ThreadFunction(void* arg);
		private:
			pthread_t __cm_ThreadID;
			bool __cm_bIsRuning;
	};


	//constructor of IThead
	inline
	IThread::IThread(void)
		:__cm_ThreadID(0)
		,__cm_bIsRuning(false)
	{

	}


	//destructor of IThead
	/* virtual */
	IThread::~IThread(void)
	{
		if (__cm_bIsRuning)
		{
			::pthread_detach(__cm_ThreadID);
			__cm_bIsRuning = false;
		}
	}


	// Start of IThread
	inline void
	IThread::Start(void)
	{
		::pthread_create(&__cm_ThreadID, nullptr, ThreadFunction,static_cast<void*>(this));
		__cm_bIsRuning = true;
	}

	//Join of Ithread
	inline void
	IThread::Join(void) const
	{
		::pthread_join(__cm_ThreadID, nullptr);
	}

	
	//get the thread ID of current son thread
	inline pthread_t
	IThread::GetThreadID(void) const
	{
		return __cm_ThreadID;
	}

	
	//start a thread
	inline void*
	IThread::ThreadFunction(IN void* arg)
	{
		static_cast<IThread*>(arg)->Run();
		return nullptr;
	}


	//mutex class
	class CMutexLock : public CForbidCopyAndAssign
	{
		public:
			CMutexLock(void);
			~CMutexLock(void);

			void Lock(void);
			void Unlock(void);

			pthread_mutex_t* GetMutex(void);
		private:
			pthread_mutex_t __cm_Mutex;
	};

	
	//constructor of CMutexLock
	inline
	CMutexLock::CMutexLock(void)
	{
		__cm_Mutex=PTHREAD_MUTEX_INITIALIZER;
		//或则pthread_mutex_init(&__cm_Mutex, nullptr);
	}


	//destructor of CMutexLock
	CMutexLock::~CMutexLock(void)
	{
		::pthread_mutex_destroy(&__cm_Mutex);
	}

	
	//lock
	inline void
	CMutexLock::Lock(void)
	{
		::pthread_mutex_lock(&__cm_Mutex);
	}
	

	//unlock
	inline void
	CMutexLock::Unlock(void)
	{
		::pthread_mutex_unlock(&__cm_Mutex);
	}

	//get a mutex
	inline pthread_mutex_t*
	CMutexLock::GetMutex(void)
	{
		return &__cm_Mutex;
	}

	//this class be used to unlock mutex,when exit after lock
	//the destructor be auto called when a object be destroyed
	class CMutexLockGuard : public CForbidCopyAndAssign
	{
		public:
			CMutexLockGuard(IN CMutexLock& cMutexLock);
			~CMutexLockGuard(void);
		private:
			CMutexLock& __cm_cMutexLock; 
	};

	//constructor of CMutexLockGuard
	inline
	CMutexLockGuard::CMutexLockGuard(IN CMutexLock& cMutexLock)
		:__cm_cMutexLock(cMutexLock)
	{
		__cm_cMutexLock.Lock();
	}
	

	//destructor of CMutexLockGuard
	inline
	CMutexLockGuard::~CMutexLockGuard(void)
	{
		__cm_cMutexLock.Unlock();
	}


	//condtion variable,used to synchronize,conditon variable  must bind with a mutex
	class CConditonVariable :public CForbidCopyAndAssign
	{
		public:
			CConditonVariable(IN CMutexLock& cMutexLock);
			~CConditonVariable(void);
			
			void Wait(void);
			void ActivateOne(void);
			void ACtivateAll(void);
		
		private:
			CMutexLock& __cm_cMutexLock;
			pthread_cond_t __cm_Condvar;
	};


	//constructor of CConditonVariable
	inline
	CConditonVariable::CConditonVariable(IN CMutexLock& cMutexLock)
		:__cm_cMutexLock(cMutexLock)
		, __cm_Condvar(PTHREAD_COND_INITIALIZER)
	{
		//或者使用::pthread_cond_init(&__cm_Condvar,nullptr);
	}


	//destructor of CConditonVariable
	inline
	CConditonVariable::~CConditonVariable(void)
	{
		::pthread_cond_destroy(&__cm_Condvar);
	}

	
	//wait conditon variable and block this point
	inline void
	CConditonVariable::Wait(void)
	{
		//先加锁，pthread_cond_wait会解锁后阻塞在这里，直到条件被满足，然后在加速，执行完操作后
		//再解锁，c中应该用pthread_cleanup_push/pop保护。
		::pthread_cond_wait(&__cm_Condvar, __cm_cMutexLock.GetMutex());
	}
	

	//activate a block thread
	inline  void
	CConditonVariable::ActivateOne(void)
	{
		::pthread_cond_signal(&__cm_Condvar);
	}

	
	//activate all block thread
	inline void
	CConditonVariable::ACtivateAll(void)
	{
		::pthread_cond_broadcast(&__cm_Condvar);
	}


	class CBuffer : public CForbidCopyAndAssign
	{
		public:
			CBuffer(IN size_t ulnSize);
			~CBuffer(void);

			bool Full(void) const;
			bool Empty(void) const;
			void Push(const int& TElem);
			const int& Pop(void);
		private:
			CMutexLock __cm_cMutexLock;
			CConditonVariable __cm_cNotFull;
			CConditonVariable __cm_cNotEmpty;
			size_t __cm_ulnSize;
			queue<int> __cm_quQueue;
	};

	
	//constructor of CBuffer
	inline
	CBuffer::CBuffer(IN size_t ulnSize)
		:__cm_cMutexLock()
		,__cm_cNotFull(__cm_cMutexLock)
		,__cm_cNotEmpty(__cm_cMutexLock)
		,__cm_ulnSize(ulnSize)
	{
	}


	//derstructor of CBuffer
	inline
	CBuffer::~CBuffer(void)
	{
	}


	//judge queue is full?
	inline bool
	CBuffer::Full(void) const
	{
		return __cm_ulnSize == __cm_quQueue.size();
	}
	


	//judge queue is empty?
	inline bool
	CBuffer::Empty(void) const
	{
		return __cm_quQueue.empty();
	}

	
	// push a element to queue
	void 
	CBuffer::Push(const int& TElem)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock); //保护进程，相当于pthread_cleanup_push/pthead_cleanup_pop
		while (Full()) //如果缓冲区满了，则阻塞
		{
			__cm_cNotFull.Wait();
		}
		__cm_quQueue.push(TElem); //否则生产一个
		__cm_cNotEmpty.ActivateOne(); //通知消费者，有了产品
	}


	//pop a element to queue
	const int&
	CBuffer::Pop(void)
	{
		CMutexLockGuard cMutexLockGuard(__cm_cMutexLock);
		while (Empty()) // 当为空时，消费者阻塞，用while可以避免异常唤醒
		{
			__cm_cNotEmpty.Wait();
		}
		int& temp = __cm_quQueue.front(); //否则消费一个
		__cm_quQueue.pop();
		__cm_cNotFull.ActivateOne();//并通知生产者缓冲区有空间
		return temp;
	}
	
	
	//productor class
	class CProductor : public IThread
	{
		public:
			CProductor(CBuffer& rcBuffer);
			virtual ~CProductor(void);
			virtual void Run(void);
		private:
			CBuffer& __cm_rcBuffer;

	};

	inline
	CProductor::CProductor(CBuffer& rcBuffer)  //引用成员，const成员只能在初始化列表中绑定
		:__cm_rcBuffer(rcBuffer) 
	{
	}


	inline
	CProductor::~CProductor(void)
	{
	}


	inline /* virtual */ void
	CProductor::Run(void) 
	{
		while (true)
		{
			::srand(::time(nullptr));
			int nValue = ::rand() % 101;
			__cm_rcBuffer.Push(nValue);
			cout << "thread  " << ::pthread_self() << "  produce a number :" << nValue << endl;
			::sleep(1);
		}
	}


	//customer class
	class CCustomer : public IThread
	{
		public:
			CCustomer(CBuffer& rcBuffer);
			~CCustomer(void);
			virtual void Run(void);
		private:
			CBuffer& __cm_rcBuffer;
	};


	inline
	CCustomer::CCustomer(CBuffer& rcBuffer)
		:__cm_rcBuffer(rcBuffer)
	{
	}


	inline
	CCustomer::~CCustomer(void)
	{
	}

	inline /* virtual */ void
	CCustomer::Run(void)
	{
		::srand(::time(nullptr));
		while(true)
		{ 
			int nValue = __cm_rcBuffer.Pop();
			cout << "thread  " << ::pthread_self() << "  customer a number :" << nValue << endl;
			::sleep(5);
		}
	}
}


int main(void)
{
	using namespace MyNameSpace;
	CBuffer cBuffer(10);
	IThread* pcProductor = new CProductor(cBuffer);
	IThread* pcCustomer = new  CCustomer(cBuffer);

	pcProductor->Start();
	pcCustomer->Start();

	pcProductor->Join();
	pcCustomer->Join();
	return 0;
}
