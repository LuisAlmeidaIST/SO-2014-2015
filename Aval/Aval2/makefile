# Conteúdo da Makefile

all: clean escritor leitor escritor-filhos

escritor: escritor.o
	  	  gcc -o escritor  escritor.o

escritor.o: escritor.c escritor.h macros.h 
			gcc -g -c escritor.c

leitor: leitor.o
		gcc -o leitor leitor.o

leitor.o: leitor.c leitor.h macros.h
		  gcc -g -c leitor.c

escritor-filhos: escritor-filhos.o
				 gcc -o escritor-filhos escritor-filhos.o

escritor-filhos.o: escritor-filhos.c escritor-filhos.h macros.h
				   gcc -g -c escritor-filhos.c

clean: 
	   rm -f *.o escritor leitor escritor-filhos
	   rm -f SO2014*.txt

teste: clean escritor leitor escritor-filhos
	   ./escritor-filhos 
	   ./leitor


