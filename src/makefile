# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -O3

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

OBJS=$(BUILDDIR)/models.o $(BUILDDIR)/internal.o $(BUILDDIR)/internalmodel.o $(BUILDDIR)/libinternal.o

ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
	LIBFILE=libinternalfield.dll
else
#linux and mac here
	OS=$(shell uname -s)
	ifeq ($(OS),Linux)
		LIBFILE=libinternalfield.so
		ARCMD=ar -rcs ../lib/libinternalfield.a $(OBJS)
	else
		LIBFILE=libinternalfield.dylib
		ARCMD=libtool -static -o ../lib/libinternalfield.a $(OBJS)
	endif
	MD=mkdir -p
endif



all: obj lib 

obj: models internal internalmodel libinternal

models:
	$(CCo) models.cc -o $(BUILDDIR)/models.o

internal: ../generated/out.h
	$(CCo) internal.cc -o $(BUILDDIR)/internal.o 

../generated/out.h:
	+cd ../tools/coeff_registry_codegen; make all
	$(MD) ../generated
	../tools/coeff_registry_codegen/coeff_registry_codegen $(DATADIR)/coeffs ../generated/out.h

internalmodel:
	$(CCo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 

libinternal:
	$(CCo) libinternal.cc -o $(BUILDDIR)/libinternal.o

lib: obj
	$(CC) $(OBJS) -shared -o ../lib/$(LIBFILE)
	$(ARCMD)


windows: winobj dll

winobj:
	$(CCWo) models.cc -o $(BUILDDIR)/models.o
	$(CCWo) internal.cc -o $(BUILDDIR)/internal.o 
	$(CCWo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 
	$(CCWo) libinternal.cc -o $(BUILDDIR)/libinternal.o

dll:
	$(CCW) $(OBJS) -shared -o ../lib/libinternalfield.dll

clean:
	-rm coeffs/*/*.bin
	-rm variable/*/*.bin
	
header:
	+cd codegen; make all
	+cd codegen; make clean
