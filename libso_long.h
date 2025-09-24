#ifndef LIBSO_LONG_H
#define LIBSO_LONG_H

#include <stdio.h>
#include <unistd.h>

typedef struct s_data_image
{
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
}	t_data_img;

void	ft_mlx_pixel_put(t_data_img *data, int x, int y, int color);

#endif
