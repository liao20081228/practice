#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int read_data(int* data, const char* filename, int dim)
{	
	int count=0;
	FILE* filep=fopen(filename, "r");
	char buf[100];
	fgets(buf, 100, filep);
	fgets(buf, 100, filep);
	while (1)
	{
		memset(buf, '\0', 100);
		fgets(buf, 100, filep);
		if (feof(filep))
		{       
			break;
		}
		if (1 != strlen(buf))
		{
		
			*(data+count*dim)= atoi(strtok(buf, ",() \n "));
			for (int i = 1; i < dim; ++i)
			{
				*(data+(count*dim+i))=atoi(strtok(NULL, ",() \n "));
			}
			count += 1;
		}
	}
	fclose(filep);
	return count-1;
}




int main()
{
	int road[100][7]={0},
	    car[100][5]={0},
	    cross[100][5]={0};
	int road_n=read_data((int*)road,"./Road.txt",7),
	    car_n=read_data((int*)car,"./Car.txt",5),
	    cross_n=read_data((int*)cross,"./Cross.txt",5);
	return 0;
}
