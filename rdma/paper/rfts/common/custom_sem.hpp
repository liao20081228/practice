#pragma once
#ifndef HPP_CUSTOM_SEM_HPP
	#define HPP_CUSTOM_SEM_HPP

#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cerrno>
#include<cstdlib>
#include<cstdio>
#include<system_error>
#include<iostream>
#include<string>
#ifndef CUSTOM_REGULAR_FILE_MODE
	#define REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif

#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {perror(#a);exit(errno);}
	#define PERR(c) _PERR(c() failed)
#endif
class posix_sem
{
private:
	sem_t*		__sem;
	std::string	__name;
public:
	explicit posix_sem(int pshared = 0,  unsigned int value = 0) noexcept;
	explicit posix_sem(const char* name, int oflag = O_RDWR | O_CREAT,
			mode_t mode = REGULAR_FILE_MODE,
			unsigned int value = 0) noexcept;
	explicit posix_sem(const std::string& name, int oflag = O_RDWR | O_CREAT,
			mode_t mode = REGULAR_FILE_MODE,
			unsigned int value = 0) noexcept;
	explicit posix_sem(const std::string* name, int oflag = O_RDWR | O_CREAT,
			mode_t mode = REGULAR_FILE_MODE,
			unsigned int value = 0) noexcept;
	posix_sem(const posix_sem& ref) = delete;
	posix_sem(posix_sem&& ref) noexcept;
	~posix_sem(void) noexcept;

	posix_sem& operator = (posix_sem& ref) = delete;
	posix_sem& operator = (posix_sem&& ref) = delete;

	void post(void) noexcept ;
	void wait(void) noexcept;
	int  trywait(void) noexcept;
	int  timewait(const struct timespec* abs_timeout) noexcept;
	int  getvalue(int* val = nullptr) const noexcept;
};



#endif /* end of include guard: HPP_CUSTOM_SEM_HPP */
