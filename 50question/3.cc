#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
#include<climits>
bool fun(int n)
{
	assert(n>=100);
	int tmp=n,sum=0,count=0;
	while(tmp)
	{
		++count;
		tmp /= 10;
	}
	tmp=n;
	while(tmp)
	{
		sum+=pow(tmp%10,count);
		tmp /= 10;
	}
	if (sum == n)
		return true;
	else
		return false;
}


bool fun1(int n)
{
	assert(n>=100);
	int count=0,sum=0;
	for (int tmp =n ; tmp;tmp/=10)
		count++;
	for (int tmp =n ; tmp;tmp/=10)
		sum+=pow(tmp%10,count);
	if (sum==n)
		return true;
	else
		return false;
}

int main(void)
{
	using namespace std;
	std::clock_t time1=std::clock();
	for ( int i=100;i <=INT_MAX/100; ++i )
		//if (fun(i))
		if (fun1(i))
			std::cout<< i << " is shui xian hua:"  << std::endl;
	std::clock_t time2=std::clock();

	
	cout << "method 1 spend time(ms):"<<(float)(time2 - time1) / CLOCKS_PER_SEC * 1000 << endl;
}
