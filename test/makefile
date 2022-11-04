# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all:
	$(CC) test.cc -o test -Wl,-rpath='$$ORIGIN/../lib/libinternalfield' -L../lib/libinternalfield -linternalfield
	$(CC) timer.cc -o timer -Wl,-rpath='$$ORIGIN/../lib/libinternalfield' -L../lib/libinternalfield -linternalfield
		
	./test
	./timer
	
clean:
	-rm -v test
	-rm -v timer
