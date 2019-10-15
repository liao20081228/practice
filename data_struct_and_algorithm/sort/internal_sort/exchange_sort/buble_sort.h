#pragma once
#ifndef MY_BUBLE_SORT_H
#define MY_BUBLE_SORT_H
#endif
void buble_sort(int* a, int n)
{
	int i = 0, 
	    j = 0,
	    flag = 0,
	    temp = 0;
	for(i = 0; i < n-1; ++i)
	{
		flag = 0;
		for(j = 0; j < n - 1 - i; ++j)
		{
			if(*(a + j) > *(a + j +1))
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		if (!flag)
			return;
	}	
}
