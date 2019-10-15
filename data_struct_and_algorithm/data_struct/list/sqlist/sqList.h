#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H

#include<stdio.h>


struct _sqList
{
	int * sqList;
	int capacity;
	int length;

	bool (*initialize)(int n);



};











#endif /* end of include guard: MY_SQLIST_H */
