/*****************************************************************************80
    > File Name: t.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年08月11日 星期五 21时08分39秒
*******************************************************************************/
/*myhead_cpp.h is a headfile in “/usr/local/include”,include all headfiles*/
#include<myhead_cpp.h>
int a=20;
namespace 
{
	int a = 10;

	void te()
	{
		cout<<a<<endl;
	}
}


int main(void)
{
	::te();
	return 0;
}
