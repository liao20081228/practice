/*************************************************************************
    > File Name: string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月13日 星期四 13时46分01秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
class string
{
	private:
		char *_str;
	public:
		string(const char *str):_str(new char[strlen(str)+1])//构造函数
		{
			strcpy(_str,str);
		}
		string():_str(new char[1])
		{
		}
		~string()//析构函数
		{
			delete []_str;
		}
		string(const string & ref):_str(new char[strlen(ref._str)+1])//拷贝构造函数
		{
			strcpy(_str,ref._str);
		}
		string & operator=(const string & ref)//拷贝构造函数
		{
			if(this==&ref)
				return *this;
			delete []_str;
			_str=new char[strlen(ref._str)+1];
			strcpy(_str,ref._str);
			return *this;
		}
		void print()
		{
			cout<<_str<<endl;
		}
};
int  main()
{
	string str1;
	str1.print();
	string str2("i love you");
	str2.print();
	string str3=str2;
	str3.print();
	str1=str2;
	str1.print();
	return 0;
}
