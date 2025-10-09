#include "libso_long.h"

int	found_exit(char **map)
{
	int	i;
	int	j;

	if (!map || !*map)
		return (1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
