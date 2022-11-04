# CFLAGS for CC
CFLAGS=-lm -fPIC -std=c++17

# Compiler
CCo=g++ -c $(CFLAGS)
CC=g++ $(CFLAGS)
CCWo=x86_64-w64-mingw32-g++-win32 -c $(CFLAGS)
CCW=x86_64-w64-mingw32-g++-win32 $(CFLAGS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	BDIR=linux
	ARCMD=ar -rcs ../lib/libinternalfield/libinternalfield.a $(BUILDDIR)/*.o 
endif
ifeq ($(UNAME_S),Darwin)
	BDIR=macos
	ARCMD=libtool -static -o ../lib/libinternalfield/libinternalfield.a $(BUILDDIR)/*.o 
endif

all: obj lib header

obj:
	$(CCo) coeffs.cc -o $(BUILDDIR)/coeffs.o
	$(CCo) models.cc -o $(BUILDDIR)/models.o
	$(CCo) internal.cc -o $(BUILDDIR)/internal.o 
	$(CCo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 
	$(CCo) libinternal.cc -o $(BUILDDIR)/libinternal.o

lib:
	$(CC) $(BUILDDIR)/*.o  -shared -o ../lib/libinternalfield/libinternalfield.so
	$(ARCMD)


windows: winobj dll

winobj:
	$(CCWo) coeffs.cc -o $(BUILDDIR)/coeffs.o
	$(CCWo) models.cc -o $(BUILDDIR)/models.o
	$(CCWo) internal.cc -o $(BUILDDIR)/internal.o 
	$(CCWo) internalmodel.cc -o $(BUILDDIR)/internalmodel.o 
	$(CCWo) libinternal.cc -o $(BUILDDIR)/libinternal.o

dll:
	$(CCW) $(BUILDDIR)/*.o  -shared -o ../lib/libinternalfield/libinternalfield.dll

header:
ifneq (,$(shell which python3))
	python3 CodeGen.py
else
	@echo "python3 command doesn't appear to exist - skipping header regeneration..."
endif

