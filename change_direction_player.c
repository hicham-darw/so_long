#include "libso_long.h"

char    *ft_strrev_line(char *data, unsigned int start, unsigned int last)
{
    char    tmp;

    if (!data || start >= last)
        return (NULL);
    while (data[start] && start < last)
    {
        tmp = data[start];
        data[start] = data[last - 1];
        data[last - 1] = tmp;
        start++;
        last--;
    }
    return (data);
}

void    change_direction_player(t_allvars *vars)
{
    int    i;
    int    j;
    char    *left_pixel, *right_pixel;
    unsigned int tmp_color;

    if (!vars || !vars->data_img[4].addr)
        return;
    i = 0;
    while (i < (vars->data_img[4].xpm_height))
    {
        j = 0;
        while (j < (vars->data_img[4].xpm_width) / 2)
        {
			left_pixel = vars->data_img[4].addr + (i * vars->data_img[4].line_length) + (j * (vars->data_img[4].bpp / 8));
            right_pixel = vars->data_img[4].addr + (i * vars->data_img[4].line_length) + ((vars->data_img[4].xpm_width - 1 - j) * (vars->data_img[4].bpp / 8));
            if (!right_pixel)
            {
                printf("Error: right os null\n");
                exit(1);
            }
            printf("R.line_length: %d\n", vars->data_img[4].line_length);
            printf("R.bpp        : %d\n", vars->data_img[4].bpp);
            printf("R.xpm width  : %d\n", vars->data_img[4].xpm_width);

            printf("left color: %u\n",*(unsigned int *)left_pixel);
            printf("right color: %u\n",*(unsigned int *)right_pixel);
            tmp_color = *(unsigned int *)right_pixel;
            *(unsigned int *)right_pixel = *(unsigned int *)left_pixel;
            *(unsigned int *)left_pixel = tmp_color;
            j += 1;
        }
        i += 1;
    }
}