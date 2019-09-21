//把Ai和Ai+1比较，如果Ai>Ai+1，则交换位置，i为0~n-2
//一趟排序完成后，最大值位于最后，下一次只是排序前n-1个元素
//时间：最好O（n），最坏O（n^2），平均O（n^2）
//空间：O（1）
//稳定



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
