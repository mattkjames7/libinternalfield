
ifndef BUILDDIR
export BUILDDIR=$(shell pwd)/build
endif

ifeq ($(OS),Windows_NT)
#windows stuff here
	MD=mkdir
else
#linux and mac here
	MD=mkdir -p
endif

.PHONY: all obj lib windows winobj dll clean test

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
	cd src; make winlib

test:
	cd test; make all

updatemodels:
	cd src; make header

clean:
	-rm -v build/*
	-rmdir -v build
	-rm -v lib/libinternalfield/libinternalfield.a
	-rm -v lib/libinternalfield/libinternalfield.so
	-rm -v lib/libinternalfield/libinternalfield.dll
	-rmdir -v lib/libinternalfield
	cd test; make clean

