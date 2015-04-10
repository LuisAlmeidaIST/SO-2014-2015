#include "escritor.h"

#define NB_ITERATIONS  512


void escritor(){
	int i;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	for(i=0;i<NB_ITERATIONS;i++){
		char* filename = ficheiros[get_random(NB_FILES)];
		char* caracteres = letras[get_random(NB_STRINGS)];
		int fd = open(filename,O_RDWR | O_CREAT,mode);

		if (fd == -1) {
      		perror ("Error opening file");
      		exit (EXIT_FAILURE);
   		}

   		else{
   			int j;
   			for (j=0; j<NB_ENTRIES; j++) {
			if (write (fd, caracteres, STRING_SZ) == -1) {
				perror ("Error writing file");
				exit (EXIT_FAILURE);
				}
			}
   		}

   		if (close (fd) == -1)  {
   			perror ("Error closing file");
   			exit (EXIT_FAILURE);
   		}
   	}
   }

int main(int argc, char *argv[]){
	srandom ((unsigned) time(NULL));

	printf("Working...\n");

	escritor();

	printf("Finished!\n");
	return EXIT_SUCCESS;
}