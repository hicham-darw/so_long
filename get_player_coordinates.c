#include "libso_long.h"


int     get_player_coordinates(char **map, int *player_x, int *player_y)
{
    int     i;
    int     j;

    if (!map || !*map)
        return (0);
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[j])
        {
            if (map[i][j] == 'P')
            {
                *player_x = j;
                *player_y = i;
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}