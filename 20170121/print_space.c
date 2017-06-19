/*************************************************************************
    > File Name: print_space.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月05日 星期日 20时42分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/time.h>
int main()
	{
		int i=1;
		while(i<10)
		{
			printf("%*si love  you\n",i,"");
			i++;
		}
		return 0;
	}
