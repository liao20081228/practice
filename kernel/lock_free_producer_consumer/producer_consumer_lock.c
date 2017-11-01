/*****************************************************************************80
    > File Name: producer_consumer_nosync.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年11月01日 星期三 18时44分04秒
*******************************************************************************/
/*myhead_c.h is a headfile in “/usr/local/include”,include all headfiles*/
#include<myhead_c.h>
static int i = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;
static pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
void clean_func(void *arg)
{
	pthread_mutex_unlock(&mutex);
}


void* producer(void* arg)
{
	while(1)
	{
		sleep(1);
		pthread_cleanup_push(clean_func, NULL);
		pthread_mutex_lock(&mutex);
		if(i < 100)
		{
			i+=1;
			if(i == 1)
			{
				pthread_cond_signal(&notempty);
			}
		}
		else
		{
			pthread_cond_wait(&notfull, &mutex);
			i+=1;
		}
		printf(" producer thread see the i = %d\n",i );
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
	}
	pthread_exit(NULL);
}
void* consumer(void* arg)
{
	while(1)
	{
		sleep(1);
		pthread_cleanup_push(clean_func, NULL);
		pthread_mutex_lock(&mutex);
		if(i > 0)
		{
			i-=1;
			if(i == 99)
			{
				pthread_cond_signal(&notfull);
			}
		}
		else
		{
			pthread_cond_wait(&notempty, &mutex);
			i-=1;
		}
		printf(" consumer thread see the i = %d\n",i );
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(0);
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
