/*************************************************************************
    > File Name: safefile.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月09日 星期二 09时59分59秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/

/*
 *RAII 1.获取资源就构建对象或者托管资源
 *     2.析构时释放资源
 *     3.严格保证该资源的获取与释放顺序相反
 *     4.不允许拷贝和赋值
 *     5.要提供专用的方法来访问资源
 */

class safefile
{
	private:
		FILE *_fp;
	public:
		safefile(const string & filename ):_fp(fopen(filename.c_str(),"w+"))//构造函数
		{
			if(!_fp)
			{
				cout<<"打开出错"<<endl;
			}
		}
		safefile(FILE *fp):_fp(fp)
		{}
		~safefile()//析构函数
		{
			if(_fp)
			{
				fclose(_fp);
				cout<<"关闭文件"<<endl;
				
			}
		}
		size_t write(const string &str)
		{
			return fwrite(str.c_str(),1,str.size(),_fp);
		}
	private: /* RAII 禁止拷贝和赋值*/
		safefile(const safefile &lref)/*init_member_lsit*///拷贝构造函数
		{
		}
		safefile & operator=(const safefile &lref)//拷贝赋值运算符函数
		{
			if(this!=&lref)
			{
			}
			return *this;
		}
};

int  main()
{
	safefile sa("test.txt");
	sa.write("wangdap,hello");
	return 0;
}
