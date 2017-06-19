/*************************************************************************
    > File Name: operator_overload_array.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月18日 星期二 21时39分40秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class arr
{
	private:
		size_t _maxsize;
		char *_p;
	public:
		arr(size_t sz):_maxsize(sz),_p(new char[sz])//构造函数
		{
			memset(_p,'\0',sizeof(*_p));
		}
		size_t  size()const
		{
			return _maxsize;
		}
		~arr()//析构函数
		{
			delete []_p;
		}
		arr(const arr &ref):_maxsize(ref._maxsize),_p(new char[strlen(ref._p)+1])//拷贝构造函数
		{
			strcpy(_p,ref._p);
		}
		arr & operator=(const arr &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			delete []_p;
			_maxsize=ref._maxsize;
			_p=new char[strlen(ref._p)+1];
			strcpy(_p,ref._p);
			return *this;
		}
		char & operator[](size_t idx)
		{
			static char nullchar='\0';
			if(idx>=_maxsize)
			{
				return nullchar;
			}
			return _p[idx];
		}
		void print()
		{
			cout<<_p<<endl;
		}
		
};

int  main()
{
	const char *p="hello world!";
	arr a(strlen(p));
	for (size_t i = 0; i <= strlen(p); ++i) 
	{
		a[i]=p[i];
	}
	a.print();
	return 0;
}
