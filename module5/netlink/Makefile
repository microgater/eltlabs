obj-m += knetlink.o
NAME = unetlink

all: $(NAME)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf $(NAME) *.o

$(NAME): $(NAME).c
	gcc -Wall -o $(NAME) $(NAME).c 
