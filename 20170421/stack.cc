/*************************************************************************
  > File Name: stack.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月24日 星期一 09时37分21秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class stack
{
	private:
		int *_data;
		int _top;
		int _size;
	public:
		stack(int size):_data(new int[size]),_top(-1),_size(size)//构造函数
		{
		}
		~stack()//析构函数
		{
			delete []_data;
		}
		stack(const stack &ref):_data(new int[ref._size]),_top(ref._top),_size(ref._size)//拷贝构造函数
		{
			memcpy(_data,ref._data, _size);
		}
		stack & operator=(const stack &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			delete []_data;
			_data=new int[ref._size];
			_top=ref._top;
			_size=ref._size;
			memcpy(_data,ref._data, _size);
			return *this;
		}
		bool Isfull()  const
		{
			if(_top+1==_size)
				return true;
			else
				return  false;
		}
		bool Isempty() const
		{
			if(_top==-1)
				return true;
			else 
			{
				return false;
			}
		}
		bool Push(int element)
		{
			if(Isfull())
			{
				cout<<"stack is fulled"<<endl;
				exit(-1);
			}
			_data[++_top]=element; /* 指针指向当前元素*/
			return true;
		}
		bool Pop(int &element)
		{
			if(Isempty())
			{
				cout<<"stack is emptyed"<<endl;
				exit(-1);
			}
			element=_data[_top--];
			return true;
		}
		int  Pop()
		{
			if(Isempty())
			{
				cout<<"stack is emptyed"<<endl;
				exit(-1);
			}
			return _data[_top--];
		}
		int Gettop()
		{
			if(Isempty())
			{
				cout<<"stack is emptyed"<<endl;
				exit(-1);
			}
			return _data[_top];
		}
};
int  main()
{
	stack s(5);
	cout<<s.Isempty()<<endl;
	cout<<s.Isfull()<<endl;
	s.Push(5);
	s.Push(4);
	s.Push(3);
	s.Push(2);
	s.Push(1);
	cout<<s.Isempty()<<endl;
	cout<<s.Isfull()<<endl;
	cout<<s.Pop()<<endl;
	cout<<s.Gettop()<<endl;
	return 0;
}
