#include<myhead_cpp.h>

bool judge1(int n)
{	if (n == 1)
		return false;
	else
		for ( int i = 2; i <n ; ++i )
			if (n % i == 0)
				return false;
	return true;
}

bool judge2(int n)
{
	if (n==1)
		return false;
	else
		for(int i=2; i<= sqrt(n); i++)
			if (n% i==0)
				return false;
	return true;
}

bool judge3(int n)
{
	if (n%2 == 0 || n ==1)
		return false;
	else if (n == 2)
		return true;
	for (int i =3; i<=sqrt(n);i+=2)
		if (n % i==0)
			return false;
	return true;
}

bool judge4(int n)
{
	if (n ==2 || n==3)
		return  true;
	else if (n ==1)
		return false;
	if (n % 6 !=1 && n%6!=5)
		return false;
	for (int i=5; i<=sqrt(n);i+=6)
		if (n % i == 0 || n % (i+2) ==0)
			return false;		
	return true;
}


void fenjie1(int n)
{
	if (judge4(n))
	{
		cout<<n<<endl;
		return;
	}
	else
		for ( int i=2 ; i<n;i++ )
			if (n %i==0)
			{
				cout<<i<<"x";
				fenjie1(n/i);
				return ;
			}			
}


void fenjie2(int n)
{
	cout<< n<< "=";
	for ( int i =2;i<n ;++i )
		if (n%i==0)
		{
			cout<< i <<"x";
			n/=i;
			--i;
		}
	//另一种写法
	//for (int i =2 ; i<n;)
	//	if (n%i==0)
	//	{
	//		cout<<i<<"x";
	//		n/=i;
	//	}
	//	else 
	//		++i;
	//
	//还有一种写法
	//for ( int i =2;i< n;++i )
	//	while(n%i==0)
	//	{
	//		cout<< i <<"x";
	//		n/=i;
	//	}


	cout << n <<endl;
}

void fenjie3(int n)
{
	cout << n << "=";
	while(n % 2 ==0 && n != 2)
	{
		cout<< 2 << "x";
		n /=2;
	}
	for ( int i=3;i< n ; )	
	{
		if (n % i == 0)
		{
			cout << i <<"x";
			n /= i;
		}
		else 
			i+=2;
	}
	cout << n <<endl;
}







int main( int argc,char*argv[])
{
	int n=atoi(argv[1]);
	clock_t a1=clock();
	fenjie1(n);
	clock_t a2=clock();
	fenjie2(n);
	clock_t a3=clock();
	fenjie3(n);
	clock_t a4=clock();

	cout << (float)(a2-a1)/ CLOCKS_PER_SEC*1000 << endl;
	cout << (float)(a3-a2)/ CLOCKS_PER_SEC*1000 << endl;
	cout << (float)(a4-a3)/ CLOCKS_PER_SEC*1000 << endl;
	return 0;
}
