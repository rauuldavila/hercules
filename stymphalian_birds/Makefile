NAME = #
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(INCLUDES) -c $(SRC)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
