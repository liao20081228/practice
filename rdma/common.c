#include"common.h"

void show_help_info(void)
{
	printf("Usag: app [-H] [-V] -[s|c] [-a ipaddress]\n");
	printf("\t-H,--help          dispaly help info\n");
	printf("\t-V,--version       dispaly version info\n");
	printf("\t-c,--client        run as client\n");
	printf("\t-V,--version       run as server\n");
	printf("\t-a,--address       specify ip address\n");
	printf("\t-p,--port          specify port\n");
}





struct option longopt[]=
{
	{"help", no_argument, NULL, 'H'},
	{"version", no_argument, NULL, 'V'},
	{"server", no_argument, NULL, 's'},
	{"client",no_argument, NULL, 'c'},
	{"port",required_argument, NULL, 'p'},
	{"address",required_argument, NULL, 'a'},
	{0,0,0,0,}
};



void handle_cmd(int argc, char* argv[])
{
	int ret=0;
	int opt_index=0
	while((ret=getopt_long(argc,argv,"HVscp:a:",longopt, &opt_index))!=-1)
	{
		switch(ret)
		{
			case 'H':

		}
	}		
}
   
