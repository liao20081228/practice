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
	handle_cmd(&user_params,argc, argv))
	

	/*struct rdma_cm_id *rdma_id = NULL;*/
	/*struct ibv_mr *send_mr = NULL,*/
			/**recv_mr = NULL;*/
	/*int flags = 0;*/
	
	/*char send_msg[100];*/
	/*char recv_msg[100];*/


	/*struct rdma_addrinfo hints, */
			     /**res = NULL;*/
	/*memset(&hints, 0, sizeof(struct rdma_addrinfo));*/
	
	/*if(0!=rdma_getaddrinfo(address, port, &hints, &res))*/
	/*{*/
		/*perror("reason:");*/
		/*exit(0);*/
	/*}*/
	
	/*printf("ai_flags: %d\n", hints.ai_flags);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_qp_type: %d\n", hints.ai_qp_type);		*/
	/*printf("ai_port_space: %d\n", hints.ai_port_space);		*/
	/*printf("ai_src_len: %d\n", hints.ai_src_len);		*/
	/*printf("ai_dst_len: %d\n", hints.ai_dst_len);*/
	/*printf("ai_src_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(hints.ai_src_addr))->sin_addr));*/
	/*printf("ai_dst_addr: %s\n", inet_ntoa( ((struct sockaddr_in*)(hints.ai_dst_addr))->sin_addr));*/
	/*printf("ai_src_canonname: %s\n", hints.ai_src_canonname);		*/
	/*printf("ai_dst_canonname: %s\n", hints.ai_dst_canonname);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/
	/*printf("ai_family: %d\n", hints.ai_family);		*/

	printf(" %s, %s\n", user_params.address,user_params.port)	;
	return 0;
}
