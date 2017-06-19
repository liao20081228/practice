/*************************************************************************
  > File Name: RAII.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月09日 星期二 17时28分13秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T>
class RAII
{
	private:
		T *_p;
	public:
		explicit RAII(T *p=nullptr):_p(p)//构造函数
		{
			/*fucntion_body*/
		}
		T * get() const
		{
			return _p;
		}
		T & operator*()const 
		{
			return *_p;
		}
		T * operator->()
		{
			return _p;
		}
		void reset(T *p)
		{
			_p=p;
		}
		~RAII()//析构函数
		{
			if(_p)
				delete _p;
		}
		//private: /* 要删除摸个成员函数，可以直接放在private区，也可用=delete*/
		RAII(const RAII &ref)=delete;//拷贝构造函数
		RAII & operator=(const RAII &lref)=delete;//拷贝赋值运算符函数
};
class SomeResource
{
	public:
		SomeResource()
		{
			cout << "SomeResource()" << endl;
		}
		~SomeResource()
		{
			cout << "~SomeResource()" << endl;
		}
		void display()
		{
			cout << "SomeResource::display()" << endl;
		}
};

class Example
{
	private:
		RAII<SomeResource> _p1;
		RAII<SomeResource> _p2;

	public:
		Example(): _p1(new SomeResource()), _p2(new SomeResource())
		{}
		Example(const Example & rhs): _p1(new SomeResource(*(rhs._p1))) , _p2(new SomeResource(*rhs._p2))
		{}
		Example & operator=(const Example & rhs)
		{
			if(this != &rhs)
			{
				*_p1 = *rhs._p1;
				*_p2 = *rhs._p2;
			}
			return *this;
		}
		void print()
		{
			_p1.operator->()->display();
			_p2->display();
		}
};
int  main()
{
	Example ex;
	ex.print();

	return 0;
}
