# CFLAGS for CC
CFLAGS=-fPIC -std=c++17 -O3

OS=$(shell uname -s)
ifeq ($(OS),Linux) 
	LDFLAGS=-Wl,-rpath='$$ORIGIN/../lib/libinternalfield' -L ../lib/libinternalfield -linternalfield -lm
else 
	LDFLAGS=-L ../lib/libinternalfield -linternalfield -lm
endif
IFLAGS=-I ../include/

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all:
	$(CC) test.cc -o test $(LDFLAGS)
	$(CC) timer.cc -o timer $(LDFLAGS)
	gcc $(IFLAGS) ctest.c -o ctest $(LDFLAGS)
	$(CC) $(IFLAGS) cpptest.cc -o cpptest $(LDFLAGS)
	./test
	./timer
	./ctest
	./cpptest
	
clean:
	-rm -v test
	-rm -v timer
	-rm -v ctest
	-rm -v cpptest