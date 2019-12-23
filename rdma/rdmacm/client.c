#include"parameters.h"
#include"print_filed.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{

	//parse cmd line arguments
	struct user_parameters user_params={0};
	user_params.address="192.168.3.190";
	user_params.port="8888";
	handle_cmd(&user_params,argc, argv);

	//get addinfo
	struct rdma_addrinfo hints, 
			     *res = NULL;
	memset(&hints, 0, sizeof(struct rdma_addrinfo));
	hints.ai_port_space=RDMA_PS_TCP;//RC
	hints.ai_port_space=user_params.portspace;	
	if(0 != rdma_getaddrinfo(user_params.address, user_params.port, &hints, &res))
	{
		perror("call rdma_getaddrinfo  failed:");
		exit(-2);
	}

	printf("------------------struct rdma_addrinfo----------------\n");		
	printf("ai_flags: %d\n", res->ai_flags);		
	printf("ai_family: %d\n", res->ai_family);		
	printf("ai_qp_type: %d\n", res->ai_qp_type);		
	printf("ai_port_space: %d\n", res->ai_port_space);		
	printf("ai_src_len: %d\n", res->ai_src_len);		
	printf("ai_dst_len: %d\n", res->ai_dst_len);
	if(res->ai_src_len!=0)
		printf("ai_src_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(res->ai_src_addr))->sin_addr));
	if(res->ai_dst_len!=0)
		printf("ai_dst_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(res->ai_dst_addr))->sin_addr));
	printf("ai_src_canonname: %s\n", res->ai_src_canonname);		
	printf("ai_dst_canonname: %s\n", res->ai_dst_canonname);		
	printf("ai_route_len: %lu\n", res->ai_route_len);		
	printf("ai_route: %p\n", res->ai_route);		
	printf("ai_connect_len: %lu\n", res->ai_connect_len);		
	printf("ai_connect: %p\n", res->ai_connect);		
	printf("ai_next: %p\n", res->ai_next);		

	//create iD and QP
	struct rdma_cm_id *id=NULL;

	struct ibv_qp_init_attr qp_init_attr;
	memset (&qp_init_attr, 0, sizeof(struct ibv_qp_init_attr));
	qp_init_attr.cap.max_send_wr = 1;
	qp_init_attr.cap.max_recv_wr = 1;
	qp_init_attr.cap.max_send_sge = 1; 
	qp_init_attr.cap.max_recv_sge = 1;


	if(0 != rdma_create_ep(&id, res, NULL, &qp_init_attr))
	{
		perror("call rdma_create_ep failed");
		exit(-2);
	}

	printf("------------------struct inv_qp_init_attr----------------\n");		
	printf("qp_context: %p \n",qp_init_attr.qp_context);
	printf("send_cq: %p \n",qp_init_attr.send_cq);
	printf("recv_cq: %p \n",qp_init_attr.recv_cq);
	printf("srq: %p \n",qp_init_attr.srq);
	printf("max_inline_data: %u \n",qp_init_attr.cap.max_inline_data);
	printf("max_send_wr: %u \n",qp_init_attr.cap.max_send_wr);
	printf("max_recv_wr: %u \n",qp_init_attr.cap.max_recv_wr);
	printf("max_send_sge: %u \n",qp_init_attr.cap.max_send_sge);
	printf("max_recv_sge: %u \n",qp_init_attr.cap.max_recv_sge);
	printf("qp_type: %u \n",qp_init_attr.qp_type);
	printf("sq_sig_all: %u \n",qp_init_attr.sq_sig_all);
	
	printf("------------------struct rdma_cm_id----------------\n");		
	PRINT_FILED(id->verbs, verbs, p);
	PRINT_FILED(id->ps,ps,d);
	PRINT_FILED(id->qp_type, qp_type, d);		
	





	return 0;

}
