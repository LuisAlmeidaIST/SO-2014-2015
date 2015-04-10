#include "leitor1.h"

void leitor(int file){
    char* filename = ficheiros[file];
    int fd = open(filename,O_RDONLY);
    
    
    if (flock(fd,LOCK_SH) == -1){
        perror ("Error Locking the file");
        exit (-EXIT_FAILURE);
    }
    
    
    printf("Monitor will check if file %s is consistent...\n", filename);
    
    if (fd == -1) {
        perror ("Error opening file");
        exit (-EXIT_FAILURE);
    }
    
    else {
        char string_to_read[STRING_SZ];
        char first_string[STRING_SZ];
        int  i;
        
        if (read (fd, first_string, STRING_SZ) == -1) {
            perror ("Error reading file");
            exit (-EXIT_FAILURE);
        }
        for (i=0; i<NB_ENTRIES-1; i++) {
            
            if (read (fd, string_to_read, STRING_SZ) == -1) {
                perror ("Error reading file");
                exit (-EXIT_FAILURE);
            }
            
            if (strncmp(string_to_read, first_string, STRING_SZ)) {
                fprintf (stderr, "Inconsistent file: %s\n", filename);
                exit (-EXIT_FAILURE);
            }
        }
        
        if (flock(fd,LOCK_UN) == -1){
            perror ("Error Unlocking the file");
            exit (-EXIT_FAILURE);
        }
        
        if (close (fd) == -1)  {
            perror ("Error closing file");
            exit (-EXIT_FAILURE);
        }
    }
    printf("File %s is consistent\n",filename);
}

int main(int argc, char *argv[]){
    srandom ((unsigned) time(NULL));
    int f=atoi(argv[1]);
    leitor(f);
    
    return EXIT_SUCCESS;
}