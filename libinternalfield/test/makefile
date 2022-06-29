# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all:
	$(CC) test.cc -o test -Wl,-rpath='$$ORIGIN/..' -L.. -linternalfield
	
clean:
	-rm -v test
