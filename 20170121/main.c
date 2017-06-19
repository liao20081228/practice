/*************************************************************************
    > File Name: main.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年02月18日 星期六 18时58分01秒
 ************************************************************************/
#include<myhead.h>
int main(int argc,char* argv[])
{
		if(argc!=2)
		{
					printf("error args\n");
							return -1;
								
		}
			struct stat buf;
				DIR *dir;
					dir=opendir(argv[1]);
						if(NULL==dir)
						{
									perror("opendir");
											return -1;
												
						}
							struct dirent *p;
								off_t pos;
									while((p=readdir(dir))!=NULL)
									{
												memset(&buf,0,sizeof(buf));	
														int ret;
																ret=stat(p->d_name,&buf);
																		if(-1==ret)
																		{
																						perror("stat");
																									return -1;
																											
																		}
																				printf("%x %lu %7s %7s %ld %20s %10s\n",buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,ctime(&buf.st_mtime),p->d_name);
																					
									}
										return 0;

}
