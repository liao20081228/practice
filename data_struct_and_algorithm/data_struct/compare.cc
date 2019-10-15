/*************************************************************************
    > File Name: compare.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月06日 星期四 23时34分29秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int MyCompare(const string& str1, const string& str2)
{
	int i = 0,
		len1 = str1.size(),
		len2 = str2.size();
	for (; i < len1 && i < len2 && str1[i] == str2[i]; ++i) 
	{
	}
	if (i == len1 || i == len2)
	{
		return len1 - len2;
	}
	else
		return str1[i] - str2[i];

}

int main(void)
{
	cout << MyCompare("liao","han") << endl;
	cout << MyCompare("liao","12liao") << endl;
	cout << MyCompare("liao","liao") << endl;
	cout << MyCompare("liao","liao28") << endl;
	return 0;
}
