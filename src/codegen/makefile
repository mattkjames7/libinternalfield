# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -O3

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

COEFFDIR=$(DATADIR)/coeffs


all: obj exe

obj: savecoeffs igrf savemodels savevariable splitstring listfiles savelibheader trimstring

savecoeffs:
	$(CCo) savecoeffs.cc -o savecoeffs.o

igrf:
	$(CCo) igrf.cc -o igrf.o

savemodels:
	$(CCo) savemodels.cc -o savemodels.o

savevariable:
	$(CCo) savevariable.cc -o savevariable.o

splitstring:
	$(CCo) splitstring.cc -o splitstring.o

listfiles:
	$(CCo) listfiles.cc -o listfiles.o

savelibheader:
	$(CCo) savelibheader.cc -o savelibheader.o

trimstring:
	$(CCo) trimstring.cc -o trimstring.o

exe: obj
	$(CC) listfiles.o splitstring.o trimstring.o savecoeffs.o igrf.o\
		savemodels.o savevariable.o savelibheader.o main.cc -o savecoeffs
	./savecoeffs $(DATADIR)

clean:
	-rm savecoeffs
	-rm *.o
	
