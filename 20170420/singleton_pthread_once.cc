/*************************************************************************
  > File Name: singleton.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月23日 星期日 14时05分18秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class singleton
{
	private:
		static singleton *_psingleton;
		static pthread_once_t _once;
	private:
		singleton(/*arguments*/)/*init_member_lsit*///构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~singleton()//析构函数
		{
			/*fucntion_body*/
		}
	public:
		static singleton *getinstance()
		{
			pthread_once(&_once,init);
			return _psingleton;
		}
		static void init()
		{
			_psingleton=new singleton;
			atexit(destory);
		}
		static void destory ()
		{
			if(_psingleton!=NULL)
				delete _psingleton;
			cout<<"destory"<<endl;
			
		}
};
singleton * singleton::_psingleton=NULL;
pthread_once_t singleton::_once=PTHREAD_ONCE_INIT;
int  main()
{
	singleton *p1=singleton::getinstance();
	singleton *p2=singleton::getinstance();
	printf("%p\n",p1 );
	printf("%p\n",p2 );
	return 0;
}
