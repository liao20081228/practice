/*************************************************************************
    > File Name: atoi.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月07日 星期五 07时18分43秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int Myatoi(const string& str)
{
	int i = 0;
	long value = 0;
	bool flag = false;
	if (str[0] == '-')
	{
		i = 1;
		flag = true;
	}
	else if (str[0] == '+')
	{
		i = 1;
	}
	for (; i < static_cast<int>(str.size()) && str[i] >= '0' && str[i] <= '9'; ++i)
	{
		value = value * 10 + (str[i] - '0');
		if (value > pow(2, 32) -1)
		{
			value = 0;
			cout <<"溢出"<< endl;
			return 0;
		}
	}

	if (flag)
	{
		value = 0 - value;
	}
	return value;
}

int main(void)
{
	cout << Myatoi("-100000asdasd") << endl;
	return 0;
}
