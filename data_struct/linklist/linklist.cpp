#include<iostream>
namespace mystd
{
	struct node
	{
		int data;
		node* next;
	
	};


	class LinkList
	{
		node head;
		
	public:
		LinkList(void)
		{
			head.data=0;
			head.next=nullptr;
		}
		
		bool establish(void);
		bool establish_reverse(void);
		bool insert(int pos, int val);
		bool del(int pos, int& val);
		bool del(int val);
		int search(int val) const;
		int search_by_order(int pos) const;
		int search_by_val(int val) const;
		int length(void ) const;
		bool is_empty(void) const;
		~LinkList(void);
	};
}

bool mystd::LinkList::insert(int pos, int val)
{
	int i=0;
	node* p = &head;
	while(i!=pos && p->next != nullptr)
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
