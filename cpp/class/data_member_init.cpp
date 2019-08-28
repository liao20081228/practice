#include<iostream>
class animal 
{

	static const int count0=1;//c++98只有静态常量整形或者枚举数据成员可以就地初始化
	static const int count01(2);
	
	static const float count1=3;
	static int count2=4;
	static float count3=5;
	int count4=6;
	float count5=7;

	public:

	void display(void)  
	{
		std::cout<< count0 << std::endl;
		std::cout<< count01 << std::endl;
		std::cout<< count1 << std::endl;
		std::cout<< count2 << std::endl;
		std::cout<< count3 << std::endl;
		std::cout<< count4 << std::endl;
		std::cout<< count5 << std::endl;
	}

};


int main(void)
{
	animal cat;
	cat.display();
	animal cat1=animal();
	cat1.display();
	return 0;
}
