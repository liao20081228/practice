/*************************************************************************
    > File Name: operator_overload_brackets.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月18日 星期二 20时45分25秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class deom
{
	public:
	int operator()(int x,int y)
	{
		return x > y ? x : y;
	}
	double operator()(double x, double y, double z)
	{
		return (x + y) * z;
	}
};
int  main()
{
	deom a;
	cout<<a(1,2)<<a(1,2,3)<<endl;
	return 0;
}
