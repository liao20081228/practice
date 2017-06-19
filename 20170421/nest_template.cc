/*************************************************************************
    > File Name: nest_template.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月24日 星期一 11时27分15秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T=int>
class test
{
	public:
	template<typename F,int size>  /* 类模板放在另一个类模板中*/
	class stack;
	template<typename D>     /* 函数模板放在另一类模板中*/
	D add(D x,D y);
};

template<typename T>template<typename D>D test<T>::add(D x,D y)
{
	return x+y;
}

template<typename T>
template<typename F,int size>
class test<T>::stack
{
	private:
		F *_data;
		int _size;
		int _top;
	public:
		stack();
		~stack();
		bool Push(F element);
		bool Pop(F &element);
		F Pop();
		F & Gettop() const;
		bool Gettop(F &element) const;
		bool Isempty() const;
		bool Isfull() const;
};

template<typename T>
template<typename F,int size>
test<T>::stack<F,size>::stack():_data(new F[size]),_size(size),_top(-1)
{
}
template<typename T>
template<typename F,int size>
test<T>::stack<F,size>::~stack()
{
	if(_data!=NULL)
		delete []_data;
}

template<typename T>
template<typename F,int size>
bool test<T>::stack<F,size>::Push(F element)
{
	if(Isfull())
	{	
		cout<<"stack is full"<<endl;
		exit(-1);
	}
	_data[++_top]=element;
	return true;
}

template<typename T>
template<typename F,int size>
bool test<T>::stack<F,size>::Pop(F &element)
{
	if(Isempty())
	{	
		cout<<"stack is empty"<<endl;
		exit(-1);
	}
	element=_data[_top--];
	return true;
}
template<typename T>
template<typename F,int size>
F test<T>::stack<F,size>::Pop()
{
	if(Isempty())
	{	
		cout<<"stack is empty"<<endl;
		exit(-1);
	}
	return _data[_top--];
}
template<typename T>
template<typename F,int size>
bool test<T>::stack<F,size>::Isfull() const
{
	if(_top+1==_size)
		return true;
	else 
	{
		return false;
	}
}
template<typename T>
template<typename F,int size>
bool test<T>::stack<F,size>::Isempty() const
{
	if(_top==-1)
		return true;
	else 
	{
		return false;
	}
}
template<typename T>
template<typename F,int size>
F & test<T>::stack<F,size>::Gettop() const
{
	if(Isempty())
	{	
		cout<<"stack is empty"<<endl;
		exit(-1);
	}
	return _data[_top];
}

int  main()
{
	test<int>s;
	cout<<s.add<double>(1.1,2.1)<<endl;
	class test<int>::stack<int,5>s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	cout<<s1.Gettop()<<endl;
	cout<<s1.Pop()<<endl;
	cout<<s1.Isfull()<<endl;
	cout<<s1.Isempty()<<endl;
	
	return 0;
}
