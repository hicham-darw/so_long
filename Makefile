CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I minilibx-linux
NAME = so_long

$(NAME): libmlx
	$(CC) $(CFLAGS) -o $(NAME) main.c $(INC) -L minilibx-linux -lmlx -lXext -lX11

libmlx:
	make -C minilibx-linux
