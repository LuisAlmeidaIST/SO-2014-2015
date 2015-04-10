#include "leitor.h"

void leitor(){
    char* filename = ficheiros[get_random(NB_FILES)];
    int fd = open(filename,O_RDONLY);
    
    
    if (flock(fd,LOCK_SH) == -1){
        perror ("Error Locking the file");
        exit(EXIT_FAILURE);
    }
    
    
    printf("Monitor will check if file %s is consistent...\n", filename);
    
    if (fd == -1) {
        perror ("Error opening file");
        exit (-1);
    }
    
    else {
        char string_to_read[STRING_SZ];
        char first_string[STRING_SZ];
        int  i;
        
        if (read (fd, first_string, STRING_SZ) == -1) {
            perror ("Error reading file");
            exit (-1);
        }
        for (i=0; i<NB_ENTRIES-1; i++) {
            
            if (read (fd, string_to_read, STRING_SZ) == -1) {
                perror ("Error reading file");
                exit (-1);
            }
            
            if (strncmp(string_to_read, first_string, STRING_SZ)) {
                fprintf (stderr, "Inconsistent file: %s\n", filename);
                exit (-1);
            }
        }
        
        if (flock(fd,LOCK_UN) == -1){
            perror ("Error Unlocking the file");
            exit (EXIT_FAILURE);
        }
        
        if (close (fd) == -1)  {
            perror ("Error closing file");
            exit (-1);
        }
    }
    printf("File %s is consistent\n",filename);
}

int main(int argc, char *argv[]){
    srandom ((unsigned) time(NULL));
    
    leitor();
    
    return 0;
}