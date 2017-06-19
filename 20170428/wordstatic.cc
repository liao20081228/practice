/*************************************************************************
    > File Name: wordstatic.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月20日 星期六 19时14分29秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class wordstatic
{
	public:
		void readfile(const string &filename)
		{
			ifstream ifs(filename);
			if(!ifs.good())
			{
				cout<<filename<<"open faild"<<endl;
				return;
			}
			string line,word;
			//c风格字符串的输入方式>> cin.get() cin.getline()，
			//string的输入方式>>，std::getline，这两种会自动调整string的大小
			while(ifs>>line) //while(std:getline(ifs,line))
			{
				istringstream iss(line,std::ios::in);
				while(iss>>word)
				{
					map<string,int>::iterator it=_dict.find(word);
					if(it!=_dict.end())
					{
						++it->second;
					}
					else 
					{
						_dict.emplace(word,1);
						//或_dict.emplace_hint(_dict.end(),word,1);
						//或_dict.insert(std::make_pair(word,1));
						//或者_dict.insert(std::pair<string,int>(word,1));
						//或_dict.insert(_dict.end(),std::make_pair(word,1));
					}
				}
			}
			ifs.close();
		}
		void writefile(const string &filename)
		{
			ofstream ofs(filename,std::ios::out);
			/*for(map<string,int>::iterator it=_dict.begin();it!=_dict.end();++it)*/
			/*{*/
				/*ofs<<it->first<<"  "<<it->second<<endl;*/
			/*}*/
			for(std::pair<string,int> elem :_dict)
			{
				ofs<<elem.first<<"  "<<elem.second<<endl;
			}
			// for_each(_dict.begin(),_dict.end(),#<{(|fuction|)}>#);
			ofs.close();
		}
	private:
		map<string,int>_dict;
};
int  main()
{
	wordstatic ws;
	ws.readfile("./The_Holy_Bible.txt");
	ws.writefile("./dic.txt");
	return 0;
}
