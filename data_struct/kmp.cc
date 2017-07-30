/*************************************************************************
    > File Name: kmp.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月07日 星期五 21时46分11秒
 ************************************************************************/
#include<myhead_cpp.h>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
void GetNext(const string& substr, int next[])
{
	int k = -1,
		j = 0,
		len = substr.size();
	next[0] = -1;
	while (j < len -1) //k < j 一直成立
	{
		if (k == -1 || substr[j] == substr[k])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

int kmp(const string& str, const  string& substr)
{
	
	int i= 0,
		j= 0;
	int len = str.size(),
		sublen = substr.size();
	int* next = new int[sublen];
	GetNext(substr, next);  //获取next数组
	while (i < len && j < sublen)
	{
		if ( j == -1 ||  str[i] == substr[j]) 
		//j==-1 本来应放在后面的分支中
		{
			++i; ++j;
		}
		else
		{
			j = next[j];
			/*本应放在这里
			if (j == -1)
			{
				++i; ++j;
			}
			*/
		}
	}
	if (j == sublen)  //说明子串已经匹配完全
	{
		return i-j; //从0计算
		//return i-j+1; //从1计算
	}
	return -1; //说明匹配失败
}


int main(void)
{
	cout << kmp("liao","ao") << endl;
	return 0;
}
