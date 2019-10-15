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

	bool resize(int n);
	bool insert(int pos, T e, bool direction);
	bool del(int pos, T & e);
	bool del(T e);
	bool clear(void);
	int size(void) const;
	bool empty(void) const;
	bool full(void) const;
	bool find(T e, int & pos) const;
};









#endif /* end of include guard: MY_SQLIST_H */
