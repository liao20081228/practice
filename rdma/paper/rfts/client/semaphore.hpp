#pragma once
#ifndef LIAOWEIZHI_POSIX_SEMAPHORE_H
	#define RFTS_SEMAPHORE_H

#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cerrno>
#include<cstdlib>
#include<cstdio>
#include<system_error>
#include<iostream>

#ifndef LIAOWEIZHI_REGULAR_FILE_MODE
	#define LIAOWEIZHI_REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif
class semaphore
{
	private:
		sem_t* sem;
		const char* name;
	public:
		explicit semaphore(int pshared = 0,  unsigned int value = 0);
		explicit semaphore(const char* name, int oflag = O_RDWR | O_CREAT,
				 mode_t mode = LIAOWEIZHI_REGULAR_FILE_MODE,
				 unsigned int value = 0) ;
		semaphore(const semaphore& ref) = delete;
		semaphore(semaphore&& ref) noexcept;
		
		~semaphore(void) noexcept;
		
	
		void post(void) noexcept ;
		void wait(void) noexcept;
		int  trywait(void) noexcept;
		int  timewait(const struct timespec* abs_timeout) noexcept;
		int  getvalue(int* val = nullptr) noexcept;
};



#endif /* end of include guard: RFTS_SEMAPHORE_H */
