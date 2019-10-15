#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H
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
	bool insert(int pos, T e);//在位置pos上插入e
	bool del(int pos, T & e);//删除位置pos的 元素
	bool del(T e);//删除值为e的元素
	bool clear(void);//清空元素
	int  size(void) const;//返回元素个数
	bool empty(void) const;//为空
	bool full(void) const;//为满
	bool find(T e, int & pos) const;//返回第一个e出现的位置
	void display(void)const;//显示所有元素
};

template<typename T>
sqList<T>::sqList(int n):data(new T[n]()),capacity(n),length(0)
{

}











#endif /* end of include guard: MY_SQLIST_H */
