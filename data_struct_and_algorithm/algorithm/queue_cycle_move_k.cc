#include<iostream>
//左移k=右移n-b
//
void reverse(int a[], int n)
{
	for(int i=0,j=n-1;i<=j;++i,--j)
	{
		int temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
}
void fun(int a[],int dir,int n , int k)
{
	reverse(a,n);
	if (dir)//右移
	{
		reverse(a,k);
		reverse(&a[k],n-k);
	}
	else	//左移
	{
		reverse(a,n-k);
		reverse(&a[n-k],k);
	}
}


int main()
{
	int a[]={1,2,3,4,5,6};
	int b[]={1,2,3,4,5,6};
	fun(a,1,6,4);
	fun(b,0,6,2);

	for (int e : a)
		std::cout<<e<<",";
	for (int e:b)
		std::cout<<e<<",";
}
