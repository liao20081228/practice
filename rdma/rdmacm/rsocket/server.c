#include<rdma/rsocket.h>
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<endian.h>
#include<sys/socket.h>


struct rdma_addrinfo hint, res;
static char *src_addr;
static char *dst_addr;	
static const char * port = "10000"; 
static struct timeval start, end;

int main(int argc, char *argv[])
{
	return 0;
}
