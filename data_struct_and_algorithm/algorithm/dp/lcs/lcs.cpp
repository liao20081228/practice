#include<iostream>
#include<string>
#include<vector>
int main(void)
{
	using std::vector;
	vector<int> vec1;
	vector<int> vec2;
	int temp=0;
	while(std::cin>>temp)
		vec1.push_back(temp);
	while(std::cin>>temp)
		vec2.push_back(temp);
	
	vector< vector<int> > vec(vec1.size());
	return 0;
}
