#include "leitor3.h"

pthread_t fio[NB_THREADS];
int linhas;
int* leitor(int* ficheiro){
    int start,end;
    int i;
    int filenumber=*ficheiro;
    char* filename = ficheiros[filenumber];
    int fd = open(filename,O_RDONLY);
    int print;
    char first_string[STRING_SZ];
    
    if (read (fd, first_string, STRING_SZ) == -1) {
        perror ("Error reading file");
        return (int*)-EXIT_FAILURE;
    }
    
    if(lseek(fd,(size_t)0,SEEK_SET)==-1)
    {
        perror("Error Setting the SEEK");
        return (int*)-EXIT_FAILURE;
    }
    
    if(fio[0]==pthread_self()){
        start=0;
        end=linhas;
        print=end/10;
    }
    
    if(fio[NB_THREADS-1]==pthread_self()){
        start=linhas*(NB_THREADS-1);
        end = linhas +((NB_ENTRIES*STRING_SZ) - (linhas*NB_THREADS));
        print=((linhas*NB_THREADS)+((NB_ENTRIES*STRING_SZ) - (linhas*NB_THREADS)))/10;
    }
    
    for(i=1;i<NB_THREADS-1;i++)
    {
        if(fio[i]==pthread_self())
        {
            start=linhas*i;
            end=linhas;
            print=(linhas*(i+1))/10;
            break;
        }
        
    }
    
    if(lseek(fd,(size_t)start,SEEK_SET)==-1)
    {
        perror("Error Setting the SEEK");
        return (int*)-EXIT_FAILURE;
    }
    
    if(flock(fd,LOCK_SH) == -1){
        perror ("Error Locking the file");
        return (int*)-EXIT_FAILURE;
    }
    
    printf("Monitor will check if file %s is consistent from %d to %d...\n", filename,(start/10)+1,print);
    
    if (fd == -1) {
        perror ("Error opening file");
        return (int*)-EXIT_FAILURE;
    }
    
    else {
        char string_to_read[STRING_SZ];
        
        for (i=1; i<=end/10; i++) {
            
            if (read (fd, string_to_read, STRING_SZ) == -1) {
                perror ("Error reading file");
                return (int*)-EXIT_FAILURE;
            }
            
            if (strncmp(string_to_read, first_string, STRING_SZ)) {
                fprintf (stderr, "Inconsistent file: %s between %d and %d in %d\n", filename,(start/10)+1,print,i+start/10);
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
    printf("File %s is consistent from %d to %d\n",filename,(start/10)+1,print);
    return(EXIT_SUCCESS);
}


void* wraper(void* p){
    pthread_exit((void*)leitor((int*)p));
}

int main(int argc, char *argv[]){
    srandom ((unsigned) time(NULL));
    int i;
    int fileran=get_random(NB_FILES);
    linhas=(NB_ENTRIES/NB_THREADS)*STRING_SZ;
    
    for(i=0;i<NB_THREADS;i++){
        if(pthread_create(&fio[i],NULL,wraper,(void*)&fileran)!=0)
        perror("Error creating thread");
    }
    
    int ptr[NB_THREADS];
    for(i=0;i<NB_THREADS;i++){
        if(pthread_join(fio[i],(void*)&ptr[i])!=0)
        perror("Error joining thread");
        printf("Thread %d Finished With: %d\n",i,ptr[i]);
    }
    
    for(i=0;i<NB_THREADS;i++)
    {
        if(ptr[i]==-1)
        printf("The File %s is Inconsistent\n",ficheiros[fileran]);
        else
            printf("The File %s is Consistent\n",ficheiros[fileran]);
        break;
    }
    
    return EXIT_SUCCESS;
}