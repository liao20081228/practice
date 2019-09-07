//假设一个序列的前i个元素个有序，将第i+1个元素插入该队列，
//然后将第i+2插入前面有i+1元素的有序序列
//重复，直到最后一个元素插入，则整个序列有序
void direct_insert_sort(int array[], int n)
{
	int temp = 0, i,j;
	for (i = 1 ; i < n; ++i)
	{
		if (array[i]<array[i-1])
		{
			temp=array[i];
			for (j = i-1 ; array[j] > temp && j >= 0; --j)
			{
				array[j+1] =array[j];
			}
			array[j]=temp;
		}
	}
}
