#pragma once
#ifndef MY_HEAP_SORT_H
#define MY_HEAP_SORT_H

#endif /* end of include guard: MY_HEAP_SORT_H */


void adjust_down(int a[], int m ,int k)
{

}



void build_max_heap(int a[], int n)
{
	for(int i = n/2; i > 0; --i)
		adjust_down(a, n, i);
}


void heap_sort(int a[] , int n)
{
	build_max_heap(a, n);
	for(int i = n; i > 1;--i)
	{
		a[0] = a[i];
		a[i] = a[1];
		a[1] = a[0];
		adjust_down(a, n, 1);
	}
}
