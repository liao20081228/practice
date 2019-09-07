#include<iostream>

void buble_down_sort(int array[] , int n)
{
	int temp=0;
	bool flag=false;
	for ( int i = 0; i < n-1; ++i )
	{
		flag = false;
		for (int j=0;j < n-1-i;j++)
		{
			if (array[j] > array[j+1])
			{
				temp = array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				flag=true;
			}
		}
		if ( ! flag)
			return;
	}
}
