#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "macros.h"


int main(int argc, char *argv[]){
	int ficheironum;
	int letrasnum;
	char *filename;
	char *caracteres;
	int i,j,openres;
	printf("Working...\n");
	for(i=0;i<5120;i++){
		ficheironum=randint(5);
		letrasnum=randint(10);
		filename=ficheiros[ficheironum];
		caracteres=letras[letrasnum];
		openres = open(filename, O_CREAT|O_EXCL|O_WRONLY,S_IRUSR|S_IWUSR|S_IROTH|S_IRGRP);
		if(openres<0){
			openres=open(filename,O_WRONLY);
		}
		for(j=0;j<1024;j++)
		{
			if(write(openres,caracteres,10)!=10){
				return;
			}
		}
		close(openres);
	}
	printf("Finished!\n");
	return 0;
}