/*************************************************************************
    > File Name: string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月22日 星期六 14时20分24秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	/* string 构造函数*/
	cout<<"构造函数"<<endl;
	
	string s1;/* 空串*/
	string s2("hello,world");/* */
	string s3("hello,world122",11);/* 取字符串前11*/
	string s4(10,'u');/* 建立长为10，用u填充*/
	string s5(s2);
	string s6(s2,2,2);/* 从s2的第个字符的后一个开始取至多2个字符*/
	cout<<s1<<endl;
	cout<<s2<<endl;
	cout<<s3<<endl;
	cout<<s4<<endl;
	cout<<s5<<endl;
	cout<<s6<<endl;
	cout<<"访问元素-------------------------------------------"<<endl;
	
	cout<<s2[4]<<endl;/* 某个字符但不检查下标合法性,从下标0开始算起*/
	cout<<s2.at(4)<<endl;/* 某个字符*/
	cout<<s2.front()<<endl;/* 第一个字符*/
	cout<<s2.back()<<endl;/* 最后一个字符*/
	/* 迭代器,相当于指针*/
	cout<<"迭代器---------------------------------------------"<<endl;
	cout<<*s2.begin()<<endl;  /* 返回第一字符的迭代器*/
	cout<<*s2.end()<<endl; /* 返回最后一个字符之后的字符的迭代器,为空*/
	cout<<*s2.rbegin()<<endl;/* 返回最后一个字符的迭代器*/
	cout<<*s2.rend()<<endl;/* 返回第一个字符之前的字符的迭代器，为空*/
	cout<<*s2.cbegin()<<endl;/* 和上面的类似，只是是常迭代器不能用于修改*/
	cout<<*s2.cend()<<endl;
	cout<<*s2.crbegin()<<endl;
	cout<<*s2.crend()<<endl;
	cout<<"用迭代器修改字符-----------------------------"<<endl;
	cout<<s2<<endl;
	*s2.begin()='i';
	cout<<s2<<endl;
	//*s2.cbegin()='i';/* 常迭代器不能用于修改字符*/
	*s2.begin()='h';
	cout<<"容量---------------------------------------"<<endl;
	cout<<s2<<endl;
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.length()<<endl;/*真是长度 */
	cout<<s2.max_size()<<endl;/* 系统允许最大容量*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<"调整长度==============影响size和capacity====================="<<endl;
	s2.resize(5); /*调整长度,当小于size时发生截断,不影响capacity */
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;

	s2.resize(8); /*调整长度,当大于size时，小于capacity，扩充 */
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;

	s2.resize(5,'u'); /*调整长度,当小于size，指定填充值，无效*/
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	
	s2.resize(8,'z'); /*调整长度,当大于size时，小于capacity，以指定字符扩充 */
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	
	s2.resize(20,'z'); /*调整长度大于于capacity，以指定字符扩充，内存重新分配 */
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	
	s2.resize(25); /*调整长度大于于capacity，内存重新分配，默认初始化扩充 */
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	
	cout<<"调整容量++++++++++++不影响size+++++++++++++++++"<<endl;
	s2.reserve(28); /*调整容量，比当前容量小且大于size，调整为指定容量*/
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;

	s2.reserve(10); /*调整容量，比当前size小，调整为size*/
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;

	s2.reserve(35); /*调整容量，比当前容量大，重新分配内存，为指定容量或者更大*/
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	cout<<"shrink_to_fit"<<endl;
	s2.shrink_to_fit();
	cout<<s2.size()<<endl;/* 真实长度*/
	cout<<s2.capacity()<<endl; /*当前容量*/
	cout<<s2<<endl;
	
	cout<<"字符串判空"<<endl;
	cout<<s2.empty()<<endl;
	
	cout<<"字符串修改"<<endl;
	s2.assign("hello");/* 赋值*/
	cout<<s2<<endl;
	s2="hello,";/* 赋值*/
	cout<<s2<<endl;
	s2.append("world");/* 追加*/
	cout<<s2<<endl;
	s2+="!";/* 追加*/
	cout<<s2<<endl;
	s2.push_back('a');
	cout<<s2<<endl;
	s2.pop_back();
	cout<<s2<<endl;
	s2.insert(10,"fuck!");
	cout<<s2<<endl;
	s2.replace(10,5,"you");
	cout<<s2<<endl;
	s2.erase(10,3);
	cout<<s2<<endl;
	s2.erase(10);
	s2.assign(s3);
	cout<<s2<<endl;
	s2.clear();
	cout<<s2<<endl;
	s2.assign(s3);
	cout<<s2<<endl;
	s2.swap(s4);
	cout<<s2<<endl;
	swap(s2,s4);
	cout<<s2<<endl;
	printf("%p\n",s2.c_str() );
	printf("%p\n",s2.data() );
	char str[10];
	s2.copy(str,5,3);
	cout<<str<<endl;
	cout<<s2.find("el")<<endl;
	cout<<s2.find("el",3)<<endl;
	cout<<s2.find("elk",0,2)<<endl;
	cout<<s2.rfind("l")<<endl;
	cout<<s2.find_first_of("zzl")<<endl;
	cout<<s2.find_last_of("zzl")<<endl;
	cout<<s2.find_last_not_of("zzl")<<endl;
	cout<<s2.find_first_not_of("zzl")<<endl;
	cout<<s2.substr(3,5)<<endl;
	cout<<s2.compare("hello")<<endl;
	s2="13.23";
	cout<<stoi(s2)<<endl;
	cout<<stol(s2)<<endl;
	cout<<stoll(s2)<<endl;
	cout<<stoull(s2)<<endl;
	cout<<stoul(s2)<<endl;
	s2="13.23";
	cout<<stof(s2)<<endl;
	cout<<stod(s2)<<endl;
	cout<<stold(s2)<<endl;
	cout<<std::to_string(20.56)<<endl;
	return 0;
}
