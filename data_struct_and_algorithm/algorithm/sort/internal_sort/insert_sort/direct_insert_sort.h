#pragma once
#ifndef MY_DIRECT_INSERT_SORT_H
#define MY_DIRECT_INSERT_SORT_H
#endif /* end of include guard: MY_DIRECT_INSERT_SORT_H */

void direct_insert_sort(int a[], int n)
{
	int i = 0,
	    j = 0,
	    temp = 0;
	for(i = 1;i < n; ++i)
	{
		if(a[i] < a[i - 1])
		{
			temp = a[i];
			for(j = i - 1; j >= 0 && a[j] > temp; --j)
				a[j + 1] = a[j];
			a[j+1] = temp;
		}
	}
}
