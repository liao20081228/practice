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
		singleton(/*arguments*/)/*init_member_lsit*///构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~singleton()//析构函数
		{
			/*fucntion_body*/
		}
	/*	class autorelease
		{
			public:
				~autorelease()//析构函数
				{
					cout<<"destory"<<endl;
					
					if(_psingleton!=NULL)
						delete _psingleton;
				}
		};*/
		class autorelease;
		static autorelease _auto;
	public:
		static singleton *getinstance()
		{
			if(_psingleton==NULL)
				_psingleton=new singleton;
			return _psingleton;
		}
		void play();

};
class  singleton::autorelease
{	
	public:
		~autorelease()//析构函数
		{
			cout<<"destory"<<endl;
			if(_psingleton!=NULL)
				delete _psingleton;
		}
};

singleton * singleton::_psingleton=NULL;
singleton::autorelease singleton::_auto;
int  main()
{
	singleton *p1=singleton::getinstance();
	singleton *p2=singleton::getinstance();
	printf("%p\n",p1 );
	printf("%p\n",p2 );
	return 0;
}
