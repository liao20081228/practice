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
/**
 * rdma_join_multicast - Joins a multicast group.
 * @id: Communication identifier associated with the request.
 * @addr: Multicast address identifying the group to join.
 * @context: User-defined context associated with the join request.
 * Description:
 *   Joins a multicast group and attaches an associated QP to the group.
 * Notes:
 *   Before joining a multicast group, the rdma_cm_id must be bound to
 *   an RDMA device by calling rdma_bind_addr or rdma_resolve_addr.  Use of
 *   rdma_resolve_addr requires the local routing tables to resolve the
 *   multicast address to an RDMA device.  The user must call
 *   rdma_leave_multicast to leave the multicast group and release any
 *   multicast resources.  The context is returned to the user through
 *   the private_data field in the rdma_cm_event.
 * See also:
 *   rdma_leave_multicast, rdma_bind_addr, rdma_resolve_addr, rdma_create_qp
 */
int rdma_join_multicast(struct rdma_cm_id *id, struct sockaddr *addr,
			void *context);

/**
 * rdma_leave_multicast - Leaves a multicast group.
 * @id: Communication identifier associated with the request.
 * @addr: Multicast address identifying the group to leave.
 * Description:
 *   Leaves a multicast group and detaches an associated QP from the group.
 * Notes:
 *   Calling this function before a group has been fully joined results in
 *   canceling the join operation.  Users should be aware that messages
 *   received from the multicast group may stilled be queued for
 *   completion processing immediately after leaving a multicast group.
 *   Destroying an rdma_cm_id will automatically leave all multicast groups.
 * See also:
 *   rdma_join_multicast, rdma_destroy_qp
 */
int rdma_leave_multicast(struct rdma_cm_id *id, struct sockaddr *addr);

/**
 * rdma_get_cm_event - Retrieves the next pending communication event.
 * @channel: Event channel to check for events.
 * @event: Allocated information about the next communication event.
 * Description:
 *   Retrieves a communication event.  If no events are pending, by default,
 *   the call will block until an event is received.
 * Notes:
 *   The default synchronous behavior of this routine can be changed by
 *   modifying the file descriptor associated with the given channel.  All
 *   events that are reported must be acknowledged by calling rdma_ack_cm_event.
 *   Destruction of an rdma_cm_id will block until related events have been
 *   acknowledged.
 * See also:
 *   rdma_ack_cm_event, rdma_create_event_channel, rdma_event_str
 */
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
 * rdma_get_devices - Get list of RDMA devices currently available.
 * @num_devices: If non-NULL, set to the number of devices returned.
 * Description:
 *   Return a NULL-terminated array of opened RDMA devices.  Callers can use
 *   this routine to allocate resources on specific RDMA devices that will be
 *   shared across multiple rdma_cm_id's.
 * Notes:
 *   The returned array must be released by calling rdma_free_devices.  Devices
 *   remain opened while the librdmacm is loaded.
 * See also:
 *   rdma_free_devices
 */
struct ibv_context **rdma_get_devices(int *num_devices);

/**
 * rdma_free_devices - Frees the list of devices returned by rdma_get_devices.
 * @list: List of devices returned from rdma_get_devices.
 * Description:
 *   Frees the device array returned by rdma_get_devices.
 * See also:
 *   rdma_get_devices
 */
void rdma_free_devices(struct ibv_context **list);

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
