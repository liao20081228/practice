#include"common.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>

int main(int argc, char *argv[])
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
	
	return 0;
}
