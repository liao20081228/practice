#include"common.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Gint main(int argc, char *argv[])
{
	struct option longopts[]=
	{
		{"help",    no_argument,       NULL, 'H'},
		{"version", no_argument,       NULL, 'V'},
		{"client",  no_argument,       NULL, 'c'},
		{"server",  no_argument,       NULL, 's'},
		{"port",    required_argument, NULL, 'p'},
		{"a:ddress", optional_argument, NULL, 'a'},
		{0,         0,                 0,     0}
	};
	handle_cmd(argc, argv, longopts);
	

	struct rdma_cm_id *rdma_id = NULL;
	struct ibv_mr *send_mr = NULL,
			*recv_mr = NULL;
	int flags = 0;
	
	char send_msg[100];
	char recv_msg[100];


	struct rdma_addrinfo hints, 
			     *res = NULL;
	memset(&hints, 0, sizeof(struct rdma_addrinfo));
	rdma_getaddrinfo(address, port, &hints, &res);
	
	printf("ai_flags: %d\n", hints.ai_flags);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_qp_type: %d\n", hints.ai_qp_type);		
	printf("ai_port_space: %d\n", hints.ai_port_space);		
	printf("ai_src_len: %d\n", hints.ai_src_len);		
	printf("ai_dst_len: %d\n", hints.ai_dst_len);
	printf("ai_src_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(hints.ai_src_addr))->sin_addr));
	printf("ai_dst_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(hints.ai_dst_addr))->sin_addr));
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	printf("ai_family: %d\n", hints.ai_family);		
	
	return 0;
}
