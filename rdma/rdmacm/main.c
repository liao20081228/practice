#include"common.h"
  

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
