#include<stdio.h>
int main(int argc, char *argv[])
{
	int a[5]={1,2,3,4,5};
	for (int i=0; i <5 ;++i)
		printf("%d,",a[i]);
	printf("\n");

	int i=0;
	for (; i < 5 ; ++i)
		printf("%d,",a[i]);
	printf("\n");

	i=0;
	for (;i<5;)
		printf("%d,",a[i++]);
	printf("\n");

	i=0;
	for (;;)
	{
		if (i >= 5)
			break;
		printf("%d,",a[i++]);
	}
	printf("\n");
	
	i=0;
	while(i<5)
		printf("%d,",a[i++]);
	printf("\n");
	
	i=0;
	while(1)
	{
		if (i>=5)
			break;
		printf("%d,",a[i++]);
	}
	printf("\n");

	i=0;
	do 
	{
		printf("%d,",a[i++]);
		
	}while(i<5);
	printf("\n");

	i=0;
	do 
	{
		if ( i >=5 )
			break;
		printf("%d,",a[i++]);
	}while(1);
	printf("\n");
	
	for(int i : a)
		printf("%d,",i);
}
