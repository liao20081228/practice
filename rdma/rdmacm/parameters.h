
#pragma once
#ifndef RDMA_COMMON_H
	#define RDMA_COMMON_H
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include"version.h"

struct user_parameters 
{
	char * port;
	char * address;
};



int handle_cmd(struct user_parameters*, int, char*[], struct option[]);



#endif /* end of include guard: RDMA_COMMON_H */
