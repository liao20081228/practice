#include"common.h"
#include<stdio.h>
void main(int argc, char** argv)
{
	const char* opstring="a:c:s";
	printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d",optind,optarg,optarg,opterr,optopt,optopt);
	getopt(argc,argv,opstring);
}

