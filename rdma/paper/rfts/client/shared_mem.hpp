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

//posix shared memory
class pshmem
{
	private:
		int fd;
		void *buf;
		size_t length;
	public:
		explicit pshmem(const char* name = "/rfts_pshmem", size_t size = 1024,
			int oflag = O_RDWR | O_CREAT,
			mode_t mode  = LIAOWEIZHI_REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE, int flags = MAP_SHARED,
			off_t offset = 0);
		pshmem(const pshmem& ref) = delete;
		pshmem(pshmem&& ref) noexcept;
		~pshmem(void) noexcept;
		
		pshmem& operator = (const pshmem& ref) = delete;
		pshmem& operator = (const pshmem&& ref) = delete;

		void* getaddr(void ) const noexcept ;
		int read(void* buf, size_t length, off_t offset) const noexcept;
		int write(const void* buf, size_t length, off_t offset) const noexcept;
};


#endif /* end of include guard: RFTS_SHARED_MEM_H */


