#include<iostream>
//一个序列A1,A2,...,An，按增量d分割为[A1,A2,...,Ad-1],[Ad,Ad+1,...,A2d-1],...
//对于 Ai,Ai+d，...,Ai+kd，（i是0~d-1）这样的子序列
//对这些子序列直接插入排序
//然后缩小增量，重复以上步骤，直到d=1
//某些时候，时间复杂度为O(n^1.3),最坏为O(n^2)，空间复杂度O(1)， 不稳定
void shell_sort(int array[], int n)
{
	int temp=0,d=0,i=0,j=0;
	for (d = n / 2; d>=1; d/=2 )
	{
		for ( i = d;i < n;++i)
		{
			if (array [i] < array[i-d])
			{
				temp = array[i];
				for ( j = i - d; j >= 0 && array[j] > temp; j-=d)
				{
					array[j+d] = array[j];
				}
				array[j+d]=temp;
			}
		}
	}
}
