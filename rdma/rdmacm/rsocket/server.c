#include<rdma/rsocket.h>
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<endian.h>
#include<sys/socket.h>
#include<time.h>
#include<getopt.h>
#include<strings.h>

struct rdma_addrinfo rs_hint;//rdma address info 
struct addrinfo s_hint; // socket address info
static char *src_addr; // souurce address
static char *dst_addr; // destnation address  
static const char *port = "10000";  // port number 
static struct timespec start = {0, 0} , end = {0, 0}; // time of start and end;
static int iteration = 1000; // num of repeat test
static int transfer_size = 1000; // 
static int transfer_count = 1000;// num of each test
static int buffer_size = 0;
static int inline_size = 64; 
static int keepalive = 0;
static int flags = MSG_DONTWAIT;
static int poll_timeout = 0;
static void *buf = NULL;
enum rs_optimization {LANT, BW, MIX};
static enum rs_optimization optimization;
static int rd, lrs;
static int use_async;
static int verify;
static int use_fork;
static pid_t fork_pid;
static int size_option;


int main(int argc, char *argv[])
{
	int op, ret;
	while((op = getopt(argc, argv, "s:b:f:B:i:I:C:S:p:K:p:k:T:")) != -1 )
	{
		switch (op)
		{
			case 'b':
				src_addr = optarg;
			case 'f':
				if(!strncasecmp("ip", optarg, 2))
				else 
					if (!strncasecmp("gid", optarg ,3))
					{
						rs_hint.__attribute_malloc__
					}

		}
	}
}
