#pragma once
#ifndef HPP_CUSTOM_SHM_HPP
	#define HPP_CUSTOM_SHM_HPP

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cerrno>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<system_error>
#include<iostream>
#include<atomic>
#include<string>
#ifndef CUSTOM_REGULAR_FILE_MODE
	#define REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif

#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {::perror(#a);::exit(errno);}
	#define PERR(c) _PERR(c() failed)
#endif /* ifndef CUSTOM_PRINT_ERROR_INFO */

//posix shared memory
namespace custom
{
class posix_shm
{
private:
	const std::string	__name;		//shm对应文件名
	const int		__fd;		//shm对应的fd
	void*			__addr;		//shm起始地址
	size_t			__length;	//shm长度
	std::atomic_uint64_t	__cur;		//shm当前读写位置
	int			__protect;	//shm保护模式
private:
	void __access(void* buf, size_t buf_len, size_t nbytes,
			bool reset, bool is_read) noexcept;
public:
	explicit posix_shm(const char* name, size_t size = sysconf(_SC_PAGESIZE),
			int oflag = O_RDWR | O_CREAT, mode_t mode  = REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE,
			int flags = MAP_SHARED, off_t offset = 0) noexcept;
	explicit posix_shm(const std::string& name, size_t size = sysconf(_SC_PAGESIZE),
			int oflag = O_RDWR | O_CREAT, mode_t mode  = REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE,
			int flags = MAP_SHARED, off_t offset = 0) noexcept;
	explicit posix_shm(const std::string* name, size_t size = sysconf(_SC_PAGESIZE),
			int oflag = O_RDWR | O_CREAT, mode_t mode  = REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE,
			int flags = MAP_SHARED, off_t offset = 0) noexcept;
	
	posix_shm(const posix_shm& ref) = delete;
	posix_shm(posix_shm&& ref) noexcept;
	~posix_shm(void) noexcept;

	posix_shm& operator = (const posix_shm& ref) = delete;
	posix_shm& operator = (const posix_shm&& ref) = delete;
	
	void*	getaddr(void) const noexcept;
	size_t	getlength(void) const noexcept;
	void	clear(void) noexcept;
	int	sync(int flags = MS_SYNC) const noexcept;
	size_t	seek(off_t offset = 0, int whence = SEEK_SET) noexcept;
	size_t	tell(void) const noexcept;
	void	read(void* buf, size_t buf_len, size_t nbytes, bool reset = true) noexcept;
	void	write(void* buf, size_t buf_len, size_t nbytes, bool reset = true) noexcept;
};
}

#endif /* end of include guard: HPP_CUSTOM_SHM_H */


