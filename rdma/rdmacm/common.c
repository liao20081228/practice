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
	opterr = 0;
	while((ret = getopt_long(argc,argv,"HVscp:a:",longopt, &opt_index)) != -1)
	{

		printf("--------------------\noptind is: %d,  optopt is:%d,    ", optind , optopt);

		switch(ret)
		{
			case 'H':
				printf("opt_index is$%d\n", opt_index);
				show_help_info();
				break;
			case 'V':
				printf("opt_index is$%d\n", opt_index);
				printf("current version:%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
				break;
			case 's':
				printf("opt_index is$%d\n", opt_index);
				break;
			case 'c':
				printf("opt_index is$%d\n", opt_index);
				break;
			case 'a':
				printf("opt_index is$%d\n", opt_index);
				printf("the arg of -%c , --%s is %s\n",ret, longopt[opt_index].name, optarg);
				break;
			case 'p':
				printf("opt_index is$%d\n", opt_index);
				printf("the arg of -%c , --%s is %s\n",ret, longopt[opt_index].name, optarg);
				break;
			case '?':
				printf("opt_index is$%d\n", opt_index);
				printf("erro: -%c is invalid options \n", optopt);
				show_help_info();
				break;
			case ':':
				printf("opt_index is$%d\n", opt_index);
				printf("erro: -%c,--%s is missing arg \n", optopt, longopt[opt_index].name);
				show_help_info();
				break;
			default:
				show_help_info();
				break;
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
		{"address", required_argument, NULL, 'a'},
		{0,         0,                 0,     0}
	};
	handle_cmd(argc, argv, longopts);
	return 0;
}
