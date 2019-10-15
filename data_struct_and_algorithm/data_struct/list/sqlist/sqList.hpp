#pragma once
#ifndef MY_SQLIST_HPP
#define MY_SQLIST_HPP
#include<cstdlib>
#include<iostream>
#include<cstring>
template<typename T>
class sqList
{
	T *  data;
	int capacity;
	int length;
public:
	sqList(int n=1);
	~sqList(void);

	bool resize(int n);//重新分配大小
	bool insert(T e, int pos);//在位置pos上插入e
	bool del(int pos, T & e);//删除位置pos的 元素
	void del(T e);//删除值为e的元素
	void clear(void);//清空元素
	int  size(void) const;//返回元素个数
	bool empty(void) const;//为空
	bool full(void) const;//为满
	int find(T e) const;//返回第一个e出现的位置
	void display(void)const;//显示所有元素
};

template<typename T>
sqList<T>::sqList(int n):data(new T[n]()),capacity(n),length(0)
{
	if (!data)
	exit(-1);
}

template<typename T>
sqList<T>::~sqList(void)
{
	if(data)
	{
		delete[]data;
		data=NULL;
	
	}
}
template<typename T>
void sqList<T>::clear(void)
{
	memset(data, 0, sizeof(T)*capacity);
	length=0;
}


template<typename T>
bool sqList<T>::resize(int n)
{
	T* temp=data;
	data=new T[n]();
	if(data)
	{
		memcpy(data,temp,sizeof(T)*length);
		delete []temp;
		capacity=n;
		return true;
	}
	else
	{
		data=temp;
		return false;
	}
}



template<typename T>
bool sqList<T>::insert(T e, int pos)
{
	if(pos>=length+2 || pos <1)
		return false;
	if(full() && !resize(capacity*2))
		return false;
	for(int i=length; i >= pos ;--i)
		data[i]=data[i-1];
	data[pos-1]=e;
	++length;
	return true;
}

template<typename T>
bool sqList<T>::del(int pos, T&e)
{
	if (pos >= length || pos < 1 )
		return false;
	e=data[pos-1];
	for(int i=pos-1;i<length-1;++i)
		data[i]=data[i+1];
	--length;
	return true;
}

template<typename T>
void sqList<T>::del(T e)
{
	int pos=0;
	T c;
	while((pos=find(e)) != -1)
	{
		del(pos,c);
	}
}

template<typename T>
int sqList<T>::size(void) const
{
	return length;
}

template<typename T>
bool sqList<T>::full(void) const
{
	return length==capacity;
}

template<typename T>
bool sqList<T>::empty(void) const
{
	return !length;
}


template<typename T>
int sqList<T>::find(T e)const
{
	if (empty())
		return -1;
	for(int i=0; i < length; ++i)
		if(e== data[i])
			return i;
	return -1;

}

template<typename T>
void sqList<T>::display(void)const
{
	for(int i=0;i<length;++i)
		std::cout<<data[i]<<",";
	std::cout<<std::endl;
}

#endif /* end of include guard: MY_SQLIST_H */
