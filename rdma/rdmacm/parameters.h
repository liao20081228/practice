
#pragma once
#ifndef RDMA_COMMON_H
	#define RDMA_COMMON_H
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include"version.h"
extern const char *port;
extern const char *address;

void handle_cmd(int, char*[], struct option[]);








#endif /* end of include guard: RDMA_COMMON_H */
