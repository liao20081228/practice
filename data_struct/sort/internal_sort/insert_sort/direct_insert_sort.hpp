#include<iostream>

void direct_insert_sort(int array[], int n)
{
	int temp = 0,
	    i = 0,
	    j = 0;
	for (i = 1; i < n; ++i)
	{
		if (array[i] < array[i-1])
		{
			temp = array[i];
			for (j = i-1; j >= 0 && array[j] > temp; --j)
			{
				array[j+1] = array[j];
			}
			array[j+1] = temp;

		}
	}
}
