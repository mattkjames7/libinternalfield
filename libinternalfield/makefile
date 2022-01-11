# CFLAGS for CC
CFLAGS=-lm -fopenmp -fPIC -std=c++17 -g

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)

all: obj lib test

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
	$(CC) coeffs/*.o coeffs.o internal.o models.o internalmodel.o libinternal.o  -shared -o libinternalfield.so
	rm -v *.o
	rm -v coeffs/*.o
	rm -v coeffs/*.bin
	cd test; make all
	
test:
	echo "here"
	
	
clean:
	rm -v *.so
	cd test; make clean
	rm -v ../libinternalfield.h
