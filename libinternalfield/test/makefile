# CFLAGS for CC
CFLAGS=-lm -fopenmp -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all:
	$(CC) test.cc -o test -Wl,-rpath='$$ORIGIN/..' -L.. -linternal 
	
clean:
	rm -v test
