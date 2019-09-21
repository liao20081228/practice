//第一次排序完成后将分割元素放在其最终位置，左边都是小于它的，右边都是大于它的
//对左边子序列，右边子序列分别快排
//时间：最好O（nlog2 n）， 最坏O（n^2），平均O（nlog2 n)
//空间:最好O（log2 n）,最坏o(n),平均O(log2 n)
void quick_sort(int a[], int low, int high)
{
	if (low >= high)
		return;
	int pos=a[low];
	int i=low;
	int j=high;
	while(i< j)
		while(i<j&& a[j]>=pos )
			j--;
		a[i]=a[j];
		while(i<j&& a[i]<=pos)
			i++;
		a[j]=a[i];
	a[i]=pos;
	quick_sort(a,low,i-1);
	quick_sort(a,i+1,high);
	
}
