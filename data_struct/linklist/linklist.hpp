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
		
		bool establish_before(void);
		bool establish_after(void);
		bool establish_reverse(void);
		bool insert_after(int pos, int val);
		bool insert_before(int pos, int val);
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
