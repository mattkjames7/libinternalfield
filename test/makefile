# CFLAGS for CC
CFLAGS=-fPIC -std=c++17 -O3

OS=$(shell uname -s)
ifeq ($(OS),Linux) 
	LDFLAGS=-Wl,-rpath='$$ORIGIN/../lib' -L ../lib -linternalfield -lm
else 
	LDFLAGS=-L ../lib -linternalfield -lm
endif
IFLAGS=-I ../include/

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all:
	$(CCo) $(IFLAGS) testdata.cc -o testdata.o
	$(CC) $(IFLAGS) testdata.o test.cc -o test $(LDFLAGS)
	$(CC) $(IFLAGS) timer.cc -o timer $(LDFLAGS)
	gcc $(IFLAGS) ctest.c -o ctest $(LDFLAGS)
	$(CC) $(IFLAGS) cpptest.cc -o cpptest $(LDFLAGS)
	@./test
	@./ctest
	@./cpptest
	@./timer
	
save:
	$(CC) $(IFLAGS) testdata.cc savetestdata.cc -o savetestdata $(LDFLAGS)
	./savetestdata

clean:
	-rm -v test
	-rm -v timer
	-rm -v ctest
	-rm -v cpptest