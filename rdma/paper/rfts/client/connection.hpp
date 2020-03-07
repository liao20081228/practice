#include<infiniband/verbs.h>
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
namespace rfts
{

class cm_event_channel
{
private:
	rdma_event_channel* cm_channel;
public:
};

} // rfts
