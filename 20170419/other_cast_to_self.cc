/*************************************************************************
    > File Name: other_cast_to_the.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月19日 星期三 20时35分13秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class anotherpoint
{
	private:
		float _x,_y;
		friend class point;
		friend ostream &operator <<(ostream &os,const anotherpoint & ref);
	public:
		anotherpoint(float x,float y):_x(x),_y(y)//构造函数
		{
			cout<<"我是构造函数anotherpoint(float,float)"<<endl;
		}
		~anotherpoint()//析构函数
		{
			cout<<"我是析构函数~anotherpoint()"<<endl;
		}
		anotherpoint(const anotherpoint &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
			cout<<"我是拷贝构造函数anotherpoint(const anotherpoint&ref)"<<endl;
		}
		anotherpoint & operator=(const anotherpoint &ref)//赋值运算符函数
		{
			cout<<"我是赋值构造函数anotherpoint &operator(const anotherpoint &ref)"<<endl;
			if(this==&ref)
				return *this;
			_x=ref._x;
			_y=ref._y;
			return *this;
		}
	protected:
		/* member */
};
ostream & operator << (ostream &os,const anotherpoint &ref)
{
	os<<ref._x<<","<<ref._y<<endl;
	return os;
}
class point
{
	private:
		int _x, _y;
	public:
	explicit point(int x=1,int y=1):_x(x),_y(y)//构造函数
		{
			cout<<"我是构造函数point(int,int)"<<endl;
		}
		point(const anotherpoint &ref):_x(ref._x),_y(ref._y)
		{
		}
		~point()//析构函数
		{
			/*fucntion_body*/
			cout<<"我是析构函数~point()"<<endl;
		}
		point(const point &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
			/*fucntion_body*/
			cout<<"我是拷贝构造函数"<<endl;
		}
		point & operator=(const point &ref)//赋值运算符函数
		{
			cout<<"我是赋值构造函数"<<endl;
			if(this==&ref)
				return *this;
			_x=ref._x;
			_y=ref._y;
			return *this;
		}
		friend ostream & operator << (ostream &os,const point &ref);
};
ostream & operator << (ostream &os,const point &ref)
{
	os<<ref._x<<","<<ref._y<<endl;
	return os;
}
int  main()
{
	anotherpoint ap(2.10,2.15);
	cout<<"ap="<<ap<<endl;
	point p1(10.5,10.5);
	cout<<"p1="<<p1<<endl;
	p1=ap;
	cout<<"p1="<<p1<<endl;
	return 0;
}
