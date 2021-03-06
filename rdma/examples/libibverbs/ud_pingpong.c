/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
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
#define _GNU_SOURCE
#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <malloc.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <time.h>

#include "pingpong.h"

enum {
	PINGPONG_RECV_WRID = 1,		//接收WR 的 ID
	PINGPONG_SEND_WRID = 2,		//发送WR 的 ID
};

static int page_size;		//页大小
static int validate_buf;	//验证buf

struct pingpong_context {
	struct ibv_context	*context;	//设备上下文
	struct ibv_comp_channel *channel;	//完成通道
	struct ibv_pd		*pd;		//保护域
	struct ibv_mr		*mr;		//注册内存
	struct ibv_cq		*cq;		//完成队列
	struct ibv_qp		*qp;		//QP
	struct ibv_ah		*ah;		//AH
	char			*buf;		//buf
	int			 size;		//buf大小
	int			 send_flags;	//发送标志
	int			 rx_depth;	//接收深度
	int			 pending;	//挂起
	struct ibv_port_attr     portinfo;	//端口信息
};

struct pingpong_dest {
	int lid;		//lid
	int qpn;		//QP编号
	int psn;		//包序列号
	union ibv_gid gid;	//GID
};

static int pp_connect_ctx(struct pingpong_context *ctx, int port, int my_psn,
			  int sl, struct pingpong_dest *dest, int sgid_idx)
{
	struct ibv_ah_attr ah_attr = {
		.is_global     = 0,
		.dlid          = dest->lid,
		.sl            = sl,
		.src_path_bits = 0,
		.port_num      = port
	};
	struct ibv_qp_attr attr = {
		.qp_state		= IBV_QPS_RTR
	};

	if (ibv_modify_qp(ctx->qp, &attr, IBV_QP_STATE)) {
		fprintf(stderr, "Failed to modify QP to RTR\n");
		return 1;
	}

	attr.qp_state	    = IBV_QPS_RTS;
	attr.sq_psn	    = my_psn;

	if (ibv_modify_qp(ctx->qp, &attr,
			  IBV_QP_STATE              |
			  IBV_QP_SQ_PSN)) {
		fprintf(stderr, "Failed to modify QP to RTS\n");
		return 1;
	}

	if (dest->gid.global.interface_id) {
		ah_attr.is_global = 1;
		ah_attr.grh.hop_limit = 1;
		ah_attr.grh.dgid = dest->gid;
		ah_attr.grh.sgid_index = sgid_idx;
	}

	ctx->ah = ibv_create_ah(ctx->pd, &ah_attr);
	if (!ctx->ah) {
		fprintf(stderr, "Failed to create AH\n");
		return 1;
	}

	return 0;
}

//客户端将my_dest发送给服务端,并接受来自服务端的信息
static struct pingpong_dest *pp_client_exch_dest(const char *servername, int port,
						 const struct pingpong_dest *my_dest)
{
	struct addrinfo *res, *t;
	struct addrinfo hints = {
		.ai_family   = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM
	};
	char *service;
	char msg[sizeof "0000:000000:000000:00000000000000000000000000000000"];
	int n;
	int sockfd = -1;
	struct pingpong_dest *rem_dest = NULL;
	char gid[33];

	if (asprintf(&service, "%d", port) < 0)
		return NULL;

	n = getaddrinfo(servername, service, &hints, &res);//获取服务端的信息

	if (n < 0) {
		fprintf(stderr, "%s for %s:%d\n", gai_strerror(n), servername, port);
		free(service);
		return NULL;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);//创建套接字
		if (sockfd >= 0) {
			if (!connect(sockfd, t->ai_addr, t->ai_addrlen))//发起连接
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo(res);
	free(service);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't connect to %s:%d\n", servername, port);
		return NULL;
	}

	gid_to_wire_gid(&my_dest->gid, gid);//将二进制的gid转为wire_gid
	sprintf(msg, "%04x:%06x:%06x:%s", my_dest->lid, my_dest->qpn,
							my_dest->psn, gid);//将my_dest中的lid、qpn、psn、wire__gid转为msg
	if (write(sockfd, msg, sizeof msg) != sizeof msg) {//发送my_dest
		fprintf(stderr, "Couldn't send local address\n");
		goto out;
	}

	if (read(sockfd, msg, sizeof msg) != sizeof msg ||//接受服务端发来的my_dest
	    write(sockfd, "done", sizeof "done") != sizeof "done") {
		perror("client read/write");
		fprintf(stderr, "Couldn't read/write remote address\n");
		goto out;
	}

	rem_dest = malloc(sizeof *rem_dest);
	if (!rem_dest)
		goto out;

	sscanf(msg, "%x:%x:%x:%s", &rem_dest->lid, &rem_dest->qpn,
							&rem_dest->psn, gid);//从msg中去读取远端的lid、qpn、psn、wire_gid并存入rem_dest
	wire_gid_to_gid(gid, &rem_dest->gid);//将wire_gid转为gid

out:
	close(sockfd);
	return rem_dest;
}

