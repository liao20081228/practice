/*************************************************************************
    > File Name: operator_overload.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月18日 星期二 11时40分45秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class complex
{
	public:
		int _real,_image;
	public:
		complex(int real=0,int image=0):_real(real),_image(image)//构造函数
		{
			/*fucntion_body*/
		}
		/*member*/
		~complex()//析构函数
		{
			/*fucntion_body*/
		}
		complex(const complex &ref):_real(ref._real),_image(ref._image)//拷贝构造函数
		{
			/*fucntion_body*/
		}
		complex & operator=(const complex &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_real=ref._real;
			_image=ref._image;
			return *this;
		}
		void print(  )
		{
			cout<<_real<<"+"<<_image<<"i"<<endl;
		}
};
#if 0 
int operator+(int x,int y) /* 运算符的基本内置功能不能重载*/
{
	return x+y;
}
#endif
complex  operator+(complex x,complex y)/* 自由函数要求操作数的必须具有public属性*/
{
	return complex(x._real+y._real,y._image+x._image);
}

int  main()
{
	complex c1(1,1);
	complex c2(2,2);
	complex c=c1+c2;
	c.print();
	return 0;
}
