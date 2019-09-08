#include<iostream>

void direct_insert_sort(int array[], int n)
{
	int temp = 0;
	for (int i = 1; i < n; ++i)
	{
		if (array[i] < array[i-1])
		{
			temp = array[i];
			for (int j = i-1; j >= 0 && array[j] > temp; --j)
			{
				array[j+1] = array[j];
			}

		}
	}
}
