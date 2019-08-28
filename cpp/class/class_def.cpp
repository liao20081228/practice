#include<iostream>
#include<cstring>
class animal
{
private:
	static const  float age=100;
	char name[20];
	char action[20];

public:
	animal(short int age, const char name[], const char action[]);
	animal(void);
	~animal(void);
	void act(void) const;
	
};

animal::animal(short int age , const char name[], const char action[]):age(age)
{
	memset(this->name,0,20);
	memset(this->action,0,20);
	::strncpy(this->name,name,strlen(name));
	::strncpy(this->action,action,strlen(action));
	std::cout << "call constructor, once explicit define constuctor, system will not  call auto define default  constructor." << std::endl;
}

animal::animal(void):age(0)
{
	memset(name,0,20);
	memset(action,0,20);
	std::cout << " if you want call default no parameter constructor, you must explicit defien it." << std::endl;
}


animal::~animal(void)
{
	std::cout << "deconstuctor" << std::endl;
}


void animal::act(void) const
{
	std::cout<< name <<" "<<  age <<  "  "  << action <<std::endl;
}

int main(void)
{
	animal cat0(1, "cat0", "run");
	cat0.act();
	animal cat1 = animal( 2 , "cat1", "run");
	cat1.act();
	animal cat2=cat0;
	cat2.act();
	//cat2=cat1;
}
