#include<iostream>
//思想：
//假设n个元素中前i个（i最初为1）有序，则只需把第i+1个元素插入前面的i个有序元素中，
//同时插入的位置之后的元素向后移动，则前i+1个元素也是有序的
//重复直到所有元素都有序
//时间复杂度O(n) 平均O(n^2) 最坏O(n^2) ,空间复杂度O(1) ，稳定
void direct_insert_sort(int array[], int n)
{
	int temp = 0,
	    i = 0,
	    j = 0;
	for (i = 1; i < n; ++i)
	{
		if (array[i] < array[i-1])
		{
			temp = array[i];
			for (j = i-1; j >= 0 && array[j] > temp; --j)
			{
				array[j+1] = array[j];
			}//array[j]是要插入位置的前一个位置
			array[j+1] = temp;
		}
	}
}
