/*************************************************************************
    > File Name: priority_queue.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017 Туу 30, Ня 16:31:28
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	priority_queue<int>q1;
	priority_queue<int,vector<int>,std::greater<int>>q2; /* 元素类型，基本容器，比价函数*/
	int arr[5]={10,45,82,45,13};
	for (int i = 0; i < 5; ++i) 
	{
		q1.push(arr[i]);
		q2.emplace(arr[i]);
		cout<<"当前q1中优先级最高的是"<<q1.top()<<endl;
		cout<<"当前q2中优先级最高的是"<<q2.top()<<endl;
	}
	q2.pop();
	cout<<"q1.size"<<q1.size()<<"  q2"<<q2.size()<<endl;
	cout<<"q1.empty()"<<q1.empty()<<"  q2.empty()"<<q2.empty()<<endl;
	cout<<"当前q1中优先级最高的是"<<q1.top()<<endl;
	cout<<"当前q2中优先级最高的是"<<q2.top()<<endl;
	/*q1.swap(q2);*//* priority_queue::swap, std::swap and relation operator need  base same kind container*/
	return 0;
}
