
ifndef BUILDDIR
export BUILDDIR=$(shell pwd)/build
endif

ifeq ($(PREFIX),)
#install path
	PREFIX=/usr/local
endif



ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
	LIBFILE=libinternalfield.dll
else
#linux and mac here
	OS=$(shell uname -s)
	ifeq ($(OS),Linux)
		LIBFILE=libinternalfield.so
	else
		LIBFILE=libinternalfield.dylib
	endif
	MD=mkdir -p
endif

.PHONY: all obj lib windows winobj dll clean test header

all: obj lib


obj:
	$(MD) $(BUILDDIR)
	cd src; make obj

lib:
	$(MD) $(BUILDDIR)
	$(MD) lib/libinternalfield
	cd src; make lib


windows: winobj dll

winobj:
	$(MD) $(BUILDDIR)
	cd src; make winobj

dll:
	$(MD) $(BUILDDIR)
	$(MD) lib/libinternalfield
	cd src; make dll

test:
	cd test; make all

updatemodels:
	cd src; make header

clean:
	-rm -v build/*
	-rmdir -v build
	-rm -v lib/libinternalfield/$(LIBFILE)
	-rmdir -v lib/libinternalfield
	cd test; make clean

header:
	cd src; make header

install:
	cp -v include/internalfield.h $(PREFIX)/include
	cp -v include/internalfieldc.h $(PREFIX)/include
	cp -v lib/libinternalfield/$(LIBFILE) $(PREFIX)/lib
ifeq ($(OS),Linux)
	ldconfig
endif

uninstall:
	rm -v $(PREFIX)/include/internalfield.h
	rm -v $(PREFIX)/include/internalfieldc.h
	rm -v $(PREFIX)/lib/$(LIBFILE)
ifeq ($(OS),Linux)
	ldconfig
endif