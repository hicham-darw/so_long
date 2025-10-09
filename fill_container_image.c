#include "libso_long.h"
#include <mlx.h>
#include <stdio.h>

void	fill_container_image(void *mlx,t_data_img *s_img, t_data_img *d_img, int window_sx, int window_sy, int width_map, int height_map)
{
    int i, j;
    int src_x, src_y;
    char    *src_pixel, *dst_pixel;

   	d_img->img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_img->addr = mlx_get_data_addr(d_img->img, &d_img->bpp, &d_img->line_length, &d_img->endian);
	if (!d_img->addr)
	{
		printf("error dst img\n");
		return ;
	}

	s_img->img = mlx_xpm_file_to_image(mlx, s_img->xpm_file, &s_img->xpm_width, &s_img->xpm_height);
	s_img->addr = mlx_get_data_addr(s_img->img, &s_img->bpp, &s_img->line_length, &s_img->endian);

	if (!s_img->addr)
	{
		printf("error dst img2\n");
		return ;
	}
	
	i = 0;
	while (i < (window_sy / height_map))
	{
		j = 0;
		while (j < (window_sx / width_map))
		{
			src_x = (j * s_img->xpm_width) / (window_sx / width_map);
			src_y = (i * s_img->xpm_height) / (window_sy / height_map);

			src_pixel = s_img->addr + (src_y * s_img->line_length) + (src_x * (s_img->bpp / 8));
			dst_pixel = d_img->addr + (i * d_img->line_length) + (j * (d_img->bpp / 8));

			*(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
			j++;
		}
		i++;
	}
}
