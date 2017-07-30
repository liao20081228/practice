/*************************************************************************
  > File Name: auto_ptr.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月09日 星期二 12时04分36秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
using std::auto_ptr;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
/*
 * auto_ptr
 *不能托管栈指针
 *不能托管堆数组的指针
 *不能做容器元素
 *不能auto_ptr指向同一对象
 *不能将裸指针转为auto_ptr对象，必须通过构造函数
 *auto_ptr对象拷贝和赋值时，原对象会失效 
 */
class point
{
	public:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)
	{
	}
		void display()
		{
			cout<<_x<<","<<_y<<endl;
		}
};
class point3d :public point
{
	private :
		int _z;
	public:
		point3d(int x,int y,int z):point(x,y),_z(z)
	{
	}
		void display()
		{
			cout<<_x<<","<<_y<<","<<_z<<endl;
		}
};
int   test0()
{
	double *p=new double(7.77);
	double *p0=new double(6.66);
	std::auto_ptr<double> ap1(p);
	cout<<"p: "<<p<<endl;
	cout<<"*p: "<<*p<<endl;
	cout<<"ap1.get: "<<ap1.get()<<endl;
	cout<<"*ap1: "<<*ap1<<endl;
	//
	cout<<"拷贝后"<<endl;
	std::auto_ptr<double> ap2(ap1); /* 拷贝时，原对象失效*/
	cout<<"p: "<<p<<endl;
	cout<<"*p: "<<*p<<endl;
	cout<<"ap1.get: "<<ap1.get()<<endl;
	cout<<"ap2.get: "<<ap2.get()<<endl;
	cout<<"*ap2: "<<*ap2<<endl;
	//
	cout<<"重置ap2"<<endl;
	ap2.reset(p0);
	cout<<"p: "<<p<<endl;
	cout<<"*p: "<<*p<<endl;
	cout<<"p0: "<<p0<<endl;
	cout<<"*p0: "<<*p0<<endl;
	cout<<"*ap2: "<<*ap2<<endl;
	cout<<"ap2.get: "<<ap2.get()<<endl;
	//
	cout<<"释放ap2"<<endl;
	ap2.release();
	cout<<"p0: "<<p0<<endl;
	cout<<"*p0: "<<*p0<<endl;
	cout<<"&ap2: "<<&ap2<<endl;
	/*ap1=p;*//* 裸指针不能直接变成auto_ptr对象*/
	//
	std::auto_ptr<int >ap4(new int(10));/*自动调用类型转换函数,用临时对象构造*/
	cout<<"*ap4 "<<*ap4<<endl;
	cout<<"ap4.get: "<<ap4.get()<<endl;
	//
	point3d *p2=new point3d(1,2,3);/*自动调用， 拷贝派生对象为基类对象*/
	std::auto_ptr<point3d>ap5(p2);
	std::auto_ptr<point>ap6(ap5);
	ap6->display();
	return 0;
}
/*
 *unique_ptr
 *(1)完全拥有它所指向的对象
 *(2)无法进行拷贝复制、拷贝赋值操作
 *(3)保存指向某个对象的指针，当它本身被删除释放的时候，会使用给定的删除器释放它指向的对象
 *(4)具有移动(std::move)语义，可做为容器元素
 *(5)可以托管动态数组
 */
