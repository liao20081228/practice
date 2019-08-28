#include<iostream>
#include<cstring>
class animal
{
private:
	char name[20];
	char action[20];

public:
	void act(void);
	
};


animal cat1; //类 就像是普通给的自定义数据类型一样
int main(void)
{
	animal cat0;//类变量和普通的变量没有什么区别，具有相同的作用和生命周期 可见性
}
