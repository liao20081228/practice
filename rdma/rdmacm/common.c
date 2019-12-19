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
	int ret=-1;	
	while((ret= getopt_long(argc,argv,"HVscp:a:",longopt, &opt_index)) != -1)
	{

		printf("--------------------\noptind is: %d,  optopt is:%d,    ", optind , optopt);

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
				break;
			case 'p':
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
  

int main(int argc, char *argv[])
{
	struct option longopts[]=
	{
		{"help",    no_argument,       NULL, 'H'},
		{"version", no_argument,       NULL, 'V'},
		{"client",  no_argument,       NULL, 'c'},
		{"server",  no_argument,       NULL, 's'},
		{"port",    required_argument, NULL, 'p'},
		{"address", optional_argument, NULL, 'a'},
		{0,         0,                 0,     0}
	};
	handle_cmd(argc, argv, longopts);
	return 0;
}
