#pragma once
#ifndef HPP_CONNECTION_HPP
#define HPP_CONNECTION_HPP

#include<infiniband/verbs.h>
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include<cerrno>

#ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
#define CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO
#endif /* ifndef CUSTOM_PRINT_ERROR_INFO_AND_EXIT_WITH_ERRNO */


namespace rfts
{

class cm_event_channel
{
private:
	rdma_event_channel* cm_channel;
public:
	cm_event_channel() noexcept;
	~cm_event_channel() noexcept;
};

} // rfts

#endif /* end of include guard: HPP_CONNECTION_HPP */
