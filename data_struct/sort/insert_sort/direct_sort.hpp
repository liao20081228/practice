void direct_insert_sort(int array[], int n)
{
	int temp = 0, i,j;
	for (i = 1 ; i <= n-1; ++i)
	{
		if (array[i]<array[i-1])
		{
			temp=array[i];
			for (j = i ; array[j] > temp && j > 0; --j)
			{
				array[j] =array[j-1];
			}
			array[j]=temp;
		}
	}
}
