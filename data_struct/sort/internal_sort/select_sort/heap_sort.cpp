#include<iostream>
void adjust_up(int a[], int k)
{
	a[0]=a[k];
	int i=k/2;
	while(i>0 && a[i]<a[0])
	{
		a[k]=a[i];
		k=i;
		i=k/2;
	}
	a[k]=a[0];


}
void adjust_down(int a[], int k, int n)
{
	a[0]=a[k];
	for(int i=2*k;i<=n;i*=2)
	{
		if (i<n && a[i]<a[i+1])
			i++;
		if(a[0]>a[i])
			break;
		else
		{
			a[k]=a[i];
			k=i;
		}
		
	a[k]=a[0];
	}
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







