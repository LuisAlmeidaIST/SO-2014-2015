# Conteúdo da Makefile

escritor:  escritor.o
	  gcc -o escritor  escritor.o

escritor.o: escritor.c macros.h
		gcc -g -c escritor.c

leitor: leitor.o
		gcc -o leitor leitor.o

leitor.o: leitor.c macros.h
		gcc -g -c leitor.c
clean: 
		rm -f *.o escritor leitor
		rm -f SO2014*.txt

teste: clean escritor leitor
	   ./escritor 
	   ./leitor


