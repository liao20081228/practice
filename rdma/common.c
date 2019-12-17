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
	
        const char* opstring="-m:n::o";
        char ret=0;
        printf("0                        optind is %d,             optarg is %s,      opterr is %d,           optopt is %c, %d,       return value is %c, %d\n",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
	
	ret=getopt(argc,argv,opstring);
        printf("1                        optind is %d,             optarg is %s,      opterr is %d,           optopt is %c, %d,       return value is %c, %d\n",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);                                                                                                                                                    
        printf("2                        optind is %d,             optarg is %s,      opterr is %d,           optopt is %c, %d,       return value is %c, %d\n",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);
        printf("3                        optind is %d,             optarg is %s,      opterr is %d,           optopt is %c, %d,       return value is %c, %d\n",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
        
	ret=getopt(argc,argv,opstring);
        printf("4                        optind is %d,             optarg is %s,      opterr is %d,           optopt is %c, %d,       return value is %c, %d\n",optind,optarg,opterr,optopt,optopt,ret,ret);
        fun(argc,argv);
}        
   
