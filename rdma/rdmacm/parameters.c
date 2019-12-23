#include"parameters.h"
int opterr=0;
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


void handle_cmd(struct user_parameters* user_params,int argc, char* argv[])
{
	struct option longopts[]=
	{
		{"help",    no_argument,       NULL, 'H'},
		{"version", no_argument,       NULL, 'V'},
		{"client",  no_argument,       NULL, 'c'},
		{"server",  no_argument,       NULL, 's'},
		{"port",    required_argument, NULL, 'p'},
		{"address", required_argument, NULL, 'a'},
		{"flag", required_argument, NULL, 'f'},
		{"portspace", required_argument, NULL, 'z'},
		{0,         0,                 0,     0}
	};

	int ret=-1;
	int longindex=-1;	
	while((ret= getopt_long(argc,argv,":HVscp:a:",longopts, &longindex)) != -1)
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
			case 'f':
				user_params->flag=atoi(optarg);
				break;
			case 'z':
				user_params->portspace=atoi(optarg);
				break;
			case '?':	
				printf("error:-%c is invalidate option \n", optopt);
				exit(-1);
			case ':':
				for(int i = 0; longopts[i].name != NULL; i++)            
				{
					if(longopts[i].val == optopt)
					{
						printf("error:-%c, --%s is require argument \n",optopt, longopts[i].name);
						break;
					}

				}
				exit(-2);
			default:
				show_help_info();
				break;
		}
	}
	if(argc!=optind)
	{
		printf("some user cmd arguments are invalidate\n");
		exit(-1);
	}
}
  
