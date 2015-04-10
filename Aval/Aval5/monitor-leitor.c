#include "include/macros.h"

char* buffer[BUFFER_SIZE][NAME_SIZE];
int bufferpropos=0;
int bufferconspos=0;
pthread_mutex_t esctrin;
pthread_mutex_t lertrin;
sem_t escsem;
sem_t lesem;
bool pipeclosed=true;

//----------------------------------------------------
// reader()
//----------------------------------------------------
long int reader() {
    char* file_to_open=malloc(sizeof(char)*NAME_SIZE);
    while(pipeclosed) {
        bool cons=true;

        sem_wait(&lesem);
        if(pipeclosed==false)
            break;

        pthread_mutex_lock(&lertrin);
        file_to_open=(char*)buffer[bufferconspos];
        bufferconspos=(bufferconspos+1) % BUFFER_SIZE;
        pthread_mutex_unlock(&lertrin);
        sem_post(&escsem);

        int fd;
        fd  = open (file_to_open, O_RDONLY);

        if (fd == -1) {
            perror ("Error opening file");
            //return -1;
        } else {
            char string_to_read[STRING_SZ];

            char first_string[STRING_SZ];
            int  i;

            if (flock(fd, LOCK_SH | LOCK_NB) < 0) {
                if (errno == EWOULDBLOCK)
                    perror ("Wait unlock");
                else {
                    perror ("Error locking file");
                    //   return -1;
                }
            }

            if (flock(fd, LOCK_SH) < 0) {
                perror ("Error locking file");
                //return -1;
            }

            if (read (fd, first_string, STRING_SZ) != 10) {
                perror ("Error reading file");
                // return -1;
            }

            for (i=0; i<NB_ENTRIES-1; i++) {
                if (read (fd, string_to_read, STRING_SZ) != 10) {
                    fprintf (stderr,"Error reading file: %s\n", file_to_open);
                    break;
                }

                if (strncmp(string_to_read, first_string, STRING_SZ)) {
                    //fprintf (stderr, "Inconsistent file: %s\n", file_to_open);
                    cons=false;
                    break;
                }
            }

            if (read (fd, string_to_read, STRING_SZ) != 0) {
                //fprintf (stderr, "Inconsistent file (extra lines): %s\n", file_to_open);
                cons=false;
            }
            if(cons)
                printf("File %s is Consistent\n",file_to_open);
            else
                fprintf (stderr, "Inconsistent file: %s\n", file_to_open);

            if (flock(fd, LOCK_UN) < 0) {
                perror ("Error unlocking file");
                //return (-1);
            }

            if (close (fd) == -1)  {
                perror ("Error closing file");
                //return (-1);
            }
        }
    }
    return 0;
}

//----------------------------------------------------
// reader_wrapper()
//----------------------------------------------------
void* reader_wrapper(void* ptr) {

    return (void*) reader();
}

//----------------------------------------------------
// readInput()
//----------------------------------------------------
char* readInput() {
    char* input[INPUT_MAX];
    int temp;
    int i;

    temp=read(STDIN_FILENO,input,INPUT_MAX);

    if(temp==0) {
        pipeclosed=false;
        printf("Pipe Closed monitor-leitor Stopping \n");
        for(i=0; i<NUM_CHILDREN_READER; i++)
            sem_post(&lesem);
        //exit(EXIT_SUCCESS);
    }

    if(temp<INPUT_MAX) {
        input[temp]='\0';
    } else {
        input[INPUT_MAX]='\0';
    }

    return input;
}

//----------------------------------------------------
// inputParser()
//----------------------------------------------------
void inputParser(char* input) {
    char* temp= strtok(input," ");
    while(temp!=NULL) {
        strncpy((char*)buffer[bufferpropos],temp,NAME_SIZE);
        sem_post(&lesem);
        bufferpropos=(bufferpropos+1)%BUFFER_SIZE;
        temp=strtok(NULL," ");
    }
}

//----------------------------------------------------
// receberInput()
//----------------------------------------------------
void* receberInput() {
    char* filename=malloc(sizeof(char)*2048);
    while(pipeclosed) {
        sem_wait(&escsem);
        filename=readInput();
        inputParser(filename);
    }
    exit(EXIT_SUCCESS);
}


//----------------------------------------------------
// main()
//----------------------------------------------------
int main (int argc, char** argv) {
    srandom ((unsigned) time(NULL));
    pthread_t tid[NUM_CHILDREN_READER];
    pthread_t input;
    int runningChildren;
    long int retVals[NUM_CHILDREN_READER];

    if(sem_init(&escsem,0,BUFFER_SIZE)!=0) {
        perror("Failed Initializing of escsem");
        exit(-EXIT_FAILURE);
    }

    if(sem_init(&lesem,0,0)!=0) {
        perror("Failed Initializing of lesem");
        exit(-EXIT_FAILURE);
    }

    if(pthread_mutex_init(&lertrin,NULL)!=0) {
        perror("Failed Initializing of lebuffer");
        exit(-EXIT_FAILURE);
    }

    if(pthread_mutex_init(&esctrin,NULL)!=0) {
        perror("Failed Initializing of escbuffer");
        exit(-EXIT_FAILURE);
    }

    if(pthread_create(&input,NULL,receberInput,(void*)1)!=0) {
        perror("Erro creating thread Input");
        return -EXIT_FAILURE;
    }

    for (runningChildren = 0; runningChildren < NUM_CHILDREN_READER; runningChildren++) {
        if (pthread_create(&tid[runningChildren], NULL, reader_wrapper,(void*)1 ) != 0) {
            printf("Error creating thread %d", runningChildren);
            return -1;
        }
    }

    for (runningChildren = 0; runningChildren < NUM_CHILDREN_READER; runningChildren++) {
        pthread_join(tid[runningChildren], (void**)&retVals[runningChildren]);
        printf("Leitor Thread Finished\n");
    }

    long int retVal;
    pthread_join(input, (void**)&retVal);
    write(STDOUT_FILENO,"Input Thread Finished\n",22);

    return 0;
}
