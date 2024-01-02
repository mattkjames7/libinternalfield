# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -O3

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

COEFFDIR=$(DATADIR)/coeffs


all: 
	$(CCo) savecoeffs.cc -o savecoeffs.o
	$(CCo) igrf.cc -o igrf.o
	$(CCo) savemodels.cc -o savemodels.o
	$(CCo) savevariable.cc -o savevariable.o
	$(CCo) splitstring.cc -o splitstring.o
	$(CCo) listfiles.cc -o listfiles.o
	$(CC) listfiles.o splitstring.o savecoeffs.o igrf.o savemodels.o savevariable.o main.cc -o savecoeffs
	./savecoeffs $(DATADIR)

clean:
	-rm savecoeffs
	-rm *.o
	
