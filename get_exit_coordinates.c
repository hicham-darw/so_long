#include "libso_long.h"

int	get_exit_coordinates(char **map, int *exit_x, int *exit_y)
{
	int	i;
	int	j;

	if (!map || !*map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				*exit_x = j;
				*exit_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