//服务端将my_dest发送给客户端，并接受客户端传来的数据
static struct pingpong_dest *pp_server_exch_dest(struct pingpong_context *ctx,
						 int ib_port, int port, int sl,
						 const struct pingpong_dest *my_dest,
						 int sgid_idx)
{
	struct addrinfo *res, *t;
	struct addrinfo hints = {
		.ai_flags    = AI_PASSIVE,
		.ai_family   = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM
	};
	char *service;
	char msg[sizeof "0000:000000:000000:00000000000000000000000000000000"];
	int n;
	int sockfd = -1, connfd;
	struct pingpong_dest *rem_dest = NULL;
	char gid[33];

	if (asprintf(&service, "%d", port) < 0)
		return NULL;

	n = getaddrinfo(NULL, service, &hints, &res);//获取地址信息

	if (n < 0) {
		fprintf(stderr, "%s for port %d\n", gai_strerror(n), port);
		free(service);
		return NULL;
	}

	for (t = res; t; t = t->ai_next) {
		sockfd = socket(t->ai_family, t->ai_socktype, t->ai_protocol);//创建套接字
		if (sockfd >= 0) {
			n = 1;

			setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof n);

			if (!bind(sockfd, t->ai_addr, t->ai_addrlen))
				break;
			close(sockfd);
			sockfd = -1;
		}
	}

	freeaddrinfo(res);
	free(service);

	if (sockfd < 0) {
		fprintf(stderr, "Couldn't listen to port %d\n", port);
		return NULL;
	}

	listen(sockfd, 1);//监听
	connfd = accept(sockfd, NULL, NULL);//接受连接
	close(sockfd);//关闭监听的套接字
	if (connfd < 0) {
		fprintf(stderr, "accept() failed\n");
		return NULL;
	}

	n = read(connfd, msg, sizeof msg);//接受客户端发来的msg
	if (n != sizeof msg) {
		perror("server read");
		fprintf(stderr, "%d/%d: Couldn't read remote address\n", n, (int) sizeof msg);
		goto out;
	}

	rem_dest = malloc(sizeof *rem_dest);
	if (!rem_dest)
		goto out;

	sscanf(msg, "%x:%x:%x:%s", &rem_dest->lid, &rem_dest->qpn,
							&rem_dest->psn, gid);//从msg中获取客户端的lid、qpn、psn、gid
	wire_gid_to_gid(gid, &rem_dest->gid);//将客户端wire_gid转为gid

	if (pp_connect_ctx(ctx, ib_port, my_dest->psn, sl, rem_dest,//将QP从INIT->RTR->RTS
								sgid_idx)) {
		fprintf(stderr, "Couldn't connect to remote QP\n");
		free(rem_dest);
		rem_dest = NULL;
		goto out;
	}

	gid_to_wire_gid(&my_dest->gid, gid);//将服务端的gid转为wire_gid
	sprintf(msg, "%04x:%06x:%06x:%s", my_dest->lid, my_dest->qpn,
							my_dest->psn, gid);//将服务端的lid、qpn、psn、wire_gid转为msg
	if (write(connfd, msg, sizeof msg) != sizeof msg ||//发送服务的msg给客户端
	    read(connfd, msg, sizeof msg) != sizeof "done") {
		fprintf(stderr, "Couldn't send/recv local address\n");
		free(rem_dest);
		rem_dest = NULL;
		goto out;
	}
