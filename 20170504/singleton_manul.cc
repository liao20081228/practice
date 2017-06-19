/*************************************************************************
    > File Name: singleton_manul.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月15日 星期一 10时10分23秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class singleton_manul
{
	private:
		static singleton_manul *_p;
	protected:
		singleton_manul()
		{

		}
		~singleton_manul()
		{

		}
	public:
		static singleton_manul * getinstance()
		{
			if(_p==nullptr)
				_p=new singleton_manul;
			return _p;
		}
		static void destroy()
		{
			if(_p!=nullptr)
				delete _p;
		}

};
singleton_manul * singleton_manul::_p=nullptr;


class singleton_nest
{
	private:
		static singleton_nest *_p;
	protected:
		singleton_nest()
		{

		}
		~singleton_nest()
		{

		}
	public:
		class autorelease
		{
			public:
				~autorelease()
				{
					if(_p!=nullptr)
					delete _p;
				}
		};
	public:
		static singleton_nest * getinstance()
		{
			if(_p==nullptr)
				_p=new singleton_nest;
			return _p;
		}
};
singleton_nest * singleton_nest::_p=nullptr;
singleton_nest::autorelease _auto;

class singleton_atexit
{
	private:
		static singleton_atexit *_p;
	protected:
		singleton_atexit()
		{

		}
		~singleton_atexit()
		{

		}
	public:
		static singleton_atexit * getinstance()
		{
			if(_p==nullptr)
			{	
				_p=new singleton_atexit;
				atexit(destroy);
			}
			return _p;
		}
		static void destroy()
		{
			if(_p!=nullptr)
				delete _p;
		}

};
singleton_atexit * singleton_atexit::_p=nullptr;
class singleton_pthread
{
	private:
		static singleton_pthread *_p;
		static pthread_once_t _once;
	protected:
		singleton_pthread()
		{

		}
		~singleton_pthread()
		{

		}
	public:
		static singleton_pthread * getinstance()
		{
			pthread_once(&_once,init);
			return _p;
		}
		static void init()
		{
			if(_p==nullptr)
			{
				_p=new singleton_pthread;
				atexit(destroy);
			}
		}
		static void destroy()
		{
			if(_p!=nullptr)
				delete _p;
		}

};
singleton_pthread * singleton_pthread::_p=singleton_pthread::getinstance();
pthread_once_t singleton_pthread::_once=PTHREAD_ONCE_INIT;
int  main()
{
	singleton_manul *p1=singleton_manul::getinstance();
	singleton_manul *p2=singleton_manul ::getinstance();
	cout<<p1<<endl<<p2<<endl;
	singleton_manul::destroy();
	
	singleton_nest *p3=singleton_nest::getinstance();
	singleton_nest *p4=singleton_nest ::getinstance();
	cout<<p3<<endl<<p4<<endl;

	singleton_atexit *p5=singleton_atexit::getinstance();
	singleton_atexit *p6=singleton_atexit ::getinstance();
	cout<<p5<<endl<<p6<<endl;
	singleton_pthread *p7=singleton_pthread::getinstance();
	singleton_pthread *p8=singleton_pthread ::getinstance();
	cout<<p7<<endl<<p8<<endl;
	return 0;
}
