/*************************************************************************
    > File Name: set.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月29日 星期六 00时15分36秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename container>
void Display1(const container &c)
{
	/*typename container::iterator it;*/
	typename container::const_iterator it;
	for(it=c.begin();it!=c.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
template<typename container>
void Display2( container &c)
{
	typename container::iterator it;
	for(it=c.begin();it!=c.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	
}
template<typename container>
void Display3( container &c)
{
	typename container::reverse_iterator it;
	for(it=c.rbegin();it!=c.rend();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
template<typename container>
void Display4(const  container &c)
{
	typename container::const_reverse_iterator it;
	for(it=c.rbegin();it!=c.rend();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}


int  main()
{
		
	int value=100;
	 set<int>setint{1,2,3,4,5,6};
	 set<int>::iterator it=setint.find(3);
	 /**it=5;*/ /* set中的元素不能修改*/
	 cout<<value<<endl;
	 Display1(setint);
	 Display2(setint);
	 Display3(setint);
	 Display4(setint);
	 vector<int>vec{1,2,3,4,5,6};
	 Display1(vec); /* vector 的迭代器有两种普通迭代器和常迭代器，普通对象可转为常对象，常对象是不可以转为普通对象的，当模板参数有const修饰，他的begin返回的是常迭代器，而后面采用的是普通迭代器因此出错,加上const后就可以*/
	 Display2(vec);
	 Display3(vec);
	 Display4(vec);
	return 0;
}
