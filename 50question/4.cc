#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cassert>
#include<ctime>
int fun(int n)
{

	for (int i=2;i<=sqrt(n);++i)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}



bool prime(int n)
{
	if (n==2)
		return true;
	else if (n % 2 == 0)
		return false;
	else 
		return fun(n);
}

//法1
void fenjie( int n )
{
	if (prime(n))
	{	
		std::cout<< n <<std::endl;
		return;
	}
	else
		for (int i=2;i<n;++i)
			if( n%i==0 )
			{
				std::cout<<i<<"x"<<std::ends;
				fenjie(n/i);
				return;
			}
}

//法2

void fenjie2(int n)
{
	for (int i =2;i<n ;++i)
		if (n%i==0)
		{
			n/=i;
			std::cout << i-- << "x" ;
		}
	std::cout<<n<<std::endl;
}

//法3
void fenjie3(int n)
{
	while(n%2==0)
	{
		std::cout<<2<<"x";
		n/=2;
	}
	for (int i=3;i<n ;i+=2)
	{
		if (n%i==0)
		{
			std::cout<<i<<"x";
			n/=i;
			i-=2;
		}
	}
	std::cout<<n<<std::endl;
}



//分解4
void fenjie4(int n)
{
	for(int k=2;k<n;k++)
	{
		while(k!=n)
		{
		       if(n%k==0)
		       {
		           printf("%d\n",k);
		           n=n/k;
		       }
		       else break;         //跳出while使k+1                
		}
	}
	printf("%d\n",n);       //打印最后一个质因数，即k等于n是的那个
}


int main(int argc, char *argv[])
{
	const int MAXVAL=atoi(argv[1]);

	clock_t a1=clock();
		fenjie(MAXVAL);

	clock_t a2=clock();
		fenjie2(MAXVAL);
	
	clock_t a3=clock();
		fenjie2(MAXVAL);
	clock_t a4=clock();
	std::cout<<a2-a1<<"us  " << a3-a2 <<"us  "<<a4-a3<< "us"<<std::endl;
	return 0;

}
