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







void handle_cmd(int argc, char* argv[], struct option* longopt)
{
	int ret = 0;
	int opt_index = 0;
	while((ret = getopt_long(argc,argv,"HVscp:a:",longopt, &opt_index)) != -1)
	{
		switch(ret)
		{
			case 'H':
				show_help_info();
				break;
			case 'V':
				printf("current version:%d.%d", VERSION_MAJOR, VERSION_MINOR);
				break;
			case 's':
				break;
			case 'c':
				break;
				{
					
				}
				break;	
			case 'a':
				printf("the arg of -%c , --%s is %s\n",ret, longopt[opt_index].name, optarg);
				break;
			case 'p':
				printf("the arg of -%c , --%s is %s\n",ret, longopt[opt_index].name, optarg);
				break;
			case '?':
				printf("the violate option is -%c ", ret);
			default:
				show_help_info();
		}
	}		
}
   
