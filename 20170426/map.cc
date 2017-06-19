/*************************************************************************
    > File Name: associativecontainer.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月27日 星期四 12时00分14秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	pair<int,string>sz[3]={pair<int,string>(5,"xiao ming"),pair<int,string>(6,"xiao wang"),make_pair(7,"xiao zhang")};
	cout<<"Created map"<<endl;
	map<int,string>map1;
	map<int,string>map2(sz,sz+3);
	map<int,string>map3(map2);
	map<int,string>map4{make_pair(1,"zhao"),make_pair(2,"qian"),make_pair(3,"sun"),pair<int,string>(4,"li")};
	map<int,string>map5={make_pair(1,"zhao"),make_pair(2,"qian"),make_pair(3,"sun"),pair<int,string>(4,"li")};
	map<int,string>::iterator it;
	cout<<"map1:";for(it=map1.begin();it!=map1.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	cout<<"map2:";for(it=map2.begin();it!=map2.end();it++){cout<<it->first<<" "<<it->second<<" ;";}cout<<endl;
	cout<<"map3:";for(it=map3.begin();it!=map3.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	cout<<"map4:";for(it=map4.begin();it!=map4.end();it++){cout<<it->first<<" "<<it->second<<" ;";}cout<<endl;
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<" ;";}cout<<endl;
	cout<<"iterator"<<endl;
	cout<<"begin:"<<map5.begin()->first<<" "<<map5.begin()->second<</*" end:"<<map5.end()->first<<" "<<map5.end()->second<<*/" rbegin:"<<map5.rbegin()->first<<" "<<map5.rbegin()->second/*<<" rend:"<<map5.rend()->first<<" "<<map5.rend()->second*/<<endl;
	cout<<"cbegin:"<<map5.cbegin()->first<<" "<<map5.cbegin()->second<</*" end:"<<map5.end()->first<<" "<<map5.end()->second<<*/" crbegin:"<<map5.crbegin()->first<<" "<<map5.crbegin()->second/*<<" rend:"<<map5.rend()->first<<" "<<map5.rend()->second*/<<endl;
	cout<<"element access"<<endl;
	cout<<"map5[3]:"<<map5[3]<<" map5.at(3):"<<map5.at(3);  /*只有map支持[]和at,这里下标指的是主键的值，而不是数组的下标 */
	cout<<"capactity"<<endl;
	cout<<"size:"<<map4.size()<<" max_size:"<<map4.max_size()<<" empty:"<<map4.empty()<<endl;
	cout<<"modify"<<endl;
	/* insert*/
	pair<map<int,string>::iterator,bool>s=map5.insert(make_pair(1,"test"));/*插入一个元素， 返回迭代器和插入结果*/
	cout<<s.first->first<<" "<<s.first->second<<" "<<s.second<<endl;/* map不能有主键相同的元素*/
	map5.insert(map5.end(),make_pair(100,"lai xiao ")); /*参考设定位置插入一个元素， 返回迭代器i,并不会强制插入，如果位置不对则会自动调整*/
	map5.insert(sz,sz+3);/* 没有返回值，插入范围*/
	map5.insert({make_pair(60,"a "),pair<int,string>(61,"b")}); /* 插入列表*/
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	/*erase*/
	map5.erase(map5.begin());
	map5.erase(3);
	map4.erase(map4.begin(),map4.end());
	cout<<"map4:";for(it=map4.begin();it!=map4.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	/* clear*/
	map5.clear();
	/*swap */
	map5.swap(map3);
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	/* empalce*/
	map5.emplace(40,"abc");
	map5.emplace_hint(map5.begin(),50,"empalce_hint");
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	/* operator*/
	cout<<"find(5): "<<map5.find(5)->first<<" "<<map5.find(5)->second<<endl;
	cout<<"cout(11):"<<map5.count(11)<<" count(5):"<<map5.count(5)<<endl;
	cout<<"lower_bound(7)"<<map5.lower_bound(7)->first<<" "<<map5.lower_bound(7)->second<<endl;
	cout<<"upper_bound(7)"<<map5.upper_bound(7)->first<<" "<<map5.upper_bound(7)->second<<endl;
	cout<<"equal_range(7)"<<map5.equal_range(7).first->first<<" "<<map5.equal_range(7).first->second<<"----"<<map5.equal_range(7).second->first<<" "<<map5.equal_range(7).second->second<<endl;
	/* observer*/
	map<int,string>::key_compare kc=map5.key_comp(); 
	cout<<kc(1,2)<<endl;
	map<int,string>::value_compare vc=map5.value_comp(); 
	cout<<vc(make_pair(1,"a"),make_pair(2,"c"))<<endl;
	/* relation operator*/
	cout<<"  map5>map3:"<<(map5>map3)<<"  map5>=map3:"<<(map5>=map3)<<"  map5<map3:"<<(map5<map3)<<"  map5<=map3:"<<(map5<=map3)<<"  map5==map3:"<<(map5==map3)<<"  map5!=map3:"<<(map5!=map3)<<endl;
	/* no-member function*/
	std::swap(map5,map3);
	cout<<"map3:";for(it=map3.begin();it!=map3.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
	cout<<"map5:";for(it=map5.begin();it!=map5.end();it++){cout<<it->first<<" "<<it->second<<"; ";}cout<<endl;
}
