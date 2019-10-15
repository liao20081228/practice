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
	
	bool insert_by_pos(int pos, int e);

	bool del_by_pos(int pos, int & e);
	bool del_by_val(int e);




};









#endif /* end of include guard: MY_SQLIST_H */
