#include<iostream>

class sigleton
{
	static sigleton * _sigleton;
	sigleton()
	{
	}
	~sigleton()
	{

	}

public:
	static sigleton* GetInstance()
	{
		if (! _sigleton )
			_sigleton = new sigleton;
		return _sigleton;
	}

	void destory()
	{
		if (_sigleton)
			delete _sigleton;
	}
};

sigleton* sigleton::_sigleton=nullptr;


int main(void)
{
	sigleton* a=sigleton.GetInstance();
	sigleton* b;b.GetInstance();

	if (&a==&b)
		std::cout << "sigleton" <<std::endl;
	return 0;
}
