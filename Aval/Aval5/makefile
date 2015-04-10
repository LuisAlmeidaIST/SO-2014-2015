# This makefile uses implicit rules, see: http://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_10.html

CC=gcc
CFLAGS=-g -Wall -I include
LDFLAGS=-pthread
EXECS= monitor-leitor monitor-escritor monitor-independente

all: $(EXECS)

monitor-leitor: monitor-leitor.c  include/macros.h

monitor-independente: monitor-independente.c include/macros.h

monitor-escritor: monitor-escritor.c include/macros.h

clean:
	rm -f SO2014*.txt
	rm *~ $(EXECS)
	rm include/*~


