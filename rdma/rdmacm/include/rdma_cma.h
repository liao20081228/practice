/*
 * Copyright (c) 2005 Voltaire Inc.  All rights reserved.
 * Copyright (c) 2005-2014 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

/*
 * Global qkey value for UDP QPs and multicast groups created via the 
 * RDMA CM.
 */
#define RDMA_UDP_QKEY 0x01234567


enum {
	RDMA_MAX_RESP_RES = 0xFF,
	RDMA_MAX_INIT_DEPTH = 0xFF
};

#ifdef __cplusplus
}
#endif

#endif /* RDMA_CMA_H */
