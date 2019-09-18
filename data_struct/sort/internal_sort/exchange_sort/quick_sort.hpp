#include<iostream>

void quick_sort(int a[], int low , int high )
{
	if (low < high)
	{
		int i=low,j=high;
		int pos=a[i];

		while(i<j)
		{
			while(i<j&& a[j] >= pos)
				--j;
			a[i]=a[j];
			while(i<j &&  a[i] <= pos)
				++i;
			a[j]=a[i];
		}
		a[i]=pos;
		quick_sort(a,low,i-1);
		quick_sort(a,i+1,high);
	}
}


int main(void)
{
	int a[]={12,1,2,5,4,8,7,3};
	quick_sort(a,0,7);
	for(int e:a)
		std::cout<<e<<",";
	return 0;
}
