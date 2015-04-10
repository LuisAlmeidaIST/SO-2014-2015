#include "escritor-filhos.h"


int main(int argc, char *argv[]){
    struct timeval tvstart; /* data de inicio */
    struct timeval tvend; /* data de fim */
    struct timeval tvduration; /* diferenca entre as duas datas */
    float duration; /* diferenca entre as datas em microssegundos */
    time_t curtime; /* tempo em formato time_t para conversao de formatos */
    char buffer[30]; /* para escrever a data em formato legivel */
    
    if (gettimeofday(&tvstart, NULL) == -1) {
        perror("Could not get time of day, exiting.");
        exit(-1);
    } /* ler a data actual */
    
    curtime=tvstart.tv_sec;
    strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
    
    int runningChildren;
    pid_t pid[NB_CHILDS];
    char *childExecPath;
    
    if (argc >=2)
        childExecPath = argv[1];
    else
        childExecPath = FILE_PATH;
    
    for(runningChildren=0; runningChildren<NB_CHILDS; runningChildren++){
        pid[runningChildren] = fork();
        if (pid[runningChildren] < 0) {
            perror("Fork Failed");
            exit(EXIT_FAILURE);
        }
        else if (pid[runningChildren] == 0) {
            if (execl(childExecPath, FILE_NAME, NULL) == -1) {
                perror("Could not execute child program");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    int status;
    
    for(runningChildren=0; runningChildren<NB_CHILDS; runningChildren++){
        waitpid(-1,&status,0);
    }
    
    gettimeofday(&tvend, NULL); /* ler a data actual */
    curtime=tvend.tv_sec;
    strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    
    printf("Execution time is: %f seconds\n", duration/1000000);
    
    return EXIT_SUCCESS;
}