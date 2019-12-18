#include"common.h"


struct options longopt[]=
{
	{"help", no_argument, NULL, 'H'},
	{"version", no_argument, NULL, 'V'},
	{"server", no_argument, NULL, 's'},
	{"client",no _argument, NULL, 'c'},
	{"port",required_argument, NULL, 'p'},
	{"address",required_argument, NULL, 'a'},
	{0,0,0,0,}
};

void handle_cmd(int argc, char* argv[])
{
	
}
   
