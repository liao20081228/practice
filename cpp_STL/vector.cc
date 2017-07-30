/*************************************************************************
    > File Name: vector.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月26日 星期三 17时42分23秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	cout<<"vector test"<<endl;
	cout<<"Created vector method"<<endl;
	vector<int>v1;
	vector<int>v2(5);
	vector<int>v3(5,1);
	int a[5]={1,2,3,4,5};
	vector<int>v4(a,a+5);
	vector<int>v5(v4);
	vector<int>v6{6,7,8,9,10};
	vector<int>v7={11,12,13,14,15};
	cout<<"visit"<<endl;
	vector<int>::iterator it;
	cout<<"v1:";for(it=v1.begin();it!=v1.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v2:";for(it=v2.begin();it!=v2.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v3:";for(it=v3.begin();it!=v3.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v4:";for(it=v4.begin();it!=v4.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v5:";for(it=v5.begin();it!=v5.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v6:";for(it=v6.begin();it!=v6.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"iterator"<<endl;
	cout<<"begin:"<<*v7.begin()<<" end:"<<*v7.end()<<" rbegin:"<<*v7.rbegin()<<" rend():"<<*v7.rend()<<endl;
	cout<<"cbegin:"<<*v7.cbegin()<<" cend:"<<*v7.cend()<<" crbegin:"<<*v7.crbegin()<<" crend():"<<*v7.crend()<<endl;
	cout<<"element access"<<endl;
	cout<<"v7[3]:"<<v7[3]<<" at(3):"<<v7.at(3)<<" front:"<<v7.front()<<" back():"<<v7.back()<<" *data:"<<*v7.data()<<endl;
	cout<<"capacity"<<endl;
	cout<<"size():"<<v7.size()<<" maxsize():"<<v7.max_size()<<" capacity():"<<v7.capacity()<<" empty():"<<v7.empty()<<endl;
	cout<<"shrink_to_fit()"<<endl;
	v7.shrink_to_fit();
	cout<<"size:"<<v7.size()<<" capacity:"<<v7.capacity()<<endl;
	v7.resize(10,11);/* 如果大于size小于capacity则扩充,capacity不变*/
	cout<<"size:"<<v7.size()<<" capacity:"<<v7.capacity()<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.resize(5,1); /* 如果大小小于size则截断*/
	cout<<"size:"<<v7.size()<<" capacity:"<<v7.capacity()<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.resize(20,1); /* 如果大于capacity，则重新分配，并扩从，但capacity可能会大于指定值*/
	cout<<"size:"<<v7.size()<<" capacity:"<<v7.capacity()<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"modify"<<endl;
	v7[5]=100;
	v4=v7;
	v1={1,2,3,4,5};
	v3.assign(v7.begin(),v7.end());
	v5.assign(6,100); /* 填充*/
	v2.assign({1,2,3,4,5});
	cout<<"v1:";for(it=v1.begin();it!=v1.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v2:";for(it=v2.begin();it!=v2.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v3:";for(it=v3.begin();it!=v3.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v4:";for(it=v4.begin();it!=v4.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v5:";for(it=v5.begin();it!=v5.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v6:";for(it=v6.begin();it!=v6.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.push_back(1);
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.pop_back();
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.insert(v7.begin()++,5);
	v7.insert(v7.begin()+2,7,9);
	v7.insert(v7.begin()+10,v1.begin(),v1.end());
	v7.insert(v7.begin()+16,{78,79,80});
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.erase(v7.begin()+3);
	v7.erase(v7.begin()+10,v7.begin()+13);
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v7.emplace(v7.begin(),100);
	v7.emplace_back(100);
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	v5.clear();
	cout<<"v5:";for(it=v5.begin();it!=v5.end();++it){cout<<*it<<"  ";}cout<<endl;
	v5.swap(v7);
	cout<<"v5:";for(it=v5.begin();it!=v5.end();++it){cout<<*it<<"  ";}cout<<endl;
	std::swap(v5,v7);
	cout<<"v5:";for(it=v5.begin();it!=v5.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v7:";for(it=v7.begin();it!=v7.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"v6:";for(it=v6.begin();it!=v6.end();++it){cout<<*it<<"  ";}cout<<endl;
	cout<<"relation operator"<<endl;
	cout<<(v7>v6)<<endl;
	cout<<(v7>=v6)<<endl;
	cout<<(v7<v6)<<endl;
	cout<<(v7<=v6)<<endl;
	cout<<(v7==v6)<<endl;
	cout<<(v7!=v6)<<endl;
	return 0;
}
