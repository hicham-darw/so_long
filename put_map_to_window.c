#include <mlx.h>
#include "gnl/get_next_line.h"
#include "libso_long.h"
#include <fcntl.h>

int		put_map_to_window(void *mlx, void *new_win, char **map, t_data_img *dst_img, int window_sx, int window_sy)
{
    char    *line;
    int		i, j;
	int	width_map, height_map;

    if (!mlx || !new_win || !map || !dst_img)
        return (0);
	width_map = ft_strlen(map[0]);
	height_map = ft_veclen(map);

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(mlx, new_win, (dst_img + 1)->img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else if (map[i][j] == '0')
				mlx_put_image_to_window(mlx, new_win, dst_img[0].img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else if (map[i][j] == 'P')
				mlx_put_image_to_window(mlx, new_win, dst_img[4].img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else if (map[i][j] == 'C')
				mlx_put_image_to_window(mlx, new_win, dst_img[2].img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else if (map[i][j] == 'E')
				mlx_put_image_to_window(mlx, new_win, dst_img[3].img, (window_sx / width_map) * j, (window_sy / height_map) * i);
			else
				printf("invalid img!");
			j++;
		}
		i++;
	}
	return (1);
}