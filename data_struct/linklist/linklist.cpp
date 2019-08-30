#include<iostream>
#include"linklist.hpp"
bool mystd::LinkList::insert(int pos, int val)
{
	int i=0;
	node* p = &head; //node* p = head.next;
	while(i!=pos && p->next != nullptr) // while(i!=pos && p != nullptr)
	{
		++i;
		p=p->next;
	}
	
	if (i!=pos && p->next == nullptr) 
		return false;

	node* temp=p->next;
	p->next = new node;
	p->next->data = val;
	p->next->next = temp;
	return true;
}

int mystd::LinkList::length(void) const
{
	int i=0;
	node* p = head.next;
	while (p)
	{
		i++;
		p=p->next;
	}
	return i;
}

bool mystd::LinkList::establish(void)
{
	int val=0;
	std::cin >> val;
	while (val != -1)
	{
		insert(0,val);
		std::cin >> val;
	}

	return true;

}

bool mystd::LinkList::establish_reverse(void)
{
	int val=0;
	std::cin >> val;
	while (val != -1)
	{
		insert(length(),val);
		std::cin >> val;
	}

	return true;

}


bool mystd::LinkList::del(int pos, int &val)
{
	int i=0;
	node* p = head.
}
