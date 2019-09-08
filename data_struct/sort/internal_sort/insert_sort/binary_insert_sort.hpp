#include<iostream>
void binary_insert_sort( int array[], int n)
{
	int i = 0,
	    j = 0,
	    temp = 0,
	    low = 0,
	    high = 0,
	    mid = 0;
	for (i = 1; i < n; ++i)
	{
		if (array[i] < array [i-1])
		{
			temp = array[i];
			low = 0;
			high = i - 1;
			while( low <= high )
			{
				mid = (low + high) /2;
				if (array [mid] > temp)
					high = mid -1;
				else
					low = mid + 1; 
			}
			//array[high] 是要插入的位置的前一个元素
			for (j = i-1; j > high; --j)
				array[j+1] = array[j];
			array[high+1] = temp;
		}
	}
}
