#pragma once
#ifndef MY_MERGE_SORT_H
#define MY_MERGE_SORT_H

#include<stdlib.h>
#include<string.h>
void merge(int a[], int n, int low, int mid, int high)
{
	int* b=(int*)malloc(n * sizeof(int));
	memcpy(b, a, sizeof(int) * n);
	
	int i,j,k;
	for( i = low, j = mid + 1, k = i; i <= mid && j <= high; ++k)
	{
		if( b[i] < b[j] )
			a[k] = b[i++];
		else
			a[k] = b[j++];
	}
	while(i <= mid)
		a[k++]=b[i++];
	while(j <= high)
		a[k++]=b[j++];
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
#endif /* end of include guard: MY_MERGE_SORT_H */
