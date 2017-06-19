/*************************************************************************
  > File Name: operator_overload_point.cc
  > Author: liao20081228
  > Mail: liao20081228@126.com 
  > Created Time: 2017年04月18日 星期二 22时43分12秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in /usr/include by user*/
class data
{
	private:
		int _len;
	public:
		data(int len):_len(len)//构造函数
	{
	}
		/*member*/
		~data()//析构函数
		{
		}
		int length()const
		{
			return _len;
		}
};
class datamiddle
{
	private:
		data * _pdata;
	public:
		datamiddle(int len):_pdata(new data(len))//构造函数,指针=new 数据类型（初值）
		{
		}
		~datamiddle()//析构函数
		{
			delete _pdata;
		}
		data *operator->()
		{
			return _pdata;
		}
};
class DataThird
{
	public:
		DataThird(int len): _len(len)
		{
		}
		datamiddle operator->()
		{
			return datamiddle(_len);
		}
	private:
		int _len;
};
int  main()
{
	DataThird dt(5);
	cout<<dt->length()<<endl;
	cout<<((dt.operator->()).operator->())->length()<<endl;
	return 0;
}
