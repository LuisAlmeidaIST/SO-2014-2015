#include "escritor.h"


void escritor(){
    int i;
    int j;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    for(i=0; i<NB_ITERATIONS; i++){
        char* filename = ficheiros[get_random(NB_FILES)];
        char* caracteres = letras[get_random(NB_STRINGS)];
        int fd = open(filename,O_RDWR | O_CREAT,mode);
        
        if (flock(fd,LOCK_EX) == -1){
            perror ("Error Locking the file");
            exit(EXIT_FAILURE);
        }
        
        
        if (fd == -1) {
            perror ("Error opening file");
            exit (EXIT_FAILURE);
        }
        
        else{
            
            for (j=0; j<NB_ENTRIES; j++) {
                if (write (fd, caracteres, STRING_SZ) == -1) {
                    perror ("Error writing file");
                    exit (EXIT_FAILURE);
                }
            }
        }
        
        if (flock(fd,LOCK_UN) == -1){
            perror ("Error Unlocking the file");
            exit (EXIT_FAILURE);
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