/*************************************************************************
    > File Name: operator_new_delete.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月15日 星期六 15时13分01秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
class student
{
	private:
		int _num;
		char _name[10];
	public:
		student(int num,const char *name):_num(num)//构造函数
		{
			strcpy(_name,name);
			cout<<"student(int,char)"<<endl;
		}
		/*member*/
		~student()//析构函数
		{
			cout<<"~student()"<<endl;
		}
		student(const student &ref):_num(ref._num)//拷贝构造函数
		{
			strcpy(_name,ref._name);
			cout<<"student(const student&ref)"<<endl;
		}
		student & operator=(const student &ref)//赋值运算符函数
		{
			if(this==&ref)
				return *this;
			_num=ref._num;
			memset(_name,'\0',sizeof(_name));
			strcpy(_name,ref._name);
			cout<<"student &operator=(const student &ref)"<<endl;
			
			return *this;
		}
	public:
		void *operator new(size_t sz)
		{
			cout<<"void *operator new(size_t sz)"<<endl;	
			return  (void *)malloc(sz);
		}
	private:
		void operator delete (void *p)
		{
			cout <<"void operator delete(void*p)"<<endl;
			free(p);
		}
	public:
		void print()
		{
			cout<<"num:"<<_num<<endl;
			cout<<"name:"<<_name<<endl;
		}
};
/* 只有当构造和析构函数在public区时才能产生栈对象
 * 只有operator new/delete在public区时才能生存堆对象*/
int  main()
{
	student stu2(2,"mike");
	stu2.print();
	printf("\n");
	student stu4=stu2;
	stu4.print();
	printf("\n");
	student stu5=student(4,"bob");
	stu5.print();
	printf("\n");
	student stu6=student(stu2);
	stu6.print();
	printf("\n");
	stu2=stu4;
	stu2.print();
	printf("\n");
	student *stu7=new student(8,"liao");  //为单个对象申请动态内存<]
	stu7->print();
	(*stu7).print();
	delete stu7;
	printf("\n");
	student stu8[3]={student(10,"xiao"),student(20,"da"),student(30,"gege")};
	stu8[0].print();
	stu8[1].print();
	stu8[2].print();
	printf("\n");
	// student *stu9=new student[3]; #<{(|为对象数组申请动态内存，需要只有一个无参或全部参数具有缺省值的构造函数 |)}>#
	return 0;
}
