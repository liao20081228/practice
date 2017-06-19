#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>
int  main()
{
	pid_t pid=fork();
	if(pid>0)
	{
		exit(0);
	}
	setsid();
	umask(0);
	chdir("/");
	int fd=0;
	while(fd<10)
		close(fd);
	while(1);
	return 1;
}

