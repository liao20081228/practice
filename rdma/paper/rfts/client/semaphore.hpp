#pragma once
#ifndef LIAOWEIZHI_POSIX_SEMAPHORE_H
	#define RFTS_SEMAPHORE_H
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cerrno>
#include<stdexcept>
#include<system_error>

#ifndef LIAOWEIZHI_REGULAR_FILE_MODE
#define LIAOWEIZHI_REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif
class semaphore
{
	private:
		sem_t* sem;
		const  char* name;
	public:
		explicit semaphore(int pshared = 0,  unsigned int value = 0);
		explicit semaphore(const char* name, int oflag = O_RDWR | O_CREAT, 
				 mode_t mode = LIAOWEIZHI_REGULAR_FILE_MODE,
				 unsigned int value = 0);
		explicit semaphore(const semaphore& ref)  noexcept = delete;
		explicit semaphore(semaphore&& ref) noexcept;
		~semaphore(void) noexcept;
		
		semaphore& operator = (const semaphore& ref)  noexcept = delete;
		semaphore& operator=(semaphore&& ref) noexcept;
		
		void post(void);
		void wait(void);
		int trywait(void);
		int timewait(const struct timespec* abs_timeout);
		int getvalue(int * val = nullptr);
		
};





#endif /* end of include guard: RFTS_SEMAPHORE_H */
