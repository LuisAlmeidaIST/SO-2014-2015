#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <stdbool.h>


#define NB_FILES         5
#define NB_ENTRIES    1024
#define NB_STRINGS		10
#define STRING_SZ       10
#define NB_ITERATIONS  512
#define NUM_CHILDREN_READER     3
#define NUM_CHILDREN_WRITER     3
#define BUFFER_SIZE     10
#define NAME_SIZE       12
#define INPUT_MAX     2048

#define INPUT_SZ_2       2
#define INPUT_SZ_4       4
#define FILE_PATH_ES "./monitor-escritor"
#define FILE_NAME_ES "monitor-escritor"
#define FILE_PATH_LE "./monitor-leitor"
#define FILE_NAME_LE "monitor-leitor"
#define NB_CHILDS_ES   10
#define get_random(max) rand()%max

char *letras[]= {"aaaaaaaaa\n",
                 "bbbbbbbbb\n",
                 "ccccccccc\n",
                 "ddddddddd\n",
                 "eeeeeeeee\n",
                 "fffffffff\n",
                 "ggggggggg\n",
                 "hhhhhhhhh\n",
                 "iiiiiiiii\n",
                 "jjjjjjjjj\n"
                };

char *ficheiros[]= {"SO2014-0.txt",
                    "SO2014-1.txt",
                    "SO2014-2.txt",
                    "SO2014-3.txt",
                    "SO2014-4.txt"
                   };

char *mystrings[] = { "aaajaaaaa\n",
                      "bbbibbbbb\n",
                      "ccchccccc\n",
                      "dddgddddd\n",
                      "eeefeeeee\n",
                      "fffefffff\n",
                      "gggdggggg\n",
                      "hhhchhhhh\n",
                      "iiibiiiii\n",
                      "jjjajjjjj\n"
                    };


char* INPUTIL="il";
char* INPUTIE="ie";
char* INPUTSAIR="sair";





