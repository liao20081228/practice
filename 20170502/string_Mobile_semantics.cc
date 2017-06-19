/*************************************************************************
    > File Name: string.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月08日 星期一 14时47分34秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class String
{
	private:
		char *_str;
		void Refcount_init(){(*_str)=1;}
		void Refcount_increment(){++(*_str);}
		void Refcount_decrement(){--(*_str);}
		class Charproxy
		{
			private:
				size_t _index;
				String &_s;
			friend ostream &operator<<(ostream &os,const String::Charproxy&s);
			public:
				Charproxy(String &s,size_t index):_index(index),_s(s)
				{
				}
				Charproxy & operator=(const char &ch)
				{
					if(_s.Get_refcount()>1)
					{
						char *p=new char[_s.size()+2];
						strcpy(p+1,_s.c_str());
						_s.Refcount_decrement();
						_s._str=p;
						_s.Refcount_init();
					}
					(_s._str+1)[_index]=ch;
					return *this;
				}
		};
	public:
		String(/*arguments*/):_str(new char[2])//构造函数
		{
			_str[1]='\0';
			Refcount_init();
		}
		String(const char *str):_str(new char[strlen(str)+2])
		{
			strcpy(_str+1,str);
			Refcount_init();
		}
		~String()//析构函数
		{
			if(_str!=NULL)
			{
				Refcount_decrement();
				if(Get_refcount()==0)
					delete[]_str;
			}
		}
		String(const String &lref)//拷贝构造函数
		{
			if(lref.Get_refcount()==255)
			{
				_str=new char[strlen(lref._str+1)+2];
				strcpy(_str+1,lref.c_str());
				Refcount_init();
			}
			else
			{
				_str=lref._str;
				Refcount_increment();
			}
		}
		String(String &&rref)/*init_member_lsit*///移动构造函数
		{
			_str=rref._str;
			rref._str=NULL;

			cout<<"移动构造函数"<<endl;
		}
		String & operator=(const String &lref)//拷贝赋值运算符函数
		{
			if(this!=&lref)
			{
				if(lref.Get_refcount()==255)
				{
					this->~String();
					_str=new char[strlen(lref._str+1)+2];
					strcpy(_str+1,lref.c_str());
					Refcount_init();
				}
				else
				{
					this->~String();
					_str=lref._str;
					Refcount_increment();
				}
			}
			return *this;
		}
		String & operator=(String &&rref)//移动赋值运算符函数
		{
			cout<<"移动赋值运算符函数"<<endl;
			if(this!=&rref)
			{
				_str=rref._str;
				rref._str=NULL;
			}
			return *this;
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
		short unsigned int Get_refcount()const{return *_str;}
		const char* c_str()const{return _str+1;}
		size_t size()const{return strlen(_str+1);}
		size_t length()const{return strlen(_str+1);}
		String& operator+=(const String & ref)
		{
			if(Get_refcount()==1)
				strcat(_str+1,ref.c_str());
			else
			{
				char *p =new char[ref.size()+size()+2];
				strcpy(p+1,_str+1);
				strcat(p+1,ref.c_str());
				this->~String();
				_str=p;
				Refcount_init();
			}
			return *this;
		}
		String &operator+=(const char *str)
		{
			String temp(str);
			*this+=temp;
			return *this;
		}
		String &append(const String &ref ){return *this+=ref;}
		String &append(const char *str ){return *this+=String(str);}
		friend ostream &operator<<(ostream &os,const String::Charproxy&s);
};
bool operator==(const String& ref1,const String &ref2){return !static_cast<bool>(strcmp(ref1.c_str(),ref2.c_str()));}
bool operator!=(const String& ref1,const String &ref2){return !(ref1==ref2);}
bool operator<(const String& ref1,const String &ref2){return strcmp(ref1.c_str(),ref2.c_str())<0?true:false;}
bool operator<=(const String& ref1,const String &ref2){return strcmp(ref1.c_str(),ref2.c_str())<=0?true:false;}
bool operator>(const String& ref1,const String &ref2){return strcmp(ref1.c_str(),ref2.c_str())>0?true:false;}
bool operator>=(const String& ref1,const String &ref2){return strcmp(ref1.c_str(),ref2.c_str())>=0?true:false;}

bool operator==(const String& ref1,const char *str){return !static_cast<bool>(strcmp(ref1.c_str(),String(str).c_str()));}
bool operator!=(const String& ref1,const char *str){return !(ref1==str);}
bool operator<(const String& ref1,const char *str){return strcmp(ref1.c_str(),String(str).c_str())<0?true:false;}
bool operator<=(const String& ref1,const char *str){return strcmp(ref1.c_str(),String(str).c_str())<=0?true:false;}
bool operator>(const String& ref1,const char *str){return strcmp(ref1.c_str(),String(str).c_str())>0?true:false;}
bool operator>=(const String& ref1,const char *str){return strcmp(ref1.c_str(),String(str).c_str())>=0?true:false;}

bool operator==(const char *str,const String& ref1){return !static_cast<bool>(strcmp(ref1.c_str(),String(str).c_str()));}
bool operator!=(const char *str,const String& ref1){return !(ref1==str);}
bool operator<(const char *str,const String&ref1){return strcmp(String(str).c_str(),ref1.c_str())<0?true:false;}
bool operator<=(const char *str,const String& ref1){return strcmp(String(str).c_str(),ref1.c_str())<=0?true:false;}
bool operator>(const char *str,const String &ref1){return strcmp(String(str).c_str(),ref1.c_str())>0?true:false;}
bool operator>=(const char *str,const String &ref1){return strcmp(String(str).c_str(),ref1.c_str())>=0?true:false;}

ostream &operator<<(ostream &os,const String &ref) /* 不能重载为成员函数*/
{
	os<<ref.c_str();
	return os;
}
ostream &operator<<(ostream &os,const String::Charproxy&s)
{
	os<<(s._s._str+1)[s._index];
	return os;
}
istream &operator>>(istream &is,String &ref)
{
	char str[65535];
	is>>str;
	ref=str;
	return is;
}
String operator+(const String & ref1,const String &ref2){return String(ref1)+=ref2;}
String operator+(const String & ref1,const char *str){return String(ref1)+=String(str);}
String operator+(const char *str,const String &ref){return String(str)+=ref;}


int  main()
{
# define Refcount Get_refcount
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
	cout<<"std:move"<<endl;
	s1=std::move(s2);
	cout<<"s1: "<<s1<<endl;
	/*cout<<"s2: "<<s2<<endl;*/
	cout<<"s3: "<<s3<<endl;
	cout<<"s1 refcount:  "<<s1.Refcount()<<endl;
	/*cout<<"s2 refcount:  "<<s2.Refcount()<<endl;*/
	cout<<"s3 refcount:  "<<s3.Refcount()<<endl;
	printf("s1 pointer: %p\n",s1.c_str() );
	/*printf("s2 pointer: %p\n",s2.c_str() );*/
	printf("s3 pointer: %p\n",s3.c_str() );

	return 0;
}
