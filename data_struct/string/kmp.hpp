#include<string.h>
void get_next(const char* str, int next[])
{
	int i=0,j=0;
	next[i]=-1;
	while(i <  (int)strlen(str))
	{
		if (j == 0 || str[i] == str[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
			j=next[j];
	}
}


int kmp(const char* str, const char* substr)
{
	int i=0,j=0;
	while(i < (int)strlen(str) && j< (int)strlen(substr))
	{
		if (str[i] == substr[j])
			++i,++j;
		else
		j=next[j];
	}
	
}