out:
	close(connfd);
	return rem_dest;
}


//创建pingpong上下文，创建buf，创建设备上下文，判断MTU，创建CC、PD、MR、CQ、QP、并且置于INIT
static struct pingpong_context *pp_init_ctx(struct ibv_device *ib_dev, int size,
					    int rx_depth, int port,
					    int use_event)
{
	struct pingpong_context *ctx;

	ctx = malloc(sizeof *ctx);
	if (!ctx)
		return NULL;

	ctx->size       = size;
	ctx->send_flags = IBV_SEND_SIGNALED;
	ctx->rx_depth   = rx_depth;

	ctx->buf = memalign(page_size, size + 40);
	if (!ctx->buf) {
		fprintf(stderr, "Couldn't allocate work buf.\n");
		goto clean_ctx;
	}

	/* FIXME memset(ctx->buf, 0, size + 40); */
	memset(ctx->buf, 0x7b, size + 40);

	ctx->context = ibv_open_device(ib_dev);//获取设备上下文
	if (!ctx->context) {
		fprintf(stderr, "Couldn't get context for %s\n",
			ibv_get_device_name(ib_dev));
		goto clean_buffer;
	}

	{
		struct ibv_port_attr port_info = {};//获取端口信息
		int mtu;

		if (ibv_query_port(ctx->context, port, &port_info)) {
			fprintf(stderr, "Unable to query port info for port %d\n", port);
			goto clean_device;
		}
		mtu = 1 << (port_info.active_mtu + 7);//判断MTU大小
		if (size > mtu) {
			fprintf(stderr, "Requested size larger than port MTU (%d)\n", mtu);
			goto clean_device;
		}
	}

	if (use_event) {//使用事件机制
		ctx->channel = ibv_create_comp_channel(ctx->context);
		if (!ctx->channel) {
			fprintf(stderr, "Couldn't create completion channel\n");
			goto clean_device;
		}
	} else
		ctx->channel = NULL;

	ctx->pd = ibv_alloc_pd(ctx->context);//创建PD
	if (!ctx->pd) {
		fprintf(stderr, "Couldn't allocate PD\n");
		goto clean_comp_channel;
	}

	ctx->mr = ibv_reg_mr(ctx->pd, ctx->buf, size + 40, IBV_ACCESS_LOCAL_WRITE);//创建MR
	if (!ctx->mr) {
		fprintf(stderr, "Couldn't register MR\n");
		goto clean_pd;
	}

	ctx->cq = ibv_create_cq(ctx->context, rx_depth + 1, NULL,
				ctx->channel, 0);//创建CQ
	if (!ctx->cq) {
		fprintf(stderr, "Couldn't create CQ\n");
		goto clean_mr;
	}

	{
		struct ibv_qp_attr attr;
		struct ibv_qp_init_attr init_attr = {
			.send_cq = ctx->cq,
			.recv_cq = ctx->cq,
			.cap     = {
				.max_send_wr  = 1,
				.max_recv_wr  = rx_depth,
				.max_send_sge = 1,
				.max_recv_sge = 1
			},
			.qp_type = IBV_QPT_UD,
		};

		ctx->qp = ibv_create_qp(ctx->pd, &init_attr);//创建QP
		if (!ctx->qp)  {
			fprintf(stderr, "Couldn't create QP\n");
			goto clean_cq;
		}

		ibv_query_qp(ctx->qp, &attr, IBV_QP_CAP, &init_attr);//是否使用内联发送
		if (init_attr.cap.max_inline_data >= size) {
			ctx->send_flags |= IBV_SEND_INLINE;
		}
	}

	{
		struct ibv_qp_attr attr = {
			.qp_state        = IBV_QPS_INIT,
			.pkey_index      = 0,
			.port_num        = port,
			.qkey            = 0x11111111
		};

		if (ibv_modify_qp(ctx->qp, &attr,
				  IBV_QP_STATE              |
				  IBV_QP_PKEY_INDEX         |
				  IBV_QP_PORT               |
				  IBV_QP_QKEY)) {
			fprintf(stderr, "Failed to modify QP to INIT\n");
			goto clean_qp;
		}//修改QP状态
	}

	return ctx;

clean_qp:
	ibv_destroy_qp(ctx->qp);

clean_cq:
	ibv_destroy_cq(ctx->cq);

clean_mr:
	ibv_dereg_mr(ctx->mr);

clean_pd:
	ibv_dealloc_pd(ctx->pd);

clean_comp_channel:
	if (ctx->channel)
		ibv_destroy_comp_channel(ctx->channel);

clean_device:
	ibv_close_device(ctx->context);

clean_buffer:
	free(ctx->buf);

clean_ctx:
	free(ctx);

	return NULL;
}

