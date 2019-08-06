#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
int fun(int n)
{
	if (n==1)
		return 1;
	else if (n == 2)
		return 1;
	else 
		return fun(n-1)+fun(n-2);
}



int main(void)
{
	using std::cout;
	using std::endl;
	using std::clock;
	using std::clock_t;
	clock_t time1=clock();
	for (int i = 1; i < 45; ++i)
		cout << i << "th month have " << fun(i) << " rabbits" <<endl;
	clock_t time2=clock();
	clock_t time3=clock();
	long result[45]={0};
	result[0]=1;
	result[1]=1;
	cout << 1 << "th month have " << result[0] << "rabbits" <<endl;
	cout << 2 << "th month have " << result[1] << "rabbits" <<endl;
	for (int i = 2; i < 44 ; ++i )
	{
		result[i]=result[i-1]+result[i+1];
		cout << i+1 << "th month have " << result[i] << "rabbits" <<endl;
		
	}
	clock_t time4=clock();

	cout << "method 1 spend time(ms):"<<(float)(time2 - time1) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "method 2 spend time(ms):"<<(float)(time4 - time3) / CLOCKS_PER_SEC * 1000 << endl;

}
