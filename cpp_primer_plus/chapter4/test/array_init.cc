#include<iostream>
int main(void)
{
	using namespace std;
	int a[3];
	a[0]=1;
	a[1]=2;
	a[2]=3;
	//a={1,2,3};
	int b[3]={1,2,3};
	int c[3]={1};
	int d[3]={0};
	int e[3]={};
	int f[3]{1,2,3}; //c++11
	int g[3]{1};
	int h[3]{0};
	int i[3]{};
	//int j[3]={1.22,1};
	char k[3]{122222};
	cout << a[0] << " " << a[1] << " " << a[2] << endl ;
	cout << b[0] << " " << b[1] << " " << b[2] << endl ;
	cout << c[0] << " " << c[1] << " " << c[2] << endl ;
	cout << d[0] << " " << d[1] << " " << d[2] << endl ;
	cout << e[0] << " " << e[1] << " " << e[2] << endl ;
	cout << f[0] << " " << f[1] << " " << f[2] << endl ;
	cout << g[0] << " " << g[1] << " " << g[2] << endl ;
	cout << h[0] << " " << h[1] << " " << h[2] << endl ;
	cout << i[0] << " " << i[1] << " " << i[2] << endl ;
	//cout << j[0] << " " << j[1] << " " << j[2] << endl ;
	cout << k[0] << " " << k[1] << " " << k[2] << endl ;


	return 0;
}
