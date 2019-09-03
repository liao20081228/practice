#include<iostream>

class sigleton
{
private:
	static sigleton * _sigleton;
private:
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
	sigleton* a=sigleton::GetInstance();
	sigleton* b=sigleton::GetInstance();

	if (a==b)
		std::cout << "sigleton" <<std::endl;
	a->destory();
	return 0;

}
