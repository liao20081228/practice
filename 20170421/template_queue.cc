/*************************************************************************
    > File Name: template_queue.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月24日 星期一 16时56分59秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T,int size>
class Queue
{
	private:
		long int _rear,_front;
		long int _size;
		T *_data;
	public:
		Queue(/*arguments*/):_rear(-1),_front(-1),_size(size+1),_data(new T[_size])//构造函数
		{
		}
		~Queue()//析构函数
		{
			if(_data!=NULL)
				delete []_data;
		}
		Queue(const Queue &ref):_rear(ref._rear),_front(ref._front),_size(ref._size),_data( new T[_size])//拷贝构造函数
		{
			memcpy(_data,ref._data, _size);
		}
		Queue & operator=(const Queue &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			delete []_data;
			_rear=ref._rear;
			_front=ref._front;
			_size=ref._size;
			memcpy(_data,ref._data, _size);
			return *this;
		}
		bool Enqueue(T element);
		bool Dequeue(T &element);
		T &  Dequeue();
		bool Isempty() const;
		bool Isfull() const;
		bool Getrear(T & element)const;
		bool Getfront(T & element)const;
		T & Getrear()const;
		T & Getfront()const;
		size_t  Capacity()const;
		size_t  Length()const;
};
template<typename T,int size>
bool Queue<T,size>::Enqueue(T element)
{
	if(Isfull())
	{
		cout<<"Queue is full"<<endl;
		exit(-1);
	}
	_rear=(_rear+_size+1)%_size;
	_data[_rear]=element;
	return true;
}
template<typename T,int size>
bool Queue<T,size>::Dequeue(T &element)
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	_front=(_front+_size)%_size;
	element=_data[_front];
	return true;
}
template<typename T,int size>
T & Queue<T,size>::Dequeue()
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	_front=(_front+_size+1)%_size;
	return _data[_front];
}
template<typename T,int size>
bool Queue<T,size>::Isfull()const
{
	if((_rear+_size+1)%_size==_front)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
template<typename T,int size>
bool Queue<T,size>::Isempty()const
{
	if(_rear==_front)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
template<typename T,int size>
bool Queue<T,size>::Getfront(T &element) const
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	element=_data[(_front+_size+1)%_size];
	return true;
}
template<typename T,int size>
T& Queue<T,size>::Getfront() const
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	return _data[(_front+_size+1)%_size];
}
template<typename T,int size>
bool Queue<T,size>::Getrear(T &element) const
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	element=_data[_rear];
	return true;
}
template<typename T,int size>
T& Queue<T,size>::Getrear() const
{
	if(Isempty())
	{
		cout<<"Queue is empty"<<endl;
		exit(-1);
	}
	return _data[_rear];
}

template<typename T,int size>
size_t Queue<T,size>::Capacity() const
{
	return _size-1;
}

template<typename T,int size>
size_t Queue<T,size>::Length() const
{
	return (_rear-_front+_size)%_size;
}

int  main()
{
	Queue<int,10>Q1;
	for (size_t i = 0; i < Q1.Capacity(); ++i) 
	{
		Q1.Enqueue(i);
	}
	cout<<"full? "<<Q1.Isfull()<<endl;
	cout<<"empty? "<<Q1.Isempty()<<endl;
	cout<<"Capacity: "<<Q1.Capacity()<<endl;
	cout<<"Length: "<<Q1.Length()<<endl;
	cout<<"rear element: "<<Q1.Getrear()<<endl;
	cout<<"front element: "<<Q1.Getfront()<<endl;
	
	for (size_t i = 0; i <3; ++i) 
	{
		cout<<"delete element: "<<Q1.Dequeue()<<endl;
	}
	cout<<"full? "<<Q1.Isfull()<<endl;
	cout<<"empty? "<<Q1.Isempty()<<endl;
	cout<<"Capacity: "<<Q1.Capacity()<<endl;
	cout<<"Length: "<<Q1.Length()<<endl;
	cout<<"rear element: "<<Q1.Getrear()<<endl;
	cout<<"front element: "<<Q1.Getfront()<<endl;
	
	return 0;
}
