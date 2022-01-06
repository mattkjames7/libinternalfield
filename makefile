

all:
	cd libinternalfield; make all
	ln -sv libinternalfield/libinternalfield.so libinternalfield.so 

clean:
	cd libinternalfield; make clean
	rm -v libinternalfield.so
