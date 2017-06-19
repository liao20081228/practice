/*************************************************************************
    > File Name: cast.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月16日 星期二 13时36分53秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class base
{
	public:
		virtual void print()
		{
			cout<<"base:print()"<<endl;
		}
};
class derived:public base 
{
	public:
		virtual void print()
		{
			cout<<"derived ::print()"<<endl;
			
		}
		void display()
		{
				cout<<"derived ::display()"<<endl;
				
		}

};



int  main()
{
	double a=100.001;
	int b=static_cast<int>(a); /* 安全的转换类型*/
	cout<<b<<endl;
	
	const int *p=new int(100);
	*const_cast<int *>(p)=1000; /* 转换const 属性*/
	cout<<*p<<endl;

	int *pint=new int(100);
	 char *pchar=reinterpret_cast<char *>(pint); /* 在更深层次的强转类型，非常危险*/
	 cout<<*pchar<<endl;

	base *pbase=new derived;
	pbase->print();
	//pbase->display();  /* 指针访问非虚函数时取决于指针本身类型，出错*/
	dynamic_cast<derived*>(pbase)->display();/* 强转为派生类指针后在访问就不会出错了*/
	return 0;
}
