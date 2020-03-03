#pragma once
#ifndef RFTS_SHARED_MEM_H
#define RFTS_SHARED_MEM_H

#include<iostream>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

class shmem
{
private:
	int fd;
public:
	shmem()
};


#endif /* end of include guard: RFTS_SHARED_MEM_H */


