#include<iostream>
namespace mystd
{


	class LinkList
	{
		struct node
		{
			int data;
			node* next;
	
		} head;
		
	public:
		LinkList(void)
		{
			head.data=0;
			head.next=nullptr;
		}
		
		bool establish_front(void);
		bool establish_trail(void);
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
