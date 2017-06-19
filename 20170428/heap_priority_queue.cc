/*************************************************************************
    > File Name: heap.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月03日 星期三 22时54分13秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T=int>
class Priority_queue
{
	private:
		vector<T>_vec;
	public:
		Priority_queue(size_t n,...);  /* 可变参数函数*/
		Priority_queue(){_vec.push_back(0);};
		Priority_queue(const Priority_queue & lref)=delete;
		Priority_queue & operator=(const Priority_queue &lref) /* 拷贝赋值运算符函数*/
		{
			if(this==&lref)
				return *this;
			_vec=lref._vec;
			return *this;
		}
		Priority_queue & operator=(Priority_queue &&rref) /* 移动赋值运算符函数*/
		{
			if(this!=&rref)
			{
				std::swap(_vec,rref._vec);
			}
			return *this;
		}
	private:
		void AdjustUp()/* 节点插入到最后一个子节点后面*/
		{
			_vec[0]=_vec.back();
			size_t k=_vec.size();
			size_t i=k/2;/* 与自己的父节点比较*/
			while(i>0&&_vec[i]<_vec.front())/* 如果大于父节点，则与父节点交换*/
			{
				_vec[k-1]=_vec[i];
				k=i;
				i/=2;
			}
			_vec[k]=_vec.front();
		}
		void AdjustDown(size_t k)  /* 从该节点开始，依次与自己的子节点中较大者比较*/
		{
			_vec.front()=_vec[k];/* 第一个节点作为缓存*/
			for(size_t i=2*k;i<=_vec.size();i*=2)
			{
				if(i<_vec.size()&&_vec[i]<_vec[i+1])/* 找到子节点中的较大者*/
				{
					++i;
				}
				if(_vec.front()>=_vec[i])/* 作比较，如果大于或等于，说明该节点已经到了自己的位置*/
				{
					break;
				}
				else/* 否则就较大者交换*/
				{
					_vec[k]=_vec[i];
					k=i;
				}
			}
			_vec[k]=_vec.front();/* 以k节点为根节点的子树建成Priority_queue*/
		}
		void MakeMaxheap()
		{
			for(size_t i=_vec.size()/2;i>0;i--)  /* 从最后一个节点的双亲节点len/2开始到根节点，每个节点都调整*/
				AdjustDown(i);
		}
	public:
		T pop()
		{
			T temp=_vec[1];  /* 删除时首先获取堆顶元素值*/
			std::swap(_vec[1],_vec.back());/* 将堆顶节点与最后一个节点交换*/
			_vec.pop_back();/* 删除最后一个节点*/
			AdjustDown(1);/* 此时堆顶节点违背了aPriority_queue的原则需要向下调整*/
			return temp;
		}
		void push( T elem )
		{
			_vec.push_back(elem);/* 首先在最后一个元素之后插入*/
			AdjustUp();/* 再从最后一个节点向上调整*/
		}
		T  top() const
		{
			if(!empty())
				return _vec[1];
			exit(-1);
		}
		bool empty() const
		{
			return !(_vec.size()-1);
		}
		size_t size() const
		{
			return _vec.size()-1;
		}
		void empalce(T ele)
		{
			push(ele);
		}
		void swap(Priority_queue & ref)
		{
			_vec.swap(ref._vec);
		}
};

template<typename T>
Priority_queue<T>::Priority_queue(size_t n,...)  /* 可变参数函数*/
{
	_vec.push_back(0);
	va_list arg;
	va_start(arg,n);
	for(size_t i=0;i<n;i++)
		_vec.push_back(va_arg(arg,T));
	va_end(arg);
	MakeMaxheap();
}


int  main()
{
	Priority_queue<int> q(10,1,2,3,8,4,5,6,7,10,9);
	cout<<q.top()<<endl;
	q.pop();
	cout<<q.top()<<endl;
	q.push(100);
	cout<<q.top()<<endl;
	q.empalce(250);
	cout<<q.top()<<endl;
	cout<<q.empty()<<endl;
	cout<<q.size()<<endl;
}





