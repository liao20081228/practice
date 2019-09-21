#include<iostream>
#include<string>
#include<vector>
//长度为m，n的序列a b的最长公共子序列：
//f（m,n）=z，是最长子序列的长度
//如果a,b最后一个元素相同, f(m，n)=f(m-1,n-1)+1;
//否则，f(m,n)=max(f(m-1,n),f(m,n-1));
int main(void)
{
	using std::vector;
	std::string vec1;
	std::string vec2;
	std::cin>>vec1;
	std::cin>>vec2;
	int dp[1000][1000]={};
	int direct[1000][1000]={};
	for (int i=1; i <= (int)vec1.size();++i)

		for(int j=1; j <= (int)vec2.size();++j)
		{
			if ( vec1[i-1] == vec2[j-1] )
			{
				dp[i][j]=dp[i-1][j-1]+1;
				direct[i][j]=0;

			}
			else
			{
				dp[i][j]=dp[i-1][j]>dp[i][j-1]?dp[i-1][j]:dp[i][j-1];
				direct[i][j]=dp[i-1][j]>dp[i][j-1]?1:2;
				
			}
		}
	
	std::cout<<  dp[vec1.size()][vec2.size()];
}
