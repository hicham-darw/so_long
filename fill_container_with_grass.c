#include "libso_long.h"
#include <mlx.h>


void	fill_container_with_grass(void *mlx,t_data_img *floor_img, t_data_img *s_img, t_data_img *d_img, int window_sx, int window_sy, int width_map, int height_map)
{
    int i, j;
    int src_x, src_y;
    int floor_x, floor_y;
    char *src_pixel, *dst_pixel, *floor_pixel;

   	d_img->img = mlx_new_image(mlx, window_sx / width_map, window_sy / height_map);
	d_img->addr = mlx_get_data_addr(d_img->img, &d_img->bpp, &d_img->line_length, &d_img->endian);

	s_img->img = mlx_xpm_file_to_image(mlx, s_img->xpm_file, &s_img->xpm_width, &s_img->xpm_height);
	s_img->addr = mlx_get_data_addr(s_img->img, &s_img->bpp, &s_img->line_length, &s_img->endian);

    i = 0;
    while (i < window_sy / height_map)
    {
        j = 0;
        while (j < window_sx / width_map)
        {
			src_x = (j * s_img->xpm_width) / (window_sx / width_map);
			src_y = (i * s_img->xpm_height) / (window_sy / height_map);
            src_pixel = s_img->addr + (src_y * s_img->line_length) + (src_x * (s_img->bpp / 8));
            dst_pixel = d_img->addr + (i * d_img->line_length) + (j * (d_img->bpp / 8));

            if (*(unsigned int *)src_pixel == 0xFF000000)
            {
                floor_x = (j * floor_img->xpm_width) / (window_sx / width_map);
                floor_y = (i * floor_img->xpm_height) / (window_sy / height_map);
                floor_pixel = floor_img->addr + (floor_y * floor_img->line_length) + (floor_x * (floor_img->bpp / 8));
			    if (i == 0 && j == 0)
            	    printf("floor_img :pixel[%d][%d]: %X\n",i, j, *(unsigned int *)floor_pixel);
                *(unsigned int *)dst_pixel = *(unsigned int *)floor_pixel;
            }
            else
                *(unsigned int *)dst_pixel = *(unsigned int *)src_pixel;
            j++;
        }
        i++;
    }
}