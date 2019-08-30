#include"linklist.hpp"
#include<ciso646>

bool mystd::LinkList::is_empty(void) const
{
	return head.next;
}

bool mystd::LinkList::insert_before(int pos, int val) 
{

	int i = 0;
	node* p = head.next;
        while ( i != pos && p)
	{
		++i;
		p = p->next;
	}


}
