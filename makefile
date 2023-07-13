
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

all: obj lib header


obj:
	$(MD) $(BUILDDIR)
	cd src; make obj

lib:
	$(MD) $(BUILDDIR)
	$(MD) lib
	cd src; make lib

header:
	cd src; make header

windows: winobj dll

winobj:
	$(MD) $(BUILDDIR)
	cd src; make winobj

dll:
	$(MD) $(BUILDDIR)
	$(MD) lib
	cd src; make dll

test:
	cd test; make all

updatemodels:
	cd src; make header

clean:
	cd src; make clean
	-rm -v lib/$(LIBFILE)
ifeq ($(OS),Windows_NT)
	-rmdir build /s /q
else
	-rm -vfr build
endif
	cd test; make clean

install:
	cp -v include/internalfield.h $(PREFIX)/include
	cp -v lib/$(LIBFILE) $(PREFIX)/lib
ifeq ($(OS),Linux)
	ldconfig
endif

uninstall:
	rm -v $(PREFIX)/include/internalfield.h
	rm -v $(PREFIX)/lib/$(LIBFILE)
ifeq ($(OS),Linux)
	ldconfig
endif