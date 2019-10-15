#pragma once
#ifndef MY_QUICK_SORT_H
#define MY_QUICK_SORT_H
#endif /* end of include guard: MY_QUICK_SORT_H */

void quick_sort(int a[], int low, int high)
{
	if(low >= high)
		return ;
	int i = low,
	j = high,
	pos = a[low];
	while(i < j)
	{
		while(i < j && a[j] >= pos) 
			--j;
		a[i] = a[j];
		while( i < j && a[i] <= pos)
			++i;
		a[j] =  a[i];
	}
	a[i] = pos;
	quick_sort(a, i + 1, high);
	quick_sort(a, low, i - 1);
}
