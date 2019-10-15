#include"sqList.h"

int main(void)
{
	
	mystd::sqList list(10);
	list.initialize();
	list.display();
	
	list.insert(5,100);
	list.display();
	
	int val=0;
	list.del(5,&val);
	list.display();
	
	for ( auto it : list.location(6) )
		std::cout << it << std::endl;
	list.del(6);
	list.display();

	std::cout << list.is_empty() <<std::endl;
	std::cout << list.is_full() <<std::endl;
	std::cout << list.len() <<std::endl;
	


	return 0;
}
