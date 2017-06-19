/*************************************************************************
    > File Name: file.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月11日 星期四 10时33分05秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class deleter
{
	public:
		void operator()(FILE *p)
		{
			cout<<"call deleter"<<endl;
			if(p)
			{
				fclose(p);
			}
		}
};

int  main()
{ 
	FILE *fp=fopen("./RAII.cc","r");
	unique_ptr<FILE,deleter>up(fp,deleter());
	char a[100];
	while(fgets(a,sizeof(a),up.get()))
	{
		cout<<a<<endl;
	}
}
