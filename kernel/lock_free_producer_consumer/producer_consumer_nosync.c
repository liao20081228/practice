/*****************************************************************************80
    > File Name: producer_consumer_nosync.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年11月01日 星期三 18时44分04秒
*******************************************************************************/
/*myhead_c.h is a headfile in “/usr/local/include”,include all headfiles*/
#include<myhead_c.h>
static int i = 0;

void* producer(void* arg)
{
	while(1)
	{
		sleep(1);
		if(i < 100)
		{
			i+=1;
		}
		printf(" producer thread see the i = %d\n",i );
	}
	pthread_exit(NULL);
}
void* consumer(void* arg)
{
	while(1)
	{
		sleep(1);
		if(i > 0)
		{
			i-=1;
		}
		printf(" consumer thread see the i = %d\n",i );
	}
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t producer_id, consumer_id;
	pthread_create(&producer_id,NULL, producer, NULL);
	pthread_create(&consumer_id,NULL, consumer, NULL);
	pthread_join(producer_id,NULL);
	pthread_join(consumer_id,NULL);
	return 0;
}
