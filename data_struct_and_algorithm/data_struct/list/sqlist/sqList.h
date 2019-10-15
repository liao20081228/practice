#pragma once
#ifndef MY_SQLIST_H
#define MY_SQLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct sqList
{
	int * data;
	int capacity;
	int length;
	
};

bool initialize(struct sqList* l,int n)
{
	if((l->data = (int*)malloc(sizeof(int) * n)))
	{
		return true; 
	}
	else
		return false;
}












#endif /* end of include guard: MY_SQLIST_H */
