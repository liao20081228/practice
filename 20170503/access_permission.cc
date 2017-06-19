/*************************************************************************
    > File Name: test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 18时39分30秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class point
{
	private:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)
	{
		cout<<"point(int x,int y)"<<endl;
	}
	void printx()
	{
		cout<<"_x:"<<_x<<endl;
	}
	protected:
	void printy()
	{
		cout<<"_y:"<<_y<<endl;
	}
};
/*
 *继承方式：public，类的公有和保护成员原样继承给派生类，私有成员被屏蔽
 *         protect，基类的公有成员和保护成员变为派生类的保护成员。私有成员被【屏蔽
 *         private，基类的公有和保护成员变为基类的私有成员。私有成员被屏蔽
 *（1）无论哪种继承方式，在派生类内部，只有基类的私有成员不可访问
 *（2）无乱哪种继承方式，在派生类外部，只有采取public继承方式的基类的public成员可以访问
 *（3）构造和析构函数无法继承
 *（4）new、delete、=不可继承
 *（5）友元关系不可继承
 */
class point3d :public point
{
	private :
		int _z;
	public:
		point3d(int x,int y,int z):point(x,y),_z(z)
		{
			cout<<"point3d(int ,int,int)"<<endl;
		}
	void print()
	{
		/*cout<<_x<<","<<_y<<","<<_z<<endl; //派生类内部只有基类的私有成员你不可访问*/
		printx(); 
		printy();
		cout<<"_z:"<<_z<<endl;
	}
};
int  main()
{
	point3d a(1,2,3);
	a.print();
	a.printx();
	/*a.printy();*/ /* 在派生类外，只有采取公有继承方式的基类的public成员可以访问*/
	return 0;
}

