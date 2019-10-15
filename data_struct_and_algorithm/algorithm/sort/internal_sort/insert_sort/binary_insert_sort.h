#pragma once
#ifndef MY_BINARY_INSERT_H
#define MY_BINARY_INSERT_H
void binary_insert_sort(int a[], int n)
{
	int i = 0,
	    j = 0,
	    temp = 0,
	    low = 0,
	    high = 0,
	    mid = 0;
	for(i = 1; i < n ; ++i)
	{
		if(a[i] < a[i-1])
		{
			low = 0;
			high = i-1;
			temp = a[i];
			while(low <= high)
			{
				mid = (low + high ) /2;
				if(a[mid] > temp)
					high = mid - 1;
				else
					low = mid + 1;
			}
			for(j = i -1; j > high; --j) 
				a[j + 1] = a[j];
			a[high + 1] = temp;
		}

	}
}
#endif /* end of include guard: MY_BINARY_INSERT_H */
