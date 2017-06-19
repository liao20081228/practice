/*************************************************************************
    > File Name: enable_from_this.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 11时59分25秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class point:public std::enable_shared_from_this<point>
{
	private:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)
		{
			cout<<"constructor"<<endl;
		}
		~point()
		{
			cout<<"destructor"<<endl;
			
		}
		shared_ptr<point> add(const point *rhs)
		{
			_x+=rhs->_x;
			_y+=rhs->_y;
			/*return shared_ptr<point>(this);*/ /* 将本对象托管给一个全新的shared_ptr指针*/
			return shared_from_this();/* 返回的指针只是当前shared_ptr的拷贝，引用计数加1*/
		}
friend ostream & operator<<(ostream & os, const point & rhs);
};
ostream & operator <<(ostream &os,const point &rhs)
{
	os<<rhs._x<<","<<rhs._y<<endl;
	return os;
}
int  main()
{
	shared_ptr<point>sp1(new point(4,5));
	cout<<*sp1.get()<<endl;
	shared_ptr<point>sp2(new point(2,3));
	cout<<*sp2.get()<<endl;
	shared_ptr<point>sp3(sp2->add(sp1.get())); 
	cout<<*sp3.get()<<endl;
	cout << "sp3's use_count() = " << sp3.use_count() <<endl;
	return 0;
}
