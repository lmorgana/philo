CC = gcc

NAME = philo

NAME_BONUS = philo_bonus

CFLAGS = -Wall -Wextra -Werror

HEADERS = header.h

SRC = main.c src/utils.c src/ft_get_conf.c src/ft_is_dead.c\
 	  src/ft_my_atoi.c \
	  src/philo_utils.c src/ft_eat.c\
	  src/ft_get_time.c	\

SRC_BONUS = main_bonus.c	 src_bonus/ft_get_conf_bonus.c	src_bonus/utils_bonus.c \
			src/ft_get_time.c	src/ft_my_atoi.c	\
			src_bonus/ft_get_pids.c	src_bonus/ft_eat_bonus.c

OBJECTS = $(patsubst %.c, %.o, $(SRC))

OBJECTS_BONUS = $(patsubst %.c, %.o, $(SRC_BONUS))

all: $(NAME)

%.o: %.c $(HEADERS) src_bonus/header_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -pthread $(OBJECTS) -o $(NAME)

bonus:	$(OBJECTS_BONUS)
	$(CC) $(CFLAGS) -pthread $(OBJECTS_BONUS) -o $(NAME_BONUS)

clean:
	-rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	-rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all