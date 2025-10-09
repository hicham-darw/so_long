CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = fill_container_image.c fill_container_with_grass.c found_collectibles.c get_exit_coordinates.c \
	get_map.c get_player_coordinates.c put_map_to_window.c update_map.c invalid_map.c found_exit.c
OBJS = $(SRCS:.c=.o)
LIBSO = libso_long.a
INC = -I. -I gnl/ -I gnl/libft/includes -I minilibx-linux
GNL = get_next_line.a 
NAME = so_long

$(NAME): $(GNL) $(LIBSO)
	$(CC) $(CFLAGS) -o $(NAME) main.c $(INC) -L. -lso_long gnl/$(GNL) -L gnl/libft -lft -L minilibx-linux -lmlx -lXext -lX11
$(LIBFT):
	make -C gnl/libft
$(GNL):
	make -C gnl	
$(LIBSO): $(OBJS)
	ar rcs $(LIBSO) $(OBJS)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
all: $(NAME)

clean:
	make -C gnl/ clean
	rm -f $(OBJS)
fclean: clean
	make -C gnl/ fclean
	rm -f $(LIBSO) $(NAME)
re: fclean all

.PHONY: all clean fclean re
