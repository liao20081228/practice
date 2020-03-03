#include"semaphore.hpp"

semaphore::semaphore(const int pshared, const unsigned int value):
	sem(new sem_t), name(nullptr)
{
	if(sem_init(sem, pshared, value))
	{
		delete sem;
		if(errno == EINVAL)
			throw std::invalid_argument("initial value exceeds SEM_VALUE_MAX");
		if(errno == ENOSYS)
			throw std::system_error(std::error_code(errno,std::system_category()),
					"system don't supprot process-shared semaphores");
	}

}

semaphore::semaphore(const char* name, int oflag, mode_t mode, unsigned int value):
		sem(sem_open(name, oflag, mode, value)), name(name)
{
	if(sem == SEM_FAILED)
	{
		switch(errno)
		{
			case EACCES:
				throw std::invalid_argument("user have not permission to accsee");
			case EEXIST:
				throw std::invalid_argument("semaphore already exists");
			case EINVAL:
				throw std::invalid_argument("initial value exceeds SEM_VALUE_MAX");
			case EMFILE:
				throw std::system_error(std::error_code(errno, std::system_category()),
						"per-process limit on  the number of open fd has been reached");
			case ENAMETOOLONG:
				throw std::invalid_argument("name was too long");
			case ENFILE:
				throw std::system_error(std::error_code(errno, std::system_category()),
						"system limit the total number of open files has been reached");
			case ENOENT:
				throw std::invalid_argument("semaphore no exists and O_CREAT was not specified, or name was bad");
			case ENOMEM:
				throw std::runtime_error("no enough memory"); 
		}
	}
}

semaphore::semaphore(semaphore&& ref) noexcept:sem(ref.sem),name(ref.name) 
{
	ref.name = nullptr;
	ref.sem = nullptr;
}

semaphore& semaphore::operator = (semaphore&& ref) noexcept
{
	if(this == &ref)
		return *this;
	sem = ref.sem;
	name = ref.name;
	ref.name = nullptr;
	ref.sem = nullptr;
	return *this; 
}


semaphore::~semaphore(void) noexcept
{
	if(sem)
	{
		if (name)
		{
			sem_close(sem);
			sem_unlink(name);
			return;
		}
		delete sem;
		sem_destroy(sem);
	
	}
}


void semaphore::post(void)
{
	if(sem_post(sem))
		throw std::runtime_error("the value of semaphore exceed SEM_VALUE_MAX");
}

void semaphore::wait(void)
{
	if(sem_wait(sem))
		throw std::runtime_error("the call was interrupted by s signal handler");
}


int semaphore::trywait(void)
{
	return sem_trywait(sem);
}

int semaphore::timewait(const struct timespec* abs_timeout)
{
	return sem_timedwait(sem,abs_timeout);
}

int semaphore::getvalue(int * val)
{
	int n  = 0;
	sem_getvalue(sem, &n);
	if(val)
		*val=n;
	return n;
}
