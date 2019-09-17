#include<string.h>
#include<iso646.h>
bool simple_match(const char* str, const  char *substr)
{
	int i=0,j=0;
	while(i < (int)strlen(str) and j < (int)strlen(substr) )
	{
		if ( str[i] == str[j] )
		{
			++i;
			++j;
		}
		else
		{
			j=0;
		 	i= i - j + 1;
		}
	}
	if (j > (int)strlen(substr))
		return i - j;
	else
		return 0;
}
