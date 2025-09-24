#include "mlx.h"
#include "libso_long.h"

int	main(void)
{
	void	*mlx, *new_win;
	t_data_img	img;

	//initial window;
	mlx = mlx_init();
	if (!mlx)
	{
		printf("connection failed\n");
		return (1);
	}
	
	//create new window
	new_win = mlx_new_window(mlx, 1000, 920, "DARWIN");
	if (!new_win)
	{
		printf("can't creat new window!\n");
		return (1);
	}

	// create container images
	img.img = mlx_new_image(mlx, 500, 500);

	// get data addr	
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,&img.endian);
	int i, j;
	int start = 500 / 2;
	int last = 500 / 2;
	i = 0;
	while(i < 500)
	{
		j = 0;
		while (j < 500)
		{
			if (j >= start && j <= last && start >= 0 && last < 500)
				ft_mlx_pixel_put(&img, j, i, 0x00FF00);
			else
				ft_mlx_pixel_put(&img, j, i, 0xFF0000);
			j++;
		}
		start -= 1;
		last += 1;
		i++;
	}

	mlx_put_image_to_window(mlx, new_win, img.img, 50, 50);
	mlx_loop(mlx);
	
	/* prototype mlx_clear_window(t_xvar *xvar, t_win_list *win)
	* 	return (int) ---> boolean maybe
	*	params 1: mlx from mlx_init();
	*	params 2: new_window  from mlx_new_window();
	*/
	return (0);
}
