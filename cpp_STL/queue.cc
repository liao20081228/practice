/*************************************************************************
    > File Name: queue.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月29日 星期六 16时19分06秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	queue<int>q1,q2;
	for (int i = 0; i < 5; ++i) 
	{
		q1.push(i);
		q2.emplace(i);
	}
	cout<<"q1.front:"<<q1.front()<<endl;
	cout<<"q1.back:"<<q1.back()<<endl;
	q2.pop();
	cout<<"q1.front:"<<q1.front()<<endl;
	cout<<"q1.back:"<<q1.back()<<endl;
	cout<<"q1 size:"<<q1.size()<<" q2.size:"<<q2.size()<<endl;
	cout<<"empty()"<<q1.empty()<<endl;
	q1.swap(q2);
	cout<<"q1.front:"<<q1.front()<<endl;
	cout<<"q1.back:"<<q1.back()<<endl;
	std::swap(q1,q2);
	cout<<"q1.front:"<<q1.front()<<endl;
	cout<<"q1.back:"<<q1.back()<<endl;
	cout<<" q1>q2:"<<(q1>q2)<<" q1>=q2:"<<(q1>=q2)<<" q1<q2:"<<(q1<q2)<<" q1<=q2:"<<(q1<=q2)<<" q1==q2:"<<(q1==q2)<<" q1!=q2:"<<(q1!=q2);
	return 0;
}
