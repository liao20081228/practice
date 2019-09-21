void buble_sort(int a[], int n)
{
	int i,j,temp,flag;
	for (i = 0; i < n-1; ++i) //因为判断a[i]>a[i+1],所以只需取到n-2即可
	{
		flag = 0;
		for ( j = 0; j < n - 1 -i; ++j)
		{
			if (a[j] > a[j+1])
			{
				temp=a[j+1];
				a[j+1]=a[j];
				a[j]=temp;
				flag=1;
			}
		}
		if(!flag)
			break; //或者  return

	}
}
