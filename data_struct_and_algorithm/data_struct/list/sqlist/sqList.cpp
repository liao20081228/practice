#include"sqList.h"
#include<vector>
using  namespace mystd;

bool sqList::is_empty(void) const
{
	return length == 0;
}

bool sqList::is_full(void ) const
{
	return length==size;
}

bool sqList::initialize(void)
{
	int val=0;
	std::cin >> val;
	while(val != -1 && !is_full())
	{
		List[length++]=val;
		std::cin >> val;
	}
	return true;
}

bool sqList::insert(int pos, int val)
{
	if (pos<0 or pos >length or is_full())
	{
		return false;
	}

	for ( int i=length; i>=pos; --i )
	{
		List[i]=List[i-1];
	}
	List[pos-1]=val;
	++length;
	return true;
}




bool sqList::del(int pos, int* val)
{
	if (pos < 0 || pos > length)
		return false;
	if ( val )
		*val =  List[pos-1];
	for ( int i=pos-1; i<length-1; ++i )
	{
		List[i]=List[i+1];
	}
	--length;
	return true;
}


bool sqList::del(int val)
{
	for (int i=0; i < length; ++i)
	{
		if (List[i] == val)
			del(i+1,nullptr);
	}
	return true;
}



bool sqList::clear(void)
{
	std::memset(List,0, length);
	length = 0;
	return true;	
}

void sqList::display(void)  const
{
	for (int i=0; i < length; ++i)
		std::cout<< List[i] << ",";
	std::cout << std:: endl;
}

sqList::~sqList()
{
	delete[] List;
	std::cout << "call deconstructor" << std::endl; 
}



std::vector<int> sqList::location(int val) const
{
	std::vector<int> vec;
	for (int i=0; i < length ;i++)
	{
		if (List[i] == val)
		{
			vec.push_back(i+1);
		}
	}
	return vec;
}

int sqList::len(void)const
{
	return length;
}
