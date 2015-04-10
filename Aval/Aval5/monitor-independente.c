#include "include/macros.h"


//----------------------------------------------------
// main()
//----------------------------------------------------
int main(int argc, char *argv[]) {

    pid_t childes;
    pid_t childle;
    bool sair=true;
    childes = fork();

    if (childes < 0) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    } else if (childes==0) {
        if (execl(FILE_PATH_ES, FILE_NAME_ES, NULL) == -1) {
            perror("Could not execute child program");
            exit(EXIT_FAILURE);
        }
    }

    int fds[2];
    pipe(fds);
    childle = fork();

    if (childle < 0) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    } else if (childle==0) {
        close(0);
        dup2(fds[0],STDIN_FILENO);
        close(fds[1]);
        if (execl(FILE_PATH_LE, FILE_NAME_LE, NULL) == -1) {
            perror("Could not execute child program");
            exit(EXIT_FAILURE);
        }
    }

    write(STDOUT_FILENO,"-----Monitor-Independente Started-----\n",39);
    while(sair) {
        char* input[INPUT_MAX];
        int temp;
        temp=read(0,input,INPUT_MAX);
        if(temp==0) {
            printf("Failed reading from STDIN\n");
            exit(-EXIT_FAILURE);
        }

        if(temp<INPUT_MAX) {
            input[temp]='\0';
        } else {
            input[INPUT_MAX]='\0';
        }

        if(temp<=12) {
            if(temp==3) {
                if(strncmp((char*)input, INPUTIE, INPUT_SZ_2)==0)
                    kill(childes,SIGUSR2);

                if(strncmp((char*)input, INPUTIL, INPUT_SZ_2)==0)
                    kill(childes,SIGUSR1);
            }

            if(temp==5) {
                if(strncmp((char*)input, INPUTSAIR, INPUT_SZ_4)==0) {
                    kill(childes,SIGTSTP);
                    sair=false;
                    close(fds[1]);
                }
            }
        } else
            write(fds[1],input,temp);
    }

    int status[2];
    waitpid(childes,&status[0],0);
    write(STDOUT_FILENO,"-----Monitor-Escritor Finished-----\n",36);
    waitpid(childle,&status[1],0);
    write(STDOUT_FILENO,"------Monitor-Leitor Finished------\n",36);

    return 0;
}