#include"custom_shm.hpp"
int main()
{
	std::string name("/test");
	posix_shm a(name);
	posix_shm b(&name);
	posix_shm c = posix_shm(name);
	name =" o love you";
}
