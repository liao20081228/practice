#pragma once
#ifndef RFTS_SEMAPHORE_H
#define RFTS_SEMAPHORE_H
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
class semaphore
{
	private:
		sem_t* const sem;
		bool name;
	public:
		explicit semaphore(const int pshared = 0, const unsigned int value = 0);
		explicit semaphore(const char* name, int oflag = O_RDWR | O_CREAT);
		explicit semaphore(const char* name, const int oflag = O_RDWR | O_CREAT, 
				const mode_t mode = 00666, const unsigned int value = 0);
		~semaphore(void);
		void post(void);
		void wait(void);
};





#endif /* end of include guard: RFTS_SEMAPHORE_H */
