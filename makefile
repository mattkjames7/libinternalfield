

all:
	cd libinternalfield; make all
	ln -svf libinternalfield/libinternalfield.so libinternalfield.so 
	ln -svf libinternalfield/libinternalfield.a libinternalfield.a

windows:
	cd libinternalfield; make windows

clean:
	cd libinternalfield; make clean
	-rm -v libinternalfield.so
	-rm -v libinternalfield.a
