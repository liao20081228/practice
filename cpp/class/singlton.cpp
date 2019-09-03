#include<iostream>

class singleton
{	
	static singleton* p;
	static singleton* init()
	{
		if(p)
			return p;
		else
			return new singleton;
	}
	private:
		singleton()
		{

		}
		~singleton()
		{

		}

};
singleton* singleton::p=nullptr;

int main(void)
{
	return 0;
}
