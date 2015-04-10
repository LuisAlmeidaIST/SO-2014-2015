#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "macros.h"

int main(int argc, char *argv[]){
	char buff[10240];
	char *filename=ficheiros[randint(10)];
	int fd,i,j;
	char ini[10],temp[10];
	fd=open(filename,O_RDONLY);
	read(fd,buff,buffer);
	for(i=0;i<=9;i++)
		ini[i]=buff[i];
	for(i=0;i<1024;i++){
		for(j=0;j<=9;j++)
		{
			temp[j]=buff[i*10+j];
		}
		if(strcmp(ini,temp)<0){
				printf("Failed Line %d\n",i+1);
				return -1;
			}		
		if(strcmp(ini,temp)>0){
			printf("Failed Line %d\n",i+1);
			return -1;
			}				
		}
	close(fd);
	printf("SUCCESS! \n");
	return 0;
}