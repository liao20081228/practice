#pragma once
#ifndef RFTS_SHARED_MEM_H
	#define RFTS_SHARED_MEM_H

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cerrno>
#include<cstdio>
#include<cstdlib>
#include<system_error>
#include<iostream>
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
	shmem(const char* name = "/rfts_shmem", off_t size = 1024,
			int oflag = O_RDWR | O_CREAT,
			mode_t mode  = LIAOWEIZHI_REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE,int flags = MAP_SHARED,
			off_t offset = 0);
	~shmem();

	
};


#endif /* end of include guard: RFTS_SHARED_MEM_H */


