/*************************************************************************
    > File Name: seq_containor.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月25日 星期二 22时37分40秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	cout<<"====================array 测试=================="<<endl;
	array<int ,5>arr1;
	array<int,5>arr2{ {1,2,3,4,5} };
	array<int,5>arr3={{6,7,8,9,10}};
	array<int,5>*arr4=new array<int,5>{{10}};
	array<int,5>*arr5=new array<int,5>{{11,12,13,14,15}};
	cout<<"=======================元素访问================="<<endl;
	cout<<"arr3[3]:"<<arr3[3]<<"  arr3.at(3):"<<arr3.at(3)<<"  arr3.front():"<<arr3.front()<<"  arr3.back():"<<arr3.back()<<"  *arr3.data():"<<*arr3.data()<<endl;
	cout<<"=======================迭代器=================="<<endl;
	cout<<"begin():"<<arr2.begin()<<"  end():"<<arr2.end()<<" cbegin():"<<arr2.cbegin()<<" cend():"<<arr2.cend()<<endl;
	cout<<"*begin():"<<*arr2.begin()<<"  *end():"<<*arr2.end()<<" *rbegin():"<<*arr2.rbegin()<<" *rend():"<<*arr2.rend()<<endl;/* end（）和rend 都是不存在的*/
	cout<<"=========================迭代器的操作方法======="<<endl;
	cout<<"distance(inputiterator,inputiterator):"<<std::distance(arr2.end(),arr2.begin())<<endl;
	cout<<"==============用迭代器遍历array====================="<<endl;
	cout<<"arr4"<<endl;
	for(array<int,5>::iterator it=arr4->begin();it!=(*arr4).end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	cout<<"arr5"<<endl;
	for(array<int,5>::iterator it=arr5->begin();it!=(*arr5).end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	cout<<"=========================容量========================="<<endl;
	cout<<"arr1.size():"<<arr1.size()<<" arr1.max_size():"<<arr1.max_size()<<" empty():"<<arr1.empty()<<endl;
	cout<<"============================修改======================"<<endl;
	/*arr4[2]=100;*//* 不能用等号赋值*/
	arr4->fill(50);
	arr4->swap(*arr5);
	swap(*arr5,arr3);
	cout<<"arr4"<<endl;
	for(array<int,5>::iterator it=arr4->begin();it!=(*arr4).end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	cout<<"arr5"<<endl;
	for(array<int,5>::iterator it=arr5->begin();it!=(*arr5).end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	cout<<"arr3"<<endl;
	for(array<int,5>::iterator it=arr3.begin();it!=arr3.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	return 0;
}
