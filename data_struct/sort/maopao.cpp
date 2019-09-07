#include<iostream>

void bubble_sort(int array[], int n)
{
	int temp=0;
	for (int i = 0; i < n-1; ++i)
	{
		bool flag=false;
		for(int j = n-1; j > i; --j)
		{
			if (array[j-1] > array[j])
			{
				temp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp;
				flag = true;
			}
		}
		for(int k=0;k<n;++k)
		{
			std::cout<< array[k] << ",";
		}
			std::cout<<"\n";
		if ( !flag )
			return ;
	}
}


int main(void)
{
	int a[]={7,5,4,28,1,9,4};
	bubble_sort(a,sizeof(a));
	return 0;
}
