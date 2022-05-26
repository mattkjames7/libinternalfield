# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ARCMD=ar -rcs libinternalfield.a *.o 
endif
ifeq ($(UNAME_S),Darwin)
	ARCMD=libtool -static -o libinternalfield.a *.o 
endif

all: obj lib

obj:
	#this bit converts the internale field model coefficients into 
	#something addressable within the library
	python3 CodeGen.py
	$(CCo) coeffs.cc -o coeffs.o
	$(CCo) models.cc -o models.o
	$(CCo) internal.cc -o internal.o 
	$(CCo) internalmodel.cc -o internalmodel.o 
	$(CCo) libinternal.cc -o libinternal.o

lib:
	#$(CC) *.o coeffs/*.o -shared -o libinternal.so
	$(CC) coeffs.o internal.o models.o internalmodel.o libinternal.o  -shared -o libinternalfield.so
	$(ARCMD)
	#ar -rcs libinternalfield.a *.o 
	rm -vf *.o

	
test:
	echo "Making tests"
	cd test; make all
	
	
clean:
	rm -vf coeffs/*.cc
	rm -vf *.so *.a
	cd test; make clean;\
	rm -vf ../libinternalfield.h

