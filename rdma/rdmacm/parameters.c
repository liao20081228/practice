#include"parameters.h"
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







int handle_cmd(struct user_parameters* user_params,int argc, char* argv[], struct option* longopt )
{
	int ret=-1;	
	while((ret= getopt_long(argc,argv,":HVscp:a:",longopt, NULL)) != -1)
	{
		switch(ret)
		{
			case 'H':
				show_help_info();
				exit(0);
			case 'V':
				printf("version is : %d.%d\n", VERSION_MAJOR, VERSION_MINOR);
				exit(0);
			case 's':
				break;
			case 'c':
				break;
			case 'a':
				user_params->address = optarg;
				break;
			case 'p':
				user_params->port = optarg;
				break;
			case '?':	
				printf("-%c is invalidate option \n");
				break;
			case ':':
				break;
			default:
				show_help_info();
				return 0;
		}
	}
	return 0;
misarg:

unkonw:	
}
  
