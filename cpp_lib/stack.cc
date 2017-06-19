/*************************************************************************
    > File Name: stack.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月29日 星期六 15时56分59秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	stack<int>s1,s2;
	for (int i = 0; i < 10; ++i) 
		s1.push(i);
	cout<<"s1 size:"<<s1.size()<<endl;
	while(!s1.empty())
		s1.pop();
	for(int i=10;i<15;++i)
		s2.emplace(i);
	cout<<"s2 size:"<<s2.size()<<endl;
	while(!s2.empty())
	{
		cout<<s2.top()<<endl;
		s2.pop();
	}
	for (int i = 0; i < 10; ++i) 
		s1.push(i);
	for(int i=10;i<15;++i)
		s2.emplace(i);
	s1.swap(s2);
	while(!s2.empty())
	{
		cout<<s2.top()<<endl;
		s2.pop();
	}
	std::swap(s1,s2);
	while(!s2.empty())
	{
		cout<<s2.top()<<endl;
		s2.pop();
	}
	s1.push(100);
	cout<<" s1>s2:"<<(s1>s2)<<" s1>=s2:"<<(s1>=s2)<<" s1<s2:"<<(s1<s2)<<" s1<=s2:"<<(s1<=s2)<<" s1==s2:"<<(s1==s2)<<" s1!=s2:"<<(s1!=s2);
	return 0;
}
