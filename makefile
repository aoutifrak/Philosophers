NAME = philo

SRC = utils2.c utils.c philo.c

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror 

HEADER = philo.h

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re :clean all

.PHONY :all clean re fclean
