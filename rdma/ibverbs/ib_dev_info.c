#include<infiniband/verbs.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(void)
{
	int num = 0;
	struct ibv_device** dev_list = ibv_get_device_list(&num);
	for
}
