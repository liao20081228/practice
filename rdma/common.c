#include"common.h"
#include<stdio.h>
int main(int argc, char** argv)
{ 
	opterr=0;	
        const char* opstring="m:n::o";
        char ret=0;
        printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d, return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);
        printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d, return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);                                                                                                                                                    
        printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d, return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);
        printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d, return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
        ret=getopt(argc,argv,opstring);
        printf("optind is %d, optarg is %s, %p, opterr is %d, optopt is %c, %d, return value is %c, %d\n",optind,optarg,optarg,opterr,optopt,optopt,ret,ret);
}        
   
