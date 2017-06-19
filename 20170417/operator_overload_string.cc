/*************************************************************************
    > File Name: operator_overload_string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月19日 星期三 13时06分09秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user,which include all headfiles we need*/
class String
{
	private:
		char *_str;
	public:
		String():_str(new char('\0'))//构造函数
		{
		}
		String(const char *str):_str(new char[strlen(str)+1])//构造函数
		{
			strncpy(_str,str,strlen(str));
		}
		~String()//析构函数
		{
			delete []_str;
		}
		String(const String &ref):_str(new char[strlen(ref._str)+1])//拷贝构造函数
		{
			strncpy(_str,ref._str,strlen(ref._str)+1);
		}
		String & operator=(const String &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			delete []_str;
			_str=new char[strlen(ref._str)+1];
			strncpy(_str,ref._str,strlen(ref._str)+1);
			return *this;
		}
		String &operator=(const char * str)
		{
			delete []_str;
			if(strlen(str)==0)
				_str=new char('\0');
			else
			{
				_str=new char[strlen(str)+1];
				strncpy(_str,str,strlen(str)+1);
			}
			return *this;
		}
		String &operator+=(const String &ref)
		{
			size_t len=strlen(_str)+strlen(ref._str)+1;
			char *str=new char[len];
			strcpy(str,_str);
			strcat(str,ref._str);
			_str=str;
			return *this;
		}
		String &operator+=(const char *str)
		{
			if(strlen(str)==0)
				return *this;
			size_t len=strlen(_str)+strlen(str)+1;
			char *pstr=new char[len];
			strcpy(pstr,_str);
			strcat(pstr,str);
			_str=pstr;
			return *this;
		}
		char &operator[](size_t index)
		{
			static char  nullchar='\0';
			if(index>=strlen(_str))
				return  nullchar;
			else
				return _str[index]; 
		}
		const char &operator[](size_t index) const
		{
			static char  nullchar='\0';
			if(index>=strlen(_str))
				return  nullchar;
			else
				return _str[index]; 
		}
		size_t size() const
		{
			return  strlen(_str);
		}
		size_t length() const
		{
			return  strlen(_str);
		}
		const char *c_str()const
		{
			return _str;
		}
		friend bool operator==(const String &, const String &);
		friend bool operator!=(const String &, const String &);
		friend bool operator<(const String &, const String &);
		friend bool operator>(const String &, const String &);
		friend bool operator<=(const String &, const String &);
		friend bool operator>=(const String &, const String &);
		friend ostream &operator<<(ostream &os, const String &s);
		friend istream &operator>>(istream &is, String &s);
};
bool operator==(const String & ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)==0)
		return true;
	else
		return false;
}
bool operator!=(const String & ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)==0)
		return false;
	else
		return true;
}
bool operator<(const String &ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)<0)
		return true;
	else
		return false;
}
bool operator>(const String &ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)>0)
		return true;
	else
		return false;
}
bool operator<=(const String &ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)<=0)
		return true;
	else
		return false;
}
bool operator>=(const String &ref1, const String &ref2)
{
	if(strcmp(ref1._str,ref2._str)>=0)
		return true;
	else
		return false;
}
ostream &operator<<(ostream &os, const String &s)
{
	os<<"  string:  "<<s._str<<endl;
	return os;
}
istream &operator>>(istream &is, String &s)
{
	is>>s._str;
	while(is.get()!='\n');
	return is;
}
String operator+(const String &ref1, const String &ref2)
{
	String temp=ref1;
	temp+=ref2;
	return temp;
}
String operator+(const String &ref,const char *str)
{
	String temp1=ref;
	String temp2(str);
	temp1+=temp2;
	return temp1;
}
String operator+(const char *str, const String &ref)
{
	String temp(str);
	temp+=ref;
	return temp;
}
int  main()
{
	String s1;
	cout<<"s1"<<s1;
	cout<<"s1's size: "<<s1.size()<<endl;;
	String s2("hello");
	cout<<"s2's length:  "<<s1.length()<<endl;
	cout<<"s2"<<s2;
	String s3="world";
	cout<<"s3"<<s3;
	s1=s2+s3;
	cout<<"s1=s2+s3"<<s1;
	s2+=s3;
	cout<<"s2+=s3"<<s2;
	cout<<"s2>s3?   "<<(s2>s3)<<endl;
	cout<<"s2<s3?   "<<(s2<s3)<<endl;
	cout<<"s2==s3?  "<<(s2==s3)<<endl;
	cout<<"s2!=s3?  "<<(s2!=s3)<<endl;
	cout<<"s2>=s3?  "<<(s2>=s3)<<endl;
	cout<<"s2<=s3?  "<<(s2<=s3)<<endl;
	s1="welcome"+s2;
	cout<<"welcome +s2"<<s1;
	return 0;
}
