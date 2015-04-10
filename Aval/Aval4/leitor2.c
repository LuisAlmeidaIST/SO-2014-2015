#include "leitor2.h"


int* leitor(int* ficheiro){
    int file = *ficheiro;
    char* filename = ficheiros[file];
    int fd = open(filename,O_RDONLY);
    
    
    if(flock(fd,LOCK_SH) == -1){
        perror ("Error Locking the file");
        return (int*)-EXIT_FAILURE;
    }
    
    
    printf("Monitor will check if file %s is consistent...\n", filename);
    
    if (fd == -1) {
        perror ("Error opening file");
        return (int*)-EXIT_FAILURE;
    }
    
    else {
        char string_to_read[STRING_SZ];
        char first_string[STRING_SZ];
        int  i;
        
        if (read (fd, first_string, STRING_SZ) == -1) {
            perror ("Error reading file");
            return (int*)-EXIT_FAILURE;
        }
        for (i=0; i<NB_ENTRIES-1; i++) {
            
            if (read (fd, string_to_read, STRING_SZ) == -1) {
                perror ("Error reading file");
                return (int*)-EXIT_FAILURE;
            }
            
            if (strncmp(string_to_read, first_string, STRING_SZ)) {
                fprintf (stderr, "Inconsistent file: %s\n", filename);
                return (int*)-EXIT_FAILURE;
            }
        }
        
        if (flock(fd,LOCK_UN) == -1){
            perror ("Error Unlocking the file");
            return (int*)-EXIT_FAILURE;
        }
        
        if (close (fd) == -1)  {
            perror ("Error closing file");
            return (int*)-EXIT_FAILURE;
        }
    }
    printf("File %s is consistent\n",filename);
    return(EXIT_SUCCESS);
}

void* wraper(void* p){
    pthread_exit((void*)leitor((int*)p));
}

int main(int argc, char *argv[]){
    srandom ((unsigned) time(NULL));
    int i;
    int file_id[NB_THREADS];
    
    pthread_t fio[NB_THREADS];
    
    for(i=0;i<NB_THREADS;i++){
        file_id[i] = get_random(NB_FILES);
    }
    
    while(file_id[0]==file_id[1]||file_id[0]==file_id[2]||file_id[1]==file_id[2])
    {
        file_id[0] = get_random(NB_FILES);
        file_id[1] = get_random(NB_FILES);
        file_id[2] = get_random(NB_FILES);
        
    }
    
    for(i=0;i<NB_THREADS;i++){
        
        if(pthread_create(&fio[i], NULL,wraper,(void*) &file_id[i]) == -1)
        {
            perror("Error creating Thread");
            return -EXIT_FAILURE;
        }
    }
    
    for(i=0;i<NB_THREADS;i++){
        int ptr[NB_THREADS];
        if(pthread_join(fio[i],(void*)&ptr[i])==-1)
        {
            perror("Error Joining thread");
            return -EXIT_FAILURE;
        }
        printf("Thread %d Finished With: %d\n",i+1,ptr[i]);
    }
    return EXIT_SUCCESS;
}