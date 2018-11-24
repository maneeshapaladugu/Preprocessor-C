cc=gcc

CFLAGS=-c -Wall

all: ppc

ppc: c_preprocessor.o macro_replace.o header_inclusion.o rem_comments.o
	$(cc) c_preprocessor.o header_inclusion.o rem_comments.o -o ppc

c_preprocessor.o: c_preprocessor.c
	$(cc) $(CFLAGS) c_preprocessor.c

header_inclusion.o: header_inclusion.c
	$(cc) $(CFLAGS) header_inclusion.c

rem_comments.o: rem_comments.c
	$(cc) $(CFLAGS) rem_comments.c

clean:
	rm -rf *o mcc
