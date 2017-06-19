/*************************************************************************
  > File Name: thread_oo.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年06月01日 星期四 13时02分34秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
namespace MyNameSpace
{
	class CThread
	{
		public:
			CThread(IN std::function<void()> Run = nullptr);
			~CThread(void);
			CThread(IN const CThread& lref) = delete; //禁止拷贝
			CThread& operator = (IN const CThread& lref) = delete; //禁止赋值
			
			void Start(void);
			void Join(void) const;
			::pthread_t GetThreadID(void) const;
		
		private:
			static void* ThreadFunction(IN void* arg); //线程函数,因为成员的第一参数是this指针，因此这里只能是static函数
		
		private:
			::pthread_t __ThreadID;
			bool __cm_bIsRuning;
			std::function<void()> __Run;
		
	};
	

	//constructor of CThread class
	inline
	CThread::CThread(std::function<void()>Run)
		:__ThreadID(0)
		 , __cm_bIsRuning(false)
		 ,__Run(Run)
	{
	}
	

	//destructor of CThread class
	/*virtual*/
	CThread::~CThread(void)
	{
		if (true == __cm_bIsRuning)
		{
			::pthread_detach(__ThreadID); //将线程设为分离状态，此时不能用jion等待回收，而由系统管理
			__cm_bIsRuning = false;
			cout << "对象已经销毁" << endl;
			
		}
	}
	
	
	//start a thread
	inline void
	CThread::Start(void)
	{
		::pthread_create(&__ThreadID, nullptr, ThreadFunction, this);
		__cm_bIsRuning = true;
	}


	//thread fucntion which  be used run a real task
	/* static */ void*
	CThread::ThreadFunction(IN void* arg)
	{
		CThread* pCThread = static_cast<CThread*>(arg);
		if (nullptr != pCThread && nullptr != pCThread->__Run)
		{
			pCThread->__Run();
		}
		return nullptr;
	}


	//return  current  thread ID
	inline ::pthread_t
	CThread::GetThreadID(void) const
	{
		return __ThreadID;
	}

	
	//wait the end of thread and cycle resource
	void
	CThread::Join(void) const
	{
		::pthread_join(__ThreadID, nullptr);
	}

	
	//realize task
	void
	Run(void)
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
	MyNameSpace::CThread* pCThread = new MyNameSpace::CThread(std::bind(MyNameSpace::Run));
	pCThread->Start();
	cout << pCThread->GetThreadID() << endl;
	cout << ::pthread_self() <<endl;
	pCThread->Join();
	delete pCThread;
	return 0;
}
