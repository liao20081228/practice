/*************************************************************************
  > File Name: singleton_nest.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月22日 星期六 11时12分44秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class singleton
{
	private:
		static singleton * _psingleton;
	public:
		class autorelease
		{
			public:
				 ~autorelease()
				{
					if(_psingleton !=NULL)
						delete _psingleton;
					cout<<"desttory"<<endl;
				}
		};
	private:
		static autorelease _auto;
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
		static singleton* getinstance()
		{
			if(_psingleton==NULL)
				_psingleton=new singleton;
			return _psingleton;
		}

};
singleton* singleton::_psingleton=singleton::getinstance();
singleton::autorelease _auto;
int  main()
{
	singleton *p1=singleton::getinstance();
	singleton *p2=singleton::getinstance();
	cout<<"p1:"<<p1<<endl;
	cout<<"p2:"<<p2<<endl;
	return 0;
}
