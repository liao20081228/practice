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
		static singleton * getinstance()
		{
			if(_psingleton==NULL)
				_psingleton=new singleton;
			return _psingleton;
		}
		static void destory ()
		{
			delete _psingleton;
		}
};
singleton * singleton::_psingleton=NULL;
int  main()
{
	singleton *p1=singleton::getinstance();
	singleton *p2=singleton::getinstance();
	printf("%p\n",p1 );
	printf("%p\n",p2 );
	singleton::destory();
	return 0;
}
