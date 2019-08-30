#include<iostream>
#include<vector>
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
		
		bool establish_front(void);
		bool establish_trail(void);
		bool establish_reverse(void);
		bool insert_after(int pos, int val);
		bool insert_before(int pos, int val);
		bool del(int pos, int& val);
		bool del(int val);
		std::vector<int> search(int val) const;
		node* search_by_pos(int pos) const;
		int length(void ) const;
		bool is_empty(void) const;
		~LinkList(void);
	};
}
