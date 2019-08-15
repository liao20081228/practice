#include<myhead_cpp.h>

float wanquan1(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;++i)
	{
		sum=0;
		for ( int j=1;j<i;++j )
			if (i % j==0 )
				sum+=j;
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}


float wanquan2(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;++i)
	{
		sum=1;
		for ( int j=2;j*2<=i;++j ) //1.一个数的因子除了1和本身，最大只能是n/2，
					   // 2.每个数都有因子1，所以只需要从2开始
			if (i % j==0 )
				sum+=j;
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}


float wanquan3(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;i+=2) //完全数性质，都为偶数 10^300
	{
		sum=1;
		for ( int j=2;j*j<=i;++j )//优化3，一个数的因数总是成对出现的，i=j*k,因此求出一个因数后另一个因数就不必再求
				          //此外，一个数的因数总是位于1~sqrt（n），另一个因数位于sqrt（n）~n之间,弹药注意处理1和本身是约束的问题
					  //内层循环，要么不算1，要么算完后减去1
			if (i % j==0 )
			{
				sum+=j;
				sum+=i/j;
			}  
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}


float wanquan4(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;i+=2) //在n<10^1500，完全数都为偶数
	{
		sum=1;
		for ( int j=2;j*j<=i/*优化3*/;++j )//优化3，一个数的因数总是成对出现的，i=j*k,因此求出一个因数后另一个因数就不必再求
				          //此外，一个数的因数总是位于1~sqrt（n），另一个因数位于sqrt（n）~n之间,弹药注意处理1和本身是约束的问题
					  //内层循环，要么不算1，要么算完后减去1
			if (i % j==0 )
			{
				sum+=j;
				sum+=i/j;
			}  
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}


float wanquan5(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;++i) //优化4，完全数的性质：完全数位数要么是6，要么是28
	{
		sum=1;
		for ( int j=2;j*j<=i && (i%10==6 || i% 100 == 28);++j ) 
			if (i % j==0 )
			{
				sum+=j;
				sum+=i/j;
			}
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}


float wanquan6(int n)
{
	clock_t time1=clock();
	int sum=0;
	for (int i=6;i<=n;i+=10) //完
	{
		sum=1;
		for ( int j=2;j*j<=i ;++j ) //一个数的因子除了1和本身，最大只能是n/2，
					    //每个数都有因子1，所以只需要从2开始
			if (i % j==0 )
			{
				sum+=j;
				sum+=i/j;
			}
		if (sum == i)
			cout << i<<",";
		
	}
	for (int i=28;i<=n;i+=100) //完全数的性质：完全数位数要么是6，要么是28
	{
		sum=1;
		for ( int j=2;j*j<=i ;++j ) //一个数的因子除了1和本身，最大只能是n/2，
					  //每个数都有因子1，所以只需要从2开始
			if (i % j==0 )
			{
				sum+=j;
				sum+=i/j;
			}
		if (sum == i)
			cout << i<<",";
		
	}
	cout << "\n";
	clock_t time2=clock();
	return (float)(time2-time1)/CLOCKS_PER_SEC*1000;
}








int main(void)
{
	int n=0;
	cin>>n;
	//cout << wanquan1(n) <<" ms\n";	
	//cout << wanquan2(n) <<" ms\n";	
	//cout << wanquan3(n) <<" ms\n";	
	cout << wanquan4(n) <<" ms\n";	
	cout << wanquan5(n) <<" ms\n";	
	cout << wanquan6(n) <<" ms\n";	
	return 0;
}
