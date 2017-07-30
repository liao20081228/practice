/*************************************************************************
    > File Name: eventfd.c
    > Author: liao20081228
    > Mail: liao20081228@126.com 
    > Created Time: 2017年07月01日 星期六 16时46分56秒
 ************************************************************************/
#include<myhead_c.h>/*myhead.h is a headfile defined in the directory:/usr/include,which include all headfile we need*/
int main(int argc, char *argv[])
{
	int efd = 0;
	uint64_t u = 0;
	ssize_t s = 0;
	if (argc < 2)
	{
		fprintf(stderr, "usage:%s num..", argv[0]);
		printf("%d\n", EXIT_FAILURE);
		
		exit(EXIT_FAILURE);
	}

	efd = eventfd(10, 0);
	if (efd == -1)
	{
		do 
		{
			perror("eventfd() faild or ocurr error");
			exit(EXIT_FAILURE);
		} while(0);
	}

	switch (fork())
	{
		case 0:
			for (int i = 0; i < argc; ++i) 
			{
				printf("child write %s to efds\n", argv[i]);
				u = strtoull(argv[i], NULL, 0);
				s = write(efd, &u, sizeof(uint64_t));
				if (s !=  sizeof(uint64_t))
				{
					do
					{
						perror("write failed");
						exit(EXIT_FAILURE);
					} while(0);
				}
			}
			printf("complete write loop \n");
			printf("%d\n", EXIT_SUCCESS);
			printf("%d\n", EXIT_FAILURE);
			exit(EXIT_SUCCESS);
	
		default:
			/*sleep(2);*/
			printf("parent about to read\n");
			s= read(efd,&u,sizeof(uint64_t));
			if (s!=sizeof(uint64_t))
			{
				perror("read faild");
				exit(EXIT_FAILURE);
			}
			printf("parent read %lu(%lX) from efd",u,u);
			exit(EXIT_SUCCESS);
		case -1:
				perror("fork()failed");
				exit(EXIT_FAILURE);
	}
	return 0;
}
