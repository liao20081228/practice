#pragma once
#ifndef RFTS_SEMAPHORE_H
#define RFTS_SEMAPHORE_H
#include<semaphore.h>
class semaphore
{
	private:
		sem_t *sem;
		bool name;
	public:
		explicit semaphore(const int pshared = 0, const unsigned int value = 0);
		explicit semaphore(const char* name, int oflag);
		explicit semaphore(const char* name, const int oflag, 
				const mode_t mode, const unsigned int value);
		~semaphore(void);
		void post(void);
		void wait(void);
};





#endif /* end of include guard: RFTS_SEMAPHORE_H */
