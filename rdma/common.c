#include"common.h"
#include<stdio.h>
void fun(int argc, char**argv)
{
	printf("argv is :");
	for(int i=0;i<argc;++i)
		printf("%s,", argv[i]);
		printf("\n");

}
int main(int argc, char** argv)
{ 
	
        const char* opstring="m:n::o";
        char ret=0;
        fun(argc,argv);
        printf("optind is %d|optarg is %s, %p,| opterr is %d,| optopt is %c, %d,| return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
	ret=getopt(argc,argv,opstring);
        fun(argc,argv);
        printf("optind is %d|optarg is %s, %p,| opterr is %d,| optopt is %c, %d,| return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);                                                                                                                                                    
        fun(argc,argv);
        printf("optind is %d|optarg is %s, %p,| opterr is %d,| optopt is %c, %d,| return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);
        fun(argc,argv);
        printf("optind is %d|optarg is %s, %p,| opterr is %d,| optopt is %c, %d,| return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);
        fun(argc,argv);
        printf("optind is %d|optarg is %s, %p,| opterr is %d,| optopt is %c, %d,| return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
}        
   