void test1() /* unique_ptr 具有移动语义，可做容器元素*/
{
	unique_ptr<double>up0(new double(8.88));
	/*vector<unique_ptr<double>>vec0{up0};*//* 必须通过转为右值才能拷贝、赋值*/
	vector<unique_ptr<double>>vec1;
	vec1.push_back(std::move(up0));
	cout<<*vec1.front()<<endl;
}
void test2(/*arguments*/)
{
	//constructor
	unique_ptr<int>up0;/* default*/
	unique_ptr<int>up1(nullptr);/* from nullptr*/
	int *p0=new int(10);
	unique_ptr<int>up2(p0);/* frome name pointer*/
	cout<<"*up2: "<<*up2<<endl;
	unique_ptr<int>up3(new int(15));/*from anonymous pointer */
	cout<<"*up3: "<<*up3<<endl;
	unique_ptr<int,std::default_delete<int>>up4(new int(20),std::default_delete<int>());/* from pointer +lvalue deleter*/
	cout<<"*up4: "<<*up4<<endl;
	unique_ptr<int,std::default_delete<int>>up5(new int(25),std::default_delete<int>());/* frome pointer +rvalue deleter*/
	cout<<"*up5: "<<*up5<<endl;
	unique_ptr<int>up6(std::move(up2));/* move semantics*/
	cout<<"*up6: "<<*up6<<endl;
	unique_ptr<int>up7(unique_ptr<int,std::default_delete<int>>(new int(30),std::default_delete<int>())); /* move-cast*/
	cout<<"*up7: "<<*up7<<endl;
	unique_ptr<int>up8(std::auto_ptr<int>(new int(35))); /* from auto_ptr<typename U>*/
	cout<<"*up8: "<<*up8<<endl;
	/*unique_ptr<int>up1=new int(10); *//* 禁止裸指针直接转换，explicit*/
	//
	//
	//opretor=
	/*up1=new int(40);*/ /* 禁止裸指针直接转换*/
	up0=nullptr; /* 空指针赋值*/
	if(up2) /*operator bool()*/
		cout<<"np2 has object"<<endl;
	else
		cout<<"np2 has no object"<<endl;
	if(up6) /*operator bool()*/
		cout<<"np6 has object"<<endl;
	else
		cout<<"np6 has no object"<<endl;
	/* 移动赋值*/
	up2=std::move(up6);
	//
	if(up2) /*operator bool()*/
		cout<<"np2 has object"<<endl;
	else
		cout<<"np2 has no object"<<endl;
	if(up6) /*operator bool()*/
		cout<<"np6 has object"<<endl;
	else
		cout<<"np6 has no object"<<endl;
	// get()返回持有的指针
	cout<<"up2.get(): "<<up2.get()<<endl; 
	cout<<"*up2.get(): "<<*up2.get()<<endl;
	//get_deleter()
	//up2.get_deleter()
	//operator *
	cout<<"*up2: "<<*up2<<endl;
	//operator []
	unique_ptr<int[]>up9(new int[5]);
	cout<<"up9[0]:"<<up9[0]<<endl;
	up9[0]=40;
	cout<<"up9[0]:"<<up9[0]<<endl;
	//swap() 只是交换所有权，不会释放空间
	int *p1=new int(45);
	unique_ptr<int>up10(p1);
	up2.swap(up10);
	cout<<"*p0: "<<*p0<<endl;
	cout<<"*p1: "<<*p1<<endl;
	cout<<"*up2: "<<*up2<<endl;
	cout<<"*up10: "<<*up10<<endl;
	cout<<"std::swap()"<<endl;
	std::swap(up10,up2);
	cout<<"*p0: "<<*p0<<endl;
	cout<<"*p1: "<<*p1<<endl;
	cout<<"*up2: "<<*up2<<endl;
	cout<<"*up10: "<<*up10<<endl;
	cout<<"reset()会销毁空间，要想不损坏空间，用realse"<<endl;
	up2.reset(p1);
	cout<<"*p0: "<<*p0<<endl;
	cout<<"*p1: "<<*p1<<endl;
	cout<<"*up2: "<<*up2<<endl;
	cout<<"release 不会销毁空间，只是释放持有的指针"<<endl;
	up2.release();
	cout<<"*p0: "<<*p0<<endl;
	cout<<"*p1: "<<*p1<<endl;
	/*cout<<"*up2: "<<*up2<<endl;*/ /* 释放后不能再取内容*/
	cout<<"*up10: "<<*up10<<endl;
}
/*
 *shared_ptr
 *(1)引入了引用计数器表示当前有多少个指针指向同一个内存区
 *(2)析构函数只在引用计数为0时才销毁内存,没拷贝一个引用计数加1
 *(3)赋值与拷贝都是浅拷贝，会出现循环引用的问题
 */
