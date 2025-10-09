#ifndef LIBSO_LONG_H
#define LIBSO_LONG_H

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"

#define WIN_SX 1000
#define WIN_SY 1000

typedef struct s_data_image
{
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
	char	*xpm_file;
	int		xpm_width;
	int		xpm_height;
}	t_data_img;

typedef struct s_player
{
	int	player_x;
	int	player_y;
	int direction;
}t_player;

typedef struct s_exit
{
	int exit_x;
	int	exit_y;
}t_exit;

typedef struct s_item
{
	int player;
	int	exit;
	int collectible;
}t_item;

typedef struct s_allvars
{
	void *mlx;
	void *window;
	int window_sx;
	int window_sy;
	char **map;
	int	width_map;
	int	height_map;
	t_player player;
	t_exit exit;
	t_data_img data_img[6];

}t_allvars;

void fill_container_image(void *mlx, t_data_img *s_img, t_data_img *d_img,  int window_sx, int window_sy, int width_map, int height_map);
void fill_container_with_grass(void *mlx, t_data_img *floor_img, t_data_img *s_img, t_data_img *d_img, int window_sx, int window_sy, int width_map, int height_map);
char	**get_map(char *filename, int height);
int	put_map_to_window(t_allvars *allvars, int direction);
int	get_player_coordinates(char **map, int *player_x, int *player_y);
int	get_exit_coordinates(char **map, int *exit_x, int *exit_y);
int	key_hook(int keycode, t_allvars *vars);
char	**update_map(char **map, int *px, int *py, int keycode);
int		found_collectibles(char **map);
void	change_direction_player(t_allvars *vars, int px, int py);
int		found_exit(char **map);
int invalid_map(char **map, int px, int py);

#endif

