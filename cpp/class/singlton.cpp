#include<iostream>

class singleton
{
	private:
		~singleton()
		{

		}
	public:
		singleton()
		{

		}

};

int main(void)
{
	singleton *a=new singleton;
	return 0;
}
