/*************************************************************************
    > File Name: textquery.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月22日 星期一 12时26分38秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class textquery
{
	private:
		map<string,int>_dict;/* 记录单词出现的频率*/
		map<string,set<size_t>>_line;/* 记录每个单词在哪些行*/
		vector<string>_line2;/* 记录每一行*/
	public:
		void readfile(const string &finename);
		void query(const string &filename);
};
void textquery::readfile(const string &filename)
{
	ifstream ifs(filename,std::ios::in);
	assert(ifs);//或者 if(!ifs.good()){cout<<filename<<"open failed"<<endl;return;}
	string line,word;
	size_t linenumber=0;
	while(std::getline(ifs,line))
	{
		_line2.push_back(line); //录入每一行
		std::replace_if(line.begin(),line.end(),std::not1(std::ptr_fun(isalpha)),' '); /* 将每一个非字母字符替换为空格*/
		istringstream iss(line,std::ios::in);
		while(iss>>word)
		{
			map<string,int>::iterator it=_dict.find(word); /* 查看_dict中是否有该单词*/
			if(it==_dict.end())/* 如果不存在则插入一个pair*/
			{
				_dict.emplace(word,1);
				/*或者_dict.emplace_hint(_dict.end(),word,1);*/
				/*或者_dict.insert(std::pair<string,int>(word,1));*/
				/*或者_dict.insert(std::make_pair(word,1));*/
				/*或者_dict.insert(_dict.end(),std::make_pair(word,1));*/
			}
			else /* 否则频率+1*/
			{
				++it->second;
			}
			map<string,set<size_t>>::iterator it2=_line.find(word);/* 查看_line中是否存在该单词*/
			if(it2==_line.end())/* 如果不存在，就插入一个pair，且记录其行号*/
			{
				_line.emplace(word,set<size_t>()).first->second.insert(linenumber);
			}
			else/* 否则插入行号，由于set，map，主键都是唯一的，因此同一行的相同元素不会重复插入*/
			{
				it2->second.insert(linenumber);
			}
			/*
			 * ++_dict[word];
			 * _line[word].intsert(linenumber);  // 如果map的operator[]不存在则会创建
			 */
		}
		++linenumber;/* 行号+1*/
	}
	ifs.close(); /* 文件流关闭*/
}

void textquery::query(const string &word)
{
	map<string,int>::iterator it=_dict.find(word);/* 查看是否存在该单词*/
	if(it!=_dict.end())/* 如果存在*/
	{
		cout<<"   "<<word<<"出现"<<it->second<<"次"<<endl;/* 输出出现的频率*/
		for(const size_t & elem :_line[word])/* 打印出所在行*/
		{
			cout<<"第"<<elem<<"行： "<<_line2[elem]<<endl;
		}
	}
	else
	{
		cout<<"  !本文不含此单词"<<endl;
	}
}


int  main(int argc, char *argv[])
{
	if(argc!=2)
	{
		cout<<"argc is wrong"<<endl;
		exit(-1);
	}
	textquery tq;
	tq.readfile(argv[1]);
	string word;
	cout<<"请输入要查询的单词: ";
	cin >>word;
	while(word!="@#$")
	{
		tq.query(word);
		cout<<"请输入要查询的单词";
		cin>>word;
	}
	return 0;
}
