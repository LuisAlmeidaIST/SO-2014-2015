#include "include/macros.h"

bool siguser1=false;
bool siguser2=true;
bool sigstp=true;

//----------------------------------------------------
// escritor()
//----------------------------------------------------
void* escritor() {
    int i;
    int j;
    int temp;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while(sigstp) {
        for(i=0; i<NB_ITERATIONS; i++) {
            char* filename = ficheiros[get_random(NB_FILES)];
            temp=get_random(NB_STRINGS);
            char* caracteres = letras[temp];
            char* caractereserrados=mystrings[temp];
            int fd = open(filename,O_RDWR | O_CREAT,mode);

            if(siguser1) {
                if (flock(fd,LOCK_EX) == -1) {
                    perror ("Error Locking the file");
                    exit(EXIT_FAILURE);
                }
            }

            if (fd == -1) {
                perror ("Error opening file");
                exit (EXIT_FAILURE);
            }

            for (j=0; j<NB_ENTRIES; j++) {

                if(siguser2) {
                    if (write (fd, caracteres, STRING_SZ) == -1) {
                        perror ("Error writing file");
                        exit (EXIT_FAILURE);
                    }

                } else {
                    if((j%2)==0) {
                        if (write (fd, caracteres, STRING_SZ) == -1) {
                            perror ("Error writing file");
                            exit (EXIT_FAILURE);
                        }
                    } else {
                        if (write (fd, caractereserrados, STRING_SZ) == -1) {
                            perror ("Error writing file");
                            exit (EXIT_FAILURE);
                        }
                    }
                }
            }

            if(siguser1) {
                if (flock(fd,LOCK_UN) == -1) {
                    perror ("Error Unlocking the file");
                    exit (EXIT_FAILURE);
                }
            }

            if (close (fd) == -1)  {
                perror ("Error closing file");
                exit (EXIT_FAILURE);
            }
        }
    }

    return 0;
}

//----------------------------------------------------
// writer_wrapper()
//----------------------------------------------------
void* writer_wrapper(void* ptr) {

    return (void*) escritor();
}

//----------------------------------------------------
// Signal Handlers
//----------------------------------------------------
void usr1_handler(int p) {
    if(siguser1) {
        siguser1=false;
        printf("SIGUSR1 Recieved: Locks Stopped\n");
    } else {
        siguser1=true;
        printf("SIGUSR1 Recieved: Locks Started\n");
    }

}

void usr2_handler(int p) {
    if(siguser2) {
        siguser2=false;
        printf("SIGUSR2 Recieved: Errors Started\n");
    } else {
        siguser2=true;
        printf("SIGUSR2 Recieved: Errors Stopped\n");
    }
}

void stp_handler(int p) {
    if(sigstp)
        sigstp=false;
    else
        sigstp=true;
    printf("SIGTSTP Recieved: %s Stopping\n",FILE_NAME_ES);
}

//----------------------------------------------------
// main()
//----------------------------------------------------
int main(int argc, char *argv[]) {
    srandom ((unsigned) time(NULL));

    pthread_t tid[NUM_CHILDREN_WRITER];
    int runningChildren;
    long int retVals[NUM_CHILDREN_WRITER];

    struct sigaction new_action1;

    new_action1.sa_handler = usr1_handler;
    sigemptyset (&new_action1.sa_mask);
    sigaddset(&new_action1.sa_mask, SIGUSR1);
    new_action1.sa_flags = 0;
    sigaction(SIGUSR1, &new_action1, NULL);

    struct sigaction new_action2;

    new_action2.sa_handler = usr2_handler;
    sigemptyset (&new_action2.sa_mask);
    sigaddset(&new_action2.sa_mask, SIGUSR2);
    new_action2.sa_flags = 0;
    sigaction(SIGUSR2, &new_action2, NULL);

    struct sigaction new_action3;

    new_action3.sa_handler = stp_handler;
    sigemptyset (&new_action3.sa_mask);
    sigaddset(&new_action3.sa_mask, SIGTSTP);
    new_action3.sa_flags = 0;
    sigaction(SIGTSTP, &new_action3, NULL);

    for (runningChildren = 0; runningChildren < NUM_CHILDREN_WRITER; runningChildren++) {
        if (pthread_create(&tid[runningChildren], NULL, writer_wrapper,(void*)1 ) != 0) {
            printf("Error creating thread %d", runningChildren);
            return -1;
        }

    }

    for (runningChildren = 0; runningChildren < NUM_CHILDREN_WRITER; runningChildren++) {
        pthread_join(tid[runningChildren], (void**)&retVals[runningChildren]);
    }

    return EXIT_SUCCESS;
}
