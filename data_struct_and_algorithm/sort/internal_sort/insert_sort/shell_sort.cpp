void shell_sort(int a[], int n)
{
	int i,j,temp,d;
	for (d = n/2; d >= 1; d/=2)
	{
		for ( i = d; i < n ; ++i)
		{
			if (a[i] < a[i-d])
			{
				temp = a[i];
				for (j = i-d ; j>=0 && a[j] > temp; j-=d)
				{

				}
			}
		}
	}
}
