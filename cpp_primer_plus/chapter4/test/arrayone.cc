#include<iostream>
int main(int argc, char *argv[])
{
	using namespace std;
	int yams[3];
	yams[0]=7;
	yams[1]=8;
	yams[2]=6;
	int yamcost[3]={20, 30 , 5};
	std::cout << "Total yams=" << yams[0] + yams[1] + yams[2] << std::endl;
	std::cout << "the package with" << yams[1] << " yams costs" <<std::endl;
	cout << yamcost[1] << "cent per yam .\n";
	int total=yams[0]* yams[1]* yams[2];
	total+=(yams[2]* yamcost[2]);
	cout << "the total yam expense is " << total << "cents . \n";
	cout << "\n size of yams array ="<<sizeof yams <<" bytes .\n";
	cout << "sizof one element = "<< sizeof yams[0] << "byttes . \n";
	return 0;
}
