/*************************************************************************
    > File Name: textquery.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年05月23日 星期二 12时02分42秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
class CQueryResult;
class CTextQuery/* 收集并整理每个单词，记录单词出现的频率，记录单词所在行*/
{
	private:
		shared_ptr<vector<string>> __cm_vespLineText;
		shared_ptr<map<string,shared_ptr<set<size_t>>>> __cm_maspLineNumber;//c++11只有静态非常量数据成员才需要在类外初始化
		shared_ptr<map<string,size_t>> __cm_maspDictionary;
	public:
		CTextQuery(const  string & filename);
		CQueryResult Query(const string & word) const;
};
CTextQuery::CTextQuery( const string & filename):__cm_vespLineText(new vector<string>),__cm_maspLineNumber(new map<string,shared_ptr<set<size_t>>>),__cm_maspDictionary(new map<string,size_t>)
{
	ifstream ifs(filename,std::ios::in);
	if(!ifs.good())
		cout<<filename<<"open failed"<<endl;
	string strLine,strWord;
	size_t ulnLineNumber=0;
	while(std::getline(ifs,strLine))
	{
		__cm_vespLineText->push_back(strLine);
		std::replace_if(strLine.begin(),strLine.end(),std::not1(std::ptr_fun(isalpha)),' ');
		istringstream iss(strLine,std::ios::in);
		while(iss>>strWord)
		{
			map<string,size_t>::iterator It1=__cm_maspDictionary->find(strWord);
			if(It1!=__cm_maspDictionary->end())
				++It1->second;
			else
			{
				__cm_maspDictionary->emplace(strWord,1);
				/*//或者__cm_maspDictionary->emplace_hint(__cm_maspDictionary->end(),strWord,1);*/
				/*//或者__cm_maspDictionary->insert(std::pair<string,size_t>(strWord,1));*/
				/*//或者__cm_maspDictionary->insert(__cm_maspDictionary->end(),std::pair<string,size_t>(strWord,1));*/
				/*//或者__cm_maspDictionary->insert(__cm_maspDictionary->end(),std::make_pair(strWord,1));*/
			}
			map<string,shared_ptr<set<size_t>>>::iterator It2=__cm_maspLineNumber->find(strWord);
			if(It2!=__cm_maspLineNumber->end())
			{
				It2->second->insert(ulnLineNumber);
				//或者It2->second.emplace(ulnLineNumber);
			}
			else
			{
				__cm_maspLineNumber->emplace(strWord,shared_ptr<set<size_t>>(new set<size_t>)).first->second->insert(ulnLineNumber);
			}
			/*
			 * map支持operator[key]，返回映射值,如果关键字不存在则插入
			 *++(*__cm_maspDictionary)[strWord];
			 *(*__cm_maspLineNumber)[strWord]->insert(ulnLineNumber);
			 */
		}
		++ulnLineNumber;
	}
	ifs.close();
}

class CQueryResult
{
	private:
		const string & __cm_strWord;
		size_t __cm_ulnFrequency;
		shared_ptr<set<size_t>> __cm_sespLineNumber;
		shared_ptr<vector<string>> __cm_vespLineText;
	public:
		CQueryResult(const string & word,size_t frequency,shared_ptr<set<size_t>> linenumber,shared_ptr<vector<string> > linetext):__cm_strWord(word),__cm_ulnFrequency(frequency),__cm_sespLineNumber(linenumber),__cm_vespLineText(linetext)
		{
		}
		friend ostream & operator<<(ostream & os,const CQueryResult & queryresult);
};
ostream & operator<<(ostream &os,const CQueryResult & queryresult)
{
	if(queryresult.__cm_ulnFrequency==0)
	{
		os<<"  !此文章不含有该单词"<<endl;
		return os;
	}
	os<<"  "<<queryresult.__cm_strWord<<"一共出现"<<queryresult.__cm_ulnFrequency<<"次"<<endl;
	for(const size_t & elem:*(queryresult.__cm_sespLineNumber))
	{
		os<<"  第"<<elem<<"行：  "<<(*queryresult.__cm_vespLineText)[elem]<<endl;
	}
	 /*或者*/
	/*for(set<size_t>::iterator it=queryresult.__cm_sespLineNumber->begin();it!=queryresult.__cm_sespLineNumber->end();++it)*/
	/*{*/
		/*os<<"  第"<<*it<<"行：  "<<(*queryresult.__cm_vespLineText)[*it]<<endl;*/
	/*}*/
	return os;
}

CQueryResult CTextQuery::Query(const string & word) const
{
	map<string,size_t>::iterator It=__cm_maspDictionary->find(word);
	static shared_ptr<set<size_t>>s_sespNoData(new set<size_t>);
	if(It==__cm_maspDictionary->end())
	{
		return CQueryResult(word,0,s_sespNoData,__cm_vespLineText);
	}
	else
	{
		return CQueryResult(word,It->second,(*__cm_maspLineNumber)[word],__cm_vespLineText);
	}
};


class CQuery
{
	private:
		friend CQuery operator~(const CQuery &);
		friend CQuery operator|(const CQuery &,const CQuery&);
		friend CQuery operator&(const CQuery &,const CQuery&);
	public:
		CQuery(const string &);
		CQueryResult eval(const CTextQuery & t) const
		{
			return 
		}
};
class CQueryBase
{
	private:
		friend class CQuery;
	public:


};



int  main()
{
	CTextQuery file("./test.txt");
	cout<<file.Query("you");
	return 0;
}
