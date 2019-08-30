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
        while (i != pos && p->next)
	{
		++i;
		p = p->next;
	}
	if (p->next == nullptr)
		return false;


}
