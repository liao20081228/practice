#include"common.h"
int port=5000;
const char* address="127.0.0.1";
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
	int ret=-1;	
	while((ret= getopt_long(argc,argv,"HVscp:a:",longopt, NULL)) != -1)
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
				address = optarg;
				break;
			case 'p':
				port = atof(optarg);
				break;
			case '?':
				break;
			case ':':
				break;
			default:
				show_help_info();
				exit(0);
		}
	}		
}
  
