#include "escritor-filhos.h"


int main(int argc, char *argv[]){
   struct timeval tvstart; /* data de inicio */
   struct timeval tvend; /* data de fim */
   struct timeval tvduration; /* diferenca entre as duas datas */
   float duration; /* diferenca entre as datas em microssegundos */

   time_t curtime; /* tempo em formato time_t para conversao de formatos */
   char buffer[30]; /* para escrever a data em formato legivel */

   gettimeofday(&tvstart, NULL); /* ler a data actual */
   curtime=tvstart.tv_sec;
   strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));

   int i;
   int pid[NB_CHILDS],status[NB_CHILDS];

   for(i=0;i<NB_CHILDS;i++){

      pid[i] = fork();
      if (pid[i] == -1) {
         perror("Fork Failed");
         exit(EXIT_FAILURE);
      }

      else if (pid[i] == 0) {
         execl(FILE_PATH,FILE_NAME,(char *) NULL); 
      }
   }

   for(i=0;i<NB_CHILDS;i++){

      //(void)waitpid(pid[i], &status[i], 0);
      waitpid(-1,&status[i],0);
      //printf("pid: %d status: %d\n", pid[i], status[i]);
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
