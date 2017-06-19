/*************************************************************************
    > File Name: stream_iterator.cc
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月27日 星期四 20时59分49秒
 ************************************************************************/
#include<myhead>/*myhead is a headfile defined in in the directory:/usr/include,which include all headfile we need*/
int  main()
{
	vector<int>v;
	std::istream_iterator<int>isit(cin);
	std::copy(isit,std::istream_iterator<int>(),std::back_inserter(v));
	std::ostream_iterator<int>osit(cout,",");
	std::copy(v.begin(),v.end(),osit);
	return 0;
}
