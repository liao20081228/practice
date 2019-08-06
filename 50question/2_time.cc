#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
#include<climits>
#include<cstdlib>
//从2到n-1
using namespace std;
bool judge1(int n)
{
	for(int i=2;i<n;++i)
		if ( n % i == 0 )
			return false;
	return true;
}

//如果一个能被分解因数，至少有一个数位于2~sqrt（n）
bool judge2(int n)
{
	for (int i=2;i<=sqrt(n);++i)
		if (n % i ==0)
			return false;
	return true;
}

bool judge3(int n)
{

}

int main(int argc,char** argv)
{
	//无函数调用
	//朴素算法优化
	
	std::clock_t time1=std::clock();
	for ( int i=2,j=2;i <  MAXVAL;++i)
	{
		for (j = 2; j <= std::sqrt(i) ; ++j )
			if ( i % j == 0 )
				break;
		if (i==j || i%j!=0)
			std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time2=std::clock();
	std::cout << std::endl;
	
	//朴素算法
	std::clock_t time3=std::clock();
	for ( int i=2,j=2;i <  MAXVAL;++i)
	{	for (j = 2; j <= i-1 ; ++j )
			if ( i % j == 0 )
				break;
		if (i==j || i%j!=0)
			std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time4=std::clock();
	std::cout <<   std::endl;
	
	//朴素算法二次优化
	std::clock_t time5=std::clock();
	for ( int i=2,j=2;i <  MAXVAL;)
	{
		for (j = 2; j <= sqrt(i) ; ++j )
			if ( i % j == 0 )
				break;
		if (i==j || i%j!=0)
				std::cout<< i << " is zhishu:"<< std::endl;
		if (i==2)
			++i;
		else
			i+=2;
	}
	std::clock_t time6=std::clock();
	std::cout <<   std::endl;

	std::clock_t time7=std::clock();
	for ( int i=2,j=2;i <  MAXVAL;)
	{
		for (j = 2; j <= i-1 ; ++j )
			if ( i % j == 0 )
				break;
		if (i==j||i%j!=0)
			std::cout<< i << " is zhishu:"<< std::endl;
		if (i==2)
			++i;
		else
			i+=2;
	}
	std::clock_t time8=std::clock();
	std::cout <<   std::endl;


	//有函数调用
	//朴素算法优化
	std::clock_t time9=std::clock();
	for ( int i=2;i <  MAXVAL;++i)
		if (fun1(i))
			std::cout<< i << " is zhishu:"<< std::endl;
	std::clock_t time10=std::clock();
	std::cout <<   std::endl;

	//朴素算法
	std::clock_t time11=std::clock();
	for ( int i=2;i <  MAXVAL;++i)
		if (fun2(i))
			std::cout<< i << " is zhishu:"<< std::endl;
	std::clock_t time12=std::clock();
	std::cout <<   std::endl;
	
	std::clock_t time13=std::clock();
	for ( int i=2;i <  MAXVAL;)
	{
		if (fun1(i))
			std::cout<< i << " is zhishu:"<< std::endl;
		if (i==2)
			++i;
		else
			i+=2;
	}
	std::clock_t time14=std::clock();
	std::cout <<   std::endl;

	std::clock_t time15=std::clock();
	for ( int i=2;i <  MAXVAL;)
	{
		if (fun2(i))
			std::cout<< i << " is zhishu:"<< std::endl;
		if (i==2)
			++i;
		else
			i+=2;
	}
	std::clock_t time16=std::clock();
	std::cout <<   std::endl;



	std::clock_t time17=std::clock();
	for ( int i=3,j=2;i <  MAXVAL;i+=2)
	{
		for (j = 2; j <= sqrt(i) ; ++j )
			if ( i % j == 0 )
				break;
		if(i==j || i%j!=0)
				std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time18=std::clock();
	std::cout <<   std::endl;

	std::clock_t time19=std::clock();
	for ( int i=3,j=2;i <  MAXVAL;i+=2)
	{
		for (j = 2; j <= i-1 ; ++j )
			if ( i % j == 0 )
				break;
		if (i==j || i%j!=0)
			std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time20=std::clock();
	std::cout <<   std::endl;

	std::clock_t time21=std::clock();
	for ( int i=3;i <  MAXVAL;i+=2)
	{
		if (fun1(i))
			std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time22=std::clock();
	std::cout <<   std::endl;

	std::clock_t time23=std::clock();
	for ( int i=3;i <  MAXVAL;i+=2)
	{
		if (fun2(i))
			std::cout<< i << " is zhishu:"<< std::endl;
	}
	std::clock_t time24=std::clock();
	std::cout <<   std::endl;



	cout << "method 1 spend time(ms):"<<(float)(time2 - time1) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2 spend time(ms):"<<(float)(time4 - time3) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 1_2 spend time(ms):"<<(float)(time6 - time5) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2_2 spend time(ms):"<<(float)(time8 - time7) / CLOCKS_PER_SEC * 1000 << endl;

	cout << "method 1 call function spend time(ms):"<<(float)(time10 - time9) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2 call function spend time(ms):"<<(float)(time12 - time11) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 1_2 call function spend time(ms):"<<(float)(time14 - time13) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2_2 call function spend time(ms):"<<(float)(time16 - time15) / CLOCKS_PER_SEC * 1000 << endl;
	
	cout << "method 1_2 no if spend time(ms):"<<(float)(time18 - time17) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2_2 no if spend time(ms):"<<(float)(time20 - time19) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 1_2 no if call function spend time(ms):"<<(float)(time22 - time21) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2_2 no if call function spend time(ms):"<<(float)(time24 - time23) / CLOCKS_PER_SEC * 1000 << endl;
}