void  test3()
{
	/*constructor*/
	shared_ptr<int>sp1; /* default*/
	shared_ptr<int>sp2(nullptr);/* from nullptr*/
	int *p0=new int(5);
	shared_ptr<int>sp3(p0);/* from name  pointer*/
	shared_ptr<int>spr(new int(10));/* from anonymous pointer*/
	shared_ptr<int>sp4(p0,std::default_delete<int>()); /* from pointer with deleter*/
	shared_ptr<int>sp5(nullptr,std::default_delete<int>());/*from nullptr with deleter */
	shared_ptr<int>sp6(p0,std::default_delete<int>(),std::allocator<int>());/* from pointer with deleter and allocator*/
	shared_ptr<int>sp7(nullptr,std::default_delete<int>(),std::allocator<int>());/* from nullptr with deleter and allocator*/
	const shared_ptr<int>sp8(sp3);/* copy shared_ptr*/
	shared_ptr<int>sp9(sp8);/* copy const shared_ptr*/
	shared_ptr<int>sp10(weak_ptr<int>(shared_ptr<int>(new int(15)))); /* copy from a weak_ptr*/
	shared_ptr<int>sp11(std::move(sp8));/* move from a object*/
	shared_ptr<int>sp12(shared_ptr<int>(new int(20)));/* move from a anonymous object*/
	shared_ptr<int>sp13(auto_ptr<int>(new int(25)));/* move from a auto_ptr*/
	shared_ptr<int>sp14(unique_ptr<int>(new int(30)));/* move from a unique_ptr*/
	shared_ptr<int>sp15(sp3,p0);/* alias of another shared_ptr*/
	//member function
	//operator =
	sp1=sp3;/* copy from a named object*/
	sp2=shared_ptr<int>(new int(10));/* copy from a anonymous object*/
	sp2=std::move(sp1);/* move from a named object */
	sp2=auto_ptr<int>(new int(15)); /* move from auto_ptr*/
	sp2=unique_ptr<int>(new int(20));/* move from unique_ptr*/
	//get
	int *p3=new int(25);
	shared_ptr<int>sp16(p3);
	cout<<"get: "<<sp16.get()<<endl;
	//use_count
	cout<<"sp16.use_count: "<<sp16.use_count()<<endl;
	shared_ptr<int>sp17(p3);/* 直接将指针托管给另一个并不会曾加引用计数*/
	cout<<"sp16.use_count: "<<sp16.use_count()<<endl;
	shared_ptr<int>sp18(sp16);/* 只有拷贝shared_ptr才能增加引用计数*/
	cout<<"sp16.use_count: "<<sp16.use_count()<<endl;
	//unique
	int *p4=new int(30);
	shared_ptr<int>sp19(p4);
	cout<<"sp19.unique(): "<<sp19.unique()<<endl;
	shared_ptr<int>sp20(p4);/*新建立并不会返回false*/
	cout<<"sp19.unique(): "<<sp19.unique()<<endl;
	shared_ptr<int>sp21(sp19);/* 拷贝才会返回false*/
	cout<<"sp19.unique(): "<<sp19.unique()<<endl;
	//owner_before
	/*
	 *用当前指针与other比较：如果同为空或者同时指向同一个对象（包含继承关系,新建立不会，拷贝才会），
	 *就返回false;如果是其它情况，则用指针所指向的对象的地址来比较大小，若当前指针的地址<other的地址，
	 *则返回true，否则返回false。
	 */
	cout<<"owner_before: "<<sp19.owner_before(sp20)<<endl;
	cout<<"owner_before: "<<sp19.owner_before(sp21)<<endl;
	cout<<"owner_before: "<<sp19.owner_before(sp3)<<endl;
	//operator */->/[]
	cout<<"*sp16: "<<*sp16<<endl;
	cout<<"*sp19: "<<*sp19<<endl;
	cout<<"*sp20: "<<*sp20<<endl;
	cout<<"*sp21: "<<*sp21<<endl;
	//swap
	sp21.swap(sp16);
	cout<<"*sp16: "<<*sp16<<endl;
	cout<<"*sp19: "<<*sp19<<endl;
	cout<<"*sp20: "<<*sp20<<endl;
	cout<<"*sp21: "<<*sp21<<endl;
	//reset 会销毁原对象
	int *p5=new int(40);
	int *p6=new int(45);
	shared_ptr<int>sp23(p5);
	cout<<"*p5: "<<*p5<<endl;
	cout<<"*sp23: "<<*sp23<<endl;
	sp23.reset(p6);
	cout<<"*p5: "<<*p5<<endl;
	cout<<"*sp23: "<<*sp23<<endl;
	//nomember function
	//std::swap
	cout<<"*sp16: "<<*sp16<<endl;
	cout<<"*sp23: "<<*sp23<<endl;
	std::swap(sp16,sp23);
	cout<<"*sp16: "<<*sp16<<endl;
	cout<<"*sp23: "<<*sp23<<endl;
	//get_deleter
	cout<<"std::get_deleter: "<<std::get_deleter<std::default_delete<int>,int>(sp6)<<endl;
	//relation operator
	int *p8=new int(55);
	int *p7=new int(50);
	shared_ptr<int>sp25(p8);
	shared_ptr<int>sp24(p7);
	cout<<"*sp24: "<<*sp24<<endl;
	cout<<"*sp25: "<<*sp25<<endl;
	cout<<"sp24>sp25: "<<(sp24>sp25)<<endl;
	cout<<"sp24>=sp25: "<<(sp24>=sp25)<<endl;
	cout<<"sp24<sp25: "<<(sp24<sp25)<<endl;
	cout<<"sp24<=sp25: "<<(sp24<=sp25)<<endl;
	cout<<"sp24==sp25: "<<(sp24==sp25)<<endl;
	cout<<"sp24!=sp25: "<<(sp24!=sp25)<<endl;
	//make_shared
	shared_ptr<int>sp26=std::make_shared<int>(60);
	cout<<"*sp26: "<<*sp26<<endl;
	//allocate_shared
	shared_ptr<int>sp27=std::allocate_shared<int,std::allocator<int>>(std::allocator<int>(),65);
	//operator <<
	cout<<"cout<<sp24: "<<sp24<<endl;
	cout<<"cout<<sp24: "<<sp24<<endl;
	//static_pointer_cast<int>等效static_cast<int*> 只能用于基类与派生类指针
	float*p9=new float(65);
	shared_ptr<float>sp28(p9);
	shared_ptr<int>sp29;
	/*sp29=std::static_pointer_cast<int>(sp28); */ /* 强制指针转化只能派生类为基类,不能是其他类型指针之间的转化*/
	point3d *p11=new point3d(4,5,6);
	shared_ptr<point3d>sp30(p11);
	shared_ptr<point>sp31=std::static_pointer_cast<point>(sp30);
	sp31->display();
}
/*
 *weak_ptr
 *1.弱引用，并不增加对象的引用计数，但它知道对象是否存在。如果存在，提升为shared_ptr成功；否则，提升失败。
 *通过weak_ptr，访问对象的成员的时候，要提升为shared_ptr
 */
