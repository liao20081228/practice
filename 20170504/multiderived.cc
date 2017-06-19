/*************************************************************************
    > File Name: multiderived.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月15日 星期一 21时48分47秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class baseA 
{
	public:
		virtual void a()
		{
			cout<<"a() in baseA"<<endl;
		}
		virtual void b()
		{
			cout<<"b() in baseA"<<endl;
		}
		virtual void c()
		{
			cout<<"c() in baseA"<<endl;
		}

};
class baseB
{
	public:
		virtual void a()
		{
			cout<<"a() in baseB"<<endl;
			
		}
		virtual void b()
		{
			cout<<"b() in baseB"<<endl;
			
		}
		 void c()
		{
			cout<<"c() in baseB"<<endl;
			
		}
		void d()
		{
			cout<<"d() in baseB"<<endl;
			
		}
};
class derived:public baseA,public baseB
{
	public:
		virtual void a()  /*基类与派生类有相同的虚函数，发生覆盖，当基类指针指向派生类对象时，通过基类指针访问哪一个类的虚函数，取决于指针所指对象类型，访问非虚函数取决于指针本身类型*/
		{
			cout<<"a() in derived"<<endl;
			
		}
		void c()/* c非常特殊*/
		{
			cout<<"c()in derived"<<endl;
			
		}
		void d()/* 基类与派生类有同名成员（相同虚函数除外）则发生隐藏，可用作用限定符指明*/
		{
			cout<<"d() in derived "<<endl;
		}
};
int  main()
{
	cout<<"通过派生类对象访问"<<endl;
	derived c;/* 生成一个派生类对象,通过对象访问取决于对象类型*/ 
	c.a();/* 虽然多个基类中有虚函数a()，但是派生类覆盖了，不会导致二义性*/
	//c.b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	c.baseA::b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	c.baseB::b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	c.c(); /* c在一个baseA为虚函数，在baseb中为非虚函数，对baseA相当于覆盖，对baseB相当于隐藏，无论按照什么函数处理都一样*/
	c.d();
	cout<<"通过baseA的指针访问"<<endl;
	baseA *pa=&c;
	pa->a();/* 通过指向派生类对象的基类指针访问虚函数，取决于所指的对象，与指针本身类型无关*/
	pa->b(); /* 由于b（）是虚函数，且在派生类中没有覆盖，如果采用动态联编则无法确定访问的是哪一个，因此采用静态联编，取决于指针本生类型*/
	pa->c();/* c在一个baseA为虚函数，在baseb中为非虚函数，则取决于指针本身类型，按照虚函数处理*/
	//pa->d();/*通过指向派生类对象的基类指针不能访问派生类的非虚成员，也就是说只能访问自己的成员，*/
	cout<<"通过baseB的指针访问"<<endl;
	baseB *pb=&c;
	pb->a();
	pb->b();
	pb->c();/* c在一个baseA为虚函数，在baseb中为非虚函数，则取决于指针本身类型，按照非虚函数处理*/
	pb->d();
	cout<<"通过derived 的指针访问"<<endl;
	derived *pc=&c;
	pc->a();
	//pc->b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	pc->baseA::b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	pc->baseB::b();/*虽然多个基类中有虚函数b（），但是派生类中没有覆盖，因此会导致无法确定要访问哪一个b（），解决方案是用作用域限定福 */
	pc->c();/* c在一个baseA为虚函数，在baseb中为非虚函数，则取决于指针本身类型，无论按照什么函数处理都一样*/
	pc->d();
	return 0;
}
