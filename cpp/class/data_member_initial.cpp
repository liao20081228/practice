#include<iostream>
class animal
{
	int age;
	const char name[12];
	const char*color;
	int&& weight;
	animal():name("bird"),weight(10)
	{
		age=10;
		color=new char[15];
	}
};


