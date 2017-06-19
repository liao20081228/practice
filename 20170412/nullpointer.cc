/*************************************************************************
    > File Name: nullpointer.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月14日 星期五 09时25分25秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class NullPointer
{
	private:
		static int _ix;
		int _iy;
	public:
		static void test1();
		void test2();
		void test3(int x);
		void test4();
};
int NullPointer ::_ix=0;
void NullPointer::test1()
{
		cout << "NullPointer::_ix = " << _ix << endl;
}
void NullPointer::test2()
{
		cout << "very cool!" << endl;
}
void NullPointer::test3(int ix)
{
		cout << "ix = " << ix << endl;
}
void NullPointer::test4()
{
		cout << "_iy = " << _iy << endl;
}

int  main()
{
	NullPointer *p=NULL;
	p->test1();
	p->test2();
	p->test3(1);
	p->test4();
	p->test1();
	return 0;
}
