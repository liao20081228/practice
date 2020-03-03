#pragma once
#ifndef RFTS_SHARED_MEM_H
#define RFTS_SHARED_MEM_H

#include<iostream>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>
#include<stdexcept>
#include<errno.h>
#ifndef LIAOWEIZHI_REGULAR_FILE_MODE
#define LIAOWEIZHI_REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif 
class shmem
{
private:
	int fd;
	const void* buf;
	int length;
public:
	shmem(const char* name = "/rfts_shmem", int size = 1024, 
			int oflag = O_RDWR | O_CREAT,
			mode_t mode  = LIAOWEIZHI_REGULAR_FILE_MODE);
	~shmem();

	
};


#endif /* end of include guard: RFTS_SHARED_MEM_H */


