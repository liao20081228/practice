#include<iostream>
#include<string>
#include<vector>
int main(void)
{
	using std::vector;
	std::string vec1;
	std::string vec2;
	std::cin>>vec1;
	std::cin>>vec2;
	int dp[1000][1000]={};
	for (int i=1; i <= (int)vec1.size();++i)

		for(int j=1; j <= (int)vec2.size();++j)
		{
			if ( vec1[i-1] == vec2[j-1] )
				dp[i][j]=dp[i-1][j-1]+1;
			else
				dp[i][j]=dp[i-1][j]>dp[i][j-1]?dp[i-1][j]:dp[i][j-1];
		}
	
	std::cout<<  dp[vec1.size()-1][vec2.size()-1];



	return 0;
}
