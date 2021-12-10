.PHONY: all clean

all: dynamic

clean:
	rm -rf dynamic *.o *.so

mod_idiv.o: mod_idiv.c
	gcc -fPIC -c mod_idiv.c

libmod_idiv.so: mod_idiv.o
	gcc -shared -o libmod_idiv.so mod_idiv.o

main.o: main.c
	gcc -c main.c

dynamic: main.o libmod_idiv.so
	gcc main.o -L. -lmod_idiv -o dynamic
