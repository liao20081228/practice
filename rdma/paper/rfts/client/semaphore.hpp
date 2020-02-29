#pragma once
#ifndef RFTS_SEMAPHORE_H
#define RFTS_SEMAPHORE_H
#include<semaphore.h>

class semaphore
{
	private:
		sem_t sem;
	public:
		explicit semaphore(void) noexcept;
		~semaphore(void) noexcept;
		void post(void) noexcept;
		void wait(void) noexcept;
};







#endif /* end of include guard: RFTS_SEMAPHORE_H */
