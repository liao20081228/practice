#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
int main() 
{
	char szBuf[32] ={'\0'}; 
	int iFile =open("./a.txt",O_RDONLY); 
	if(fork()>0)
	{
		//parent process 
		close(iFile); 
		return 0;/*orphan process*/
	} //child process 
	else
	{
		sleep(4); //wait forparent process closing fd 
		if(read(iFile, szBuf, sizeof(szBuf)-1)<1)
		{
			perror("read fail"); 
		}
		else
		{
			printf("string:%s\n",szBuf); 
		} 
		close(iFile); 
		return 0;
	}
}
