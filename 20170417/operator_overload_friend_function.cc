/*************************************************************************
  > File Name: operator_overload.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月18日 星期二 11时40分45秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class complex
{
	private:
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
			if(_real==0)
			{	
				if(_image!=0)
				{
					if(_image!=1&&_image!=-1)
						cout<<_image<<"i"<<endl;
					else if(_image==-1)
						cout<<"-i"<<endl;
					else if (_image==1)
						cout<<"i"<<endl;
				}
				else
				{
					cout<<"0"<<endl;
				}
			}
			else
			{
				if(_image!=0)
				{
					if(_image!=1&&_image!=-1)
					{
						if(_image>0)
							cout<<_real<<"+"<<_image<<"i"<<endl;
						else
							cout<<_real<<_image<<"i"<<endl;
					}
					else if(_image==1)
					{
						cout<<_real<<"+i"<<endl;
					}
					else
						cout<<_real<<"-i"<<endl;
				}
				else
				{
					cout<<_real<<endl;
				}
			}
		}
		friend complex operator+(complex x,complex y);/*以自由友元函数形式重载运算符,可以在类内定义或者类内声明，类外实现*/
		complex operator-(complex y)/* 以成员函数形式重载双目运算符，必须省略左操作数，用有this指针传入*/
		{
			return complex(_real-y._real,_image-y._image);
		}
		complex &operator+=(complex x)
		{
			_real+=x._real;
			_image+=x._image;
			return *this;
		}
		complex &operator-=(complex x)
		{
			_real-=x._real;
			_image-=x._image;
			return *this;
		}
		complex &operator++()/* ++x*/
		{
			++_real;
			++_image;
			return *this;
		}
		complex operator++(int)/* x++*/ 
		{
			complex temp(*this);
			++_real;
			++_image;
			return temp;
		}
};

#if 0 
int operator+(int x,int y) /* 运算符的基本内置功能不能重载*/
{
	return x+y;
}
#endif
complex operator+(complex x,complex y)//重载友元函数的运算符重载函数，只能自由函数做友元函数的形式
{
	return complex(x._real+y._real,y._image+x._image);
}
int  main()
{
	complex c1(1,1);
	complex c2(2,2);
	complex c=c1+c2;
	c1.print();
	c2.print();
	c.print();
	c=c1-c2;
	c.print();
	c++;
	c.print();
	++c;
	c.print();
	c=c1+c2++;
	c.print();
	c2.print();
	c=c1+(++c2);
	c.print();
	c2.print();

	complex c3=c1-5;
	/*complex c4=5-c1;//对于重载为成员函数的运算符重载，不能采取这种方式的，因为5不会转为对象*/
	return 0;
}
