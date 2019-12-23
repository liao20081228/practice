#include"parameters.h"
#include<rdma/rdma_cma.h>
#include<rdma/rdma_verbs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{

	//parse cmd line arguments
	struct user_parameters user_params={0,0};
	user_params.address="192.168.3.190";
	user_params.port="8888";
	handle_cmd(&user_params,argc, argv);

	//get addinfo
	struct rdma_addrinfo hints, 
			     *res = NULL;
	memset(&hints, 0, sizeof(struct rdma_addrinfo));
	hints.ai_port_space=RDMA_PS_TCP;//RC
	hints.ai_flags=RAI_NUMERICHOST;
	hints.ai_port_space=user_params.portspace;	
	if(0 != rdma_getaddrinfo(user_params.address, user_params.port, &hints, &res))
	{
		perror("call rdma_getaddrinfo  failed:");
		exit(-2);
	}
	
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
	printf("ai_family: %lu\n", res->ai_route_len);		
	printf("ai_family: %p\n", res->ai_route);		
	printf("ai_family: %lu\n", res->ai_connect_len);		
	printf("ai_family: %p\n", res->ai_connect);		
	printf("ai_family: %p\n", res->ai_next);		

	//create iD and QP
	struct rdma_cm_id *id=NULL;

	struct ibv_qp_init_attr qp_init_attr;
	memset (&qp_init_attr, 0, sizeof(struct ibv_qp_init_attr));
	
	if(0 != rdma_create_ep(&id))


	return 0;

}
