#pragma once
#ifndef RFTS_SEMAPHORE_H
#define RFTS_SEMAPHORE_H
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<cerrno>
#include<stdexcept>
#include<system_error>
class semaphore
{
	private:
		sem_t* sem;
		const  char* name;
	public:
		explicit semaphore(int pshared = 0,  unsigned int value = 0);
		explicit semaphore(const char* name, int oflag = O_RDWR | O_CREAT, 
				 mode_t mode = 00666, unsigned int value = 0);
		semaphore(const semaphore& ref) = delete;
		semaphore& operator = (const semaphore& ref) = delete;
		explicit semaphore(semaphore&& ref);
		semaphore& operator=(semaphore&& ref);
		~semaphore(void);
		void post(void);
		void wait(void);
};





#endif /* end of include guard: RFTS_SEMAPHORE_H */
