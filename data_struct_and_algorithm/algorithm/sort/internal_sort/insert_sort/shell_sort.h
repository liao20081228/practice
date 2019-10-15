#pragma once
#ifndef MY_SHELL_SORT_H
#define MY_SHELL_SORT_H

void shell_sort(int a[], int n)
{
	int i = 0,
	    j = 0,
	    d = 0,
	    temp = 0;
	for( d = n/2; d >= 1; d/=2 )
	{
		for(i = d; i < n; ++i)
		{
			if( a[i] < a[i - d] )
			{
				temp = a[i];
				for(j = i - d; j >= 0 && a[j] > temp; j-=d )
					a[j + d] = a[j];
				a[j + d] =temp;
			}

		}
	}
}

#endif /* end of include guard: MY_SHELL_SORT_H */
