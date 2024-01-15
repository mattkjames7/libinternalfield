# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -O3

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
	LIBFILE=libinternalfield.dll
else
#linux and mac here
	OS=$(shell uname -s)
	ifeq ($(OS),Linux)
		LIBFILE=libinternalfield.so
		ARCMD=ar -rcs ../lib/libinternalfield.a $(BUILDDIR)/*.o 
	else
		LIBFILE=libinternalfield.dylib
		ARCMD=libtool -static -o ../lib/libinternalfield.a $(BUILDDIR)/*.o 
	endif
	MD=mkdir -p
endif



all: header obj lib 

obj: header coeffs models internal internalmodel libinternal

coeffs:
	$(CCo) coeffs.cc -o $(BUILDDIR)/coeffs.o

models:
	$(CCo) models.cc -o $(BUILDDIR)/models.o

internal: 
	$(CCo) internal.cc -o $(BUILDDIR)/internal.o 

internalmodel:
	$(CCo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 

libinternal:
	$(CCo) libinternal.cc -o $(BUILDDIR)/libinternal.o

lib: obj
	$(CC) $(BUILDDIR)/coeffs.o $(BUILDDIR)/models.o $(BUILDDIR)/internal.o\
		$(BUILDDIR)/internalmodel.o $(BUILDDIR)/libinternal.o -shared -o ../lib/$(LIBFILE)
	$(ARCMD)


windows: header winobj dll

winobj:
	$(CCWo) coeffs.cc -o $(BUILDDIR)/coeffs.o
	$(CCWo) models.cc -o $(BUILDDIR)/models.o
	$(CCWo) internal.cc -o $(BUILDDIR)/internal.o 
	$(CCWo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 
	$(CCWo) libinternal.cc -o $(BUILDDIR)/libinternal.o

dll:
	$(CCW) $(BUILDDIR)/*.o  -shared -o ../lib/libinternalfield.dll

clean:
	-rm coeffs/*/*.bin
	-rm variable/*/*.bin
	cd codegen; make clean
	
header:
	+cd codegen; make all
	+cd codegen; make clean
