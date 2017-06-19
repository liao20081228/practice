/*************************************************************************
    > File Name: singleton_auto_recycle.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月21日 星期五 20时35分24秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class singleton
{
	private:
		static singleton *_ps;
		singleton(/*arguments*/)/*init_member_lsit*///构造函数
		{
			/*fucntion_body*/
		}
		~singleton()
		{
			/*fucntion_body*/
		}
	public:
		static singleton *getinstance()
		{
			if(_ps==NULL)
				_ps=new singleton;
			return _ps;
		}
		void Destory(/*arguments*/)
		{
			if(_ps)
				delete _ps;
		}
};
singleton*singleton ::_ps=NULL;

int  main()
{
	singleton *p1=singleton::getinstance();/* 懒汉模式，先不分配地址*/
	singleton *p2=singleton::getinstance();
	cout<<"p1:"<<p1<<"p2:"<<p2<<endl;
	p1->Destory();
	return 0;
}