static int pp_close_ctx(struct pingpong_context *ctx)
{
	if (ibv_destroy_qp(ctx->qp)) {
		fprintf(stderr, "Couldn't destroy QP\n");
		return 1;
	}

	if (ibv_destroy_cq(ctx->cq)) {
		fprintf(stderr, "Couldn't destroy CQ\n");
		return 1;
	}

	if (ibv_dereg_mr(ctx->mr)) {
		fprintf(stderr, "Couldn't deregister MR\n");
		return 1;
	}

	if (ibv_destroy_ah(ctx->ah)) {
		fprintf(stderr, "Couldn't destroy AH\n");
		return 1;
	}

	if (ibv_dealloc_pd(ctx->pd)) {
		fprintf(stderr, "Couldn't deallocate PD\n");
		return 1;
	}

	if (ctx->channel) {
		if (ibv_destroy_comp_channel(ctx->channel)) {
			fprintf(stderr, "Couldn't destroy completion channel\n");
			return 1;
		}
	}

	if (ibv_close_device(ctx->context)) {
		fprintf(stderr, "Couldn't release context\n");
		return 1;
	}

	free(ctx->buf);
	free(ctx);

	return 0;
}

//发布n个接收工作请求到接收队列中，返回值表示成功发布的接收请求数量
static int pp_post_recv(struct pingpong_context *ctx, int n)
{
	struct ibv_sge list = {
		.addr	= (uintptr_t) ctx->buf,
		.length = ctx->size + 40,
		.lkey	= ctx->mr->lkey
	};
	struct ibv_recv_wr wr = {
		.wr_id	    = PINGPONG_RECV_WRID,
		.sg_list    = &list,
		.num_sge    = 1,
	};
	struct ibv_recv_wr *bad_wr;
	int i;

	for (i = 0; i < n; ++i)
		if (ibv_post_recv(ctx->qp, &wr, &bad_wr))
			break;

	return i;
}

static int pp_post_send(struct pingpong_context *ctx, uint32_t qpn)
{
	struct ibv_sge list = {
		.addr	= (uintptr_t) ctx->buf + 40,
		.length = ctx->size,
		.lkey	= ctx->mr->lkey
	};
	struct ibv_send_wr wr = {
		.wr_id	    = PINGPONG_SEND_WRID,
		.sg_list    = &list,
		.num_sge    = 1,
		.opcode     = IBV_WR_SEND,
		.send_flags = ctx->send_flags,
		.wr         = {
			.ud = {
				 .ah          = ctx->ah,
				 .remote_qpn  = qpn,
				 .remote_qkey = 0x11111111
			 }
		}
	};
	struct ibv_send_wr *bad_wr;

	return ibv_post_send(ctx->qp, &wr, &bad_wr);
}

