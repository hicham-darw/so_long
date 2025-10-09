#include "libso_long.h"

static char    **flood_fill(char **map, int px, int py);
static void    depth_first_search(char **map, int px, int py);

int invalid_map(char **map, int px, int py)
{
    t_item  items;
    char    **tmp;
    int     i;
    int     j;

    if (!map || !*map)
        return (1);
    items.player = 0;
    items.collectible = 0;
    items.exit = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
                items.player++;
            else if (map[i][j] == 'E')
                items.exit++;
            else if (map[i][j] == 'C')
                items.collectible++;
            j++;
        }
        i++;
    }
    if (items.player != 1 || items.exit != 1 || items.collectible < 1)
        return (1);
    tmp = flood_fill(map, px, py);
    if (!tmp)
        return (1);
    if (found_collectibles(tmp) || found_exit(tmp))
    {
        i = 0;
        while (tmp[i])
            free(tmp[i++]);
        free(tmp);
        return (1);
    }
    i = 0;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
    return (0);
}

static char    **flood_fill(char **map, int px, int py)
{
    char **tmp;
    int     i;

    if (!map || !*map)
        return (NULL);
    tmp = (char **)malloc(sizeof(char *) * ft_veclen(map) + 1);
    if (!tmp)
        return (NULL);
    i = 0;
    while (map[i])
    {
        tmp[i] = ft_strdup(map[i]);
        if (!tmp[i])
        {
            while (i > 0)
                free(tmp[--i]);
            free(tmp);
            return (NULL);
        }
        i++;
    }
    tmp[i] = NULL;
    depth_first_search(tmp, px, py);
    return (tmp);
}

static void    depth_first_search(char **map, int px, int py)
{
    if (!map || !*map)
        return ;
    if (px < 0 || px >= (int)ft_strlen(map[0]) || py < 0 || py >= (int)ft_veclen(map) || map[py][px] == '1' || map[py][px] == 'X')
        return ;
    map[py][px] = 'X';
    depth_first_search(map, px + 1, py);
    depth_first_search(map, px - 1, py);
    depth_first_search(map, px, py + 1);
    depth_first_search(map, px, py - 1);
}