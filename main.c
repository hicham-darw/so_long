#include "mlx.h"
#include "mlx_int.h"
#include "libso_long.h"
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	void	*mlx, *new_win;
	t_allvars allvars;

	t_data_img s_data_img[5] /*d_data_img[5]*/;
	int	window_sx, window_sy;
	int	wall_width, wall_height, floor_width, floor_height, jewellery_width, jewellery_height, exit_width, exit_height, player_width, player_height;
	char	**map;

	if (ac != 2)
	{
		printf("Usage: ./program_name file.ber\n");
		exit(EXIT_FAILURE);
	}
	s_data_img[0].xpm_file = ft_strdup("textures/floor.xpm");
	s_data_img[1].xpm_file = ft_strdup("textures/wall.xpm");
	s_data_img[2].xpm_file = ft_strdup("textures/jewellery.xpm");
	s_data_img[3].xpm_file = ft_strdup("textures/exit.xpm");
	s_data_img[4].xpm_file = ft_strdup("textures/player.xpm");

	//read file .ber
	//open file.ber
	char	*line_map;
	int		width_map, height_map;
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	height_map = 0;
	while (get_next_line(fd, &line_map) > 0)
	{
		width_map = strlen(line_map);
		height_map += 1;
	}
	close(fd); // think about how can use maps to put all correct map 

	/*
	*mlx_init = this function establish a connection to correct graphical system
	*
	*@return (void *) hold the location of current MLX | NULL if fails
	*@params (void)
	*/
	mlx = mlx_init();
	if (!mlx)
	{
		printf("connection failed\n");
		return (1);
	}

	/*
	* mlx_new_window = this func initializing a new window 
	*
	*@return (void *) pointer to the window we have created
	*@param 1: mlx location of current MLX
	*@param 2: width of window
	*@param 3: height of window
	*@param 4: window title
	*/
	window_sx = 960;
	window_sy = 500;
	new_win = mlx_new_window(mlx, window_sx, window_sy, "DARWIN");
	if (!new_win)
	{
		printf("can't create new window!\n");
		return (1);
	}
	
	/*
	* mlx_new_image(); create new container (img) for rendering
	*
	*@return (void*) t_img  
	*@param 1: (void *) mlx for init
	*@param 2: width image
	*@param 3: height image
	*/
	int i = 0;
	while (i < 5)
	{
		fill_container_image(mlx, &s_data_img[i], &allvars.data_img[0], window_sx, window_sy, width_map, height_map);
		i++;
	}

	map = get_map(av[1], height_map);
	if (!map)
	{
		printf("failed allocation: map\n");
		return (1);
	}
	printf("OK!\n");
	put_map_to_window(mlx, new_win, map, allvars.data_img, window_sx, window_sy);
	printf("OK!\n");
	sleep(4);
	allvars.mlx = mlx;
	allvars.window = new_win;
	allvars.map = map;
	allvars.window_sx = window_sx;
	allvars.window_sy = window_sy;
	if (!get_player_coordinates(allvars.map, &allvars.player.player_x, &allvars.player.player_y))
	{
		printf("error: get player (x, y)?\n");
		return (1);
	}
	if (!get_exit_coordinates(allvars.map, &allvars.exit.exit_x, &allvars.exit.exit_y))
	{
		printf("error: get exit (x, y)?\n");
		return (1);
	}

	mlx_key_hook(new_win, key_hook, &allvars);
	//	mlx_put_image_to_window(mlx, new_win, img.img, 0, 0);
	mlx_loop(mlx);
	
	/* prototype mlx_clear_window(t_xvar *xvar, t_win_list *win)
	* 	return (int) ---> boolean maybe
	*	params 1: mlx from mlx_init();
	*	params 2: new_window  from mlx_new_window();
	*/
	return (0);
}

int	key_hook(int keycode, t_allvars *vars)
{
	if (!vars)
		return (1);
	if (keycode == 'A' || keycode == 'a')
	{
		if (vars->map[vars->player.player_y][vars->player.player_x - 1] == '1')
			return (1);
		if (vars->player.player_y == vars->exit.exit_y && (vars->player.player_x - 1) == vars->exit.exit_x)
		{
			printf("*********\n*You Win*\n*********\n");
			return (-1);
		}
		printf("LEFT\n");
		update_map(vars->map, vars->player.player_x - 1, vars->player.player_y);
		put_map_to_window(vars->mlx, vars->window, vars->map, vars->data_img, vars->window_sx, vars->window_sy);
	}
	else if (keycode == 'W' || keycode == 'w')
	{
		if (vars->map[vars->player.player_y - 1][vars->player.player_x] == '1')
			return (1);
		if ((vars->player.player_y - 1) == vars->exit.exit_y && vars->player.player_x == vars->exit.exit_x)
		{
			printf("*********\n*You Win*\n*********\n");
			return (-1);
		}
		update_map(vars->map, vars->player.player_x, vars->player.player_y - 1);
		put_map_to_window(vars->mlx, vars->window, vars->map, vars->data_img, vars->window_sx, vars->window_sy);

		printf("UP\n");

	}
	else if (keycode == 'D' || keycode == 'd')
	{
		if (vars->map[vars->player.player_y][vars->player.player_x + 1] == '1')
			return (1);
		if (vars->player.player_y == vars->exit.exit_y && (vars->player.player_x + 1) == vars->exit.exit_x)
		{
			printf("*********\n*You Win*\n*********\n");
			return (-1);
		}
		update_map(vars->map, vars->player.player_x + 1, vars->player.player_y);
		put_map_to_window(vars->mlx, vars->window, vars->map, vars->data_img, vars->window_sx, vars->window_sy);


		printf("RIGHT\n");

	}
	else if (keycode == 'S' || keycode == 's')
	{
		if (vars->map[vars->player.player_y + 1][vars->player.player_x] == '1')
			return (1);
		if ((vars->player.player_y + 1) == vars->exit.exit_y && vars->player.player_x == vars->exit.exit_x);
		{
			printf("*********\n*You Win*\n*********\n");
			return (-1);
		}
		update_map(vars->map, vars->player.player_x, vars->player.player_y + 1);
		put_map_to_window(vars->mlx, vars->window, vars->map, vars->data_img, vars->window_sx, vars->window_sy);

		printf("DOWN\n");

	}
	else
	{
		printf("invalide key!");
		return (1);
	}
	return (0);
}