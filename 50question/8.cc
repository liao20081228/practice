#include<myhead_cpp.h>
int main(void)
{
	int a=0,n=0,sum=0;
	cin >> a>>n;
	for (int i=1;i<=n;++i)

	{
		sum+=a*pow(10,i-1)*(n-i+1);	
	}
	cout << sum <<endl;
	return 0;
}
