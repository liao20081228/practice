#include<myhead_cpp.h>

int fun( int a )
{
	cout<<"Test"<<endl;
	return 0;
}

//函数名，就是函数的入口地址
//


int main(void)
{
	int a[10]={1,2,3,4}; //a是数组的首地址
	printf("%p\n",a);   //
	printf("%p\n",&a[0]);//&a[0]是数组第一个元素的地址
	printf("%p\n",&a[0]);//&a是数组的地址

	int* p1=a;
	int (*p2)[10]=&a;
	
	cout<<p1[0]<<endl;
	cout<<p2[2]<<endl;

	int (*pfun1)(int)=&fun;
	int (*pfun2)(int)=fun;
	pfun1(1);
	(*pfun1)(1);
	pfun2(2);
	(*pfun2)(2);
}
