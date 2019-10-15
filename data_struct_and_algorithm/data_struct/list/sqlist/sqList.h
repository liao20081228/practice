#include<cstring>
#include<iostream>
#include<exception>
#include<random>
#include<vector>
namespace mystd
{
class sqList
{
	int* List;
	int size;
	int length;
	
	public:
		sqList(int size);
		~sqList(void);
		bool  initialize(void);

		bool  insert(int pos, int val);

		bool  del(int pos, int* ret);

		bool  del(int val);

		bool  clear(void);

		void  display (void ) const;

		bool  is_empty(void) const;

		bool  is_full(void) const;

		int   length(void) const;
};
} // namespace mystd
