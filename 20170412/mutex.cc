/*************************************************************************
    > File Name: mutex.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月14日 星期五 19时40分26秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class mutex
{
	private:;
		int _val;
		int _kind;
		unsigned long _thid;
	public:
		mutex(int val=0,int kind=PTHREAD_MUTEX_TIMED_NP):_val(val),_kind(kind),_thid(0)
		{
		}
		~mutex()
		{
		}
		int Lock();
		int Unlock();
};
int  mutex::Lock()
{
	switch(_kind)
	{
		case PTHREAD_MUTEX_TIMED_NP:
									while(_val!=0)
									{
									}
									_val=1;
									break;
		case PTHREAD_MUTEX_RECURSIVE_NP:
										if(_thid==0)
										{
											_val++;
											_thid=pthread_self();
										}
										else
										{
											if(_thid==pthread_self())
											{
												_val++;
												_thid=pthread_self();
											}
											else
											{
												while(_val!=0)
												{
												}
												_val++;
												_thid=pthread_self();
											}
										}
										break;
		case PTHREAD_MUTEX_ERRORCHECK_NP:
										if(_val!=0)
										{
											return EDEADLK;
										}
										else
										{
											_val=1;
											_thid=pthread_self();
										}
										break;
		default:cout<<"unkonw kind mutex"<<endl;exit(0);break;
	}
	return 0;
}
int mutex::Unlock()
{
	switch(_kind)
	{
		case PTHREAD_MUTEX_TIMED_NP:
									_val=0;
									break;
		case PTHREAD_MUTEX_RECURSIVE_NP:
										if(_val!=0)
										{
											if(_thid==pthread_self())
											{
												_val--;
											}
											else
											{
												return EPERM;
											}
										}
										break;
		case PTHREAD_MUTEX_ERRORCHECK_NP:
										if(_val!=0)
										{
											if(_thid==pthread_self())
											{
												_val=0;
											}
										}
										break;
		default:cout<<"unkonw kind mutex"<<endl;exit(0);break;
	}
	return 0;
}
mutex lock;
void *threadfunction(void *p)
{
	unsigned long  i=1;
	while(i<=100000)
	{
		lock.Lock();
		(*(unsigned long*)p)++;
		i++;
		lock.Unlock();
	}
	pthread_exit((void*)0);
}
int  main()
{
	pthread_t thid1,thid2;
	/*pthread_t thid3;*/
	unsigned long *p=new unsigned long;
	*p=0;
	pthread_create(&thid1,NULL,threadfunction,(void*)p);
	pthread_create(&thid2,NULL,threadfunction,(void*)p);
	/*pthread_create(&thid3,NULL,threadfunction,(void*)p);*/
	pthread_join(thid1,NULL);
	pthread_join(thid2,NULL);
	/*pthread_join(thid3,NULL);*/
	cout<<*p<<endl;
	delete p;
	return 0;
}
