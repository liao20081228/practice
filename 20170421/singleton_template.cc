/*************************************************************************
    > File Name: singleton_template.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月24日 星期一 22时19分48秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
template<typename T>
class singleton
{
	private:
		static T *_p;
		singleton()
		{
		}
		~singleton()
		{
		}
	public:
		static T *Getinstance()
		{
			if(_p==NULL)
				{
					_p=new T;
					atexit(Destroy);
				}
			return _p;
		}
		static void Destroy()
		{
			if(_p!=NULL)
				delete _p;
			cout<<"Destroy"<<endl;
			
		}
};
template<typename T>
T* singleton<T>::_p=singleton<T>::Getinstance();
class point
{
	private:
		int _x,_y;
	public:
		point(int x=0,int y=0):_x(x),_y(y)
		{
		}
		void print()const
		{
			cout<<"(x,Y)="<<"("<<_x<<","<<_y<<endl;
		}
};
int  main()
{
	point *p1=singleton<point>::Getinstance();
	point *p2=singleton<point>::Getinstance();
	point *p3=singleton<point>::Getinstance();
	printf("p1=%p\n",p1 );
	printf("p2=%p\n",p2 );
	printf("p3=%p\n",p3 );
	
	return 0;
}
