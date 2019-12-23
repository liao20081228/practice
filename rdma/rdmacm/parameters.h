
#pragma once
#ifndef RDMA_PARAMETERS_H
	#define RDMA_PARAMETERS_H
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include"version.h"

struct user_parameters 
{
	char * port;
	char * address;
};



void handle_cmd(struct user_parameters*, int, char*[]);



#endif /* end of include guard: RDMA_COMMON_H */
