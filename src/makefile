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



all: obj lib header

obj:
	$(CCo) coeffs.cc -o $(BUILDDIR)/coeffs.o
	$(CCo) models.cc -o $(BUILDDIR)/models.o
	$(CCo) internal.cc -o $(BUILDDIR)/internal.o 
	$(CCo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 
	$(CCo) libinternal.cc -o $(BUILDDIR)/libinternal.o

lib:
	$(CC) $(BUILDDIR)/*.o  -shared -o ../lib/$(LIBFILE)
	$(ARCMD)


windows: winobj dll

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
	
header:
ifneq (,$(shell which python3))
	python3 CodeGen.py $(BUILDDIR)
else
	@echo "python3 command doesn't appear to exist - skipping header regeneration..."
endif

