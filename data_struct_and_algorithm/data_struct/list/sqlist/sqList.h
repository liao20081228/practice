#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H

#include<stdio.h>
#include<stdlib.h>

struct sqList
{
	int * sqList;
	int capacity;
	int length;
	
};

bool initialize(struct sqList l,int n)
{
	if((l.sqList = (int*)malloc(sizeof(int) * n)))
	{
		return 
	}
	
}











#endif /* end of include guard: MY_SQLIST_H */
