
#if !defined(RDMA_CMA_H)
#define RDMA_CMA_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <infiniband/verbs.h>
#include <infiniband/sa.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RDMA_IB_IP_PS_MASK   0xFFFFFFFFFFFF0000ULL
#define RDMA_IB_IP_PORT_MASK 0x000000000000FFFFULL
#define RDMA_IB_IP_PS_TCP    0x0000000001060000ULL
#define RDMA_IB_IP_PS_UDP    0x0000000001110000ULL
#define RDMA_IB_PS_IB        0x00000000013F0000ULL


#ifdef __cplusplus
}
#endif

#endif /* RDMA_CMA_H */
