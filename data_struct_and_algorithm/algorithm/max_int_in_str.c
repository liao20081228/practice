#include<stdio.h>
#include<string.h>
int main(void)
{
	char a[1000]={0};
	scanf("%s",a);
	int max=0;
	int len=1;
	int i=0;
	while(i<(int)strlen(a))
	{
		int count=1;
		while(a[i]>a[i+1])
		{
			i++;
			count++;
		}
		if (count > len)
		{
			len = count;
			max = i-count+1;
		}
		else if (count < len)
		{

		}
		else for (int m=max,n=i-count+1;m<max+len && n < i+1; )
		{
			if ( a[m]==a[n] )
			{
				m++;
				n++;
			}
			else 
			{
				max=a[m]>a[n]?m:n;
				break;
			}
		}
		++i;
	}
	for (i = max;i<max+len;i++)
	{
		printf("%c",a[i]);
	}
	return 0;
}
