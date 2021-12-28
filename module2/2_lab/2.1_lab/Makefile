NAME = main

all: $(NAME)

clean:
	rm -rf $(NAME) *.o *.txt

$(NAME): $(NAME).c
	gcc -std=c99 -Wall -o $(NAME) $(NAME).c
