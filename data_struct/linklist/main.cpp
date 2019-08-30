#include"linklist.hpp"

int main(void)
{
	mystd::LinkList a{};
	//mystd::LinkList b{};
	a.establish_front();
	//b.establish_trail();
	a.display();
	//b.display();

	a.insert_after(2,10);
	//b.insert_before(2,10);
	a.display();
	//b.display();
	
	int c = 0;
	a.del(3,c);
	//b.del(5);

	a.display();
	//b.display();
	
	//std::cout<< a.length() << "," << b.length() << std::endl;
	return 0;
}
