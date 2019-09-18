void select_sort(int a[],int n)
{
	int min=0,temp=0;;
	for (int i=0; i< n-1 ;++i)
	{
		min=i;
		for (int j = i+i; j<n;++j)
		{
			if ( a[j] < a[min] )
			{
				min=j;
			}

		}
		if (min != i )
		{
			temp=a[min];
			a[min]=a[i];
			a[i]=temp;
		}

	}
}
