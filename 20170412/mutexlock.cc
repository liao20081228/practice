/*************************************************************************
    > File Name: mutexlock.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月14日 星期五 22时04分54秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class mutex_t
{
	private:
		pthread_mutex_t _mutex;
	public:
		mutex_t(int kind=PTHREAD_MUTEX_TIMED_NP);//构造函数
		~mutex_t()//析构函数
		{
			pthread_mutex_destroy(&_mutex);
		}
		void lock()
		{
			pthread_mutex_lock(&_mutex);
		}
		void trylock()
		{
			pthread_mutex_trylock(&_mutex);
		}
		void unlock()
		{
			pthread_mutex_unlock(&_mutex);
		}
};
mutex_t::mutex_t(int kind)
{
	pthread_mutexattr_t mutexattr;
	pthread_mutexattr_init(&mutexattr);
	pthread_mutexattr_settype(&mutexattr,kind);
	pthread_mutex_init(&_mutex,&mutexattr);
	pthread_mutexattr_destroy(&mutexattr);
}
class mutexguard
{
	private:
		mutex_t & _mutex;
	public:
		mutexguard(mutex_t & mutex ):_mutex(mutex)//构造函数
		{
			_mutex.lock();
		}
		/*member*/
		~mutexguard()//析构函数
		{
			_mutex.unlock();
		}
};

/*mutex_t mutex;*/
/*void cleanfunc(void *)
{
	mutex.unlock();
}*/
long sum=0;
void *threadfunction(void *p)
{
	unsigned long i=0;
	while(i<100000)
	{
		/*pthread_cleanup_push(cleanfunc,NULL);*/
		mutexguard guard(*((mutex_t*)p));
		sum++;
		i++;
		/*pthread_cleanup_pop(0);*/
	}
	pthread_exit((void*)i);
}
int  main()
{
	pthread_t thid[5];
	/*long sum=0;*/
	mutex_t mutex;
	for (int i = 0; i < 5; ++i) 
	{
		pthread_create(&thid[i],NULL,threadfunction,(void*)&mutex);
	}
	long int ret=0;
	for (int i = 0; i < 5; ++i) 
	{
		pthread_join(thid[i],(void**)&ret);
		cout<<"thid"<<i<<"return value:"<<ret<<endl;
	}
	cout<<"sum:"<<sum<<endl;
	return 0;
}
