#include"connection_common.hpp"

rfts::cm_event_channel::cm_event_channel(void) noexcept
	: cm_channel(rdma_create_event_channel())
{
	if (!cm_channel)
		PERR("cm_event_channel::rdma_create_event_channel");
}

rfts::cm_event_channel::~cm_event_channel(void) noexcept
{
	if (cm_channel)
		rdma_destroy_event_channel(const_cast<rdma_event_channel*>(cm_channel));
}
