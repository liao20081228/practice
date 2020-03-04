#pragma once
#ifndef HPP_CUSTOM_SHMEM_HPP
	#define HPP_CUSTOM_SHARED_MEM_HPP

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
#ifndef CUSTOM_REGULAR_FILE_MODE
	#define REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif

#ifndef CUSTOM_PRINT_ERROR_INFO
	#define _PERR(a) perror(#a)
	#define PERR(a) _PERR(a() failed)
#endif /* ifndef CUSTOM_PRINT_ERROR_INFO */

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
			mode_t mode  = REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE, int flags = MAP_SHARED,
			off_t offset = 0) noexcept;
		pshmem(const pshmem& ref) = delete;
		pshmem(pshmem&& ref) noexcept;
		~pshmem(void) noexcept;
		
		pshmem& operator = (const pshmem& ref) = delete;
		pshmem& operator = (const pshmem&& ref) = delete;

		void* getaddr(void ) const noexcept;
		int sync(int flags = MS_SYNC) const noexcept;
		ssize_t read(void* buf, size_t len, off_t offset) const noexcept;
		ssize_t write(const void* buf, size_t length, off_t offset) const noexcept;
};


#endif /* end of include guard: HPP_CUSTOM_SHARED_MEM_H */


