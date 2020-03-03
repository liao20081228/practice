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
	shmem(const char *name = "/rfts_shmem", int oflag = O_RDWR | O_CREAT | O_EXCL, mode_t mode  = 00644);
	~shmem() ;
};


#endif /* end of include guard: RFTS_SHARED_MEM_H */


