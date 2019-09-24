#include<string.h>
#include<iostream>
int *b=new int[10]();
void merge(int a[], int n,int low ,int mid ,int high)
{
	//int* b = new int[n];
	memcpy(b, a, n*sizeof(a[0]));
	int i,j,k;
	for( i =low ,j=mid+1,k=i; i<=low && j <= high;k++)
		if (b[i] < b[j])
			a[k]=b[i++];
		else
			a[k]=b[j++];
	while(i <=mid) 
		a[k++]=b[i++];
	while(j<=high)
		a[k++]=b[j++];
	//delete[] b;
}
void merge_sort(int a[],int n,int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		merge_sort(a,n,low, mid);
		merge_sort(a,n,mid+1, high);
		merge(a,n,low,mid,high);
	}
}


int main()
{
	int a[]={1,3,9,7,15,2,6,8,11,10};
	merge_sort(a,10,0,9);
	for(int e: a)
		std::cout << e <<",";
}
