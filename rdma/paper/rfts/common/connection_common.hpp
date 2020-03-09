#pragma once
#ifndef HPP_CONNECTION_HPP
#define HPP_CONNECTION_HPP

#include<infiniband/verbs.h>
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<cerrno>
#include<cstdio>
#include<cstdlib>
#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
	#define _PERR(a) {perror(#a);exit(errno);}
	#define PERR(c) _PERR(c() failed) 
#endif /* ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO */


namespace rfts
{

class cm_event_channel
{
private:
	rdma_event_channel* __cm_event_channel;
public:
	cm_event_channel(void) noexcept;
	~cm_event_channel(void) noexcept;
	const rdma_event_channel* get_cm_event_channel(void) const noexcept;
	cm_event_channel(const cm_event_channel&) = delete;
	cm_event_channel(cm_event_channel&& ref)  noexcept;
	cm_event_channel& operator = (const cm_event_channel&) = delete;
	cm_event_channel& operator = (cm_event_channel&&) = delete;
};	

class cm_id
{
private:
	rdma_cm_id* id;
public:
	cm_id(const cm_event_channel* cm_e_ch, void* context = nullptr, 
			rdma_port_space ps = RDMA_PS_TCP ) noexcept;
	~cm_id() noexcept;
};


} // rfts
#endif /* end of include guard: HPP_CONNECTION_HPP */
