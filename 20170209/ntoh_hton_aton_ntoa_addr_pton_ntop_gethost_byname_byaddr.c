/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年04月08日 星期六 08时50分11秒
 ************************************************************************/
#include<myhead.h>/*myhead.h is a headfile defined in /usr/include*/
int  main(int argc,char*argv[])
{
	if(argc!=3)
	{
		printf("argc is wrong\n");
		return 0;
	}
	int x=0x12345678;
	short y=0x1234;
	printf("x=%x\n",x );
	printf("htonl(x)=%x\n",htonl(x));
	printf("ntohl(htonl(x))=%x\n",ntohl(htonl(x)) );
	printf("y=%x\n",y );
	printf("htons(y)=%x\n",htons(y));
	printf("ntohs(htons(y))=%x\n",ntohs(htons(y)) );
	struct in_addr addr4;
	if(inet_aton(argv[1],&addr4)==0)
	{
		printf("inet_aton is failed\n");
		return -1;
	}
	printf("%s after inet_aton =%x\n",argv[1],addr4.s_addr);
	bzero(&addr4,sizeof(struct in_addr));
	addr4.s_addr=inet_addr(argv[1]);
	printf("%s after inet_addr =%x\n",argv[1],addr4.s_addr);
	bzero(&addr4,sizeof(struct in_addr));
	if(inet_pton(AF_INET,argv[1],&addr4)==-1)
	{
		printf("inet_pton failed\n");
		return -1;
	}
	printf("%s after inet_pton =%x\n",argv[1],addr4.s_addr);
	char ipstr[40]={'\0'};
	printf("%x after inet_ntoa=%s\n",addr4.s_addr,inet_ntoa(addr4) );
	printf("%x after inet_ntop=%s\n", addr4.s_addr,inet_ntop(AF_INET,&addr4,ipstr,16));
	struct in6_addr addr6;
	if(inet_pton(AF_INET6,"1210:1210:1210:1210:1210:1210:1210:1210",&addr6)==-1)
	{
		printf("inet_pton failed \n");
		return -1;
	}
	printf("%s after inet_pton =%s\n","1210:1210:1210:1210:1210:1210:1210:1210", addr6.s6_addr);
	printf("%s after inet_ntop =%s\n",addr6.s6_addr ,inet_ntop(AF_INET6,&addr6,ipstr,40));
	struct hostent *info=NULL;
	if((info=gethostbyaddr(&addr4.s_addr,4,AF_INET))==NULL)
	{
		/*printf("gethostbyaddr failed\n");*/
		/*return 0;*/
	}
	printf("host formal name is %s\n",info ->h_name);
	for(char**p=info->h_aliases;*p!=NULL;p++)
	{
		printf("host alias is %s\n",*p );
	}
	printf("ip type is %d,ip length is %d \n",info->h_addrtype,info->h_length );
	switch(info->h_addrtype)
	{
		case AF_INET:
					for(char**p=info->h_addr_list;*p!=NULL;p++)
					{
						printf("host ip after inet_ntop is %s\n",inet_ntop(AF_INET,*p,ipstr,16));
						printf("host ip after inet_ntoa is %s\n",inet_ntoa(*(struct in_addr*)*p));
					}
		case AF_INET6:
					for(char**p=info->h_addr_list;*p!=NULL;p++)
					{
						printf("host ip after inet_ntop is %s\n",inet_ntop(AF_INET,*p,ipstr,40));
					}
	}
	if((info=gethostbyname(argv[2]))==NULL)
	{
		printf("gethostbyname failed\n");
		return 0;
	}
	printf("host formal name is %s\n",info ->h_name);
	for(char**p=info->h_aliases;*p!=NULL;p++)
	{
		printf("host alias is %s\n",*p );
	}
	printf("ip type is %d,ip length is %d \n",info->h_addrtype,info->h_length );
	switch(info->h_addrtype)
	{
		case AF_INET:
					for(char**p=info->h_addr_list;*p!=NULL;p++)
					{
						printf("host ip after inet_ntop is %s\n",inet_ntop(AF_INET,*p,ipstr,16));
						printf("host ip after inet_ntoa is %s\n",inet_ntoa(*(struct in_addr*)*p));
					}
		case AF_INET6:
					for(char**p=info->h_addr_list;*p!=NULL;p++)
					{
						printf("host ip after inet_ntop is %s\n",inet_ntop(AF_INET,*p,ipstr,40));
					}
	}
	return 0;
}
