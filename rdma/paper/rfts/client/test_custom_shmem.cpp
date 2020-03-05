#include"custom_shmem.hpp"

int main()
{
	pshmem a;
	char str[100];
	a.read(str, 100, 100);
}
