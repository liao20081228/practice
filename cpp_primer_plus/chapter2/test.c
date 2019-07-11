#include<stdio.h>
#include<stdbool.h>
int main(void)
{
	printf("%ld  ", sizeof(bool));	
	printf("\n");
	printf("%ld ", sizeof(char));	
	printf("\n");
	printf("%ld ", sizeof(int ));	
	printf("\n");
	printf("%ld ", sizeof(long));	
	printf("\n");
	printf("%ld ", sizeof(long long));	
	printf("\n");
	printf("%ld ", sizeof(float));	
	printf("\n");
	printf("%ld ", sizeof(double ));	
	printf("\n");
	printf("%ld ", sizeof(long double));	
	printf("\n");
	return 0;
}
