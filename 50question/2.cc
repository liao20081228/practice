#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
#include<climits>
#include<cstdlib>
using namespace std;
//如果一个数不是质数，则他肯定能被2~到n-1中的一个数整数
bool judge1(int n)
{
	if (n<2)
		return false;
	for (int i=2;i< n;++i)
		if (n % i ==0)
			return false;
	return true;
}



//如果一个数不是质数，则它的一个因数肯定为0~sqrt（n）
bool judge2(int n)
{
	if (n < 2 )
		return false;
	for(int i=2;i<=sqrt(n);++i)
		if ( n % i == 0 )
			return false;
	return true;
}

//如果一个数能被2以上的偶数整除则他肯定能被2整除
bool judge3(int n)
{
	if (n == 2)
		return true;
	if ( n % 2 == 0 || n < 2)
		return false;
	for (int i=3 ; i <=sqrt(n);i+=2)
		if (n % i ==0)
			return false;
	return true;
}

//任何一个整数可以表示为6x，6x+1,6x+2=2（3x+1），6x+3=3（2x+1），6x+4=2（3x+2）,6x+5,(x=0,1...)，质数一定为6x+1或6x+5，但是2，3，要特殊处理
bool judge4(int n)
{
	if (n < 2)
		return false;
	if (n == 2 || n==3)
		return true;
	if ( n % 6 !=1 && n % 6 !=5) //因此如果n为质数，只能表示为6x+1 或 6x+5
		return false;
	//到这一步时，n最小可能为5，且只能表示为6x+1,6x+5，由此可以知道n一定不能被2，3 及其倍数整除(因为n如果能被2y，3y整除，则能被2，3整除)。
	//我们只需判断n是否能被5到sqrt（n）的数整除,5~sqrt（n）可以被表示为6x+5,6x+6，6x+1=7,6x+2=8,6x+3=9，6x+4=10,(x=0,1...)。其中由于6x+6，6x+8,6x+9,6x+10是2或3的倍数，无需判断。
	//所以只需判断n能否被6x+5和6x+7能否被整除,令i=6x+5,也改写为i和i+2
	for (int  i=5;i <= sqrt(n);i+=6)
		if (n % i == 0  || n % (i+2) == 0)
			return false;
	return true;
}




float show_zhishu_1(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge1(i))
			++count;
			//std::cout << i << "是 质数"<<std::endl;
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_2(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge2(i))
			++count;
			//std::cout << i << "是 质数"<<std::endl;
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_3(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge3(i))
			++count;
			//std::cout << i << "是 质数"<<std::endl;
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_4(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge4(i))
			++count;
			//std::cout << i << "是 质数"<<std::endl;
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}



int main(int argc,char** argv)
{
	using namespace std;
	unsigned int MAXVAL =0;
	unsigned int MINVAL =0;
	if (argc == 1)
	{
		MINVAL =2;
		MAXVAL =std::strtoul(argv[1],NULL,10);
	}
	else
	{
		MINVAL =std::strtoul(argv[1],NULL,10);
		MAXVAL =std::strtoul(argv[2],NULL,10);
	}
	float a1= show_zhishu_1(MINVAL,MAXVAL); 
	float a2= show_zhishu_2(MINVAL,MAXVAL); 
	float a3= show_zhishu_3(MINVAL,MAXVAL); 
	float a4= show_zhishu_4(MINVAL,MAXVAL);
	cout <<"2-n spend time " << a1 << " ms\n";
	cout <<"2-sqrt(n) spend time " << a2 << " ms\n";
	cout <<"2-sqrt(n) step 2 spend time " << a3 << " ms\n";
	cout <<"2-sqrt(n) step 6 spend time " << a4 << " ms\n";
}
