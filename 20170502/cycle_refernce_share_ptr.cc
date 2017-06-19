/*************************************************************************
    > File Name: cycle_refernce_share_ptr.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月10日 星期三 23时00分04秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
using std::shared_ptr;
using std::weak_ptr;
class child;
class parent
{
	public:
		shared_ptr<child>_childptr;
		parent()
		{
			cout<<"parent()"<<endl;
		}
		~parent()
		{
			cout<<"~parent()"<<endl;
		}
};
class child
{
	public:
		weak_ptr<parent>_parentptr;
		child()
		{
			cout<<"child()"<<endl;
		}
		~child()
		{
			cout<<"~child()"<<endl;
		}
};

int  main()
{
	shared_ptr<child>childptr(new child);
	shared_ptr<parent>parentptr(new parent);

	cout<<childptr.use_count()<<endl;
	cout<<parentptr.use_count()<<endl;
	
	childptr->_parentptr=parentptr;
	parentptr->_childptr=childptr;
	
	cout<<childptr.use_count()<<endl;
	cout<<parentptr.use_count()<<endl;
	return 0;
}
