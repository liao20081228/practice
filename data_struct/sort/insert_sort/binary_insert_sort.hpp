void binary_insert_sort(int array[], int n)
{
	int i,j,low,high,mid,temp;
	for (i= 1; i<= n-1; ++i)
	{
		if (array[i] < array[i-1])
		{
			temp=array[i];
			low=0;
			high=i-1;
			while( low <= high )
			{
				mid=(low+high)/2;
				if (array[mid]>temp)
					high=mid-1;
				else
					low=mid+1;
			}
			for(j=i-1;j>=high+1;--j)
			{
				array[j+1]=array[j];
			}
			array[high+1]=temp;
		}
	}
}
