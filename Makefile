CC=gcc
CFLAGS= -g -std=c99 -Wall -Werror

EXEC=arbreB_test
.PHONY: all clean tests

all: $(EXEC)

clean:
	rm -rf *.o *.exe *.out $(EXEC)

tests: arbreB_test

arbreB_test: arbreB_test.o arbreB.o test.o
	$(CC) $(LDFLAGS) -o $@ $^
