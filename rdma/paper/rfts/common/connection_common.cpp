#include"connection_common.hpp"

rfts::cm_event_channel::cm_event_channel(void) noexcept
	: __cm_event_channel(rdma_create_event_channel())
{
	if (!__cm_event_channel)
		PERR("cm_event_channel::rdma_create_event_channel");
}

rfts::cm_event_channel::~cm_event_channel(void) noexcept
{
	if (cm_channel)
		rdma_destroy_event_channel(cm_channel);
	cm_channel = nullptr;
}

const rdma_event_channel* rfts::cm_event_channel::get_cm_channel(void) const noexcept
{
	return cm_channel;
}
