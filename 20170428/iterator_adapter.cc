/*************************************************************************
    > File Name: back_insert_iterator.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月01日 星期一 22时54分13秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
using std::copy;
using std::back_insert_iterator;/* 定义一个后置插入迭代器，只能用于具有push_back方法的容器，list，deque,vector*/
using std::back_inserter;/* 返回一个后置插入迭代器*/
using std::insert_iterator;/* 定义随机插入迭代器*/
using std::inserter;/* 返回随机插入迭代器*/
using std::front_insert_iterator;/* 定义前置插入迭代器，只能用于具有push_front方法的容器:deque,lsit,forward_list*/
using std::front_inserter;/* 返回前置插入迭代器*/
using std::ostream_iterator;
int  main()
{
	vector<int>v1{1,2,3,4,5};
	vector<int>v2{6,7,8,9,10};
	list<int>l1;
	list<int>l2;
	deque<int>q1{11,12,12,11};
	deque<int>q2{11,12,12,11};
	ostream_iterator<int>osit(cout,",");
	
	cout<<"v1 :"<<endl;
	copy(v1.begin(),v1.end(),osit); /* 遍历容器的算法，copy*/
	cout<<endl;
	cout<<"v2 :"<<endl;
	copy(v2.begin(),v2.end(),osit); /* 遍历容器的算法，copy*/
	cout<<endl;
	
	copy(v1.begin(),v1.end(),back_insert_iterator<list<int>>(l1)); /* 两种等效写法*/
	copy(v1.begin(),v1.end(),back_inserter<list<int>>(l2));
	
	cout<<"list1 :"<<endl;
	copy(l1.begin(),l1.end(),osit);
	cout<<endl;
	cout<<"list2 :"<<endl;
	copy(l2.begin(),l2.end(),osit);
	cout<<endl;
	
	copy(v2.begin(),v2.end(),front_insert_iterator<list<int>>(l1)); /* 两种等效写法*/
	copy(v2.begin(),v2.end(),front_inserter<list<int>>(l2));
	cout<<"list1 :"<<endl;
	copy(l1.begin(),l1.end(),osit);
	cout<<endl;
	cout<<"list2 :"<<endl;
	copy(l2.begin(),l2.end(),osit);
	cout<<endl;
	
	copy(l1.begin(),l1.end(),insert_iterator<deque<int>>(q1,q1.begin()+2));
	copy(l1.begin(),l1.end(),inserter<deque<int>>(q2,q2.begin()+2));
	cout<<"deque1 :"<<endl;
	copy(q1.begin(),q1.end(),osit);
	cout<<endl;
	cout<<"deque2 :"<<endl;
	copy(q2.begin(),q2.end(),osit);
	cout<<endl;
	return 0;
}
