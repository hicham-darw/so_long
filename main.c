#include "mlx.h"
#include "mlx_int.h"
#include "libso_long.h"
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	t_allvars allvars;
	t_data_img s_data_img[6];

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
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open failed");
		exit(1);
	}
	allvars.height_map = 0;
	while (get_next_line(fd, &line_map) > 0)
	{
		allvars.width_map = strlen(line_map);
		allvars.height_map += 1;
		free(line_map);
	}
	close(fd); // think about how can use maps to put all correct map 

	/*
	*mlx_init = this function establish a connection to correct graphical system
	*
	*@return (void *) hold the location of current MLX | NULL if fails
	*@params (void)
	*/
	allvars.mlx = mlx_init();
	if (!allvars.mlx)
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
	allvars.window_sx = 1920;
	allvars.window_sy = 1000;
	allvars.window = mlx_new_window(allvars.mlx, allvars.window_sx, allvars.window_sy, "DARWIN");
	if (!allvars.window)
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
		if (i == 0)
			fill_container_image(allvars.mlx, &s_data_img[i], &allvars.data_img[i], allvars.window_sx, allvars.window_sy, allvars.width_map, allvars.height_map);
		else
			fill_container_with_grass(allvars.mlx, &s_data_img[0], &s_data_img[i], &allvars.data_img[i], allvars.window_sx, allvars.window_sy, allvars.width_map, allvars.height_map);
		i++;
	}

	//reverse image player
	// allvars.player.reverse_player = 1;
	// printf("%s\n", allvars.data_img[4].addr);

	// printf("%s\n", allvars.data_img[4].addr);
	// printf("*****************************\n");

	allvars.map = get_map(av[1], allvars.height_map);
	if (!allvars.map)
	{
		printf("failed allocation: map\n");
		return (1);
	}
	put_map_to_window(&allvars);

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
    printf("line_length: %d\n", allvars.data_img[4].line_length);
    printf("bpp        : %d\n", allvars.data_img[4].bpp);
    printf("xpm width  : %d\n", allvars.data_img[4].xpm_width);

	change_direction_player(&allvars);


	printf("exit (%d, %d)\n", allvars.exit.exit_x, allvars.exit.exit_y);
	mlx_key_hook(allvars.window, key_hook, &allvars);
	//	mlx_put_image_to_window(mlx, new_win, img.img, 0, 0);
	mlx_loop(allvars.mlx);
	
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
		if (vars->map[vars->player.player_y][vars->player.player_x - 1] == 'E')
		{
			if (found_collectibles(vars->map))
				return (1);
			else
			{
				printf("*********\n*You Win*\n*********\n");
				exit(0);
			}
			return (42);
		}
		printf("LEFT\n");
		update_map(vars->map, &vars->player.player_x, &vars->player.player_y, keycode);
		put_map_to_window(vars);
	}
	else if (keycode == 'W' || keycode == 'w')
	{
		if (vars->map[vars->player.player_y - 1][vars->player.player_x] == '1')
			return (1);
		if (vars->map[vars->player.player_y - 1][vars->player.player_x] == 'E')
		{
			if (found_collectibles(vars->map))
				return (1);
			else
			{
				printf("*********\n*You Win*\n*********\n");
				exit(0);
			}
			return (42);
		}
		update_map(vars->map, &vars->player.player_x, &vars->player.player_y, keycode);
		put_map_to_window(vars);
		printf("UP\n");
	}
	else if (keycode == 'D' || keycode == 'd')
	{
		if (vars->map[vars->player.player_y][vars->player.player_x + 1] == '1')
			return (1);
		if (vars->map[vars->player.player_y][vars->player.player_x + 1] == 'E')
		{
			if (found_collectibles(vars->map))
				return (1);
			else
			{
				printf("*********\n*You Win*\n*********\n");
				exit(0);
			}
			return (42);
		}
		update_map(vars->map, &vars->player.player_x , &vars->player.player_y, keycode);
		put_map_to_window(vars);
		printf("RIGHT\n");
	}
	else if (keycode == 'S' || keycode == 's')
	{
		if (vars->map[vars->player.player_y + 1][vars->player.player_x] == '1')
			return (1);
		if (vars->map[vars->player.player_y + 1][vars->player.player_x] == 'E')
		{
			if (found_collectibles(vars->map))
				return (1);
			else
			{
				printf("*********\n*You Win*\n*********\n");
				exit(0);
			}
			return (42);
		}
		update_map(vars->map, &vars->player.player_x, &vars->player.player_y, keycode);
		put_map_to_window(vars);
		printf("DOWN\n");
	}
	else
	{
		if (keycode == 65307)
			exit(0);
		printf("keycode => %d\n", keycode);
		return (1);
	}
	return (0);
}