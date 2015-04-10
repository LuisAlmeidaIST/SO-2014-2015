#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define NB_FILES         5   
#define NB_ENTRIES    1024
#define STRING_SZ       10
#define NB_STRINGS		10
#define NB_ITERATIONS  512
#define FILE_PATH "./escritor"
#define FILE_NAME "escritor"
#define NB_CHILDS   10
#define get_random(max) rand()%max

char *letras[]={"aaaaaaaaa\n",
				"bbbbbbbbb\n",
				"ccccccccc\n",
				"ddddddddd\n",
				"eeeeeeeee\n",
				"fffffffff\n",
				"ggggggggg\n",
				"hhhhhhhhh\n",
				"iiiiiiiii\n",
				"jjjjjjjjj\n"};

char *ficheiros[]={"SO2014-0.txt",
				   "SO2014-1.txt",
				   "SO2014-2.txt",
				   "SO2014-3.txt",
				   "SO2014-4.txt"};

