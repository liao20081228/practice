/*************************************************************************
    > File Name: the_cast_to_other.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月20日 星期四 20时43分38秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class anotherpoint
{
	private:
		double _x,_y;
		friend class point;
	public:
		anotherpoint(double x=0.0,double y=0.0):_x(x),_y(y)
		{
		}
		friend ostream &operator<<(ostream &os,const anotherpoint &);
};
ostream &operator<<(ostream &os,const anotherpoint &ref)
{
	os<<ref._x<<","<<ref._y<<"anotherpoint <<"<<endl;
	return os;
}
class point
{
	private:
		int _x,_y;
	public:
		point(int x,int y):_x(x),_y(y)//构造函数
		{
			/*fucntion_body*/
		}
		point(const anotherpoint &ref):_x(ref._x),_y(ref._y)
		{
		}
		operator int()  //如果同时存在int和anotherpoint的转换函数,输出时必须指明函数，否则就会出现二义性
		{
			return _x;
		}
		operator anotherpoint()  /* 无返回值类型，无参数，有返回的变量，必须为成员函数*/
		{
			return anotherpoint(_x,_y);
		}
};

int  main()
{
	point p1(100,10);
	/*cout<<p1<<endl;*/
	cout<<p1.operator anotherpoint();
	cout<<p1.operator int()<<endl;
	
	return 0;
}
