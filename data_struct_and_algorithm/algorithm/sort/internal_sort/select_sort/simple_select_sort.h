#pragma once
#ifndef MY_SIMPLE_SELECT_SORT_H
#define MY_SIMPLE_SELECT_SORT_H

#endif /* end of include guard: MY_SIMPLE_SELECT_SORT_H */

void simple_select_sort(int a[], int n)
{
	int i = 0,
	    j = 0,
	    temp = 0,
	    min = 0;
	for(i = 0; i < n-1; ++i)
	{
		min = i;
		for(j = i + 1; j < n; ++j)
		{
			if(a[j] < a[min])
				min = j;
		}
		if( min != i )
		{
			temp = a[min];
			a[min] = a[i];
			a[i] = temp;

		}
	}
}
