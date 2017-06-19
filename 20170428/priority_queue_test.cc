/*************************************************************************
    > File Name: priority_queue_test.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017 Туу 30, Ня 21:10:40
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
void test()
{
	int arr[10]={0,1,3,2,5,9,8,6,7,4};
	priority_queue<int>q1;
	for (int i = 0; i < 10; ++i) 
	{
		q1.push(arr[i]);
		cout<<"默认比较函数时，当前优先级最高的是"<<q1.top()<<endl;
	}
}
void test1()
{
	int arr[10]={0,1,3,2,5,9,8,6,7,4};
	priority_queue<int,vector<int>,std::greater<int>>q1;
	for (int i = 0; i < 10; ++i) 
	{
		q1.push(arr[i]);
		cout<<"默认比较函数时，当前优先级最高的是"<<q1.top()<<endl;
	}
}
class point
{
	private:
		int _x,_y;
	public:
		point(int x,int y ):_x(x),_y(y)//构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~point()//析构函数
		{
			/*fucntion_body*/
		}
		point(const point &ref):_x(ref._x),_y(ref._y)//拷贝构造函数
		{
			/*fucntion_body*/
		}
		point & operator=(const point &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_x=ref._x;
			_y=ref._y;
			return *this;
		}
		friend ostream & operator<<(ostream & os,const point & p);
		bool operator>(const point &p)const
		{
			return _x>p._x?true:false;
		}
		friend struct compare;
};

ostream &operator<<(ostream &os,const point & p)
{
	os<<"("<<p._x<<","<<p._y<<")";
	return os;
}
void test2(/*arguments*/) /* 可以自己制定优先级的函数对象,包括函数名，函数指针，仿函数*/
{
	priority_queue<point,vector<point>,std::greater<point>>q;
	 point arr[5]={point(5,2),point(1,3),point(4,6),point(9,0),point(0,7)};
	for (int i = 0; i < 5; ++i) 
	{
		q.push(arr[i]);
		cout<<"当前优先级最高的时"<<q.top()<<endl;
	}
}

struct compare 
{
	bool operator()(const point &lhs,const point &rhs)
	{
		return lhs._x>rhs._x;
	}
};
void test3(/*arguments*/)
{
	priority_queue<point,vector<point>,compare>q;
	 point arr[5]={point(5,2),point(1,3),point(4,6),point(9,0),point(0,7)};
	for (int i = 0; i < 5; ++i) 
	{
		q.push(arr[i]);
		cout<<"当前优先级最高的时"<<q.top()<<endl;
	}
}

int  main()
{
	test();
	test1();
	test2();
	test3();

	return 0;
}
