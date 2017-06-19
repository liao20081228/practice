/*************************************************************************
    > File Name: operator_overload_string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月19日 星期三 13时06分09秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user,which include all headfiles we need*/
class String
{
	private:/* 第一个字节用于存放引用计数*/
		char *_str;
		void Ref_count_init()
		{
			_str[0]=1;
		}
		void Ref_count_increment()
		{
				++_str[0];
		}
		void Ref_count_decrement()
		{
				--_str[0];
		}
	public:
		String():_str(new char[2]())//构造函数
		{
			_str[1]='\0';
			Ref_count_init();
		}
		String(const char *str):_str(new char[strlen(str)+2])//构造函数
		{
			strcpy(_str+1,str);
			Ref_count_init();
		}
		~String()//析构函数
		{
			Ref_count_decrement();
			if(Ref_count()<1)
				delete []_str;
		}
		String(const String &ref)//拷贝构造函数
		{
			if(ref.Ref_count()<255)
			{
				_str=ref._str;
				Ref_count_increment();
			}
			else
			{
				_str=new char[ref.size()+2];
				strcpy(_str+1,ref._str+1);
				Ref_count_init();
			}
		}
		String & operator=(const String &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			if(ref.Ref_count()<255)
			{
				this->~String();
				_str=ref._str;
				Ref_count_increment();
			}
			else
			{
				this->~String();
				_str=new char[ref.size()+2];
				strcpy(_str+1,ref._str+1);
				Ref_count_init();
			}
			return *this;
		}
		String &operator=(const char * str) /* const修饰传入参数，指针，引用，自定义数据类型，防止改变*/
		{
			if(strcmp(str,_str+1)==0)
				return *this;
			String tmp(str);
			*this=tmp;
			return *this;
		}
		String &operator+=(const String &ref)
		{
			char *p=new char[size()+ref.size()+2];
			strcpy(p+1,c_str());
			strcat(p+1,ref.c_str());
			this->~String();
			_str=p;
			Ref_count_init();
			return *this;
		}
		String &operator+=(const char *str)
		{
			String tmp(str);
			*this+=tmp;
			return *this;
		}
		char &operator[](size_t index)  /* 这种写法无法区分是访问操作还是修改操作*/
		{
			static char  nullchar='\0';
			if(index>=size())
				return  nullchar;
			else
			{
				if(Ref_count()>1)
				{
					char *p=new char[size()+2];
					strcpy(p+1,_str+1);
					Ref_count_decrement();
					_str=p;
					Ref_count_init();
				}
				return (_str+1)[index]; 
			}
		}
		const char &operator[](size_t index) const  /* const 修饰返回值（指针，引用），防止返回值改变*/
		{
			static char  nullchar='\0';
			if(index>=size())
				return  nullchar;
			else
				return (_str+1)[index]; 
		}
		size_t size() const  /* const 修饰成员函数，限制函数修改数据成员和调用非const成员函数，凡是不会修改数据成员的函数都应该声明为const*/
		{
			return  strlen(_str+1);
		}
		size_t length() const  /* 返回字符串长度*/
		{
			return  strlen(_str+1);
		}
		const char *c_str()const
		{
			return _str+1;
		}
		unsigned short  Ref_count() const  /* 获得引用计数*/
		{
			return _str[0];
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
	if(strcmp(ref1.c_str(),ref2.c_str())==0)
		return true;
	else
		return false;
}
bool operator!=(const String & ref1, const String &ref2)
{
	if(ref1==ref2)
		return false;
	else
		return true;
}
bool operator<(const String &ref1, const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())<0)
		return true;
	else
		return false;
}
bool operator>(const String &ref1, const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())>0)
		return true;
	else
		return false;
}
bool operator<=(const String &ref1, const String &ref2)
{
	if(ref1<ref2||ref1==ref2)
		return true;
	else
		return false;
}
bool operator>=(const String &ref1, const String &ref2)
{
	if(ref1>ref2||ref1==ref2)
		return true;
	else
		return false;
}
ostream &operator<<(ostream &os, const String &str)
{
	os<<str.c_str();
	return os;
}
istream &operator>>(istream &is, String &str)
{
	char buf[65535]={'\0'};
	is>>(buf);
	str=buf;
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
	cout<<"new create String object "<<endl;
	String s1="hello";
	String s2("world");
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"String s3(s1),call the copy-constructor"<<endl;
	String s3(s1);
	cout<<"s1: "<<s1<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	s1=s2;
	cout<<"s1=s2,call the \"=\" operator function"<<endl;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	
	cout<<"s1=\"hello\",s2=\",world\",call the \"=\" operator function"<<endl;
	s1="hello";
	s2=",world";
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s3=s1+s2,s1+=s2"<<endl;
	s3=s1+s2;
	s1+=s2;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s2=s1,s3=s2"<<endl;
	s2=s1;
	s3=s2;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"cout << s1[5]"<<endl;
	cout<<s1[5]<<endl;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Ref_count()<<endl;
	cout<<"s2 refcount:  "<<s2.Ref_count()<<endl;
	cout<<"s3 refcount:  "<<s3.Ref_count()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	return 0;
}
