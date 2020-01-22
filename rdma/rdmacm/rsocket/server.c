#include<rdma/rsocket.h>
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<endian.h>
#include<time.h>
#include<getopt.h>
#include<strings.h>
#include<sys/types.h>
#include<netdb.h>
#include<sys/socket.h>
#include<stdbool.h>

static struct rdma_addrinfo rs_hint; //rdma address info 
static struct addrinfo s_hint; //socket address info
static bool use_rgai = true;//if 1 ,use rdma_getaddrinfo; if 0, use getaddrinfo

static const char *src_addr = NULL; // souurce address
static const char *dst_addr = NULL; // destnation address of client 
static const char *port = "10000";  // port number

static struct timespec start = {0, 0} , end = {0, 0}; // time of start and end;
static int iteration = 1000; // num of repeat test
static int transfer_size = 1000; //num of each transfer 
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
static int use_async = false; // if 1 user async , if 0 use sync
static bool verify = false; //if  
static int use_fork;
static pid_t fork_pid;
static int size_option;
static bool custom = false; // if 0 use default test, if 1 use custom test
static bool use_rs = true;// if 1 use rsocket, if 0 use socket

//处理命令行选项
int parse_cmd(int argc, char* argv[])
{
	bzero(&rs_hint,sizeof rs_hint);
	rs_hint.ai_port_space = RDMA_PS_TCP;
	s_hint.
	int op;
	while((op = getopt(argc, argv, "s:b:f:B:i:I:C:S:p:K:p:k:T:")) != -1 )
	{
		switch (op)
		{
			case 's':
				dst_addr = optarg;
				break;
			case 'b':
				src_addr = optarg;
				break;
			case 'f':
				if(!strncasecmp("ip", optarg, 2))
					s_hint.ai_flags = AI_NUMERICHOST;//node必须使用数字地址
				else if (!strncasecmp("gid", optarg ,3))
					{
						rs_hint.ai_flags = RAI_NUMERICHOST | RAI_FAMILY;//node为数字地址，并使用ai_family字段
						rs_hint.ai_family = AF_IB;
					}
				else
						printf("ip format wrong\n");
				break;
			case 'B':
				buffer_size = atoi(optarg);
				break;
			case 'i':
				inline_size = atoi(optarg);
				break;
			case 'I':
				custom = 1;
				iteration = atoi(optarg);
				break;
			case 'C':
				custom = 1;
				transfer_count = atoi(optarg);
				break;
			case 'S':
				custom = 1;
				transfer_size = atoi(optarg);
				break;
			case 'p':
				port = optarg;
				break;
			case 'k':
				keepalive = atoi(optarg);
			case 'T':
				if (strlen(optarg) == 1)
					switch(optarg[0])
					{
						case 's':
							use_rs=0;
							break;
						case 'a':
							use_async = 1;
							break;
						case 'f':
							use_rs = 0;
							use_fork = 1;
							break;
						case 'n':
							flags |= MSG_DONTWAIT;
							break;
						case 'r':
							use_rgai = 1;
							break;
						case 'v':
							verify = 1;
							break;
						default: 
							break;
					}
			
			default :
				exit(1);

		}
	}
	return 0;
}










int main(int argc, char *argv[])
{
	parse_cmd(argc, argv);
}
