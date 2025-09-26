#include "mlx.h"
#include "mlx_int.h"
#include "libso_long.h"
#include <stdlib.h>
#include "gnl/get_next_line.h"

int	main(int ac, char **av)
{
	void	*mlx, *new_win;
	t_data_img s_wall_img, s_floor_img, d_wall_img, d_floor_img, s_jewellery_img, d_jewellery_img, s_exit_img, d_exit_img, s_player_img, d_player_img;
	int	window_sx, window_sy;
	int	wall_width, wall_height, floor_width, floor_height, jewellery_width, jewellery_height, exit_width, exit_height, player_width, player_height;

	if (ac != 2)
	{
		printf("Usage: ./program_name file.ber\n");
		exit(EXIT_FAILURE);
	}

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
		printf("%s\n", line_map);
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
	// container wall image && address buffer
	d_wall_img.img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_wall_img.addr = mlx_get_data_addr(d_wall_img.img, &d_wall_img.bpp, &d_wall_img.line_length, &d_wall_img.endian);
	// container floor image && address buffer
	d_floor_img.img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_floor_img.addr = mlx_get_data_addr(d_floor_img.img, &d_floor_img.bpp, &d_floor_img.line_length, &d_floor_img.endian);
	// container player image && addr buffer
	d_player_img.img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_player_img.addr = mlx_get_data_addr(d_player_img.img, &d_player_img.bpp, &d_player_img.line_length, &d_player_img.endian);
	// container collectible image
	d_jewellery_img.img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_jewellery_img.addr = mlx_get_data_addr(d_jewellery_img.img, &d_jewellery_img.bpp, &d_player_img.line_length, &d_player_img.endian);
	// containet exit image
	d_exit_img.img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_exit_img.addr = mlx_get_data_addr(d_exit_img.img, &d_exit_img.bpp, &d_exit_img.line_length, &d_exit_img.endian);


	// get xpm file wall image
	s_wall_img.img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &wall_width, &wall_height);
	s_wall_img.addr = mlx_get_data_addr(s_wall_img.img, &s_wall_img.bpp, &s_wall_img.line_length, &s_wall_img.endian);
	// get xpm file floor image
	s_floor_img.img = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &floor_width, &floor_height);
	s_floor_img.addr = mlx_get_data_addr(s_floor_img.img, &s_floor_img.bpp, &s_floor_img.line_length, &s_wall_img.endian);
	// get xpm file player image
	s_player_img.img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &player_width, &player_height);
	s_player_img.addr = mlx_get_data_addr(s_player_img.img, &s_player_img.bpp, &s_player_img.line_length, &s_player_img.endian);
	// get xpm file jewellery image
	s_jewellery_img.img = mlx_xpm_file_to_image(mlx, "textures/jewellery.xpm", &jewellery_width, &jewellery_height);
	s_jewellery_img.addr = mlx_get_data_addr(s_jewellery_img.img, &s_jewellery_img.bpp, &s_jewellery_img.line_length, &s_jewellery_img.endian);
	// get xpm file exit image
	s_exit_img.img = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &exit_width, &exit_height);
	s_exit_img.addr = mlx_get_data_addr(s_exit_img.img, &s_exit_img.bpp, &s_exit_img.line_length, &s_exit_img.endian);


	int	i, j, src_x, src_y;
	char	*src_pixel, *dst_pixel;
	i = 0;
	while (i < (window_sy / height_map))
	{
		j = 0;
		while (j < (window_sx / width_map))
		{
			src_x = (j * floor_width) / (window_sx / width_map);
			src_y = (i * floor_height) / (window_sy / height_map);

			src_pixel = s_floor_img.addr + (src_y * s_floor_img.line_length) + (src_x * (s_floor_img.bpp / 8));
			dst_pixel = d_floor_img.addr + (i * d_floor_img.line_length) + (j * (d_floor_img.bpp / 8));
			
			*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < (window_sy / height_map))
	{
		j = 0;
		while (j < (window_sx / width_map))
		{
			src_x = (j * wall_width) / (window_sx / width_map);
			src_y = (i * wall_height) / (window_sy / height_map);

			src_pixel = s_wall_img.addr + (src_y * s_wall_img.line_length) + (src_x * (s_wall_img.bpp / 8));
			dst_pixel = d_wall_img.addr + (i * d_wall_img.line_length) + (j * (d_wall_img.bpp / 8));
			
			*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < height_map)
	{
		j = 0;
		while (j < width_map)
		{
			if (i == 0 || j == 0 || i == height_map - 1 || j == width_map - 1)
				mlx_put_image_to_window(mlx, new_win, d_wall_img.img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else
				mlx_put_image_to_window(mlx, new_win, d_floor_img.img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			j++;
		}
		i++;
	}

	//	mlx_put_image_to_window(mlx, new_win, img.img, 0, 0);
	mlx_loop(mlx);
	
	/* prototype mlx_clear_window(t_xvar *xvar, t_win_list *win)
	* 	return (int) ---> boolean maybe
	*	params 1: mlx from mlx_init();
	*	params 2: new_window  from mlx_new_window();
	*/
	return (0);
}