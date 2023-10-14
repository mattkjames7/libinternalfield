# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -O3

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

COEFFDIR=$(DATADIR)/coeffs


all: 
	$(CC) savecoeffs.cc -o savecoeffs
	./savecoeffs $(DATADIR)

clean:
	-rm savecoeffs
	
