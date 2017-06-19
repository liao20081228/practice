/*************************************************************************
    > File Name: typeid_typedef_typename.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月16日 星期二 13时08分39秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T>
void judge(T x)
{
	cout<<typeid(x).name()<<endl;
}

int  main()
{
	int a=10;
	typedef  int arry[5];
	judge<int>(a);
	if(typeid(a)==typeid(int))
	{
		cout<<"int"<<endl;
		
	}

}

