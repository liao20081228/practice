#include<iostream>
class bird
{
	private:
		int wing;
		int leg;
	public:
		void fly(const char* place);	
		void sing(const char* song)
		{
			std::cout << song << std::endl;
		}
		void eat(const char* food)
		{
			std::cout << food << std::endl;
		}
		void setwing(int a)
		{
			leg=a;
		}
};

void bird::fly(const char* place)
{
	std::cout << place << std::endl;
}

int main(void)
{
	bird mauqe;
	mauqe.fly("north");
	mauqe.leg=10; //不能直接访问对象属性
	mauqe.setwing(10);//只能通过对象的方法访问对象属性，数据隐藏和封装
	return 0;
}
