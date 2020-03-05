#pragma once
#ifndef HPP_CUSTOM_SEMAPHORE_HPP
	#define HPP_CUSTOM_SEMAPHORE_HPP

#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cerrno>
#include<cstdlib>
#include<cstdio>
#include<system_error>
#include<iostream>

#ifndef CUSTOM_REGULAR_FILE_MODE
	#define REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif

#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {perror(#a);exit(errno);}
	#define PERR(c) _PERR(c() failed)
#endif
class psem
{
	private:
		sem_t* sem;
		const char* name;
	public:
		explicit psem(int pshared = 0,  unsigned int value = 0) noexcept;
		explicit psem(const char* name, int oflag = O_RDWR | O_CREAT,
				 mode_t mode = REGULAR_FILE_MODE,
				 unsigned int value = 0) noexcept;
		psem(const psem& ref) = delete;
		psem(psem&& ref) noexcept;
		~psem(void) noexcept;
		
		psem& operator = (psem& ref) = delete;
		psem& operator = (psem&& ref) = delete;
		
		void post(void) noexcept ;
		void wait(void) noexcept;
		int  trywait(void) noexcept;
		int  timewait(const struct timespec* abs_timeout) noexcept;
		int  getvalue(int* val = nullptr) noexcept;
};



#endif /* end of include guard: RFTS_SEMAPHORE_H */
