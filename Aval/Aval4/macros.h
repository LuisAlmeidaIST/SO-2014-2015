#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/file.h>

#define NB_FILES         5   
#define NB_ENTRIES    1024
#define STRING_SZ       10
#define NB_STRINGS		10
#define NB_ITERATIONS  512
#define FILE_PATH_ES "./escritor"
#define FILE_NAME_ES "escritor"
#define FILE_NAME_LE "leitor1"
#define FILE_PATH_LE "./leitor1"
#define NB_CHILDS_ES   10
#define NB_CHILDS_LE   3
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

