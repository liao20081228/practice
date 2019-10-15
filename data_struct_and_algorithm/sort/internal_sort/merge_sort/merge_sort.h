#pragma once
#ifndef MY_MERGE_SORT_H
#define MY_MERGE_SORT_H

#endif /* end of include guard: MY_MERGE_SORT_H */
#include<stdlib.h>
#include<string.h>
void merge(int a[], int n, int low, int mid, int high)
{
	int* b=(int*)malloc(n * sizeof(int));
	memcpy(b, a, sizeof(int) * n);
}



void merge_sort(int a[], int n, int low , int high)
{
	if( low < high )
	{
		int mid = (low + high) / 2;
		merge_sort(a, n, low, mid );
		merge_sort(a, n, mid + 1, high);
		merge(a, n, low, mid, high);
	}
}
