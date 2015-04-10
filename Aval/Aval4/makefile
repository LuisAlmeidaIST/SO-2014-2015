# Conteúdo da Makefile

all: escritor leitor1 escritor-pai leitor1-pai leitor2 leitor3

escritor: escritor.o
	  	  gcc -o escritor  escritor.o

escritor.o: escritor.c escritor.h macros.h 
			gcc -g -c escritor.c


escritor-pai: escritor-pai.o
				 gcc -o escritor-pai escritor-pai.o

escritor-pai.o: escritor-pai.c escritor-pai.h macros.h
				   gcc -g -c escritor-pai.c

leitor1: leitor1.o
		gcc -o leitor1 leitor1.o

leitor1.o: leitor1.c leitor1.h macros.h
		  gcc -g -c leitor1.c

leitor2: leitor2.o
		 gcc -pthread -o leitor2 leitor2.o 

leitor2.o: leitor2.c leitor2.h macros.h
		   gcc -g -c -pthread leitor2.c

leitor3: leitor3.o
		 gcc -pthread -o leitor3 leitor3.o

leitor3.o: leitor3.c leitor3.h macros.h
		   gcc -g -c -pthread leitor3.c

leitor1-pai: leitor1-pai.o
			gcc -o leitor1-pai leitor1-pai.o

leitor1-pai.o: leitor1-pai.c leitor1-pai.h
			  gcc -g -c leitor1-pai.c

clean: 
	   rm -f *.o escritor leitor1 escritor-pai leitor1-pai leitor2 leitor3
	   rm -f SO2014*.txt

teste: clean escritor leitor1 escritor-pai leitor1-pai leitor2 leitor3
	   ./escritor
	   ./leitor1 2
	   ./escritor-pai 
	   ./leitor1-pai
	   ./leitor2	
	   ./leitor3

#gcc -o XPTO -lpthread source.c para threads