#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H
#include<stdlib.h>
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
void sqList<T>::clear(void)
{
	memset(data, 0, sizeof(T)*capacity);
}


template<typename T>
bool sqList<T>::resize(int n)
{
	T* temp=data;
	data=new T[n]();
	if(data)
	{
		delete []temp;
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
	if(capacity == length && !resize(capacity*2))
		return false;
	for(int i=length; i >= pos ;--i)
		data[i]=data[i-1];
	data[pos-1]=e;
	return true;
}

template<typename T>
bool sqList<T>::del(int pos, T&e)
{
	if (pos >= length || pos < 1)
		return false;
	e=data[pos-1];
	for(int i=pos-1;i<length-1;++i)
		data[i]=data[i+1];
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




#endif /* end of include guard: MY_SQLIST_H */
