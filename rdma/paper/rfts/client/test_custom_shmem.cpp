#include"custom_shmem.hpp"

int main()
{
	pshmem a;
	char str[100] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	a.mwrite(str, 100, 80 );
	std::cout << (char*)a.getaddr() <<std::endl;
	char ra[100] ={0};
	a.mread(ra,100,100);
	std::cout << ra <<std::endl;

}
