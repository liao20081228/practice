#include"common.h"
#include<stdio.h>
void fun(int argc, char**argv)
{
	printf("argv is :");
	for(int i=0;i<argc;++i)
		printf("%s,  ", argv[i]);
		printf("\n");
		printf("--------------------------------------------------------------------------------------------\n");

}
int main(int argc, char** argv)
{ 
	
        const char* opstring="m:";
        char ret=0;
        printf("0\toptind is %d,\toptarg is %s,\topterr is %d,\tptopt is %c, %d,\treturn value is %c, %d,\t",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
	
	ret=getopt(argc,argv,opstring);
        printf("0\toptind is %d,\toptarg is %s,\topterr is %d,\tptopt is %c, %d,\treturn value is %c, %d,\t",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);                                                                                                                                                    
        printf("0\toptind is %d,\toptarg is %s,\topterr is %d,\tptopt is %c, %d,\treturn value is %c, %d,\t",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);
        printf("0\toptind is %d,\toptarg is %s,\topterr is %d,\tptopt is %c, %d,\treturn value is %c, %d,\t",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);
        printf("0\toptind is %d,\toptarg is %s,\topterr is %d,\tptopt is %c, %d,\treturn value is %c, %d,\t",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
}        
   
