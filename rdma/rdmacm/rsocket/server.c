#include<rdma/rsocket.h>
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<endian.h>
#include<sys/socket.h>
#include<time.h>
#include<getopt.h>
#include<strings.h>
struct rdma_addrinfo hint, res;
static char *src_addr;
static char *dst_addr;	
static const char *port = "10000"; 
static struct timespec start = {0, 0} , end = {0, 0};
static int iteration = 1000;
static int transfer_size = 1000;
static int transfer_count = 1000;
static int buffer_size = 0;
static int inline_size = 64; 
static int keepalive = 0;
static int flags = MSG_DONTWAIT;
static int poll_timeout = 0;
static void *buf = NULL;
enum rs_optimization {LANT, BW, MIX};
static enum rs_optimization optimization;






int main(int argc, char *argv[])
{
	int op, ret;
	hint.ai_port_space = RDMA_PS_TCP;
	while((op = getopt(argc, argv, "b:f:B:i:I:C:S:p:K:p:k:T:")) != -1 )
	{
		switch (op)
		{
			case 'b':
				src_addr = optarg;
			case 'f':
				if(strncasecmp)
		}
	}
}
