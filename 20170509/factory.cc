/*************************************************************************
  > File Name: figure.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月26日 星期五 10时37分40秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
/*
 *1.虚函数在派生类中自动成为虚函数，构造函数不能是虚函数，但含虚函数的类应该具有虚析构函数，因为析构若不为虚，则基类指针只能调用基类析构函数，不能调用派生类析构函数,虚析构函数在其派生类中也是自动称为虚函数
 *2.虚函数的的类的对象的第一个成员是指向虚函数表的指针，该表记录了该类的所有虚函数，派生类会覆盖基类的虚函数
 *3.虚基派生类对象的第一个成员是指向虚基表的指针，该表记录该类的所有虚基类，同一个虚基类会发生覆盖
 *4.多态分为静态（重载）和动态（虚函数）
 *5.当通过指向派生类的基类指针访问虚函数时，就会形成多态
 *6.派生类中要对虚函数重定义，如果参数不同会发成隐藏，如果只有返回值不同则发生冲突
 *7.基类与派生类同名成员发生隐藏，如果是同名虚函数则发生覆盖，同一个类中同名函数则重载，但不能依靠返回值来重载
 *8.确定函数调用的具体函数的过程叫做联编，在编译时完成的联编叫静态联编，如：重载，在运行时才能完成的联编叫动态联编，如，虚函数
 *9.通过对象访问成员函数取决于对象类型，通过指针或引用访问非虚函数取决于指针类型，访问虚函数取决于指针所指对象的类型。在
 * 成员函数中如果用this或省略this访问虚函数，采用动态联编，如果作用域限定符则采用静态联编。在构造和析构函数中访问虚函数即使使用this指针也只能采用静态联编
 *10.首先通过派生类构造函数调用虚基类构造函数，在按照继承顺序调用基类构造函数，再按声明顺序调用对象成员的构造函数。
 * 析构时通过派生类析构函数，先调用对象成员的析构函数，再调用基类析构函数，最后调用虚基类析构函数
 *11.若无法或无必要实现虚函数，则可以声明为纯虚函数，纯虚函数不能调用，只是提供接口
 *12.含纯虚函数的类是抽象类，不能定义对象，但可以定义指针和派生类，只有当派生类中所有纯虚函数都被重定义时，才能定义对象
 *13.只有protected构造函数的类不能定义对象但能派生类也是一种抽象类
 *14.可以用static静态成员函数为没有public构造函数的创建对象。
 *15.typeid可以测试表达式类型，返回typeinfo，里面有一个name（）成员，表示类型名，typeinfo重载了==和!=，可以用来判断类型
 *16.dynamic_csat用于将指向派生类对象的基类指针转为派生类指针以及相反过程，用于上行转换时等效于static_cast
 */
/*
 *1.多基派生时要访问多个基类的同名成员应该用作用域限定符，共同基派生时访问共同基成员应用作用域限定符或者虚基派生
 *2.构造和析构函数、new delete =，友元关系不能继承
 *3.派生类内部只有基类的私有成员不能访问，派生类的外部只有公有继承的基类的public成员可以访问
 *4.派生类构造函数缺省或者没有显示调用基类构造函数，基类构造函数应缺省或无参或所有参数有默认值
 *  派生类构造函数显示调用基类构造函数，基类应该具有被调用的构造函数
 *5.派生类定义了拷贝构造函数和赋值运算符函数则不会自动调用基类的，需要手动调用，否则派生类执行缺省操作，基类执行定义的操作
 *6.如果只复用原类型用组合，如果要复用原类型的接口用继承，优先使用组合
 *7.派生对象，指针，引用可以赋值给基类对象指针引用
 */

class IFigure
{
	public:
		virtual double DoGetArea()=0;
		virtual void DoDisplay()=0;
};
class CCircle:public IFigure
{
	private:
		double __cm_dRadius;
	public:
		CCircle(double Radius):__cm_dRadius(Radius)
		{
		}
		virtual double DoGetArea()
		{
			return 3.14*pow(__cm_dRadius,2);
		}
		virtual void DoDisplay()
		{
			cout<<DoGetArea()<<endl;
		}
};
class CRectangle:public IFigure
{
	private:
		double __cm_dLength,__cm_dWidth;
	public:
		CRectangle(double Length,double Width):__cm_dLength(Length),__cm_dWidth(Width)
		{

		}
		virtual double DoGetArea()
		{
			return __cm_dLength*__cm_dWidth;
		}
		virtual void DoDisplay()
		{
			cout<<DoGetArea()<<endl;
		}
};
class CTriangle:public IFigure
{
	private:
		double __cm_dUpLength,__cm_dDownLength,__cm_dHigh;
	public:
		CTriangle(double UpLength,double DownLength,double High):__cm_dUpLength(UpLength),__cm_dDownLength(DownLength),__cm_dHigh(High)
		{
		}
		virtual double DoGetArea()
		{
			return (__cm_dUpLength+__cm_dDownLength)/2*__cm_dHigh;
		}
		virtual void DoDisplay()
		{
			cout<<DoGetArea()<<endl;
		}
};

void gDisplay(IFigure *pIFigure)
{
	pIFigure->DoDisplay();
}
//问题：如果每个对象的构造参数获取都很繁琐时，每创建一个对象就要进行一次获取构造参数
//工厂模式就是将每个对象的创建之前的工作都交给另一个类（工厂）来做
class IFactory
{
	public:
		 IFigure * Creat()
		 {
			 return _FactoryMethod();
		 }
	protected:
		 virtual IFigure*_FactoryMethod()=0;
};
class CCreatCircle:public IFactory
{
	public:
		virtual IFigure *_FactoryMethod()
		{
			//load xml
			//...
			return new CCircle(10);
		}
};
class CCreatRectangle:public IFactory
{
	public:
		virtual IFigure *_FactoryMethod()
		{
			//load xml
			//...
			return new CRectangle(10,10);
		}
};

class CCreatTriangle:public IFactory
{
	public:
		virtual IFigure *_FactoryMethod()
		{
			//load xml
			//...
			return new CTriangle(10,10,10);
		}
};

int  main()
{ 
	IFactory *pIFactory;
	IFigure *pIFigure;
//多态实现
	pIFactory=new CCreatCircle;
	pIFigure=pIFactory->Creat();
	gDisplay(pIFigure);

	pIFactory=new CCreatRectangle;
	pIFigure=pIFactory->Creat();
	gDisplay(pIFigure);

	pIFactory=new CCreatTriangle;
	pIFigure=pIFactory->Creat();
	gDisplay(pIFigure);
	return 0;
}
