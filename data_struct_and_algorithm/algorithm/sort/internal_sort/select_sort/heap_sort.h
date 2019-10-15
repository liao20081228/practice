#pragma once
#ifndef MY_HEAP_SORT_H
#define MY_HEAP_SORT_H



void adjust_down(int a[], int n ,int k)
{

	a[0] = a[k];
	for(int i = 2 * k; i <= n; i*=2)
	{
		if(a[i] < a[i +1] && i < n)
			++i;
		if(a[0] > a[i])
			break;
		else
		{
			a[k]=a[i];
			k = i;
		}

	}
	a[k]= a[0];
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
		adjust_down(a, i - 1, 1);
	}
}
#endif /* end of include guard: MY_HEAP_SORT_H */
