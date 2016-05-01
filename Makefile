CC=gcc
CFLAGS= -g -std=c99 -Wall -Werror

EXEC=main arbreB_test
.PHONY: all clean tests

all: $(EXEC)

clean:
	rm -rf *.o *.exe *.out $(EXEC)
	
tests: arbreB_test

main: main.o arbreB.o
	$(CC) $(LDFLAGS) -o $@ $^
	
arbreB_test: arbreB_test.o arbreB.o test.o
	$(CC) $(LDFLAGS) -o $@ $^