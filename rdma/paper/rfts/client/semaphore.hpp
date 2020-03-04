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

#ifndef CUSTOM_PRINT_ERROR_INFO
	#define _PERR(a) perror(#a)
	#define PERR(a) _PERR(a() failed)
#endif
class semaphore
{
	private:
		sem_t* sem;
		const char* name;
	public:
		explicit semaphore(int pshared = 0,  unsigned int value = 0) noexcept;
		explicit semaphore(const char* name, int oflag = O_RDWR | O_CREAT,
				 mode_t mode = REGULAR_FILE_MODE,
				 unsigned int value = 0) noexcept;
		semaphore(const semaphore& ref) = delete;
		semaphore(semaphore&& ref) noexcept;
		~semaphore(void) noexcept;
		
		semaphore& operator = (semaphore& ref) = delete;
		semaphore& operator = (semaphore&& ref) = delete;
		
		void post(void) noexcept ;
		void wait(void) noexcept;
		int  trywait(void) noexcept;
		int  timewait(const struct timespec* abs_timeout) noexcept;
		int  getvalue(int* val = nullptr) noexcept;
};



#endif /* end of include guard: RFTS_SEMAPHORE_H */
