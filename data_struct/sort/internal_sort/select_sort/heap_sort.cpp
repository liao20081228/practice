#include<iostream>

void adjust_down(int a[], int k, int n)
{

}
void build_max_heap(int a[], int n)
{
	for(int i=n/2;i > 0 ; i--)
	{
		adjust_down(a,i,n);
	}
}
void heap_sort(int a[], int n)
{
	build_max_heap(a,n);
	for(int i =n; i>1;i--)
	{
		a[0]=a[1];
		a[1]=a[i];
		a[i]=a[0];
		adjust_down(a,1,i-1);
	}
}







