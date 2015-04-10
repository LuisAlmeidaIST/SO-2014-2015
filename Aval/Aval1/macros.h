#define buffer 10240

char *letras[]={"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n",
"ccccccccc\n","ddddddddd\n","eeeeeeeee\n",
"fffffffff\n","ggggggggg\n","hhhhhhhhh\n",
"iiiiiiiii\n","jjjjjjjjj\n"};

char *ficheiros[]={"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt",
"SO2014-3.txt","SO2014-4.txt"};


int randint(int num){
	//sleep(rand()%10/1000);
	return rand() % num;
}