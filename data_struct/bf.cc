/*************************************************************************
    > File Name: esay_match.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月06日 星期四 23时41分35秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  bf(const string& str, const string& substr)
{
	int len = str.size(),
		sublen = substr.size();
	if (len < sublen)
	{
		return 0;
	}

	int i = 0,
		j = 0,
		k = 0;
	while (i < len)
	{
		k = i;
		j = 0;
		while (j < sublen)
		{
			if (str[i] == substr[j])
			{
				++i;
				++j;
			}
			else
			{
				break;
			}
		}
		if (j == sublen)
		{
			return k+1;//从1开始计数
		}
		i = ++k;
	}

	/*或者
	 while  (i < len && j < sublen )
	 {
		if (str[i] == substr[j])
		{
			++i;
			++j;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	 }
	 if (j == sublen)
	 {
		return i-j+1;//从1开始计算
		//return i-j;// 从0 开始计算
	 }
	*/
	return 0;
}
int main(void)
{
	cout << bf("liaoweizhi","wei") << endl;
	cout << bf("liaoweizhi","liao") << endl;
	cout << bf("liaoweizhi","han") << endl;
	cout << bf("liaoweizhi","liaoweizhi") << endl;
	return 0;
}
