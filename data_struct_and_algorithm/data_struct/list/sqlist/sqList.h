#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H

#include<stdio.h>
#include<stdlib.h>

struct _sqList
{
	int * sqList;
	int capacity;
	int length;

	int initialize(int n)
	{
		sqList = (int*)malloc(sizeof(int) * n);
		if(sqList)
			return 1;
		else
			return 0;
	}
};










#endif /* end of include guard: MY_SQLIST_H */
