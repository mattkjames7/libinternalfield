# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	BDIR=linux
	ARCMD=ar -rcs libinternalfield.a build/$(BDIR)/*.o 
endif
ifeq ($(UNAME_S),Darwin)
	BDIR=macos
	ARCMD=libtool -static -o libinternalfield.a build/$(BDIR)/*.o 
endif

all: obj lib

obj:
	#this bit converts the internale field model coefficients into 
	#something addressable within the library
	python3 CodeGen.py
	mkdir -pv build/$(BDIR)
	-rm -v build/$(BDIR)/*.o
	$(CCo) coeffs.cc -o build/$(BDIR)/coeffs.o
	$(CCo) models.cc -o build/$(BDIR)/models.o
	$(CCo) internal.cc -o build/$(BDIR)/internal.o 
	$(CCo) internalmodel.cc -o build/$(BDIR)/internalmodel.o 
	$(CCo) libinternal.cc -o build/$(BDIR)/libinternal.o

lib:
	#$(CC) *.o coeffs/*.o -shared -o libinternal.so
	$(CC) build/$(BDIR)/*.o  -shared -o libinternalfield.so
	$(ARCMD)
	#ar -rcs libinternalfield.a *.o 


windows:
	python3 CodeGen.py
	mkdir -pv build/windows
	-rm -v build/windows/*.o
	$(CCWo) coeffs.cc -o build/windows/coeffs.o
	$(CCWo) models.cc -o build/windows/models.o
	$(CCWo) internal.cc -o build/windows/internal.o 
	$(CCWo) internalmodel.cc -o build/windows/internalmodel.o 
	$(CCWo) libinternal.cc -o build/windows/libinternal.o
	$(CCW) build/windows/*.o  -shared -o libinternalfield.dll


test:
	echo "Making tests"
	cd test; make all
	
	
clean:
	-rm -vf coeffs/*.cc
	-rm -vf *.so *.a
	-rm -vf build/*/*.o
	cd test; make clean;
	-rm -vf ../libinternalfield.h

