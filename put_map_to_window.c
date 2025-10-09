#include <mlx.h>
#include "gnl/get_next_line.h"
#include "libso_long.h"
#include <fcntl.h>

int		put_map_to_window(t_allvars *vars, int direction)
{
    int		i, j;

	if (!vars->map || !*vars->map)
		return (0);
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '1')
				mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[1].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
			else if (vars->map[i][j] == '0')
				mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[0].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
			else if (vars->map[i][j] == 'P')
			{
				if (direction == 'R')
					mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[5].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
				else
					mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[4].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
			}
			else if (vars->map[i][j] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[2].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
			else if (vars->map[i][j] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->window, vars->data_img[3].img, (vars->window_sx / vars->width_map) * j, (vars->window_sy / vars->height_map) * i);
			else
				printf("invalid img!");
			j++;
		}
		i++;
	}
	return (1);
}