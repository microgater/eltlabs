NAME = 4_warcraft

.PHONY: all clean

all: $(NAME)

clean:
	rm -rf $(NAME) *.o

$(NAME): $(NAME).c
	gcc -Wall -o $(NAME) $(NAME).c -lpthread 
