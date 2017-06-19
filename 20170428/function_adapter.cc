/*************************************************************************
  > File Name: function_adapter.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年05月02日 星期二 22时56分31秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename arg1,typename arg2,typename rev>
class ADD1/* 自定义类模板*/
{
	public:
	typedef arg1 first_argument_type; 
	typedef arg2 second_argument_type; 
	typedef rev result_type; 
	int operator()(int x,int y) const
	{return x>y?x:y;}
};
class ADD2   /* 自定义类*/
{
	public:
	typedef int first_argument_type; 
	typedef int second_argument_type; 
	typedef int result_type; 
	int operator()(int x,int y) const
	{return x>y?x:y;}
};
class ADD3:public std::binary_function<int,int,int>  /*继承 */
{
	public:
	int operator()(int x,int y) const
	{return x>y?x:y;}

};
class ADD5 
{
	public:
	int operator()(int x,int y) const
	{return x>y?x:y;}
	int a=10;
	float d=10.0;
	/*static int  b=20;*/ /* c++11中静态非常数据成员必须在外初始化*/
	const int e=20;  
	const double j=20;
	constexpr static float f=10;
};

int ADD4(int x,int y){return x>y?x:y;}  /* 普通函数*/

void ADD6(int w,int x,int z,const int &a,int &b)
{
	cout<<w<<","<<x<<","<<z<<","<<a<<","<<b<<endl;
	cout<<&a<<","<<&b<<endl;
}
void test0()
{
	cout<<"函数绑定器"<<endl;
	
	ADD1<int,int,int> add1; /* 使用自定义带参数信息的模板*/
	auto funobj1=std::bind1st(add1,2);/* 绑定二元函数对象的第一个参数，返回一元函数对象,绑定对象采用左值*/
	auto funobj2=std::bind2nd(ADD1<int,int,int>(),3);/* 绑定二元函数对象的第二个参数，返回一元函数对象，绑定对象采用右值*/
	cout<<funobj1(5)<<","<<funobj2(5)<<endl;
	
	ADD2 add2; /* 使用自定带参数信息的类*/
	auto funobj3=std::bind1st(ADD2(),2);/* 定对象采用右值值*/
	auto funobj4=std::bind2nd(add2,3);/* 绑定对象采用采用左值*/
	cout<<funobj3(5)<<","<<funobj4(5)<<endl;
	/*下面采用更加简单的写法*/

	/* 使用公共继承自二元函数对象模板的派生类*/
	cout<<(std::bind2nd(ADD3(),3))(5)<<endl;/* 绑定二元函数对象的第二个参数，返回一元函数对象，绑定对象采用右值*/
	/* 使用普通函数*/
	cout<<(std::bind2nd(std::ptr_fun(ADD4),3))(5)<<endl;/* 绑定二元函数对象的第二个参数，返回一元函数对象，绑定对象采用右值*/
	
	//cout<<std::bind2nd(std::ptr_fun( ADD5()::operator()),3)(5)<<endl;/* 绑定二元函数对象的第二个参数，返回一元函数对象，绑定对象采用右值*/
	/* 使用bind，采用右值做绑定*/
	cout<<std::bind(ADD1<int,int,int>(),1,std::placeholders::_1)(5,10)<<endl; /* 调用时可以传入至多9参数，但是与占位符对应的参数无效*/
	cout<<std::bind(ADD2(),1,std::placeholders::_2)(5,10)<<endl;/* 序号指的是传入参数的顺序,占位符的位置在哪，对应的参数就传给谁*/ 
	cout<<std::bind(ADD3(),1,std::placeholders::_1)(5)<<endl;
	cout<<std::bind(ADD4,1,std::placeholders::_1)(5)<<endl;
	cout<<std::bind(&ADD5::operator(),ADD5(),1,std::placeholders::_1)(5)<<endl;  /* 绑定类成员函数指针*/
	cout<<std::bind(&ADD5::a,ADD5())(5)<<endl;  /* 绑定类数据成员指针*/
	int a=5,b=6;
	cout<<&a<<","<<&b<<endl;
	std::bind(ADD6,std::placeholders::_1,2,3,std::cref(a),std::ref(b))(4,5);/* 绑定的形参为引用*/
	
	return ;
}
/*************************************************************************
    > File Name: mem_fn_mem_fun_mem_fun_ref.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月03日 星期三 20时48分53秒
 ************************************************************************/
class Numval
{
	private:
		int _val;
	public:
		Numval(/*arguments*/):_val(0)//构造函数
		{
			/*fucntion_body*/
		}
		Numval(int x):_val(x)
		{
		}
		~Numval()//析构函数
		{
		}
		bool Display()
		{
			cout<<_val<<",";
			return true;
		}
		bool isEven()
		{
			return (bool)_val%2;
		}
		bool isPrime()
		{
			for(int i=2;i<=_val/2;++i)
				if(_val%i==0)
					return false;
			return true;
		}
		friend ostream& operator<<(ostream &os,const Numval &ref);
};
ostream &operator<<(ostream & os,const  Numval & ref)
{
	os<<ref._val;
	return os;
}


void test2()
{

	cout<<"成员函数适配器和否定器"<<endl;
	vector<Numval>vec(13);
	int i=0;
	for(vector<Numval>::iterator it=vec.begin();it!=vec.end();++it)
	{
		*it=Numval(++i);
	}
	/* 用mem_fn，将成员函数转为函数对象*/
	std::for_each(vec.begin(),vec.end(),std::mem_fn(&Numval::Display)); /* for_each 的使用方法,一种遍历方法*/
	cout<<endl;
	/* erase,remove惯用法，*//* 用mem_fun_ref，容器元素是对象时，将成员函数转为*/
	vec.erase(std::remove_if(vec.begin(),vec.end(),std::mem_fun_ref(&Numval::isPrime)),vec.end());/* 容器元素是对象用mem_fun_ref,是对象指针用mem_fun，mem_fn两种都可已使用*/
	std::ostream_iterator<Numval> osit(cout,",");
	std::copy(vec.begin(),vec.end(),osit); /* 也是一种遍历方法*/
	cout<<endl;


	/* 当容器元素对象指针时，用mem_fun*/
	vector<Numval*>vec1(13);
	Numval arr[13]={Numval(1),Numval(2),Numval(3),Numval(4),Numval(5),Numval(6),Numval(7),Numval(8),Numval(9),Numval(10),Numval(11),Numval(12),Numval(13)};
	i=0;
	for(vector<Numval*>::iterator it=vec1.begin();it!=vec1.end();++it)
	{
		*it=arr+i++;
	}
	/* 用mem_fn，将成员函数转为函数对象*/
	std::for_each(vec1.begin(),vec1.end(),std::mem_fn(&Numval::Display)); /* for_each 的使用方法,一种遍历方法*/
	cout<<endl;
	/* erase,remove惯用法，*/
	/* 用mem_fun，容器元素是对象指针时，将成员函数转为函数对象*/
	/*not1用于逆转一谓词，not2逆转后院谓词,返回相反的函数对象*/
	vec1.erase(std::remove_if(vec1.begin(),vec1.end(),std::not1(std::mem_fun(&Numval::isPrime))),vec1.end());/* 容器元素是对象用mem_fun_ref,是对象指针用mem_fun，mem_fn两种都可已使用*/
	std::for_each(vec1.begin(),vec1.end(),std::mem_fn(&Numval::Display)); /* for_each 的使用方法,一种遍历方法*/
	cout<<endl;
	
	return ;
}



int  main()
{
	test0();
	test2();
	return 0;
}
