/*************************************************************************
  > File Name: thread_oo.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年06月01日 星期四 13时02分34秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNameSpace
{
	class IThread
	{
		public:
			IThread(void);
			virtual ~IThread(void);

			IThread(IN const IThread& lref) = delete; //禁止拷贝
			IThread& operator = (IN const IThread& lref) = delete; //禁止赋值
			
			void Start(void);
			void Join(void) const;
			pthread_t GetThreadID(void) const;
		
		protected:
			virtual void Run(void) const = 0;
		
		private:
			static void* ThreadFunction(IN void* arg); //线程函数,因为成员的第一参数是this指针，因此这里只能是static函数
		
		private:
			pthread_t _cm_ThreadID;
			bool _cm_bIsRuning;
		
	};
	

	//constructor of IThread class
	inline
	IThread::IThread(void)
		:_cm_ThreadID(0), _cm_bIsRuning(false)
	{
	}
	

	//destructor of IThread class
	/*virtual*/
	IThread::~IThread(void)
	{
		if (true == _cm_bIsRuning)
		{
			::pthread_detach(_cm_ThreadID); //将线程设为分离状态，此时不能用jion等待回收，而由系统管理
			_cm_bIsRuning = false;
		}
	}
	
	
	//start a thread
	inline void
	IThread::Start(void)
	{
		::pthread_create(&_cm_ThreadID, nullptr, ThreadFunction, this);
		_cm_bIsRuning = true;
	}


	//thread fucntion which  be used run a real task
	/* static */ void*
	IThread::ThreadFunction(IN void* arg)
	{
		IThread* pIThread = static_cast<IThread*>(arg);
		if (nullptr != pIThread)
		{
			pIThread->Run();
		}
		return nullptr;
	}


	//return  current  thread ID
	inline ::pthread_t
	IThread::GetThreadID(void) const
	{
		return _cm_ThreadID;
	}

	
	//wait the end of thread and cycle resource
	void
	IThread::Join(void) const
	{
		::pthread_join(_cm_ThreadID, nullptr);
	}

	
	//this class is realization of real thread task
	class CThread : public IThread
	{
		protected:
			virtual void Run(void) const;
	};


	//realize task
	void
	CThread::Run(void) const
	{
		std::srand(::time(nullptr));
		for (int i = 0; i < 20; ++i)
		{
			cout << std::rand() / static_cast<double>(RAND_MAX / 77) <<endl;
			::sleep(1);
		}
	}
};//MyNameSpace


int main(void)
{
	MyNameSpace::IThread* pIThread = new MyNameSpace::CThread;
	pIThread->Start();
	cout << pIThread->GetThreadID() <<endl;
	pIThread->Join();
	delete pIThread;
	return 0;
}
