#include<iostream>

class sigleton
{
private:
	static sigleton * _sigleton;
private:
	sigleton()
	{
	}

public:
	static sigleton* GetInstance()
	{
		if (! _sigleton )
			_sigleton = new sigleton;
		return _sigleton;
	}

	~sigleton()
	{
		if (_sigleton)
			delete _sigleton;
		std::cout << "自动销毁" <<std::endl;
		
	}
};

sigleton* sigleton::_sigleton=nullptr;


int main(void)
{
	sigleton* a=sigleton::GetInstance();
	sigleton* b=sigleton::GetInstance();

	if (a==b)
		std::cout << "sigleton" <<std::endl;
	a->~sigleton();
	return 0;

}
