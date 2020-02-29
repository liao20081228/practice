#include<pthread.h>
#include"get_clock.h"

int main()
{
	pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
	pthread_spinlock_t spin;
	pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);
}
