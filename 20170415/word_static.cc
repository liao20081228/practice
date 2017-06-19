/*************************************************************************
    > File Name: word_static.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月16日 星期二 23时29分55秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
struct record   /*C++中的结构体和类的区别只是在于一个是默认public而类默认private*/
{
	int freq;
	string word;
	record(const string & w,int f):freq(f),word(w)
	{

	}
	bool operator<(const record &ref) const
	{
		return this->word<ref.word;
	}
};
class wordstatic
{
	private:
		vector<struct record>_dict;
	public:
		void readfile(const string &filename)
		{
			ifstream ifs(filename,std::ios::in);/* 也可以创建一个空流，再用open方法打开*/
			if(!ifs.good())
			{
				cout<<filename<<"打开错误"<<endl;
				return ;
			}	
			string line,word;
			while(std::getline(ifs,line))  /* 依次读入每一行*/
			{
				istringstream iss(line,std::ios::in);
				while(iss>>word)  /* 读入每一个单词*/
				{
					vector<struct record>::iterator it=_dict.begin();
					for(;it!=_dict.end();++it)/* 遍历字典看是否有重复*/
					{
						if(it->word==word)/* 有重复，则频率加一*/
						{
							++(it->freq);
							break;
						}
						
					}
					if(it==_dict.end())/* 如果没有重复则新增*/
					{
						_dict.push_back(record(word,1));
					}
				}
			}
			ifs.close();
			std::sort(_dict.begin(),_dict.end());
		}
			void writefile(const string & filename)
			{
				ofstream ofs(filename,std::ios::out);
				if(!ofs.good())
				{
					cout<<filename<<"打开出错"<<endl;
					return;
				}
				for( struct record& elem:_dict)
				{
					ofs<<elem.word<<" "<<elem.freq<<endl;
				}
				ofs.close();
			}
};
int  main()
{
	wordstatic ws;
	ws.readfile("./The_Holy_Bible.txt");
	ws.writefile("dic.txt");
	return 0;
}