static void usage(const char *argv0)
{
	printf("Usage:\n");
	printf("  %s            start a server and wait for connection\n", argv0);
	printf("  %s <host>     connect to server at <host>\n", argv0);
	printf("\n");
	printf("Options:\n");
	printf("  -p, --port=<port>      listen on/connect to port <port> (default 18515)\n");
	printf("  -d, --ib-dev=<dev>     use IB device <dev> (default first device found)\n");
	printf("  -i, --ib-port=<port>   use port <port> of IB device (default 1)\n");
	printf("  -s, --size=<size>      size of message to exchange (default 2048)\n");
	printf("  -r, --rx-depth=<dep>   number of receives to post at a time (default 500)\n");
	printf("  -n, --iters=<iters>    number of exchanges (default 1000)\n");
        printf("  -l, --sl=<SL>          send messages with service level <SL> (default 0)\n");
	printf("  -e, --events           sleep on CQ events (default poll)\n");
	printf("  -g, --gid-idx=<gid index> local port gid index\n");
	printf("  -c, --chk              validate received buffer\n");
}

int main(int argc, char *argv[])
{
	struct ibv_device      **dev_list;		//设备列表
	struct ibv_device	*ib_dev;		//设备
	struct pingpong_context *ctx;			//pingpong上下文，设备上下文、CC、CQ、QP、AH、buf info、send flag
	struct pingpong_dest     my_dest;		//本地端信息
	struct pingpong_dest    *rem_dest;		//远程端信息
	struct timeval           start, end;		//即时
	char                    *ib_devname = NULL;	//设备名
	char                    *servername = NULL;	//服务名
	unsigned int             port = 18515;		//交换信息的端口号
	int                      ib_port = 1;		//IB设备的物理端口
	unsigned int             size = 2048;		//信息大小
	unsigned int             rx_depth = 500;	//接收工作请求大小
	unsigned int             iters = 1000;		//重复试验的次数
	int                      use_event = 0;		//轮询或事件机制
	int                      routs;			//发布成功的接收请求的数量，如果小于rx_depth则出错
	int                      rcnt, scnt;		//计数器
	int                      num_cq_events = 0;	//CQ完成数
	int                      sl = 0;		//服务级别
	int			 gidx = -1;		//gid索引
	char			 gid[33];		//gid

	srand48(getpid() * time(NULL));

	while (1) {
		int c;

		static struct option long_options[] = {
			{ .name = "port",     .has_arg = 1, .val = 'p' },
			{ .name = "ib-dev",   .has_arg = 1, .val = 'd' },
			{ .name = "ib-port",  .has_arg = 1, .val = 'i' },
			{ .name = "size",     .has_arg = 1, .val = 's' },
			{ .name = "rx-depth", .has_arg = 1, .val = 'r' },
			{ .name = "iters",    .has_arg = 1, .val = 'n' },
			{ .name = "sl",       .has_arg = 1, .val = 'l' },
			{ .name = "events",   .has_arg = 0, .val = 'e' },
			{ .name = "gid-idx",  .has_arg = 1, .val = 'g' },
			{ .name = "chk",      .has_arg = 0, .val = 'c' },
			{}
		};

		c = getopt_long(argc, argv, "p:d:i:s:r:n:l:eg:c", long_options,
				NULL);
		if (c == -1)
			break;

		switch (c) {
		case 'p'://交换信息的端口号, 默认18515
			port = strtol(optarg, NULL, 0);
			if (port > 65535) {
				usage(argv[0]);
				return 1;
			}
			break;

		case 'd'://ib设备名
			ib_devname = strdupa(optarg);
			break;

		case 'i'://ib设备的物理端口号
			ib_port = strtol(optarg, NULL, 0);
			if (ib_port < 1) {
				usage(argv[0]);
				return 1;
			}
			break;

		case 's'://数据大小
			size = strtoul(optarg, NULL, 0);
			break;

		case 'r'://接收队列深度
			rx_depth = strtoul(optarg, NULL, 0);
			break;

		case 'n'://重复次数
			iters = strtoul(optarg, NULL, 0);
			break;

		case 'l'://服务级别
			sl = strtol(optarg, NULL, 0);
			break;

		case 'e'://使用事件机制，默认同步机制
			++use_event;
			break;

		case 'g'://gid索引
			gidx = strtol(optarg, NULL, 0);
			break;

		case 'c'://验证
			validate_buf = 1;
			break;

		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (optind == argc - 1)
		servername = strdupa(argv[optind]);//服务器ip地址
	else if (optind < argc) {
		usage(argv[0]);
		return 1;
	}

	page_size = sysconf(_SC_PAGESIZE);

	dev_list = ibv_get_device_list(NULL);//获取设别列表
	if (!dev_list) {
		perror("Failed to get IB devices list");
		return 1;
	}

	if (!ib_devname) {//打开指定的Ib设备
		ib_dev = *dev_list;
		if (!ib_dev) {
			fprintf(stderr, "No IB devices found\n");
			return 1;
		}
	} else {//或者打开一个IB设备
		int i;
		for (i = 0; dev_list[i]; ++i)
			if (!strcmp(ibv_get_device_name(dev_list[i]), ib_devname))
				break;
		ib_dev = dev_list[i];
		if (!ib_dev) {
			fprintf(stderr, "IB device %s not found\n", ib_devname);
			return 1;
		}
	}

	ctx = pp_init_ctx(ib_dev, size, rx_depth, ib_port, use_event);//创建CC、CQ、QP、并置于INIT状态
	if (!ctx)
		return 1;

	routs = pp_post_recv(ctx, ctx->rx_depth);//发布rx_depth个接收请求到接收队列中,routs为成功发布的wr的数量
	if (routs < ctx->rx_depth) {
		fprintf(stderr, "Couldn't post receive (%d)\n", routs);
		return 1;
	}

	if (use_event)//如果使用事件机制,则发出请求通知
		if (ibv_req_notify_cq(ctx->cq, 0)) {
			fprintf(stderr, "Couldn't request CQ notification\n");
			return 1;
		}

	if (pp_get_port_info(ctx->context, ib_port, &ctx->portinfo)) {
		fprintf(stderr, "Couldn't get port info\n");
		return 1;
	}
	my_dest.lid = ctx->portinfo.lid;//设置my_dest用于带外交换到远端

	my_dest.qpn = ctx->qp->qp_num;
	my_dest.psn = lrand48() & 0xffffff;

	if (gidx >= 0) {//如果指定了gid索引，则获取指定gid索引对应的gid
		if (ibv_query_gid(ctx->context, ib_port, gidx, &my_dest.gid)) {
			fprintf(stderr, "Could not get local gid for gid index "
								"%d\n", gidx);
			return 1;
		}
	} else//否则gid为空
		memset(&my_dest.gid, 0, sizeof my_dest.gid);

	inet_ntop(AF_INET6, &my_dest.gid, gid, sizeof gid);//将二进制的gid转为字符串,为了打印输出
	printf("  local address:  LID 0x%04x, QPN 0x%06x, PSN 0x%06x: GID %s\n",
	       my_dest.lid, my_dest.qpn, my_dest.psn, gid);

	if (servername)
		rem_dest = pp_client_exch_dest(servername, port, &my_dest);//客户端交换信息
	else
		rem_dest = pp_server_exch_dest(ctx, ib_port, port, sl,
							&my_dest, gidx);//服务端交换信息

	if (!rem_dest)//如果rem_dest为空，则说明没有收到远端的信息
		return 1;

	inet_ntop(AF_INET6, &rem_dest->gid, gid, sizeof gid);//打印远端的信息
	printf("  remote address: LID 0x%04x, QPN 0x%06x, PSN 0x%06x, GID %s\n",
	       rem_dest->lid, rem_dest->qpn, rem_dest->psn, gid);

	if (servername)//客户端开始连接
		if (pp_connect_ctx(ctx, ib_port, my_dest.psn, sl, rem_dest,
									gidx))
			return 1;

//致此为止，两端RDMA UD 通信已经建立
	ctx->pending = PINGPONG_RECV_WRID;//=1

	if (servername) {//如果时客户端
		if (validate_buf)
			for (int i = 0; i < size; i += page_size)
				ctx->buf[i + 40] = i / page_size % sizeof(char);

		if (pp_post_send(ctx, rem_dest->qpn)) {//发布一个发送请求
			fprintf(stderr, "Couldn't post send\n");
			return 1;
		}
		ctx->pending |= PINGPONG_SEND_WRID;//=3
	}

	if (gettimeofday(&start, NULL)) {//获取开始时间
		perror("gettimeofday");
		return 1;
	}

	rcnt = scnt = 0;
	while (rcnt < iters || scnt < iters) {//接收或发送的次数小于指定的重复次数
		if (use_event) {//如果使用事件机制
			struct ibv_cq *ev_cq;
			void          *ev_ctx;

			if (ibv_get_cq_event(ctx->channel, &ev_cq, &ev_ctx)) {//获取事件
				fprintf(stderr, "Failed to get cq_event\n");
				return 1;
			}

			++num_cq_events;//事件计数+1

			if (ev_cq != ctx->cq) {
				fprintf(stderr, "CQ event for unknown CQ %p\n", ev_cq);
				return 1;
			}

			if (ibv_req_notify_cq(ctx->cq, 0)) {//请求CQ通知
				fprintf(stderr, "Couldn't request CQ notification\n");
				return 1;
			}
		}

		{
			struct ibv_wc wc[2];
			int ne, i;

			do {
				ne = ibv_poll_cq(ctx->cq, 2, wc);
				if (ne < 0) {
					fprintf(stderr, "poll CQ failed %d\n", ne);
					return 1;
				}
			} while (!use_event && ne < 1);//获取WC，由于每一次发送一个，接收一个发送了一个验证消息，所以这里第一次要取出两个完成,

			for (i = 0; i < ne; ++i) {
				if (wc[i].status != IBV_WC_SUCCESS) {//如果wc不为成功，则输出wc位于什么状态，以及wc的wr_id
					fprintf(stderr, "Failed status %s (%d) for wr_id %d\n",
						ibv_wc_status_str(wc[i].status),
						wc[i].status, (int) wc[i].wr_id);
					return 1;
				}

				switch ((int) wc[i].wr_id) {//根据工作id来判断哪个成功了,成功就+1
				case PINGPONG_SEND_WRID:
					++scnt;
					break;

				case PINGPONG_RECV_WRID://如果是接收成功则补上一个接收wr
					if (--routs <= 1) {
						routs += pp_post_recv(ctx, ctx->rx_depth - routs);
						if (routs < ctx->rx_depth) {
							fprintf(stderr,
								"Couldn't post receive (%d)\n",
								routs);
							return 1;
						}
					}

					++rcnt;
					break;

				default:
					fprintf(stderr, "Completion for unknown wr_id %d\n",
						(int) wc[i].wr_id);
					return 1;
				}

				ctx->pending &= ~(int) wc[i].wr_id;
				if (scnt < iters && !ctx->pending) {
					if (pp_post_send(ctx, rem_dest->qpn)) {
						fprintf(stderr, "Couldn't post send\n");
						return 1;
					}
					ctx->pending = PINGPONG_RECV_WRID |
						       PINGPONG_SEND_WRID;
				}
			}
		}
	}

	if (gettimeofday(&end, NULL)) {
		perror("gettimeofday");
		return 1;
	}

	{
		float usec = (end.tv_sec - start.tv_sec) * 1000000 +
			(end.tv_usec - start.tv_usec);
		long long bytes = (long long) size * iters * 2;

		printf("%lld bytes in %.2f seconds = %.2f Mbit/sec\n",
		       bytes, usec / 1000000., bytes * 8. / usec);
		printf("%d iters in %.2f seconds = %.2f usec/iter\n",
		       iters, usec / 1000000., usec / iters);

		if ((!servername) && (validate_buf)) {
			for (int i = 0; i < size; i += page_size)
				if (ctx->buf[i + 40] !=
				    i / page_size % sizeof(char))
					printf("invalid data in page %d\n",
					       i / page_size);
		}
	}

	ibv_ack_cq_events(ctx->cq, num_cq_events);

	if (pp_close_ctx(ctx))
		return 1;

	ibv_free_device_list(dev_list);
	free(rem_dest);

	return 0;
}
