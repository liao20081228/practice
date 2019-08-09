#include<myhead_cpp.h>

int main(void)
{
	srand(time(NULL));
	while (1)
	{
		int score = random() % (101);//A=a+(b-a)*random()/RAND_MAX
		char result = score >=90 ? 'A':(score >= 60 ? 'B' : 'C') ;
	        printf("%d is %c\n", score,result);	
	}
	return 0;
}
