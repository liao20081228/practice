/*!@file
 *******************************************************************************
 <PRE>
 模块名:共享内存
 文件名:custom_shmem.hpp
 相关文件:custom_shmem.cpp
 作 者:廖伟志
 版 本:v1
 -------------------------------------------------------------------------------
 备注：
 -------------------------------------------------------------------------------
 修改记录:
 日期          版本       修改人              修改内容
 2020/03/06    v1         廖伟志
</PRE>
 ******************************************************************************/

#pragma once
#ifndef HPP_CUSTOM_SHMEM_HPP
	#define HPP_CUSTOM_SHARED_MEM_HPP

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
#ifndef CUSTOM_REGULAR_FILE_MODE
	#define REGULAR_FILE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#endif

#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {perror(#a);exit(errno);}
	#define PERR(c) _PERR(c() failed)
#endif /* ifndef CUSTOM_PRINT_ERROR_INFO */

//posix shared memory
class posix_shmem
{
private:
	const char*		__name;
	int			__fd;
	void*			__addr;
	size_t			__length;
	std::atomic_uint64_t	__cur;
	int			__protect;
private:
	void __maccess(void* buf, size_t buf_len, size_t nbytes,
			bool reset, bool is_read) noexcept;

public:
	explicit pshmem(const char* name, size_t size = sysconf(_SC_PAGESIZE),
			int oflag = O_RDWR | O_CREAT, mode_t mode  = REGULAR_FILE_MODE,
			int prot = PROT_READ | PROT_WRITE,
			int flags = MAP_SHARED, off_t offset = 0) noexcept;
	pshmem(const pshmem& ref) = delete;
	pshmem(pshmem&& ref) noexcept;
	~pshmem(void) noexcept;

	pshmem& operator = (const pshmem& ref) = delete;
	pshmem& operator = (const pshmem&& ref) = delete;

	void*	getaddr(void ) const noexcept;
	void	mclear(void) noexcept;
	int	msync(int flags = MS_SYNC) const noexcept;
	size_t	mseek(off_t offset = 0, int whence = SEEK_SET) noexcept;
	size_t	mtell(void) const noexcept;
	void	mread(void* buf, size_t buf_len, size_t nbytes, bool reset = true) noexcept;
	void	mwrite(void* buf, size_t buf_len, size_t nbytes, bool reset = true) noexcept;
};


#endif /* end of include guard: HPP_CUSTOM_SHMEM_H */


