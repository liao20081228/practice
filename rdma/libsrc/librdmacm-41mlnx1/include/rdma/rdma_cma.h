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

/*
 * Upon receiving a device removal event, users must destroy the associated
 * RDMA identifier and release all resources allocated with the device.
 */
enum rdma_cm_event_type {
	RDMA_CM_EVENT_ADDR_RESOLVED,
	RDMA_CM_EVENT_ADDR_ERROR,
	RDMA_CM_EVENT_ROUTE_RESOLVED,
	RDMA_CM_EVENT_ROUTE_ERROR,
	RDMA_CM_EVENT_CONNECT_REQUEST,
	RDMA_CM_EVENT_CONNECT_RESPONSE,
	RDMA_CM_EVENT_CONNECT_ERROR,
	RDMA_CM_EVENT_UNREACHABLE,
	RDMA_CM_EVENT_REJECTED,
	RDMA_CM_EVENT_ESTABLISHED,
	RDMA_CM_EVENT_DISCONNECTED,
	RDMA_CM_EVENT_DEVICE_REMOVAL,
	RDMA_CM_EVENT_MULTICAST_JOIN,
	RDMA_CM_EVENT_MULTICAST_ERROR,
	RDMA_CM_EVENT_ADDR_CHANGE,
	RDMA_CM_EVENT_TIMEWAIT_EXIT
};


#define RDMA_IB_IP_PS_MASK   0xFFFFFFFFFFFF0000ULL
#define RDMA_IB_IP_PORT_MASK 0x0000000000010000ULL
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


struct rdma_ud_param {
	const void *private_data;
	uint8_t private_data_len;
	struct ibv_ah_attr ah_attr;
	uint32_t qp_num;
	uint32_t qkey;
};

struct rdma_cm_event {
	struct rdma_cm_id	*id;
	struct rdma_cm_id	*listen_id;
	enum rdma_cm_event_type	 event;
	int			 status;
	union {
		struct rdma_conn_param conn;
		struct rdma_ud_param   ud;
	} param;
};



/**
 * rdma_notify - Notifies the librdmacm of an asynchronous event.
 * @id: RDMA identifier.
 * @event: Asynchronous event.
 * Description:
 *   Used to notify the librdmacm of asynchronous events that have occurred
 *   on a QP associated with the rdma_cm_id.
 * Notes:
 *   Asynchronous events that occur on a QP are reported through the user's
 *   device event handler.  This routine is used to notify the librdmacm of
 *   communication events.  In most cases, use of this routine is not
 *   necessary, however if connection establishment is done out of band
 *   (such as done through Infiniband), it's possible to receive data on a
 *   QP that is not yet considered connected.  This routine forces the
 *   connection into an established state in this case in order to handle
 *   the rare situation where the connection never forms on its own.
 *   Events that should be reported to the CM are: IB_EVENT_COMM_EST.
 * See also:
 *   rdma_connect, rdma_accept, rdma_listen
 */
int rdma_notify(struct rdma_cm_id *id, enum ibv_event_type event);
int rdma_get_cm_event(struct rdma_event_channel *channel,
		      struct rdma_cm_event **event);

/**
 * rdma_ack_cm_event - Free a communication event.
 * @event: Event to be released.
 * Description:
 *   All events which are allocated by rdma_get_cm_event must be released,
 *   there should be a one-to-one correspondence between successful gets
 *   and acks.
 * See also:
 *   rdma_get_cm_event, rdma_destroy_id
 */
int rdma_ack_cm_event(struct rdma_cm_event *event);



/**
 * rdma_lib_reset - Free and restart library resources
 * Description:
 *   Should be called from child process after fork to re-initialize global
 *   resources that become unavailble to child after clone().
 * Notes:
 *   To avoid memory leaks before calling this function process should try
 *   freeing all allocated librdma resources.
 */
int rdma_lib_reset(void);


/**
 * rdma_event_str - Returns a string representation of an rdma cm event.
 * @event: Asynchronous event.
 * Description:
 *   Returns a string representation of an asynchronous event.
 * See also:
 *   rdma_get_cm_event
 */
const char *rdma_event_str(enum rdma_cm_event_type event);

/* Option levels */
enum {
	RDMA_OPTION_ID		= 0,
	RDMA_OPTION_IB		= 1
};

/* Option details */
enum {
	RDMA_OPTION_ID_TOS	 = 0,	/* uint8_t: RFC 2474 */
	RDMA_OPTION_ID_REUSEADDR = 1,   /* int: ~SO_REUSEADDR */
	RDMA_OPTION_ID_AFONLY	 = 2,   /* int: ~IPV6_V6ONLY */
	RDMA_OPTION_ID_ACK_TIMEOUT = 3	/* uint8_t */
};

enum {
	RDMA_OPTION_IB_PATH	 = 1	/* struct ibv_path_data[] */
};


#ifdef __cplusplus
}
#endif

#endif /* RDMA_CMA_H */
