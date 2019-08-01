#include<iostream>

int main(void)
{
	using namespace std;
	cout << "what yearr was your house built? \n";
	int year{};
	//cin >> year;
	//cin.get();
	(cin >> year).get();
	cout << "what  address is it?\n";
	char address[60]{};
	cin.getline(address,60,'\n');
	cout << year << " " <<address<<endl;
	return 0;
}
