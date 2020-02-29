#include<iostream>
#include<mutex>
namespace rfst
{
	using std::mutex;
	class mempool
	{
	private:
		void* addr;
		int length;
		mutex suo;
	public:
		mempool(int length);
		void* malloc(int n);
	};
};
