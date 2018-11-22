cc=gcc

CFLAGS=-c -Wall

all: pp

pp: c_preprocessor.o macro_replace.o header_inclusion.o rem_comments.o
	$(cc) c_preprocessor.o macro_replace.o header_inclusion.o rem_comments.o -o pp

c_preprocessor.o: c_preprocessor.c
	$(cc) $(CFLAGS) c_preprocessor.c

macro_replace.o: macro_replace.c
	$(cc) $(CFLAGS) macro_replace.c

header_inclusion.o: header_inclusion.c
	$(cc) $(CFLAGS) header_inclusion.c

rem_comments.o: rem_comments.c
	$(cc) $(CFLAGS) rem_comments.c

clean:
	rm -rf *o mcc
