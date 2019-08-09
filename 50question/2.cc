#include<iostream>
#include<ctime>
#include<cassert>
#include<cmath>
#include<climits>
#include<cstdlib>
#include<cstring>
using namespace std;
//如果一个数不是质数，则他肯定能被2~到n-1中的一个数整除
bool judge1(int n)
{
	if (n<2)
		return false;
	for (int i=2;i< n;++i)
		if (n % i ==0)
			return false;
	return true;
}



//如果一个正整数不是质数，则它的一个因数肯定为2~sqrt（n）另一个因数为sqrt（n）~n-1,
//所以只需要判断到sqrt（n）为止
bool judge1_1(int n)
{
	if (n < 2 )
		return false;
	for(int i=2;i<=sqrt(n);++i)
		if ( n % i == 0 )
			return false;
	return true;
}

//大于2的整数如果能被2整除（大于2的偶数）则他一定不是质数，此外如果一个数能被
//2的倍数整除，则肯定能被2整除
bool judge1_2(int n)
{
	if (n == 2)
		return true;
	if ( n % 2 == 0 || n < 2 )
		return false;
	for (int i=3 ; i <=sqrt(n);i+=2)
		if (n % i ==0)
			return false;
	return true;
}

//任何一个整数可以表示为6x，6x+1,6x+2=2（3x+1），6x+3=3（2x+1），6x+4=2（3x+2）
//6x+5,(x=0,1...)，质数一定为6x+1或6x+5，但是2，3，要特殊处理
bool judge1_3(int n)
{
	if (n == 2 || n==3)
		return true;
	if ( n<2 || (n % 6 !=1 && n % 6 !=5)) //因此如果n为质数，只能表示为6x+1 或 6x+5
		return false;
	//到这一步时，n最小可能为5，且只能表示为6x+1,6x+5，由此可以知道n一定不能
	//被2，3 及其倍数整除(因为n如果能被2y，3y整除，则能被2，3整除)。
	//只需判断n是否能被5到sqrt（n）的数整除,5~sqrt（n）可以被表示为6x+5,
	//6x+6，6x+7,6x+8,6x+9，6x+10,(x=0,1...)。其中由于6x+6，6x+8,6x+9,6x+10
	//是2或3的倍数，无需判断。所以只需判断n能否被6x+5和6x+7能否被整除,令i=6x+5,改写为i和i+2
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
		{
			++count;
			//std::cout << i << "是 质数"<<std::endl;
		}
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_1_1(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge1_1(i))
		{
			++count;
			//std::cout << i << "是 质数"<<std::endl;
		}
			clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_1_2(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge1_2(i))
		{
			++count;
			//std::cout << i << "是 质数"<<std::endl;
		}
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_1_3(int min,int max)
{
	int count=0;
	clock_t a1=clock();
	for (int i=min;i<=max;++i)
		if(judge1_3(i))
		{
			++count;
			//std::cout << i << "是 质数"<<std::endl;
		}
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}


float show_zhishu_2(int min,int max)
{
//定理：合数都能被分解为有限个素数的乘积。！！！
//
//埃式算法：要得到自然数n以内的全部素数，必须把不大于sqrt（n）的所有素数的倍数剔除，剩下的就是素数。
//朴素埃式算法：
//   1. 将所有的数写出来,假设都是素数
//   2. 从最小素数2开始，如果一个数是素数，则它的所有倍数都不是素数,因此把他的倍数全部划掉
//   3. 到最后剩下的数都是素数
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	memset(source, 1,(max+1)*sizeof(bool));
	source[0]=source[1]=false;//0是合数,1是素数

	for(int i=2;i<=max;++i)
		if (source[i])
			for(int j=2*i;j<=max;j+=i)
				source[j]=false;

	for (int i=min;i<=max;++i)
	{
		if (source[i])
		{
		      //cout << i << "是质数\n";
			count++;
		}
	}

	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}


float show_zhishu_2_1(int min,int max)
{ //埃氏算法优化
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	memset(source, 1,sizeof(bool)*(max+1));
	source[0]=source[1]=false;
	source[2]=true;
	for(int i=3;i<=sqrt(max);i+=2) 
	 //优化1：
	 //	埃式算法中，因为每一个合数都会被质因数分解，1-n中的合数的最大为n，
	 //	则所有合数的质因数的可能值为2~sqrt（n），又因为从2开始，每一质数的
	 //	所有倍数划去，所以sqrt(n)后的所有合数都划去了，所以只需循环到sqrt（n）即可
	 //优化2：
	 //	由于除了2之外的所有偶数都不是素数,因此这里的步长可以调整为2，起始值为3
	 //	但是在后面列出素数时也要这样操作,当然也可以是6但是此时在列出素数时非常复杂
		if (source[i])
			for(int j=i*i;j<=max;j+=i) 
			//优化2
			//	对于i*(i-1) 来说
			//		如果i-1是素数，则它的i倍，在之前外层循环走到i-1时已经划去
			//		如果i-1是合数，则它的i倍，在之前外层循环走到i-1的质因数时已经划去
			//	同理 i*2，i*3...i*(i-2)也已经划去
				source[j]=0;
	for (int i=min;i<=max;)
	{
		switch (i)
		{
			case 1: 
				if (max >= 1) ++i;break;
			case 2: 
				++i;++count;break;
			default:
				if ( i%2 ==0  )
				{
					++i;
					break;
				}
				else if (source[i])
				{
					++count;
					i+=2;
					break;
				}
				else
				{
					i+=2;
					break;
				}
	
		}
	}
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_2_2(int min,int max)
{ //埃氏算法优化
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	memset(source, 1,sizeof(bool)*(max+1));
	for( int i=0;i<=max+1;i++ )
	{
		if (i % 6 !=1 && i%6!=5)
			source[i]=false;
	}
	source[0]=source[1]=source[4]=false;
	source[2]=source[3]=true;

	for(int i=5;i<=sqrt(max);i+=6)
	{	
	 //优化1：
	 //	埃式算法中，因为每一个合数都会被质因数分解，1-n中的合数的最大为n，
	 //	则所有合数的质因数的可能值为2~sqrt（n），又因为从2开始，每一质数的
	 //	所有倍数划去，所以sqrt(n)后的所有合数都划去了，所以只需循环到sqrt（n）即可
	 //优化2：
	 //	由于除了2之外的所有偶数都不是素数,因此这里的步长可以调整为2，起始值为3
	 //	但是在后面列出素数时也要这样操作,当然也可以是6但是此时在列出素数时非常复杂
		if (source[i])
			for(int j=i*i;j<=max;j+=i) 
			//优化2
			//	对于i*(i-1) 来说
			//		如果i-1是素数，则它的i倍，在之前外层循环走到i-1时已经划去
			//		如果i-1是合数，则它的i倍，在之前外层循环走到i-1的质因数时已经划去
			//	同理 i*2，i*3...i*(i-2)也已经划去
				source[j]=0;
		if (source[i+2])
			for(int j=(i+2)*(i+2);j<=max;j+=(i+2))
				source[j]=0;
	}
	for (int i=min;i<=max;i++)
	{
		if (source[i])
			count++;
	}
	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_3(int min,int max)
{//欧拉算法:在埃氏筛法的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	int * prime=new int[2*(int)(max/log(max))]();
	
	assert(source && prime);
	memset(source,1,sizeof(bool)*(max+1));

	source[0]= 0;
	source[1]= 0;
	for (int i=2;i<=max;++i)
	{ // 遍历数组，如果i是素数则将它放在素数数组prime中，prime按升序排列
		if (source[i])
			prime[++prime[0]]=i;
		for (int j=1; j <= prime[0] && i * prime[j] <= max;++j)
		{
			source[i * prime[j]] = 0;
			//埃氏筛法，是用i的所有倍数来消去合数，
			//而欧拉筛法是把 prime里面纪录的素数当做要消去的合数的最小素因子。
			if (i % prime[j] == 0)//因为i=k*prime[j]，假设不跳出循环，则下一步source[i*prime[j+1]]=0,
					     //又因为i*prime[j+1]=prime[j]*k*prime[j+1];
					     //当i=k*prime[j+1]时就会,进入循环时会有source[k*prime[j+1] * prime[j]]=0,
					     //这就是重复的划去
				break;
		}
	}

	for (int i=min ; i<=max;i++)
	{
		if (source[i])
			count++;
	}
	//for (int i=1;i<=prime[0];i++)
	//{
		//if (prime[i]>= min )
			//count++;
	//}

	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	delete[] prime;
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_3_1(int min,int max)
{//欧拉算法:在埃氏筛法的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	int * prime=new int[2*(int)(max/log(max))]();
	
	assert(source && prime);
	memset(source,1,sizeof(bool)*(max+1));

	source[0]= 0;
	source[1]= 0;
	prime[1]=2;
	prime[0]=1;
	for (int i=3;i<=max;i+=2)
	{ // 遍历数组，如果i是素数则将它放在素数数组prime中，prime按升序排列
		if (source[i])
			prime[++prime[0]]=i;
		for (int j=1; j <= prime[0] && i * prime[j] <= max;++j)
		{
			source[i * prime[j]] = 0;
			//埃氏筛法，是用i的所有倍数来消去合数，
			//而欧拉筛法是把 prime里面纪录的素数当做要消去的合数的最小素因子。
			if (i % prime[j] == 0)//因为i=k*prime[j]，假设不跳出循环，则下一步source[i*prime[j+1]]=0,
					     //又因为i*prime[j+1]=prime[j]*k*prime[j+1];
					     //当i=k*prime[j+1]时就会,进入循环时会有source[k*prime[j+1] * prime[j]]=0,
					     //这就是重复的划去
				break;
		}
	}

	//for (int i=min ; i<=max;i++)
	//{
		//if (source[i])
			//count++;
	//}
	for (int i=1;i<=prime[0];i++)
	{
		if (prime[i]>= min )
			count++;
	}

	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	delete[] prime;
	return (float)(a2-a1)/CLOCKS_PER_SEC * 1000 ;
}

float show_zhishu_3_2(int min,int max)
{//欧拉算法:在埃氏筛法的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的
	int count=0;
	clock_t a1=clock();	
	bool* source=new bool[max+1]();
	int * prime=new int[2*(int)(max/log(max))]();
	
	memset(source,1,sizeof(bool)*(max+1));

	source[0]=source[1]=0;
	prime[1]=2;
	prime[2]=3;
	prime[0]=2;
	for (int i=5;i<=max;i+=6)
	{ // 遍历数组，如果i是素数则将它放在素数数组prime中，prime按升序排列
		if (source[i])
			prime[++prime[0]]=i;
		for (int j=1; j <= prime[0] && i * prime[j] <= max;++j)
		{
			source[i * prime[j]] = 0;
			//埃氏筛法，是用i的所有倍数来消去合数，
			//而欧拉筛法是把 prime里面纪录的素数当做要消去的合数的最小素因子。
			if (i % prime[j] == 0)//因为i=k*prime[j]，假设不跳出循环，则下一步source[i*prime[j+1]]=0,
					     //又因为i*prime[j+1]=prime[j]*k*prime[j+1];
					     //当i=k*prime[j+1]时就会,进入循环时会有source[k*prime[j+1] * prime[j]]=0,
					     //这就是重复的划去
				break;
		}
		if (source[i+2])
			prime[++prime[0]]=i+2;
		for (int j=1; j <= prime[0] && (i+2) * prime[j] <= max;++j)
		{
			source[(i+2) * prime[j]] = 0;
			//埃氏筛法，是用i的所有倍数来消去合数，
			//而欧拉筛法是把 prime里面纪录的素数当做要消去的合数的最小素因子。
			if ((i+2) % prime[j] == 0)//因为i=k*prime[j]，假设不跳出循环，则下一步source[i*prime[j+1]]=0,
					     //又因为i*prime[j+1]=prime[j]*k*prime[j+1];
					     //当i=k*prime[j+1]时就会,进入循环时会有source[k*prime[j+1] * prime[j]]=0,
					     //这就是重复的划去
				break;
		}

	}

	//for (int i=min ; i<=max;i++)
	//{
		//if (source[i])
			//count++;
	//}
	for (int i=1;i<=prime[0];i++)
	{
		if (prime[i]>= min )
			count++;
	}

	clock_t a2=clock();
	cout << count << "zhi shu\n";
	delete[] source;
	delete[] prime;
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
	float a2= show_zhishu_1_1(MINVAL,MAXVAL); 
	float a3= show_zhishu_1_2(MINVAL,MAXVAL); 
	float a4= show_zhishu_1_3(MINVAL,MAXVAL);
	float a5= show_zhishu_2(MINVAL,MAXVAL);
	float a6= show_zhishu_2_1(MINVAL,MAXVAL);
	float a7= show_zhishu_2_2(MINVAL,MAXVAL);
	float a8= show_zhishu_3(MINVAL,MAXVAL);
	float a9= show_zhishu_3_1(MINVAL,MAXVAL);
	float a10= show_zhishu_3_2(MINVAL,MAXVAL);
	cout <<"2-n spend time " << a1 << " ms\n";
	cout <<"2-sqrt(n) spend time " << a2 << " ms\n";
	cout <<"2-sqrt(n) step 2 spend time " << a3 << " ms\n";
	cout <<"2-sqrt(n) step 6 spend time " << a4 << " ms\n";
	cout <<"埃式算法  spend time " << a5 << " ms\n";
	cout <<"埃式算法 优化步长2  spend time " << a6 << " ms\n";
	cout <<"埃式算法 优化步长6  spend time " << a7 << " ms\n";
	cout <<"欧拉算法  spend time " << a8 << " ms\n";
	cout <<"欧拉算法 优化步长2 spend time " << a9 << " ms\n";
	cout <<"欧拉算法 优化步长6 spend time " << a10 << " ms\n";
}
