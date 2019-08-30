#include"linklist.hpp"
#include<ciso646>

bool mystd::LinkList::is_empty(void) const
{
	return static_cast<bool>(head.next);
}

bool mystd::LinkList::insert_before(int pos, int val) 
{

	int i = 0;
	node* p = &head;
        while (i != pos-1 && p->next)
	{
		++i;
		p = p->next;
	}
	if (i != pos - 1)
		return false;
	node* temp = p->next;
	p->next = new node;
	if (p->next == nullptr)
		return false;
	p->next->data = val;
	p->next->next = temp;
	return true;
}


bool mystd::LinkList::insert_after(int pos, int val) 
{

	int i = 0;
	node* p = &head;
        while (i != pos && p->next)
	{
		++i;
		p = p->next;
	}
	if (i != pos)
		return false;
	node* temp = p->next;
	p->next = new node;
	if (p->next == nullptr)
		return false;
	p->next->data = val;
	p->next->next = temp;
	return true;
}


int mystd::LinkList::length(void) const 
{
	int i=0;
	const node* p = &head;
	while(p->next)
		++i;
	return i;
}


bool mystd::LinkList::establish_front()
{
	int val=0;
	std::cin >> val;
	while( val != -1 )
	{
		if (insert_after(0, val) == false)
			return false;
		std::cin >> val;
	}
	return true;
}

bool mystd::LinkList::establish_trail()
{
	int val=0;
	std::cin >> val;
	while( val != -1 )
	{
		if (insert_after(length(), val) == false)
			return false;
		std::cin >> val;
	}
	return true;
}


bool mystd::LinkList::del(int pos, int& val)
{

}
bool mystd::LinkList::del(int val)
{

}
