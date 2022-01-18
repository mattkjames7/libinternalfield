

all:
	cd libinternalfield; make all
	ln -sv libinternalfield/libinternalfield.so libinternalfield.so 
	ln -sv libinternalfield/libinternalfield.a libinternalfield.a

clean:
	cd libinternalfield; make clean
	rm -v libinternalfield.so
	rm -v libinternalfield.a
