.PHONY: all clean

all: static

clean:
	rm -rf static *.o *.a

mod_idiv.o: mod_idiv.c
	gcc -c mod_idiv.c

main.o: main.c
	gcc -c main.c

static: main.o mod_idiv.o
	ar rc libmod_idiv.a mod_idiv.o
	ranlib libmod_idiv.a
	gcc main.o -L. -lmod_idiv -o static
