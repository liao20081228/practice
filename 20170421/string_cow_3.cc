/*************************************************************************
  > File Name: cow.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月24日 星期一 19时46分28秒
 ************************************************************************/
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;
class String
{
	private:
		char *_str;
		void Refcount_init()
		{
			_str[0]=1;
		}
		void Refcount_increment()
		{
			++_str[0];
		}
		void Refcount_decrement()
		{
			--_str[0];
		}
		class Charproxy
		{
			private:
				String &_s;
				size_t _index;
			public:
				Charproxy(String &s,size_t index):_s(s),_index(index)
				{	
				}
				Charproxy &operator=(const char ch)
				{
					if(_s.Refcount()>1)
					{
						char *p=new char[_s.size()+2];
						strcpy(p+1,_s._str+1);
						_s.~String();
						_s._str=p;
						_s.Refcount_init();
					}
					(_s._str+1)[_index]=ch;
					return *this;
				}
				operator char()
				{
					return (_s._str+1)[_index];
				}
		};
	public:
		String():_str(new char[2])//构造函数
		{
			_str[1]='\0';
		}
		String(const char *str):_str(new char[strlen(str)+2])
		{
			strcpy(_str+1,str);
			Refcount_init();
		}
		~String()//析构函数
		{
			Refcount_decrement();
			if(Refcount()<1)
				delete []_str;
		}
		String(const String &ref) //拷贝构造函数
		{
			if(ref.Refcount()<255)
			{
				_str=ref._str;
				Refcount_increment();
			}
			else
			{
				_str=new char[strlen(ref._str+1)+2];
				strcpy(_str+1,ref._str+1);
				Refcount_init();
			}
		}
		unsigned short Refcount() const
		{
			return _str[0];
		}
		String & operator=(const String &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			if(ref.Refcount()<255)
			{
				this->~String();
				_str=ref._str;
				Refcount_increment();
			}
			else
			{
				this->~String();
				_str=new char[strlen(ref._str+1)+2];
				strcpy(_str+1,ref._str+1);
				Refcount_init();
			}
			return *this;
		}
		String &operator=(const char *str)
		{
			if(strcmp(_str+1,str)==0)
				return *this;
			String temp(str);
			*this=temp;
			return *this;
		}
		String &operator+=(const String &ref)
		{
			char *p=new char[strlen(ref._str+1)+2];
			strcpy(p+1,_str+1);
			strcat(p+1,ref._str+1);
			this->~String();
			_str=p;
			Refcount_init();
			return *this;
		}
		String &operator+=(const char *str)
		{
			String temp(str);
			*this+=temp;
			return *this;
		}
		size_t size() const
		{
			return strlen(_str+1);
		}
		size_t length() const
		{
			return strlen(_str+1);
		}
		const char*c_str()  const
		{
			return _str+1;
		}
		Charproxy operator[](size_t index)
		{
			if(index<size())
				return Charproxy(*this,index);
			else
			{
				cout<<"index is crossed"<<endl;
				exit(-1);
			}
		}
		friend bool operator==(const String& ref1,const String &ref2);
		friend bool operator==(const String& ref,const char * str);
		friend bool operator==(const char * str,const String& ref);
		friend bool operator!=(const String& ref1,const String &ref2);
		friend bool operator!=(const String& ref,const char * str);
		friend bool operator!=(const char * str,const String& ref);
		friend bool operator<(const String& ref1,const String &ref2);
		friend bool operator<(const String& ref,const char * str);
		friend bool operator<(const char * str,const String& ref);
		friend bool operator<=(const String& ref1,const String &ref2);
		friend bool operator<=(const String& ref,const char * str);
		friend bool operator<=(const char * str,const String& ref);
		friend bool operator>(const String& ref1,const String &ref2);
		friend bool operator>(const String& ref,const char * str);
		friend bool operator>(const char * str,const String& ref);
		friend bool operator>=(const String& ref1,const String &ref2);
		friend bool operator>=(const String& ref,const char * str);
		friend bool operator>=(const char * str,const String& ref);
		friend ostream & operator<<( ostream &os,const String &s );
		friend istream & operator>>( istream &is, String &s );
		friend String operator+(const String& ref1,const String &ref2);
		friend String operator+(const String& ref,const char * str);
		friend String operator+(const char * str,const String& ref);

};
bool operator==(const String& ref1,const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())==0)
		return true;
	else
		return false;
}
bool operator==(const String& ref,const char * str)
{
	if(strcmp(ref.c_str(),str)==0)
		return true;
	else
		return false;
}
bool operator==(const char * str,const String& ref)
{
	if(strcmp(ref.c_str(),str)==0)
		return true;
	else
		return false;
}
bool operator!=(const String& ref1,const String &ref2)
{
	return !(ref1==ref2);
}
bool operator!=(const String& ref,const char * str)
{
	return !(ref==str);
}
bool operator!=(const char * str,const String& ref)
{
	return !(ref==str);
}
bool operator<(const String& ref1,const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())<0)
		return true;
	else
		return false;
}
bool operator<(const String& ref,const char * str)
{
	if(strcmp(ref.c_str(),str)<0)
		return true;
	else
		return false;
}
bool operator<(const char * str,const String& ref)
{
	if(strcmp(str,ref.c_str())<0)
		return true;
	else
		return false;
}
bool operator<=(const String& ref1,const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())<=0)
		return true;
	else
		return false;
}
bool operator<=(const String& ref,const char * str)
{
	if(strcmp(ref.c_str(),str)<=0)
		return true;
	else
		return false;
}
bool operator<=(const char * str,const String& ref)
{
	if(strcmp(str,ref.c_str())<=0)
		return true;
	else
		return false;
}
bool operator>(const String& ref1,const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())>0)
		return true;
	else
		return false;
}
bool operator>(const String& ref,const char * str)
{
	if(strcmp(ref.c_str(),str)>0)
		return true;
	else
		return false;
}
bool operator>(const char * str,const String& ref)
{
	if(strcmp(str,ref.c_str())>0)
		return true;
	else
		return false;
}
bool operator>=(const String& ref1,const String &ref2)
{
	if(strcmp(ref1.c_str(),ref2.c_str())>=0)
		return true;
	else
		return false;
}
bool operator>=(const String& ref,const char * str)
{
	if(strcmp(ref.c_str(),str)>=0)
		return true;
	else
		return false;
}
bool operator>=(const char * str,const String& ref)
{
	if(strcmp(str,ref.c_str())>=0)
		return true;
	else
		return false;
}

