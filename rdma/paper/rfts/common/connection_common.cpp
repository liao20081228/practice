#include"connection_common.hpp"

rfts::cm_event_channel::cm_event_channel(void) noexcept
	: cm_channel(rdma_create_event_channel())
{
	if (!cm_channel)
	{
		errno = EINVAL;
		PERR("cm_event_channel::rdma_create_event_channel");
	}
}
