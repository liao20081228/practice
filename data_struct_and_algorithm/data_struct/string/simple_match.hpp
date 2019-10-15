#include<string.h>
#include<iso646.h>
int simple_match(const char* str, const  char *substr)
{
	int i=0,j=0;
	while(i < (int)strlen(str) and j < (int)strlen(substr) )
	{
		if ( str[i] == substr[j] )
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
	if (j == (int)strlen(substr))
		return i - j; // 从0开始计算的匹配位置。
	else
		return 0;
}
