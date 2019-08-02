#include<iostream>
#include<string>
int main(void)
{
	std::cout << "enter a word" << std::endl;
	std::string word="";
	std::cin >> word;
	char temp=0;
	for (int i= word.size()-1, j=0;j<i;--i,++j)
	{
		temp=word[i];
		word[i]=word[j];
		word[j]=temp;

	}
	std::cout << word << std::endl;
	return 0;
}
