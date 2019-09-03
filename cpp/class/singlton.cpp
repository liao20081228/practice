#include<iostream>

class singleton
{
	private:
		~singleton()
		{

		}
	
	//public:
		singleton()
		{
			std::cout <<"gouzaohanshu"<< std::endl;
		}

};

int main(void)
{
	singleton *a=new singleton;
	return 0;
}
