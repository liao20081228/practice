#include<iostream>
#include<mutex>
namespace rfst
{
	class mempool
	{
	private:
		void* addr;
		int length;

		mempool(int length);
		void* malloc(int n);
	};
};
