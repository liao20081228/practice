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
			cout<<_real<<"+"<<_image<<"i"<<endl;
		}
};
int  main()
{
	complex c1(1,1);
	complex c2(2,2);
	complex c=c1+c2;
	c.print();
	return 0;
}
