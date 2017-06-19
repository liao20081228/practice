/*************************************************************************
  > File Name: vector.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月07日 星期日 18时48分55秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T>
class Vector
{
	private:
		static std::allocator<T> _alloc;
		T *_first;/* 指向起始位置*/
		T *_elem; /* 指向最后元素的下一个*/
		T *_end;/* 指向结束位置*/
		void reallocate()
		{
			size_t _oldcapacity=capacity();
			size_t _newcapacity=_oldcapacity>0?2*_oldcapacity:1;
			T *_p=_alloc.allocate(_newcapacity);
			std::uninitialized_copy(_first,_elem,_p);
			while(_elem!=_first)
				_alloc.destroy(--_elem);
			_alloc.deallocate(_first,_oldcapacity);
			_first=_p;
			_elem=_first+_oldcapacity;
			_end=_first+_newcapacity;
		}
	public:
		Vector(/*arguments*/):_first(NULL),_elem(NULL),_end(NULL)//构造函数
		{
		}
		~Vector()//析构函数
		{
			while(size())
				_alloc.destroy(--_elem);
			_alloc.deallocate(_first,capacity());
		}
		Vector(const Vector &ref)//拷贝构造函数
		{
			cout<<"Vector(const Vector &ref)"<<endl;
			T * _p=_alloc.allocate(ref.capacity());
			std::uninitialized_copy(ref._first,ref._elem,_p);
			_first=_p;
			_elem=_first+ref.size();
			_end=_first+ref.capacity();
		}
		Vector (Vector && ref)//移动构造函数
		{
			cout<<"Vector(const Vector &&ref)"<<endl;
			_first=ref._first;
			_end=ref._end;
			_elem=ref._elem;
			ref._first=NULL;
			ref._elem=NULL;
			ref._end=NULL;
		}
		Vector & operator=(const Vector &ref)//赋值运算符函数
		{
			cout<<"Vector & operator=(const Vector &ref)"<<endl;
			if(this!=&ref)
			{
				while(size())
					_alloc.destroy(--_elem);
				_alloc.deallocate(_first,capacity());
				_first=_alloc.allocate(ref.capacity());
				std::uninitialized_copy(ref._first,ref._elem,_first);
				_elem=_first+ref.size();
				_end=_first+ref.capacity();
			}
			return *this;
		}
		Vector & operator=( Vector &&ref)//移动赋值运算符函数
		{
			cout<<"Vector & operator=(const Vector&&ref)"<<endl;
			if(this!=&ref)
			{
				_first=ref._first;
				_end=ref._end;
				_elem=ref._elem;
				ref._first=NULL;
				ref._elem=NULL;
				ref._end=NULL;
			}
			return *this;
		}
		size_t capacity()const
		{
			return _end-_first;
		}
		size_t size() const
		{
			return _elem-_first;
		}
		T & operator[](const T index)
		{
			return *(_first+index);
		}
		void push_back(const T & ref)
		{
			if(size()==capacity())
				reallocate();
			_alloc.construct(_elem++,ref);
		}
		void pop_back()
		{
			if(size())
				_alloc.destroy(--_elem);
		}
};
template<typename T>
std::allocator<T> Vector<T>::_alloc;


void display(Vector<int> & vec)
{
	for(size_t idx = 0; idx != vec.size(); ++idx)
	{
		cout << vec[idx] << " ";
	}
	cout << endl;
}
void print(Vector<int> & vec)
{
	cout << "vec's size = " << vec.size() << endl;
	cout << "vec's capa = " << vec.capacity() << endl;
}

Vector<int> test()
{
	Vector<int> vec;
	for (int i = 95; i < 100; ++i) 
	{
		vec.push_back(i);
	}
	return vec;
}


int main(void)
{
	Vector<int> vecInt;
	for (int i = 1; i <=9; ++i) 
	{
		vecInt.push_back(i);
		print(vecInt);
		cout<<endl;
	}
	display(vecInt);

	Vector<int>vecint2;
	vecint2=vecInt;
	display(vecint2);
	
	Vector<int>vecint3(vecInt);
	display(vecint3);
/* 编译时要加上-fno-elide-constructors才能看见具体调用过程*/
	Vector<int>vecint4=test();
	display(vecint4);
	
	Vector<int>vecint5=test();
	display(vecint5);
	
	vecint4=test();
	display(vecint4);
		
	return 0;


}

