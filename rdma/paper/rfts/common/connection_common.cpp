#include"connection_common.hpp"

rfts::cm_event_channel::cm_event_channel(void) noexcept
	: __cm_event_channel(rdma_create_event_channel())
{
	if (!__cm_event_channel)
		PERR("cm_event_channel::rdma_create_event_channel");
}

rfts::cm_event_channel::cm_event_channel(cm_event_channel&& ref) noexcept
	: __cm_event_channel(ref.__cm_event_channel)
{
	ref.__cm_event_channel = nullptr;
}

rfts::cm_event_channel::~cm_event_channel(void) noexcept
{
	if (__cm_event_channel)
	{
		rdma_destroy_event_channel(__cm_event_channel);
		__cm_event_channel = nullptr;
	}
}

const rdma_event_channel* rfts::cm_event_channel::get_cm_event_channel(void) const noexcept
{
	return __cm_event_channel;
}