void test4()
{ 
	//constructor
	weak_ptr<int>wp1;//default
	const weak_ptr<int>wp2(wp1);//copy;
	weak_ptr<int>wp3(wp2);//copy const
	int *p=new int(5);
	shared_ptr<int>sp1(p);
	weak_ptr<int>wp4(sp1);/* from shared_ptr*/
	//member function
	//use_count
	weak_ptr<int>wp5(wp4);/* from shared_ptr*/
	cout<<"use_count: "<<wp5.use_count()<<endl;
	//expired 所指对象是否过期
	cout<<"expired: "<<wp4.expired()<<endl;
	//lock  反回对应share_ptr
	shared_ptr<int>sp2=wp4.lock();
	cout<<"*sp2: "<<*sp2<<endl;
	//swap
	int *p1=new int(10);
	shared_ptr<int>sp4(p1);
	wp1=sp4;
	wp1.swap(wp4);
	shared_ptr<int>sp3=wp4.lock();
	cout<<"*sp3: "<<*sp3<<endl;
	wp1.swap(wp4);
	shared_ptr<int>sp5=wp4.lock();
	cout<<"*sp5: "<<*sp5<<endl;
	//std::swap()
	std::swap(wp4,wp1);
	shared_ptr<int>sp6=wp4.lock();
	cout<<"*sp6: "<<*sp6<<endl;
	//owner_before
	cout<<" wp4.owner_before(wp1)): "<<(wp4.owner_before(wp1))<<endl;;
	cout<<" wp4.owner_before(sp6)): "<<(wp4.owner_before(sp6))<<endl;;
}
int  main()
{
	cout<<"==========auto_ptr============="<<endl;
	test0();
	cout<<"==========unique_ptr============="<<endl;
	test1();
	test2();
	cout<<"==========shared_ptr============="<<endl;
	test3();
	cout<<"==========weak_ptr============="<<endl;
	test4();
	return 0;
}