ostream & operator<<( ostream &os,const String &s )
{
	os<<s.c_str();
	return os;
}

istream & operator>>( istream &is, String &str)
{
	char buf[65535]={'\0'};
	is>>buf;
	str=buf;
	return is;
}

String operator+(const String& ref1,const String &ref2)
{
	String temp(ref1);
	temp+=ref2;
	return temp;
}
String operator+(const String& ref,const char * str)
{
	String temp(str);
	return ref+temp;

}
String operator+(const char * str,const String& ref)
{
	String temp(str);
	return temp+ref;
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
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"String s3(s1),call the copy-constructor"<<endl;
	String s3(s1);
	cout<<"s1: "<<s1<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	s1=s2;
	cout<<"s1=s2,call the \"=\" operator function"<<endl;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s1=\"hello\",s2=\",world\",call the \"=\" operator function"<<endl;
	s1="hello";
	s2=",world";
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s3=s1+s2,s1+=s2"<<endl;
	s3=s1+s2;
	s1+=s2;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s2=s1,s3=s2"<<endl;
	s2=s1;
	s3=s2;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"cout << s1[5]"<<endl;
	cout<<s1[5]<<endl;
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	cout<<"s1[5]='!'"<<endl;
	s1[5]='!';
	cout<<"s1: "<<s1<<endl;
	cout<<"s2: "<<s2<<endl;
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	cout<<"s2 refcount:  "<<s2.Refcount()<<endl;
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	printf("s2 pointer: %p\n",s2.c_str() );
	printf("s3 pointer: %p\n",s3.c_str() );
	return 0;
}
